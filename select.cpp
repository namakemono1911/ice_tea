/*==============================================================================

     [Select.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ■Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//ヘッダー
////////////////////////////////////
#include "main.h"
#include "select.h"
#include "menubar.h"
#include "polygon.h"
#include "bg.h"
#include "input.h"
#include "fade.h"
#include <math.h>

//////////////////////////////////
//プロトタイプ
/////////////////////////////////
HRESULT MakeVertexSelect(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////
//グローバル
////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//頂点情報格納用配列

LPDIRECT3DTEXTURE9 g_pTextureSelect = NULL;	//テクスチャ－インタフェースへのポインター

//0603 頂点パッファ管理インターフェースポインタを宣言する
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferSelect = NULL;

//////////////////////////////////
//初期化処理
//////////////////////////////////
void InitSelect(void)
{
	InitBG();
	InitMenubar();
}

//////////////////////////////////
//終了処理
//////////////////////////////////
void UninitSelect(void)
{
	UninitBG();
	UninitMenubar();
}

//////////////////////////////////
//更新処理
//////////////////////////////////
void UpdateSelect(void)
{
	UpdateBG();
	UpdateMenubar();

	if(GetKeyboardTrigger(DIK_SPACE))
	{
		//PlaySound(SOUND_LABEL_BGM001);
		SetMode(MODE_GAME);
	}
}

//////////////////////////////////
//描画処理
//////////////////////////////////
void DrawSelect(void)
{
	DrawBG();
	DrawMenubar();
}
