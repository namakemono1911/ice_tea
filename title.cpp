/*==============================================================================

     [title.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ■Update : 2016/6/28
  
==============================================================================*/


////////////////////////////////////
//ヘッダー
////////////////////////////////////
#include "bg.h"
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include <math.h>

#define TITLE_POSX (0.0f)			//ポリゴンの表示位置X
#define TITLE_POSY (0.0f)			//ポリゴンの表示位置Y
#define TITLE_WIDTH (800.0f)		//ポリゴンの幅
#define TITLE_HEIGHT (600.0f)		//ポリゴンの高さ

//05/27 texture
#define Title_TEXTURENAM "data/TEXTURE/title.png"

//////////////////////////////////
//プロトタイプ
/////////////////////////////////
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////
//グローバル
////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//頂点情報格納用配列

LPDIRECT3DTEXTURE9 g_pTextureTitle = NULL;	//テクスチャ－インタフェースへのポインター

//0603 頂点パッファ管理インターフェースポインタを宣言する
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTitle = NULL;

///////////////////////////
//初期化処理
//////////////////////////////////
HRESULT InitTitle(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//ポリゴン
	//エラー, テクスチャの読み込み
	if(FAILED(D3DXCreateTextureFromFile(pDevice,Title_TEXTURENAM,&g_pTextureTitle)))
	{
		MessageBox(NULL,"dekinai","終了メッセージ",MB_YESNO | MB_DEFBUTTON1);
	}
	//頂点の作成処理
	if(FAILED(MakeVertexTitle(pDevice)))
	{
		return E_FAIL;
	}
	InitBG();

	return S_OK;
}

//////////////////////////////////
//終了処理
//////////////////////////////////
void UninitTitle(void)
{
	if(g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();			//テクスチャインターフェースの解放
		g_pTextureTitle = NULL;
	}

	if(g_pVtxBufferTitle != NULL)
	{
		g_pVtxBufferTitle->Release();			//メイクヴァーテックス
		g_pVtxBufferTitle = NULL;
	}
	UninitBG();
}

//////////////////////////////////
//更新処理
//////////////////////////////////
void UpdateTitle(void)
{
	VERTEX_2D* pVtx = NULL;

	g_pVtxBufferTitle->Lock(0,0,(void**)&pVtx,0);

	g_pVtxBufferTitle->Unlock();

	if(GetKeyboardTrigger(DIK_SPACE))
	{
		
		SetMode(MODE_SELECT);
	}
	UpdateBG();
}

//////////////////////////////////
//描画処理
//////////////////////////////////
void DrawTitle(void)
{
	DrawBG();
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//0607 パイプライン
	pDevice->SetStreamSource(0,g_pVtxBufferTitle,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);
	//05/27
	pDevice->SetTexture(0,g_pTextureTitle);		//テクスチャの設定

	//プリミティブの描画
//	g_pD3Device->DrawPrimitiveUP(		D3DPT_TRIANGLELIST,NUM_Title,&g_aVertex[0],sizeof(VERTEX_2D));
	//プリミティブの種類   //プリミティブの数   //頂点データの先頭アドレス   //頂点データ１こ分のサイズ
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_Title,&g_aVertex[0],sizeof(VERTEX_2D));

	//0607
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
											0,	//オフセット（頂点数）
											NUM_POLYGON);//プリミティブ数
}

//////////////////////////////////
//頂点の作成
//////////////////////////////////
HRESULT MakeVertexTitle(LPDIRECT3DDEVICE9 pDevice)  //void変える
{
	//0603 頂点バッファ
	//宿題エラーチェックしろreturn E_FALL   hresult型
	if(FAILED(	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,		//作成したい頂点バッファのサイズ（１頂点サイズ＊頂点数
								D3DUSAGE_WRITEONLY,					//使用法　（書き込みのみ
								FVF_VERTEX_2D,						//頂点フォーマット
								D3DPOOL_MANAGED,					//メモリ管理方法（デバイスにおまかせ
								&g_pVtxBufferTitle,				//								宿題あとかたずけしろ！！
								NULL)))
	{
		return E_FAIL;
	}
	//エラーじゃなかったら
	VERTEX_2D* pVtx;			//仮想アドレス用のポインタ

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferTitle->Lock(0,0,(void**)&pVtx,0);

	//頂点座標の設定(2D座標 右回り)
	pVtx[0].pos = D3DXVECTOR3(TITLE_POSX, TITLE_POSY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_POSX +TITLE_WIDTH, TITLE_POSY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POSX, TITLE_POSY +TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_POSX +TITLE_WIDTH, TITLE_POSY +TITLE_HEIGHT, 0.0f);

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
	g_pVtxBufferTitle->Unlock();

	return S_OK;
}