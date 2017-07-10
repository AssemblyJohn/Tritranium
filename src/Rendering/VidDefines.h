#ifndef __TRITRANIUM_VID_DEFINES__
#define __TRITRANIUM_VID_DEFINES__

#include "Platform\Platform.h"

BEGIN_TRITRANIUM

enum EShaderType
{
	ST_VERTEX,
	ST_FRAGMENT,
	ST_GEOMETRY,
};

enum EDrawMode
{
	DM_POINTS,
	DM_LINES,
	DM_TRIANGLES,
	DM_TRIANGLE_STRIP,
};

enum EBufferType
{
	BT_ARRAY_BUFFER,
	BT_ELEMENT_BUFFER
};

enum EBufferUsage
{
	BU_STREAM_DRAW,
	BU_STATIC_DRAW,
	BU_DYNAMIC_DRAW,
};

enum ETextureBinding
{
	TB_TEXTURE_2D,
	TB_TEXTURE_CUBE,
};

// TODO: see for DX, might not be necesarry
enum EActiveTexture
{
	AT_TEXTURE_0 = 0,
	AT_TEXTURE_1 = 1,
	AT_TEXTURE_2 = 2,
	AT_TEXTURE_3 = 3,
	AT_TEXTURE_4 = 4,
	AT_TEXTURE_5 = 5,
};

enum EBlendFunc
{
	BF_ZERO,
	BF_ONE,
	BF_SRC_ALPHA,
	BF_ONE_MINUS_SRC_ALPHA,
	BF_ONE_MINUS_DST_ALPHA,
	BF_SRC_COLOR,
	BF_DST_COLOR,
	BF_ONE_MINUS_SRC_COLOR,
	BF_ONE_MINUS_DST_COLOR,
	BF_CONSTANT_COLOR,
};

enum EVecType
{
	VT_BYTE,
	VT_SHORT,
	VT_INT,
	VT_FLOAT,
	VT_DOUBLE
};

enum EClearMode
{
	CM_DEPTH,
	CM_COLOR,
	CM_COLOR_DEPTH
};

enum EVidShaderParamType
{
	// Primitives
	PT_FLOAT,
	PT_INT,

	// Vector
	PT_VEC2F,
	PT_VEC3F,
	PT_VEC4F,

	// Matrix
	PT_MAT2x2F,
	PT_MAT3x3F,
	PT_MAT4x4F,

	// Texture
	PT_TEXTURE_2D,
	PT_TEXTURE_CUBE,
};

enum EVidShaderBindingType
{
	SBT_ATTRIBUTE,
	SBT_UNIFORM,
};

enum EVidTextureFilter
{
	TF_POINT,
	TF_BILINEAR,
	TF_TRILINEAR,
};

enum EVidTextureWrap
{
	TW_CLAMP,
	TW_MIRROR,
};

enum EVidPixelType
{
	// 4 components 4 bytes each
	PT_R8G8B8A8,
	// 3 components 4 bytes each
	PT_R8G8B8,
	// 4 components 32 bytes each. See for HDR
	PT_FLOAT_RGBA,
	// 3 components 32 bytes each. See for HDR
	PT_FLOAT_RGB,
};

// Some default matrix uniforms

#define VID_UNI_MTX_MODEL TXT("uni_model")
#define VID_UNI_MTX_VIEW TXT("uni_view")
#define VID_UNI_MTX_PROJECTION TXT("uni_proj")
#define VID_UNI_MTX_MV TXT("uni_mv")
#define VID_UNI_MTX_MVP TXT("uni_mvp")

#define VID_UNI_TEX_DIFFUSE TXT("tex_diff")

// Some default attribute uniforms
#define VID_ATTR_VERTEX TXT("attr_vertex")
#define VID_ATTR_UV0 TXT("attr_uv0")
#define VID_ATTR_NORMAL TXT("attr_normal")
#define VID_ATTR_TANGENT TXT("attr_tangent")

#define VID_COMPONENTS_PER_VERTEX 3
#define VID_COMPONENTS_PER_UV 2

#define VID_STRIDE_PER_VERTEX 12
#define VID_STRIDE_PER_UV 8

END_TRITRANIUM

#endif