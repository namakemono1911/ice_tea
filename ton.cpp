/*****************************************************************************
ton.cpp
Aythor	: 上野　匠
Data	: 2016_08_30
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "ton.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define TON_POS_X			(SCREEN_WIDTH * 0.5f)	//ポリゴンの表示位置X
#define TON_POS_Y			(SCREEN_HEIGHT * 0.5f)	//ポリゴンの表示位置Y

#define TON_WIDTH			(30)					//ポリゴンの幅
#define TON_HEIGHT			(30)					//ポリゴンの高さ

#define	MAX_TON				(100)					//ここ世界レベル

#define TEXTURE_WIDTH		(1.0f)					//テクスチャ一つ分の幅
#define TEXTURE_HEIGHT		(1.0f)					//テクスチャ一つ分の高さ

#define FALL_SPEED			(0.98f)					//落下速度

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef	enum
{
	ICE01 = 0,
	ICE02,
	ICE03,
	ICE_MAX
}TON_TYPE;

typedef	struct
{
	ROTPOLYGON	conf;		//TONの中心座標とかそんなの
	TON_TYPE	type;		//TONのタイプ
	bool		alive;		//trueで生きてる証拠だよ！
}TON;


TON			ton[MAX_TON];	//TONの各種設定
TON_TYPE	tonType;		//TONのタイプ

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT		makeVertexTon	( LPDIRECT3DDEVICE9 pDevice );
D3DXVECTOR3	invisibleTon	( void );

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9		g_pTextureTon[ICE_MAX]	= {};		//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTon = NULL;		//頂点バッファ管理インターフェイス
char	*tonTexAdd[] =
{
	"data/TEXTURE/ice01.png",
	"data/TEXTURE/ice02.png",
	"data/TEXTURE/ice03.png"
};

//////////////////////////////////////////////////////////////////////////////
// 変数名	: initTon
// 返り値	:
// 説明		: 初期化は先輩まずいですよ！
//////////////////////////////////////////////////////////////////////////////
void	initTon	( void )
{
	//変数宣言
	int		i;		//loop
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスポインタ取得

	//デバイス取得
	makeVertexTon(pDevice);

	//ポリゴン初期化
	for( i = 0; i < MAX_TON; i++ )
	{
		initRotPolygon(&ton[i].conf,
			invisibleTon(),
			D3DXVECTOR3(TON_WIDTH, TON_HEIGHT, 0.f));
		ton[i].alive = false;
	}

	//テクスチャの読み込み
	for(i = 0; i < ICE_MAX; i++)
	{
		if(FAILED(D3DXCreateTextureFromFile(pDevice, tonTexAdd[i], &g_pTextureTon[i])))
		{
			MessageBox(NULL, "ton", "エラー", MB_OK);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: uninitTon
// 返り値	:
// 説明		: 終了処理は先輩まずいですよ！
//////////////////////////////////////////////////////////////////////////////
void	uninitTon	( void )
{
	//変数宣言
	int		i;		//loop

	//テクスチャインターフェイスの解放
	for(i = 0; i < ICE_MAX; i++)
	{
		if(g_pTextureTon[i] != NULL)
		{
			g_pTextureTon[i]->Release();
			g_pTextureTon[i] = NULL;
		}
	}

	//頂点バッファ管理の解放
	if(g_pVtxBufferTon != NULL)
	{
		g_pVtxBufferTon->Release();
		g_pVtxBufferTon = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: updateTon
// 返り値	:
// 説明		: 更新処理は先輩まずいですよ！
//////////////////////////////////////////////////////////////////////////////
void	updateTon	( void )
{
	//変数宣言
	int		i;		//loop
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスポインタ取得
	VERTEX_2D	*pVtx = NULL;

	//--------------------------------------
	//座標更新
	//--------------------------------------
	//trueの氷を落下させる
	for(i = 0; i < MAX_TON; i++)
	{
		if(ton[i].alive == true)
		{
			//一定以上落下していたらFalse
			if(ton[i].conf.conf.pos.y >= SCREEN_HEIGHT + TON_HEIGHT)
			{
				ton[i].conf.conf.pos = invisibleTon();
				ton[i].alive = false;
			}

			ton[i].conf.conf.pos.y += FALL_SPEED;
		}
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferTon->Lock(0, 0, (void**)&pVtx, 0);

	//バッファに座標登録
	for(i = 0; i < MAX_TON; i++)
	{
		setRotBuffer(pVtx, ton[i].conf);

		if(i < MAX_TON - 1)
		{
			setDegenerate(pVtx, ton[i].conf.conf.pos, ton[i + 1].conf.conf.pos);
		}

		pVtx += NUM_VERTEX + 2;
	}

	//バッファアンロック
	g_pVtxBufferTon->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: drawTon
// 返り値	:
// 説明		: 描画処理は先輩まずいですよ！
//////////////////////////////////////////////////////////////////////////////
void	drawTon	( void )
{
	//変数宣言
	int		i;		//loop
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferTon, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);


	//ポリゴンの描画
	for(i = 0; i < MAX_TON; i++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0,g_pTextureTon[ton[i].type]);

		pDevice->DrawPrimitive
			(
			D3DPT_TRIANGLESTRIP,		//ポリゴンの種類
			i * (NUM_VERTEX + 2),		//オフセット(頂点数)
			NUM_POLYGON * MAX_TON * 2	//ポリゴンの数
			);
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexTon
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexTon ( LPDIRECT3DDEVICE9 pDevice )
{
	//変数宣言
	int		i;		//loop
	VERTEX_2D	*pVtx = NULL;;		//仮想アドレス用ポインタ

	//頂点バッファの設定
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX_2D) * (NUM_VERTEX + 2) * MAX_TON,	//頂点バッファサイズ
			D3DUSAGE_WRITEONLY,				//頂点バッファの使用方法
			FVF_VERTEX_2D,					//
			D3DPOOL_MANAGED,				//メモリ管理方法
			&g_pVtxBufferTon,				//頂点バッファ管理インターフェイス
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferTon->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < MAX_TON; i++)
	{
		//頂点座標の設定(2D座標・右回り)
		pVtx[0].pos = D3DXVECTOR3(TON_POS_X, TON_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TON_WIDTH, TON_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TON_POS_X, TON_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TON_WIDTH, TON_HEIGHT, 0.0f);

		//rhwの設定(必ず1.0f)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定(0~155の整数値)
		pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	
		//テクスチャ頂点座標の設定(0~1)
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//ポインタ移動
		pVtx += NUM_VERTEX;
	}
	//私のこころアーンロック♪
	g_pVtxBufferTon->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: invisibleTon
//返り値	: 
//説明		: TONを見えなくする
//////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3	invisibleTon	( void )
{
	return D3DXVECTOR3(
		SCREEN_WIDTH + TON_WIDTH,
		SCREEN_HEIGHT + TON_HEIGHT,
		0.f);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: visibleTon
//返り値	: 
//説明		: TONを見えるようにする
//////////////////////////////////////////////////////////////////////////////
void	visibleTon	( TON *ton, D3DXVECTOR3 pos )
{
	ton->conf.conf.pos = pos;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setTon
//返り値	: 
//説明		: TONを調教する
//////////////////////////////////////////////////////////////////////////////
void	setTon	( D3DXVECTOR3 pos )
{
	//変数宣言
	int		i;		//loop

	for(i = 0; i < MAX_TON; i++)
	{
		if(ton[i].alive == false)
		{
			ton[i].conf.conf.pos = pos;
			ton[i].alive = true;
			break;
		}
	}
}