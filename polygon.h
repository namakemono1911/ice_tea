/*****************************************************************************
polygon.h
Aythor	: 上野　匠
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/
#ifndef POLYGON_H
#define POLYGON_H

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3	pos;		//表示座標
	D3DXVECTOR3	size;		//ポリゴンの幅高さ
}POLYGON;

typedef struct
{
	POLYGON		conf;		//中心座標とサイズ
	float	rot;			//ポリゴンの回転量
	FLOAT	length;			//ポリゴンの対角線の長さ
	float	angle;			//ポリゴンの対角線の角度
}ROTPOLYGON;

typedef struct
{
	D3DXVECTOR2	pos;		//テクスチャの描画位置
	D3DXVECTOR2	size;		//テクスチャのサイズ
}TEXTURE;

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
void initDevice ( void );
void initPolygon ( POLYGON *polygon, D3DXVECTOR3 pos, D3DXVECTOR3 size );
void initRotPolygon ( ROTPOLYGON *polygon, D3DXVECTOR3 pos, D3DXVECTOR3 size );
void setTexture ( VERTEX_2D *pVtx, POLYGON polygon );
void setBuffer ( VERTEX_2D *pVtx, POLYGON polygon );
void setListBuffer ( VERTEX_2D *pVtx, POLYGON polygon );
void setRotBuffer ( VERTEX_2D *pVtx, ROTPOLYGON polygon );
void setDegenerate ( VERTEX_2D *pVtx, D3DXVECTOR3 pos, D3DXVECTOR3 nextPos );

#endif