#pragma once

#include <EGL/egl.h>
#include <GLES/gl.h>


class Draw
{
public:
	Draw();
	void DrawBox();

private:
	float angle_;
};