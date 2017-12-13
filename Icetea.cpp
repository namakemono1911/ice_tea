/*==============================================================================

    ポリゴン [icetea.cpp]
                                                       Author : Norihiro Hayashi
                                                       Date   : 2016/05/31
--------------------------------------------------------------------------------
    ■Update : 2016/07/25

==============================================================================*/

/*******************************************************************************
* インクルードファイル
*******************************************************************************/
#include "main.h"
#include "input.h"
#include "Icetea.h"
#include "hit.h"

/*******************************************************************************
* マクロ定義
*******************************************************************************/


#define POLYGON_POS_X (200.0f)							// ポリゴンの左上X座標
#define POLYGON_POS_Y (300.0f)							// ポリゴンの左上Y座標
#define POLYGON_WIDTH (256.0f)							//SIZE_X ポリゴンの横幅
#define POLYGON_HEIGHT (256.0f)							//SIZE_Y ポリゴンの高さ
#define POLYGON_TEXTURENAME "data/TEXTURE/Icetea.png"	//テクスチャの名前

#define NUM_VERTEX (4)	//頂点数
#define NUM_POLYGON (2)	//ポリゴン数

/*******************************************************************************
* 構造体定義
*******************************************************************************/

/*******************************************************************************
* プロトタイプ宣言
*******************************************************************************/
void MakeVertexIcetea ( LPDIRECT3DDEVICE9 pDevice );

/*******************************************************************************
* グローバル変数
*******************************************************************************/
bool g_bflag ;				//移動フラグ,trueなら右にfalseなら左に移動
D3DXVECTOR2 g_posIcetea ;	//ポリゴンの中心座標
float g_rotIcetea ;			//ポリゴンの回転量(ラジアン)
float g_fLengthIcetea ;		//ポリゴンの対角線の長さ
float g_fAngleIcetea ;		//ポリゴンの対角線の角度

//VERTEX_2D g_aVertex[NUM_VERTEX];	//頂点情報格納用配列

LPDIRECT3DTEXTURE9 g_pTextureIcetea = NULL ;	//テクスチャーインターフェース

//頂点バッファ管理用インターフェースポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferIcetea = NULL ;

void InitIcetea (void)	//初期化処理
{
	g_bflag = false;
	g_rotIcetea  = 0;			//ポリゴンの回転量(ラジアン)
	g_fLengthIcetea = 0;		//ポリゴンの対角線の長さ
	g_fAngleIcetea = 0;		//ポリゴンの対角線の角度


	g_posIcetea = D3DXVECTOR2( (POLYGON_POS_X + POLYGON_WIDTH *0.5 )  , (POLYGON_POS_Y +POLYGON_HEIGHT *0.5) );

	g_rotIcetea = 0.0f ;

	//対角線の長さの算出
	g_fLengthIcetea = sqrt ( POLYGON_WIDTH * POLYGON_WIDTH + POLYGON_HEIGHT * POLYGON_HEIGHT) / 2.0f ;

	g_fAngleIcetea = atan2( POLYGON_HEIGHT , POLYGON_WIDTH) ;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのアドレスを取得

	MakeVertexIcetea (  pDevice );	//頂点の作成

	g_bflag = true ;

	//テクスチャーの読み込み
	//FAIFED(フェイルドマクロ)エラーチェック
	if( FAILED( D3DXCreateTextureFromFile ( pDevice , POLYGON_TEXTURENAME , &g_pTextureIcetea ) ) )
	{
		MessageBox(NULL,"アイスティーのテクスチャ読み込みエラー","エラー！",MB_OK | MB_ICONQUESTION );//続き
	}

//if( FAILED( D3DXCreateTextureFromFile( g_pD3DDevice , POLYGON_TEXTURENAME , &g_pTextureIcetea ) );
//	{
//		return E_FAIL;
//	}
}

void UninitIcetea (void)	//終了処理
{
	if( g_pTextureIcetea != NULL )
	{
		g_pTextureIcetea -> Release();
		g_pTextureIcetea = NULL ;
	}

	if( g_pVtxBufferIcetea != NULL)
	{
		g_pVtxBufferIcetea -> Release();
		g_pVtxBufferIcetea = NULL ;
	}
	g_bflag = false;
	g_rotIcetea  = 0;			//ポリゴンの回転量(ラジアン)
	g_fLengthIcetea = 0;		//ポリゴンの対角線の長さ
	g_fAngleIcetea = 0;		//ポリゴンの対角線の角度

}

