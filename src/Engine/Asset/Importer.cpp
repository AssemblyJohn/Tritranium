/** Copyright (c) 2016 Lazu Ioan-Bogdan */

#include "Importer.h"

#include <png.h>
#include <vector>

using namespace ::std;

#define VERTEX_		"v"
#define NORMAL_		"vn"
#define TEXTURE_UV_	"vt"
#define OBJECT_		"o"
#define TRIANGLE_	"f"
#define COMMENT_	"#"

#define TYPE_UNKNOWN	0x000000
#define TYPE_VERTEX		0x000001
#define TYPE_TEXTURE	0x000002
#define TYPE_OBJECT		0x000003
#define TYPE_FACE		0x000004
#define TYPE_COMMENT	0x000005
#define TYPE_NORMAL		0x000006

BEGIN_TRITRANIUM

typedef struct
{
	int i1, i2, i3;
	int n1, n2, n3;
	int u1, u2, u3;
} PTri;

typedef struct
{
	const unsigned char * data;
	uint32 size;
	int offset;
} tImageSource;

static void pngReadCallback(png_structp png_ptr, png_bytep data, png_size_t length)
{
	tImageSource* isource = (tImageSource*)png_get_io_ptr(png_ptr);

	if ((int)(isource->offset + length) <= isource->size)
	{
		PMemory::Memcpy(data, isource->data + isource->offset, length);
		isource->offset += length;
	}
	else
	{
		png_error(png_ptr, "pngReaderCallback failed");
	}
}

/*
void premultipliedAlpha()
{
	// CCASSERT(_renderFormat == Texture2D::PixelFormat::RGBA8888, "The pixel format should be RGBA8888!");

	unsigned int* fourBytes = (unsigned int*)_data;
	for (int i = 0; i < _width * _height; i++)
	{
		unsigned char* p = _data + i * 4;
		fourBytes[i] = CC_RGB_PREMULTIPLY_ALPHA(p[0], p[1], p[2], p[3]);
	}

	_hasPremultipliedAlpha = true;
}
*/

bool PImporter::ParseTexture(const PString &path, PTextureImportedData &data)
{
	// length of bytes to check if it is a valid png file
#define PNGSIGSIZE  8
	bool ret = false;
	png_byte        header[PNGSIGSIZE] = { 0 };
	png_structp     png_ptr = 0;
	png_infop       info_ptr = 0;

	// No need to worry about freeing this... Just see if we use the move or copy semantics
	PData image = PFileUtils::ReadEntireFileData(path);

	do
	{
		// check the data is png or not
		PMemory::Memcpy(header, image.GetBytes(), PNGSIGSIZE);

		if (png_sig_cmp(header, 0, PNGSIGSIZE)) 
			break;

		// init png_struct
		png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

		if(!png_ptr) 
			break;

		// init png_info
		info_ptr = png_create_info_struct(png_ptr);

		if(!info_ptr) 
			break;

		// set the read call back function
		tImageSource imageSource;
		imageSource.data = (unsigned char*)image.GetBytes();
		imageSource.size = image.GetByteSize();
		imageSource.offset = 0;
		png_set_read_fn(png_ptr, &imageSource, pngReadCallback);

		// read png header info

		// read png file info
		png_read_info(png_ptr, info_ptr);

		data.mWidth = png_get_image_width(png_ptr, info_ptr);
		data.mHeight = png_get_image_height(png_ptr, info_ptr);
		png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		png_uint_32 color_type = png_get_color_type(png_ptr, info_ptr);

		//CCLOG("color type %u", color_type);

		// force palette images to be expanded to 24-bit RGB
		// it may include alpha channel
		if (color_type == PNG_COLOR_TYPE_PALETTE)
		{
			png_set_palette_to_rgb(png_ptr);
		}
		// low-bit-depth grayscale images are to be expanded to 8 bits
		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		{
			bit_depth = 8;
			png_set_expand_gray_1_2_4_to_8(png_ptr);
		}
		// expand any tRNS chunk data into a full alpha channel
		if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		{
			png_set_tRNS_to_alpha(png_ptr);
		}
		// reduce images with 16-bit samples to 8 bits
		if (bit_depth == 16)
		{
			png_set_strip_16(png_ptr);
		}

		// Expanded earlier for grayscale, now take care of palette and rgb
		if (bit_depth < 8)
		{
			png_set_packing(png_ptr);
		}
		// update info
		png_read_update_info(png_ptr, info_ptr);
		bit_depth = png_get_bit_depth(png_ptr, info_ptr);
		color_type = png_get_color_type(png_ptr, info_ptr);

		switch (color_type)
		{
		case PNG_COLOR_TYPE_GRAY:
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			CHK(0);
			break;
		case PNG_COLOR_TYPE_RGB:
			data.mType = EVidPixelType::PT_R8G8B8;
			break;
		case PNG_COLOR_TYPE_RGB_ALPHA:
			data.mType = EVidPixelType::PT_R8G8B8A8;
			break;
		default:
			break;
		}

		// read png data
		png_size_t rowbytes;
		png_bytep* row_pointers = (png_bytep*)PMemory::Malloc(sizeof(png_bytep) * data.mHeight);

		rowbytes = png_get_rowbytes(png_ptr, info_ptr);

		uint32 len = (rowbytes * data.mHeight);
		uint8 *bytes = (uint8 *)PMemory::Malloc(len);

		if (!bytes)
		{
			if (row_pointers != nullptr)
			{
				PMemory::Free(row_pointers);
			}
			break;
		}

		data.mData.Assign(bytes, len);

		for (uint16 i = 0; i < data.mHeight; ++i)
		{
			row_pointers[i] = data.mData.GetBytes() + i*rowbytes;
		}
		png_read_image(png_ptr, row_pointers);
		
		png_read_end(png_ptr, nullptr);

		// premultiplied alpha for RGBA8888
		if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		{
			// TODO: we might need to premultiply
			// premultipliedAlpha();
		}
		else
		{
			// _hasPremultipliedAlpha = false;
		}

		if (row_pointers != nullptr)
		{
			PMemory::Free(row_pointers);
		}

		ret = true;
	} while (0);

	if (png_ptr)
	{
		png_destroy_read_struct(&png_ptr, (info_ptr) ? &info_ptr : 0, 0);
	}

	return ret;
}

