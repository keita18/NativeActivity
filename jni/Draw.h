#pragma once

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/asset_manager.h>

class Draw
{
public:
	Draw();
	void DrawBox();

	void InitCube(AAssetManager* mgr);
	void DrawCube();

private:
	float angle_;
};