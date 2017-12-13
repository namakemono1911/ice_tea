//////////////////////////////
//ヘッダー
/////////////////////////////
#ifndef _MAIN_H_

#define _MAIN_H_

#include <Windows.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <stdio.h>
#include <string.h>

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")		//システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")

//ウィンドウサイズ
#define SCREEN_WIDTH (800)					//ウィンド幅
#define SCREEN_HEIGHT (600)					//ウィンド高さ

#define NUM_VERTEX (4)		//頂点数
#define NUM_POLYGON (2)		//ポリゴン数

//ポリゴンの
//頂点フォーマット
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//座標変換済み頂点座標 | 頂点カラー

//頂点情報構造体(上の頂点フォーマットと合わせて)
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR color;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//画面遷移
typedef enum
{
	MODE_TITLE,
	MODE_SELECT,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX,
}MODE;

//ダイレクト３Dデバイスの取得
LPDIRECT3DDEVICE9 GetDevice(void);
//画面遷移
void SetMode(MODE mode);
MODE GetMode(void);
#endif