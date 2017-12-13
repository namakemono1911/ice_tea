/*********************************************************************************************

bg
													Autor
													日時
**********************************************************************************************

更新

*********************************************************************************************/

////////////////////////////////////
//ヘッダー
////////////////////////////////////
#include "main.h"
#include "bg.h"

#define BG_POSX (0.0f)		//ポリゴンの表示位置X
#define BG_POSY (0.0f)		//ポリゴンの表示位置Y
#define BG_WIDTH (SCREEN_WIDTH)		//ポリゴンの幅
#define BG_HEIGHT (SCREEN_HEIGHT)	//ポリゴンの高さ

//05/27 texture
#define BG_TEXTURENAM "data/TEXTURE/bg01.png"

//////////////////////////////////
//プロト
void MakeVertexBG(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////
//グローバル
////////////////////////////
//05/24
//VERTEX_2D g_aVertex [NUM_VERTEX];				//頂点情報格納用配列
//05/27
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL;	//テクスチャ－インタフェースへのポインター

//0603 頂点パッファ管理インターフェースポインタを宣言する
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBG = NULL;

///////////////////////////
//初期化処理
//////////////////////////////////
void InitBG(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//ポリゴン
	//エラー, テクスチャの読み込み
	if(FAILED(D3DXCreateTextureFromFile(pDevice,BG_TEXTURENAM,&g_pTextureBG)))
	{
		MessageBox(NULL,"dekinai","終了メッセージ",MB_YESNO | MB_DEFBUTTON1);
	}

	//頂点の作成処理
	MakeVertexBG(pDevice);
}

//////////////////////////////////
//終了処理
//////////////////////////////////
void UninitBG(void)
{
	if(g_pTextureBG != NULL)
	{
		g_pTextureBG->Release();			//テクスチャインターフェースの解放
		g_pTextureBG = NULL;
	}

	if(g_pVtxBufferBG != NULL)
	{
		g_pVtxBufferBG->Release();			//メイクヴァーテックス
		g_pVtxBufferBG = NULL;
	}

}

//////////////////////////////////
//更新処理
//////////////////////////////////
void UpdateBG(void)
{

}

//////////////////////////////////
//描画処理
//////////////////////////////////
void DrawBG(void)
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//0607 パイプライン
	pDevice->SetStreamSource(0,g_pVtxBufferBG,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);
	//05/27
	pDevice->SetTexture(0,g_pTextureBG);		//テクスチャの設定

	//プリミティブの描画
//	g_pD3Device->DrawPrimitiveUP(		D3DPT_TRIANGLELIST,NUM_BG,&g_aVertex[0],sizeof(VERTEX_2D));
	//プリミティブの種類   //プリミティブの数   //頂点データの先頭アドレス   //頂点データ１こ分のサイズ
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_BG,&g_aVertex[0],sizeof(VERTEX_2D));

	//0607
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
											0,	//オフセット（頂点数）
											NUM_POLYGON);//プリミティブ数
}

//////////////////////////////////
//頂点の作成
//////////////////////////////////
void MakeVertexBG(LPDIRECT3DDEVICE9 pDevice)  //void変える
{
	//0603 頂点バッファ
	//宿題エラーチェックしろreturn E_FALL   hresult型
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,		//作成したい頂点バッファのサイズ（１頂点サイズ＊頂点数
								D3DUSAGE_WRITEONLY,					//使用法　（書き込みのみ
								FVF_VERTEX_2D,						//頂点フォーマット
								D3DPOOL_MANAGED,					//メモリ管理方法（デバイスにおまかせ
								&g_pVtxBufferBG,				//								宿題あとかたずけしろ！！
								NULL);

	//エラーチェック

	//エラーじゃなかったら
	VERTEX_2D* pVtx;			//仮想アドレス用のポインタ

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferBG->Lock(0,0,(void**)&pVtx,0);

	//頂点座標の設定(2D座標 右回り)
	pVtx[0].pos = D3DXVECTOR3(BG_POSX, BG_POSY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_POSX +BG_WIDTH, BG_POSY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POSX, BG_POSY +BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_POSX +BG_WIDTH, BG_POSY +BG_HEIGHT, 0.0f);

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
	g_pVtxBufferBG->Unlock();
}