/*==============================================================================

     [game.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ■Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//ヘッダー
////////////////////////////////////
#include "main.h"
#include "game.h"
#include "input.h"
#include "polygon.h"
#include "bg.h"
#include "input.h"
#include "fade.h"
#include "crystal.h"
#include "oraora.h"
#include <math.h>
#include "Icetea.h"
#include "ton.h"
#include "hit.h"

//////////////////////////////////
//プロトタイプ
/////////////////////////////////
HRESULT MakeVertexGame(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////
//グローバル
////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//頂点情報格納用配列

LPDIRECT3DTEXTURE9 g_pTextureGame = NULL;	//テクスチャ－インタフェースへのポインター

//0603 頂点パッファ管理インターフェースポインタを宣言する
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferGame = NULL;

//////////////////////////////////
//初期化処理
//////////////////////////////////
void InitGame(void)
{
	InitBG();
	InitIcetea();
	//ポリゴン
//	if(FAILED( InitPolygon() ))
//	{
//		MessageBox(NULL,"イニットポリゴン失敗","イニットポリゴン失敗",MB_OK);
	//	return E_FAIL;
//	}
//	if(FAILED( InitEnemy() ))
//	{
//		MessageBox(NULL,"イニットENEMY失敗","イニットENEMY失敗",MB_OK);
//		//return E_FAIL;
//	}
//	InitBullet();
	InitCrystal();
	InitOraora();
	initTon();
}

//////////////////////////////////
//終了処理
//////////////////////////////////
void UninitGame(void)
{
	UninitBG();
	//UninitPolygon();
//	UninitEnemy();
	//UninitBullet();
	UninitCrystal();
	UninitOraora();
	UninitIcetea();
	uninitTon();
}

//////////////////////////////////
//更新処理
//////////////////////////////////
void UpdateGame(void)
{
	UpdateBG();
	//UpdatePolygon();
//	UpdateEnemy();
	//UpdateBullet();
	UpdateOraora();
	UpdateIcetea();
	updateTon();
	UpdateCrystal();
}

//////////////////////////////////
//描画処理
//////////////////////////////////
void DrawGame(void)
{
	DrawBG();
	DrawCrystal();		//クリスタル
	//DrawPolygon();	//ポリゴン
//	DrawEnemy();		//敵
	//DrawBullet();		//弾
	drawTon();
	DrawOraora();		//オラオラ
	DrawIcetea();

}
