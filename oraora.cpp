/*==============================================================================

     [Oraora.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ■Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//ヘッダー
////////////////////////////////////
#include "main.h"
#include "oraora.h"
#include "input.h"
#include <math.h>

#define OraoraMAX (1)				//弾の最大
//05/27 texture
#define Oraora_TEXTURENAMCUT "data/TEXTURE/oraora.png"

//////////////////////////////////
//プロトタイプ
/////////////////////////////////
HRESULT MakeVertexOraora(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////////
//グローバル
/////////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//頂点情報格納用配列
LPDIRECT3DTEXTURE9 g_pTextureOraora = NULL;	//テクスチャ－インタフェースへのポインター
//0603 頂点パッファ管理インターフェースポインタを宣言する
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferOraora = NULL;
//Oraora
ORAORA g_Oraora[OraoraMAX];

//連打txカウント
int g_Oraora_tx = 0;

////////////////////////////////
//初期化処理
////////////////////////////////
HRESULT InitOraora(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//エラー, テクスチャの読み込み
	if(FAILED(D3DXCreateTextureFromFile(pDevice,Oraora_TEXTURENAMCUT,&g_pTextureOraora)))
	{
		MessageBox(NULL,"dekinai","終了メッセージ",MB_YESNO | MB_DEFBUTTON1);
	}

	//頂点の作成処理
	if(FAILED(MakeVertexOraora(pDevice)))
	{
		return E_FAIL;
	}

	for(int i = 0; i < OraoraMAX ; i ++)
	{
		g_Oraora[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Oraora[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Oraora[i].nTypeOraora = 0;
		g_Oraora[i].fSpeed = 0;
		g_Oraora[i].nLife = 0;
		g_Oraora[i].bUse = false;

	}
	//連打txカウント
	g_Oraora_tx = 0;
	//セット
	SetOraora(150.0f, 100.0f, 200.0f, 300.0f, 0.0f);
	return S_OK;
}

//////////////////////////////////
//終了処理
//////////////////////////////////
void UninitOraora(void)
{
	for(int i = 0; i < OraoraMAX ; i ++)
	{
		g_Oraora[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Oraora[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Oraora[i].nTypeOraora = 0;
		g_Oraora[i].fSpeed = 0;
		g_Oraora[i].nLife = 0;
		g_Oraora[i].bUse = false;
	}

	if(g_pTextureOraora != NULL)
	{
		g_pTextureOraora->Release();			//テクスチャインターフェースの解放
		g_pTextureOraora = NULL;
	}

	if(g_pVtxBufferOraora != NULL)
	{
		g_pVtxBufferOraora->Release();			//メイクヴァーテックス
		g_pVtxBufferOraora = NULL;
	}
	//連打txカウント
	g_Oraora_tx = 0;
}

//////////////////////////////////
//更新処理
//////////////////////////////////
void UpdateOraora(void)
{

	VERTEX_2D* pVtx = NULL;

	for(int i = 0; i < OraoraMAX; i ++)
	{
		if(g_Oraora[i].bUse == true)
		{
			g_pVtxBufferOraora->Lock(0,0,(void**)&pVtx,0);
			
			pVtx += NUM_VERTEX * i;
			
			pVtx[0].pos = D3DXVECTOR3(g_Oraora[i].pos.x, g_Oraora[i].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Oraora[i].pos.x + g_Oraora[i].size.x, g_Oraora[i].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Oraora[i].pos.x, g_Oraora[i].pos.y + g_Oraora[i].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Oraora[i].pos.x + g_Oraora[i].size.x, g_Oraora[i].pos.y+ g_Oraora[i].size.y, 0.0f);
		
			//オラオラカウントが一定値
			if( g_Oraora_tx == 0)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.142f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.142f,1.0f);
			}
			//オラオラカウントが一定値
			if( g_Oraora_tx == 1)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.142f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.284f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.142f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.284f,1.0f);
			}
			//オラオラカウントが一定値
			if( g_Oraora_tx == 2)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.284f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.426f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.284f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.426f,1.0f);
			}
			//オラオラカウントが一定値
			if( g_Oraora_tx == 3)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.426f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.568f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.426f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.568f,1.0f);
			}
			//オラオラカウントが一定値
			if( g_Oraora_tx == 4)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.568f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.710f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.568f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.710f,1.0f);
			}
			//オラオラカウントが一定値
			if( g_Oraora_tx == 5)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.710f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.852f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.710f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.852f,1.0f);
			}
			//オラオラカウントが一定値
			if( g_Oraora_tx == 6)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.852f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.852f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);
			}
			//アンロック
 			g_pVtxBufferOraora->Unlock();
		}
		if(g_Oraora_tx > 6)
		{
			//カウントリセット
			g_Oraora_tx = 0;
		}
	}
	// プレイヤーのキー判定 /////////////////////
	if( ( GetKeyboardTrigger( DIK_SPACE ) ))
	{
		//カウント
		g_Oraora_tx += 1;
	}
}

//////////////////////////////////
//描画処理
//////////////////////////////////
void DrawOraora(void)
{
	int j = 0;
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//0607 パイプライン
	pDevice->SetStreamSource(0,g_pVtxBufferOraora,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);
	//05/27
	pDevice->SetTexture(0,g_pTextureOraora);		//テクスチャの設定

	//プリミティブの描画
//	g_pD3Device->DrawPrimitiveUP(		D3DPT_TRIANGLELIST,NUM_Oraora,&g_aVertex[0],sizeof(VERTEX_2D));
	//プリミティブの種類   //プリミティブの数   //頂点データの先頭アドレス   //頂点データ１こ分のサイズ
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_Oraora,&g_aVertex[0],sizeof(VERTEX_2D));
	//0607
	for(int i = 0; i < OraoraMAX * 4; i += 4 , j++)
	{
		if(g_Oraora[j].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
											i,	//オフセット（頂点数）
											NUM_POLYGON);//プリミティブ数
		}
	}
}

//////////////////////////////////
//頂点の作成
//////////////////////////////////
HRESULT MakeVertexOraora(LPDIRECT3DDEVICE9 pDevice)  //void変える
{
	//0603 頂点バッファ
	//宿題エラーチェックしろreturn E_FALL   hresult型
	if(FAILED(	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * OraoraMAX,		//作成したい頂点バッファのサイズ（１頂点サイズ＊頂点数
								D3DUSAGE_WRITEONLY,					//使用法　（書き込みのみ
								FVF_VERTEX_2D,						//頂点フォーマット
								D3DPOOL_MANAGED,					//メモリ管理方法（デバイスにおまかせ
								&g_pVtxBufferOraora,				//								宿題あとかたずけしろ！！
								NULL)))
	{
		return E_FAIL;
	}
	//エラーじゃなかったら
	VERTEX_2D* pVtx;			//仮想アドレス用のポインタ

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferOraora->Lock(0,0,(void**)&pVtx,0);

	for(int i = 0; i < OraoraMAX; i++)
	{
		//頂点座標の設定(2D座標 右回り)
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f , 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f , 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f , 0.0f , 0.0f);
	
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
		pVtx[1].tex = D3DXVECTOR2(0.25f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f,1.0f);

		pVtx += NUM_VERTEX;
	}
	//頂点バッファをアンロック
	g_pVtxBufferOraora->Unlock();

	return S_OK;
}

//******************************************************************************
// 設定処理関数
//******************************************************************************
void SetOraora(float x, float y, float w, float h, float fSpeed)
{
	int nCuntOraora;

	for(nCuntOraora = 0; nCuntOraora < OraoraMAX; nCuntOraora ++)
	{
		if(g_Oraora[nCuntOraora].bUse == false)
		{
			g_Oraora[nCuntOraora].pos = D3DXVECTOR3(x,y,0.0f);
			g_Oraora[nCuntOraora].size = D3DXVECTOR2(w,h);
			g_Oraora[nCuntOraora].fSpeed = fSpeed;
			g_Oraora[nCuntOraora].nLife = 10;
			g_Oraora[nCuntOraora].bUse = true;
			break;
		}
	}
}
//******************************************************************************
// 弾情報取得関数
//******************************************************************************
ORAORA *GetOraora(void)
{
	return &g_Oraora[0];
}