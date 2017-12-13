/*****************************************************************************
hit.cpp
Aythor	: 上野　匠
Data	: 2016_07_23
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "input.h"
#include "hit.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	PLAYER1 = 0,
	PLAYER2,
	PLAYER_MAX
}HIT_PLAYER;

typedef enum
{
	CAR1 = 0,
	CAR2,
	ENEMY_MAX
}HIT_ENEMY;

typedef enum
{
	MAP1 = 0,
	MAP_MAX
}HIT_MAP;

typedef struct
{
	POLYGON			conf;		//当たり判定コンフィグ
}HITBOX;

HITBOX hitBox;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
#ifdef	_DEBUG	//リリース時描画は行わないので無効化
HRESULT makeVertexhitView ( LPDIRECT3DDEVICE9 pDevice );
#endif

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
#ifdef	_DEBUG	//リリース時描画は行わないので無効化
LPDIRECT3DTEXTURE9	g_pTexturehitView = NULL;	//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferhitView = NULL;	//頂点バッファ管理インターフェイス
#endif

//////////////////////////////////////////////////////////////////////////////
// グローバル変数
//////////////////////////////////////////////////////////////////////////////
int	numHitBox = 0;		//ヒットボックスの数

//////////////////////////////////////////////////////////////////////////////
//関数名	:	HitCheck
//返り値	:	true	当たり有
//				false	当たり無
//説明		:	画像同士が衝突したかの判定
//////////////////////////////////////////////////////////////////////////////
bool HitCheck ( POLYGON hitBox1, POLYGON hitBox2 )
{
	if(hitBox1.size.x > hitBox2.size.x)
	{
		if(	(hitBox1.pos.x - (hitBox1.size.x * 0.5f) < hitBox2.pos.x - (hitBox2.size.x * 0.5f) &&
			hitBox1.pos.x + (hitBox1.size.x * 0.5f) > hitBox2.pos.x - (hitBox2.size.x * 0.5f)) ||
			(hitBox1.pos.x - (hitBox1.size.x * 0.5f) < hitBox2.pos.x + (hitBox2.size.x * 0.5f) &&
			hitBox1.pos.x + (hitBox1.size.x * 0.5f) > hitBox2.pos.x + (hitBox2.size.x * 0.5f)))
		{
			if(hitBox1.size.y > hitBox2.size.y)
			{
				if(	(hitBox1.pos.y - (hitBox1.size.y * 0.5f) < hitBox2.pos.y - (hitBox2.size.y * 0.5f) &&
				hitBox1.pos.y + (hitBox1.size.y * 0.5f) > hitBox2.pos.y - (hitBox2.size.y * 0.5f)) ||
				(hitBox1.pos.y - (hitBox1.size.y * 0.5f) < hitBox2.pos.y + (hitBox2.size.y * 0.5f) &&
				hitBox1.pos.y + (hitBox1.size.y * 0.5f) > hitBox2.pos.y + (hitBox2.size.y * 0.5f)))
				{
					return true;
				}
			}
			else
			{
				if(	(hitBox2.pos.y - (hitBox2.size.y * 0.5f) < hitBox1.pos.y - (hitBox1.size.y * 0.5f) &&
				hitBox2.pos.y + (hitBox2.size.y * 0.5f) > hitBox1.pos.y - (hitBox1.size.y * 0.5f)) ||
				(hitBox2.pos.y - (hitBox2.size.y * 0.5f) < hitBox1.pos.y + (hitBox1.size.y * 0.5f) &&
				hitBox2.pos.y + (hitBox2.size.y * 0.5f) > hitBox1.pos.y + (hitBox1.size.y * 0.5f)))
				{
					return true;
				}
			}
		}
	}
	else
	{
		if(	(hitBox2.pos.x - (hitBox2.size.x * 0.5f) < hitBox1.pos.x - (hitBox1.size.x * 0.5f) &&
			hitBox2.pos.x + (hitBox2.size.x * 0.5f) > hitBox1.pos.x - (hitBox1.size.x * 0.5f)) ||
			(hitBox2.pos.x - (hitBox2.size.x * 0.5f) < hitBox1.pos.x + (hitBox1.size.x * 0.5f) &&
			hitBox2.pos.x + (hitBox2.size.x * 0.5f) > hitBox1.pos.x + (hitBox1.size.x * 0.5f)))
		{
			if(hitBox1.size.y > hitBox2.size.y)
			{
				if(	(hitBox1.pos.y - (hitBox1.size.y * 0.5f) < hitBox2.pos.y - (hitBox2.size.y * 0.5f) &&
				hitBox1.pos.y + (hitBox1.size.y * 0.5f) > hitBox2.pos.y - (hitBox2.size.y * 0.5f)) ||
				(hitBox1.pos.y - (hitBox1.size.y * 0.5f) < hitBox2.pos.y + (hitBox2.size.y * 0.5f) &&
				hitBox1.pos.y + (hitBox1.size.y * 0.5f) > hitBox2.pos.y + (hitBox2.size.y * 0.5f)))
				{
					return true;
				}
			}
			else
			{
				if(	(hitBox2.pos.y - (hitBox2.size.y * 0.5f) < hitBox1.pos.y - (hitBox1.size.y * 0.5f) &&
				hitBox2.pos.y + (hitBox2.size.y * 0.5f) > hitBox1.pos.y - (hitBox1.size.y * 0.5f)) ||
				(hitBox2.pos.y - (hitBox2.size.y * 0.5f) < hitBox1.pos.y + (hitBox1.size.y * 0.5f) &&
				hitBox2.pos.y + (hitBox2.size.y * 0.5f) > hitBox1.pos.y + (hitBox1.size.y * 0.5f)))
				{
					return true;
				}
			}
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:	setNumHitBox
//返り値	:	
//説明		:	ヒットボックス総数を代入
//////////////////////////////////////////////////////////////////////////////
void setNumHitBox ( int num )
{
	numHitBox += num;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	:	getNumHitBox
//返り値	:	numHitBox
//説明		:	ヒットボックス総数の値を返す
//////////////////////////////////////////////////////////////////////////////
int getNumHitBox ( void )
{
	return numHitBox;
}