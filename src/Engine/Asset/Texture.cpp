/**
* Copyright (c) 2015 Lazu Ioan-Bogdan
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, without any restrictions.
*/

// #include "std.h"

#include "Texture.h"

/*
size_t enTexture::memused = 0;

enTexture::enTexture(SDL_Surface *texture)
{
	surf = texture;
}

size_t enTexture::Width()
{
	return surf->w;
}

size_t enTexture::Height()
{
	return surf->h;
}

size_t enTexture::MemoryUsed() const
{
	return (surf->format->BytesPerPixel * (surf->w * surf->h));
}

void *enTexture::ToPtr()
{
	return surf->pixels;
}

enTexture *enTexture::LoadTexture(const char *path)
{
	SDL_Surface *surface = IMG_Load(path);
	enTexture *tex = new enTexture(surface);

	enTexture::memused += sizeof(enTexture);
	enTexture::memused += tex->MemoryUsed();

	return tex;
}

void enTexture::Dealloc(enTexture *texture)
{
	enTexture::memused -= sizeof(enTexture);
	enTexture::memused -= texture->MemoryUsed();

	SDL_FreeSurface(texture->surf);
	delete texture;
}
*/