int HeaderType(char* c);
char *ExtractObjName(char *name);
void AddVertex(char *buff, vector<PVec3> &vect);
void AddUv(char *buff, vector<PVec2> &vect);
void AddTriangle(char *buff, vector<PTri> &vect);

void PImporter::ParseObjFile(const PString &path, PMeshImportedData &data)
{	
	FILE *file = fopen(path.c_str(), "r");

	CHK(file != NULL);

	vector<PVec3> vertices;
	vector<PVec3> normals;
	vector<PVec2>  textures;

	// Will pack based on this
	vector<PTri>  faces;
	
	char buff[100];
	char parseBuff[100];

	char *header;
	int header_code;
	
	// TODO: read bigger chunks
	while(fgets(buff, 100, file))
	{
		strcpy(parseBuff, buff);
		header = strtok(buff, " ");

		header_code = HeaderType(header);
		switch(header_code)
		{
		case TYPE_UNKNOWN:
			continue;
		case TYPE_COMMENT:
			continue;
		case TYPE_OBJECT:
			data.name = ExtractObjName(parseBuff);
			break;
		case TYPE_VERTEX:
			AddVertex(parseBuff, vertices);
			break;
		case TYPE_NORMAL:
			AddVertex(parseBuff, normals);
			break;
		case TYPE_TEXTURE:
			AddUv(parseBuff, textures);
			break;
		case TYPE_FACE:
			AddTriangle(parseBuff, faces);
			break;
		}
	}

	fclose(file);
	
	// Pack everything
	for (size_t i = 0; i < faces.size(); i++)
	{
		PTri &tri = faces[i];

		data.vertex.Add(vertices[tri.i1]);
		data.vertex.Add(vertices[tri.i2]);
		data.vertex.Add(vertices[tri.i3]);
		
		data.normal.Add(normals[tri.n1]);
		data.normal.Add(normals[tri.n2]);
		data.normal.Add(normals[tri.n3]);
		
		data.uv.Add(textures[tri.u1]);
		data.uv.Add(textures[tri.u2]);
		data.uv.Add(textures[tri.u3]);
	}	
}

int HeaderType(char* c)
{
	int code = 0;

	if (strcmp(c, VERTEX_) == 0)
		code = TYPE_VERTEX;
	else if (strcmp(c, NORMAL_) == 0)
		code = TYPE_NORMAL;
	else if(strcmp(c, TEXTURE_UV_) == 0)
		code = TYPE_TEXTURE;
	else if(strcmp(c, OBJECT_) == 0)
		code = TYPE_OBJECT;
	else if(strcmp(c, TRIANGLE_) == 0)
		code = TYPE_FACE;
	else if(strcmp(c, COMMENT_) == 0)
		code = TYPE_COMMENT;
	else
		code = TYPE_UNKNOWN;

	return code;
}

char *ExtractObjName(char *name)
{
	// Skip header
	strtok(name, " ");
	return strtok(NULL, " ");
}

void AddVertex(char *buff, vector<PVec3> &vect)
{
	// Skipp header
	strtok(buff, " ");

	PVec3 tmp;

	tmp.x = (float)atof(strtok(NULL, " "));
	tmp.y = (float)atof(strtok(NULL, " "));
	tmp.z = (float)atof(strtok(NULL, " "));

	vect.push_back(tmp);
}

void AddUv(char *buff, vector<PVec2> &vect)
{
	// Skip header
	strtok(buff, " ");

	PVec2 tmp;

	tmp.x = (float)atof(strtok(NULL, " "));
	tmp.y = (float)atof(strtok(NULL, " "));

	vect.push_back(tmp);
}

void AddTriangle(char *buff, vector<PTri> &vect)
{
	// Skip header
	strtok(buff, " ");

	PTri tmp;

	// vertex 1
	tmp.i1 = atoi(strtok(NULL, " /"));
	// texture 1
	tmp.u1 = atoi(strtok(NULL, " /"));
	// normal 1
	tmp.n1 = atoi(strtok(NULL, " /"));

	// vertex 2
	tmp.i2 = atoi(strtok(NULL, " /"));
	// texture 2
	tmp.u2 = atoi(strtok(NULL, " /"));
	// normal 2
	tmp.n2 = atoi(strtok(NULL, " /"));

	// vertex 3
	tmp.i3 = atoi(strtok(NULL, " /"));
	// texture 3
	tmp.u3 = atoi(strtok(NULL, " /"));
	// normal 3
	tmp.n3 = atoi(strtok(NULL, " /"));
	
	// Dec eveything by one
	tmp.i1 -= 1;
	tmp.i2 -= 1;
	tmp.i3 -= 1;

	tmp.n1 -= 1;
	tmp.n2 -= 1;
	tmp.n3 -= 1;

	tmp.u1 -= 1;
	tmp.u2 -= 1;
	tmp.u3 -= 1;

	vect.push_back(tmp);
}

END_TRITRANIUM