/*==============================================================================

     [fade.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ■Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//ヘッダー
////////////////////////////////////
#include "main.h"
#include "fade.h"
#include "input.h"
#include <math.h>

#define Fade_POSX (450.0f)		//ポリゴンの表示位置X
#define Fade_POSY (180.0f)		//ポリゴンの表示位置Y
#define Fade_WIDTH (200.0f)		//ポリゴンの幅
#define Fade_HEIGHT (200.0f)	//ポリゴンの高さ

//05/27 texture
#define Fade_TEXTURENAM "data/TEXTURE/akira001.png"

#define FADE_RATE (0.2f);

//////////////////////////////////
//プロトタイプ
/////////////////////////////////
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);
void SetColorFade(D3DXCOLOR color);

/////////////////////////////
//グローバル
////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//頂点情報格納用配列
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;	//テクスチャ－インタフェースへのポインター
//0603 頂点パッファ管理インターフェースポインタを宣言する
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferFade = NULL;

//フェード
D3DXCOLOR g_colorFade;
FADE g_fade = FADE_IN;
MODE g_modeNext = MODE_TITLE;

///////////////////////////
//初期化処理
//////////////////////////////////
HRESULT InitFade(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//ポリゴン
	//エラー, テクスチャの読み込み
	if(FAILED(D3DXCreateTextureFromFile(pDevice,Fade_TEXTURENAM,&g_pTextureFade)))
	{
		MessageBox(NULL,"dekinai","終了メッセージ",MB_YESNO | MB_DEFBUTTON1);
	}
	//頂点の作成処理
	if(FAILED(MakeVertexFade(pDevice)))
	{
		return E_FAIL;
	}

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_fade = FADE_IN;

	return S_OK;
}

//////////////////////////////////
//終了処理
//////////////////////////////////
void UninitFade(void)
{
	if(g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();			//テクスチャインターフェースの解放
		g_pTextureFade = NULL;
	}

	if(g_pVtxBufferFade != NULL)
	{
		g_pVtxBufferFade->Release();		//メイクヴァーテックス
		g_pVtxBufferFade = NULL;
	}
}

//////////////////////////////////
//更新処理
//////////////////////////////////
void UpdateFade(void)
{
	VERTEX_2D* pVtx = NULL;

	g_pVtxBufferFade->Lock(0,0,(void**)&pVtx,0);

	if(g_fade == FADE_NONE)
	{
		return;
	}
	if(g_fade == FADE_IN)
	{
		g_colorFade.a -= FADE_RATE;	//a値を減算して後ろの画面を浮き上がらせる
		if(g_colorFade.a <= 0.0f)
		{
			g_colorFade.a = 0.0f;
			g_fade = FADE_NONE;
		}
	}
	else if(g_fade == FADE_OUT)
	{
		g_colorFade.a += FADE_RATE;
		if(g_colorFade.a >= 1.0f)
		{
			g_colorFade.a = 1.0f;
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
	}
	SetColorFade(g_colorFade);
	g_pVtxBufferFade->Unlock();
}

//////////////////////////////////
//描画処理
//////////////////////////////////
void DrawFade(void)
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//0607 パイプライン
	pDevice->SetStreamSource(0,g_pVtxBufferFade,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);
	//05/27
	pDevice->SetTexture(0,g_pTextureFade);		//テクスチャの設定

	//プリミティブの描画
//	g_pD3Device->DrawPrimitiveUP(		D3DPT_TRIANGLELIST,NUM_Fade,&g_aVertex[0],sizeof(VERTEX_2D));
	//プリミティブの種類   //プリミティブの数   //頂点データの先頭アドレス   //頂点データ１こ分のサイズ
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_Fade,&g_aVertex[0],sizeof(VERTEX_2D));

	//0607
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
											0,	//オフセット（頂点数）
											NUM_POLYGON);//プリミティブ数
}

//////////////////////////////////
//頂点の作成
//////////////////////////////////
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)  //void変える
{
	//0603 頂点バッファ
	//宿題エラーチェックしろreturn E_FALL   hresult型
	if(FAILED(	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,		//作成したい頂点バッファのサイズ（１頂点サイズ＊頂点数
								D3DUSAGE_WRITEONLY,					//使用法　（書き込みのみ
								FVF_VERTEX_2D,						//頂点フォーマット
								D3DPOOL_MANAGED,					//メモリ管理方法（デバイスにおまかせ
								&g_pVtxBufferFade,				//								宿題あとかたずけしろ！！
								NULL)))
	{
		return E_FAIL;
	}
	//エラーじゃなかったら
	VERTEX_2D* pVtx;			//仮想アドレス用のポインタ

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferFade->Lock(0,0,(void**)&pVtx,0);

	//頂点座標の設定(2D座標 右回り)
	pVtx[0].pos = D3DXVECTOR3(Fade_POSX, Fade_POSY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Fade_POSX +Fade_WIDTH, Fade_POSY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Fade_POSX, Fade_POSY +Fade_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Fade_POSX +Fade_WIDTH, Fade_POSY +Fade_HEIGHT, 0.0f);

	//rhwの設定（必ず 1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定 ( 0～255の整数値)
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//uv
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//頂点バッファをアンロック
	g_pVtxBufferFade->Unlock();

	return S_OK;
}

//////////////////////////////////
//セット
//////////////////////////////////
void SetFade(FADE fade, MODE modeNext)	//追加でカラー指定、テクスチャ指定、フェードスピード
{

}

//////////////////////////////////
//セットカラー
//////////////////////////////////
void SetColorFade(D3DXCOLOR color)
{

}

//////////////////////////////////
//
//////////////////////////////////
FADE GetFade(void)
{
	return g_fade;
}