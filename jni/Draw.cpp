#include "Draw.h"

#define LENGTH_A (15)

Draw::Draw()
: angle_(0.0f)
{

}

void Draw::DrawBox()
{
	short triangleBufferA[] = {
	    -LENGTH_A / 2,            -LENGTH_A / 2,            0,
	    LENGTH_A - LENGTH_A / 2,    -LENGTH_A / 2,            0,
	    -LENGTH_A / 2,            LENGTH_A - LENGTH_A / 2,    0,
	    LENGTH_A -LENGTH_A / 2,    LENGTH_A - LENGTH_A / 2,    0,
	};

	float colorBufferA[] = {
	    1.0, 0.0, 0.0, 1.0,
	    0.0, 1.0, 0.0, 1.0,
	    0.0, 0.0, 1.0, 1.0,
	    0.5, 0.5, 0.0, 1.0,
	};

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -50.0);

	angle_ = (angle_ + 10);
	if ( angle_ > 360 )
	{
	    angle_ = 0;
	}

	//角度設定
	glRotatef(angle_, 0, 0, 1.0f);
	//バッファーをクリア
	glClear(GL_COLOR_BUFFER_BIT);
	//頂点リスト指定
	glVertexPointer(3, GL_SHORT, 0, triangleBufferA);
	//頂点リスト有効化
	glEnableClientState(GL_VERTEX_ARRAY);
	//頂点リスト指定
	glColorPointer(4, GL_FLOAT, 0, colorBufferA);
	//頂点カラーリストの有効化
	glEnableClientState(GL_COLOR_ARRAY);
	//三角形描画
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);

}