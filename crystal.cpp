/*==============================================================================

     [Crystal.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ■Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//ヘッダー
////////////////////////////////////
#include "main.h"
#include "crystal.h"
#include "input.h"
#include "ton.h"
#include <math.h>

#define CrystalMAX (1)				//弾の最大
//05/27 texture
#define Crystal_TEXTURENAMCUT "data/TEXTURE/koorisenpai.png"

//////////////////////////////////
//プロトタイプ
/////////////////////////////////
HRESULT MakeVertexCrystal(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////////
//グローバル
/////////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//頂点情報格納用配列
LPDIRECT3DTEXTURE9 g_pTextureCrystal = NULL;	//テクスチャ－インタフェースへのポインター
//0603 頂点パッファ管理インターフェースポインタを宣言する
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferCrystal = NULL;
//crystal
CRYSTAL g_Crystal[CrystalMAX];
//連打カウント
int g_Crystal_tapCount = 0;
//ひび割れカウント
int g_Crystal_tapCount2 = 0;
//破壊フラグ
bool g_CrystalBreak = false;
//終了カウント
int g_Crystal_tapCount3 = 0;

////////////////////////////////
//初期化処理
////////////////////////////////
HRESULT InitCrystal(void)
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//エラー, テクスチャの読み込み
	if(FAILED(D3DXCreateTextureFromFile(pDevice,Crystal_TEXTURENAMCUT,&g_pTextureCrystal)))
	{
		MessageBox(NULL,"dekinai","終了メッセージ",MB_YESNO | MB_DEFBUTTON1);
	}

	//頂点の作成処理
	if(FAILED(MakeVertexCrystal(pDevice)))
	{
		return E_FAIL;
	}

	for(int i = 0; i < CrystalMAX ; i ++)
	{
		g_Crystal[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Crystal[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Crystal[i].nTypeCrystal = 0;
		g_Crystal[i].fSpeed = 0;
		g_Crystal[i].nLife = 0;
		g_Crystal[i].bUse = false;

	}
	//連打カウント
	g_Crystal_tapCount = 0;
	//ひび割れカウント
	g_Crystal_tapCount2 = 0;
	//破壊フラグ
	g_CrystalBreak = false;
	//終了カウント
	g_Crystal_tapCount3 = 0;
	//セット
	SetCrystal(270.0f, 30.0f, 230.0f, 300.0f, 0.0f);
	return S_OK;
}

//////////////////////////////////
//終了処理
//////////////////////////////////
void UninitCrystal(void)
{
	for(int i = 0; i < CrystalMAX ; i ++)
	{
		g_Crystal[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Crystal[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Crystal[i].nTypeCrystal = 0;
		g_Crystal[i].fSpeed = 0;
		g_Crystal[i].nLife = 0;
		g_Crystal[i].bUse = false;
	}

	if(g_pTextureCrystal != NULL)
	{
		g_pTextureCrystal->Release();			//テクスチャインターフェースの解放
		g_pTextureCrystal = NULL;
	}

	if(g_pVtxBufferCrystal != NULL)
	{
		g_pVtxBufferCrystal->Release();			//メイクヴァーテックス
		g_pVtxBufferCrystal = NULL;
	}
	//連打カウント
	g_Crystal_tapCount = 0;
	//ひび割れカウント
	g_Crystal_tapCount2 = 0;
	//破壊フラグ
	g_CrystalBreak = false;
	//終了カウント
	g_Crystal_tapCount3 = 0;
}

//////////////////////////////////
//更新処理
//////////////////////////////////
void UpdateCrystal(void)
{
	VERTEX_2D* pVtx = NULL;

	for(int i = 0; i < CrystalMAX; i ++)
	{
		if(g_Crystal[i].bUse == true)
		{
			g_pVtxBufferCrystal->Lock(0,0,(void**)&pVtx,0);
			
			pVtx += NUM_VERTEX * i;
			
			pVtx[0].pos = D3DXVECTOR3(g_Crystal[i].pos.x, g_Crystal[i].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Crystal[i].pos.x + g_Crystal[i].size.x, g_Crystal[i].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Crystal[i].pos.x, g_Crystal[i].pos.y + g_Crystal[i].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Crystal[i].pos.x + g_Crystal[i].size.x, g_Crystal[i].pos.y+ g_Crystal[i].size.y, 0.0f);
		
			//ひび割れカウントが一定値
			if( g_Crystal_tapCount2 == 10)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f,1.0f);
			}
			//ひび割れカウントが一定値
			if( g_Crystal_tapCount2 == 20)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.25f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f,1.0f);
			}
			//ひび割れカウントが一定値
			if( g_Crystal_tapCount2 == 30)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.5f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.75f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.75f,1.0f);
			}
			//ひび割れカウントが一定値
			if( g_Crystal_tapCount2 == 40)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.75f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.75f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);
			}
			//ひび割れカウントが一定値
			if( g_Crystal_tapCount2 == 50)
			{
				for(int i = 0; i < CrystalMAX ; i ++)
				{
					g_Crystal[i].bUse = false;
				}
			}
			//アンロック
 			g_pVtxBufferCrystal->Unlock();
		}
		if(g_Crystal_tapCount >= 5)
		{
			//カウントリセット
			g_Crystal_tapCount = 0;
			//欠片セット
			setTon	( D3DXVECTOR3(320.0f, 300.0f, 0.0f) );
			setTon	( D3DXVECTOR3 (460.0f, 250.0f, 0.0f));
			setTon	( D3DXVECTOR3 (430.0f, 320.0f, 0.0f) );

		//	SetBullet(150.0f, 300.0f, 50.0f, 50.0f, 0.0f);
			//欠片セット
		//	SetBullet(350.0f, 300.0f, 50.0f, 50.0f, 0.0f);
			//欠片セット
		//	SetBullet(450.0f, 300.0f, 50.0f, 50.0f, 0.0f);
		}
	}
	// プレイヤーのキー判定 /////////////////////
	if( ( GetKeyboardTrigger( DIK_SPACE ) ))
	{
		//カウント
		g_Crystal_tapCount2 += 1;
		g_Crystal_tapCount +=1;
	}
	//リザルトへ
	if( g_Crystal_tapCount2 == 50)
	{
		//破壊フラグ
		g_CrystalBreak = true;
	}
	if( g_CrystalBreak == true)
	{
		//終了カウント
		g_Crystal_tapCount3 += 1;
		if(g_Crystal_tapCount3 == 180)//3秒経過
		{
		
			SetMode(MODE_RESULT);
		}
	}
}

//////////////////////////////////
//描画処理
//////////////////////////////////
void DrawCrystal(void)
{
	int j = 0;
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//0607 パイプライン
	pDevice->SetStreamSource(0,g_pVtxBufferCrystal,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);
	//05/27
	pDevice->SetTexture(0,g_pTextureCrystal);		//テクスチャの設定

	//プリミティブの描画
//	g_pD3Device->DrawPrimitiveUP(		D3DPT_TRIANGLELIST,NUM_Crystal,&g_aVertex[0],sizeof(VERTEX_2D));
	//プリミティブの種類   //プリミティブの数   //頂点データの先頭アドレス   //頂点データ１こ分のサイズ
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_Crystal,&g_aVertex[0],sizeof(VERTEX_2D));
	//0607
	for(int i = 0; i < CrystalMAX * 4; i += 4 , j++)
	{
		if(g_Crystal[j].bUse == true)
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
HRESULT MakeVertexCrystal(LPDIRECT3DDEVICE9 pDevice)  //void変える
{
	//0603 頂点バッファ
	//宿題エラーチェックしろreturn E_FALL   hresult型
	if(FAILED(	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * CrystalMAX,		//作成したい頂点バッファのサイズ（１頂点サイズ＊頂点数
								D3DUSAGE_WRITEONLY,					//使用法　（書き込みのみ
								FVF_VERTEX_2D,						//頂点フォーマット
								D3DPOOL_MANAGED,					//メモリ管理方法（デバイスにおまかせ
								&g_pVtxBufferCrystal,				//								宿題あとかたずけしろ！！
								NULL)))
	{
		return E_FAIL;
	}
	//エラーじゃなかったら
	VERTEX_2D* pVtx;			//仮想アドレス用のポインタ

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferCrystal->Lock(0,0,(void**)&pVtx,0);

	for(int i = 0; i < CrystalMAX; i++)
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
	g_pVtxBufferCrystal->Unlock();

	return S_OK;
}

//******************************************************************************
// 設定処理関数
//******************************************************************************
void SetCrystal(float x, float y, float w, float h, float fSpeed)
{
	int nCuntCrystal;

	for(nCuntCrystal = 0; nCuntCrystal < CrystalMAX; nCuntCrystal ++)
	{
		if(g_Crystal[nCuntCrystal].bUse == false)
		{
			g_Crystal[nCuntCrystal].pos = D3DXVECTOR3(x,y,0.0f);
			g_Crystal[nCuntCrystal].size = D3DXVECTOR2(w,h);
			g_Crystal[nCuntCrystal].fSpeed = fSpeed;
			g_Crystal[nCuntCrystal].nLife = 10;
			g_Crystal[nCuntCrystal].bUse = true;
			break;
		}
	}
}
//******************************************************************************
// 弾情報取得関数
//******************************************************************************
CRYSTAL *GetCrystal(void)
{
	return &g_Crystal[0];
}