void UpdateIcetea(void)	//更新処理
{
	VERTEX_2D* pVtx;

	if(g_bflag == true)
	{
		g_posIcetea.x += 5.0f ;
		if(g_posIcetea.x >= 700)
		{
			g_bflag = false ;
		}
	}
	if(g_bflag == false)
	{
		g_posIcetea.x -= 5.0f ;
		if(g_posIcetea.x <= 100)
		{
			g_bflag = true ;
		}
	}

	g_pVtxBufferIcetea ->Lock( 0 , 0 , (void**)&pVtx , 0 );//頂点バッファをロックし仮想アドレスを取得

	SetVertexIcetea(pVtx);

	g_pVtxBufferIcetea -> Unlock();//アンロック

}

void DrawIcetea(void)	//描画処理
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//デバイスのアドレスを取得

	pDevice ->SetStreamSource( 0 ,
								g_pVtxBufferIcetea ,
								0 ,//オフセット(バイト)
								sizeof(VERTEX_2D)/*ストライド値*/ );

	//ポリゴンの描画をする寸前
	//テクスチャーの設定
	pDevice -> SetTexture( 0 , g_pTextureIcetea );

	//頂点フォーマットの設定
	pDevice -> SetFVF(FVF_VERTEX_2D);

	//プリミティブの描画
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP ,	//プリミティブの種類
							0 ,						//オフセット(頂点数)
							NUM_POLYGON ) ;			//プリミティブ数

}

//頂点の作成
void MakeVertexIcetea ( LPDIRECT3DDEVICE9 pDevice )
{
	pDevice ->CreateVertexBuffer( sizeof(VERTEX_2D) * NUM_VERTEX , //作成したい頂点バッファサイズ
													D3DUSAGE_WRITEONLY,
													FVF_VERTEX_2D,
													D3DPOOL_MANAGED,
													&g_pVtxBufferIcetea,
													NULL);

	// FAILEDマクロをする

	VERTEX_2D* pVtx;	//仮想アドレスのポインタ

	//頂点バッファをロックして仮想アドレスを取得する
	g_pVtxBufferIcetea -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	SetVertexIcetea( pVtx );

	g_pVtxBufferIcetea -> Unlock();//アンロック

}
///////
//更新した座標の設定
////////
void SetVertexIcetea ( VERTEX_2D *pVtx )
{

	//頂点座標の設定(2D座標・右回り)
	pVtx[0].pos = D3DXVECTOR3(	g_posIcetea.x + cosf( g_fAngleIcetea + D3DX_PI + g_rotIcetea ) * g_fLengthIcetea ,//X
								g_posIcetea.y + sinf( g_fAngleIcetea + D3DX_PI + g_rotIcetea ) * g_fLengthIcetea ,//Y
								0.0f );
	//右上
	pVtx[1].pos = D3DXVECTOR3(	g_posIcetea.x + cosf( - g_fAngleIcetea + g_rotIcetea) * g_fLengthIcetea ,//X
								g_posIcetea.y + sinf( - g_fAngleIcetea + g_rotIcetea) * g_fLengthIcetea ,//Y
								0.0f );
	//左下
	pVtx[2].pos = D3DXVECTOR3(	g_posIcetea.x + cosf( - g_fAngleIcetea - D3DX_PI + g_rotIcetea) * g_fLengthIcetea ,//X
								g_posIcetea.y + sinf( - g_fAngleIcetea - D3DX_PI + g_rotIcetea) * g_fLengthIcetea ,//Y
								0.0f );
	//右下
	pVtx[3].pos = D3DXVECTOR3(	g_posIcetea.x + cosf( g_fAngleIcetea + g_rotIcetea) * g_fLengthIcetea ,//X
								g_posIcetea.y + sinf( g_fAngleIcetea + g_rotIcetea) * g_fLengthIcetea ,//Y
								0.0f );
	//rhwの設定(必ず1.0f)
	pVtx[0].rhw=1.0f ;
	pVtx[1].rhw=1.0f ;
	pVtx[2].rhw=1.0f ;
	pVtx[3].rhw=1.0f ;

	//頂点データへUVデータの追加
	pVtx[0].tex = D3DXVECTOR2(0,0) ;
	pVtx[1].tex = D3DXVECTOR2(1,0) ;
	pVtx[2].tex = D3DXVECTOR2(0,1) ;
	pVtx[3].tex = D3DXVECTOR2(1,1) ;

	//頂点カラーの設定(0～255の整数値)
	pVtx[0].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ) ;
	pVtx[1].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ) ;
	pVtx[2].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ) ;
	pVtx[3].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ) ;

}