#pragma once

#include <jni.h>
#include <errno.h>
#include <android/asset_manager.h>
#include <android/log.h>
#include <GLES/gl.h>

#include <png.h>

class Png
{
public:
	Png();
	static bool LoadPngImage(
		AAssetManager* mgr, 
		const char* filename, 
		png_uint_32* outWidth, 
		png_uint_32* outHeight, 
		GLint *type, 
		u_char **outData);
	static void callbackRead(png_structp pPng, png_bytep buf, png_size_t size);

private:
	static int offset_;
};