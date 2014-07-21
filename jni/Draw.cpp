#include "Draw.h"
#include "Png.h"
#include "include/glu.h"

#define LENGTH_A (15)

// 頂点リスト
static const GLfloat cubeVertices[] = {
 /*  X     Y     Z */
  -1.0f,-1.0f, 1.0f,   1.0f,-1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,   1.0f,-1.0f,-1.0f,
   1.0f, 1.0f,-1.0f,  -1.0f, 1.0f,-1.0f,
   1.0f,-1.0f, 1.0f,   1.0f,-1.0f,-1.0f,
   1.0f, 1.0f,-1.0f,   1.0f, 1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,  -1.0f,-1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f,-1.0f,
  -1.0f, 1.0f, 1.0f,   1.0f, 1.0f, 1.0f,
   1.0f, 1.0f,-1.0f,  -1.0f, 1.0f,-1.0f,
   1.0f,-1.0f, 1.0f,  -1.0f,-1.0f, 1.0f,
  -1.0f,-1.0f,-1.0f,   1.0f,-1.0f,-1.0f
};


// 頂点描画順
static const GLushort cubeIndices[] = {
   0, 1, 2,   2, 3, 0,
   5, 4, 7,   7, 6, 5,
   8, 9,10,  10,11, 8,
  12,13,14,  14,15,12,
  16,17,18,  18,19,16,
  20,21,22,  22,23,20 
};

// テクスチャ位置
const GLfloat cubeTexCoords[] = {
  0,0,1,0,1,1,0,1,
  0,0,1,0,1,1,0,1,
  0,0,1,0,1,1,0,1,
  0,0,1,0,1,1,0,1,
  0,0,1,0,1,1,0,1,
  0,0,1,0,1,1,0,1
};

GLuint texName[1];

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

void Draw::InitCube(AAssetManager* mgr)
{
 // 法線ベクトル有効化
  glEnable(GL_NORMALIZE);
  // デプステスト有効化
  glEnable(GL_DEPTH_TEST);
  // 面の破棄処理有効化
  glEnable(GL_CULL_FACE);
  // 背面を破棄する
  glCullFace(GL_BACK);
  // 陰影モード設定
  glShadeModel(GL_SMOOTH);
  // 利用するテクスチャは非圧縮とする
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  // テクスチャ割当を生成
  glGenTextures(1, &texName[0]);

  /************  main.cと変わってる  *******/
  glBindTexture(GL_TEXTURE_2D, texName[0]);

  // テクスチャ表示設定
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

  png_uint_32 width,height;  
  GLint type;
  GLubyte *textureImage;

  //--
  // PNG画像をOpenGL|ESのテクスチャとしてロードする(AssetManager経由)
  // loadPngImage(,  "texture.png", &width, &height, &type, &textureImage);
  //--
  Png::LoadPngImage(mgr, "texture.png", &width, &height, &type, &textureImage);

  // テクスチャーデータを割り当てる
  glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, textureImage);
}

void Draw::DrawCube()
{
  // カメラの位置、向きを指定
  gluLookAt(0,0,10, 0,0,-100,0,1,0);
  // 回転
  glRotatef(angle_, 1.0f, 0, 0.5f);
  // 頂点リスト指定
  glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
  // 頂点リストの有効化
  glEnableClientState(GL_VERTEX_ARRAY);
  
  // テクスチャの指定
  glEnable(GL_TEXTURE_2D);                              
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);           
  glTexCoordPointer(2, GL_FLOAT, 0, cubeTexCoords);     

  // 立方体を描画
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, cubeIndices);
}
