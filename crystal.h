//////////////////////////////
//ヘッダー 
/////////////////////////////
#ifndef _CRYSTAL_H_

#define _CRYSTAL_H_

//弾構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nTypeCrystal;		//バレットタイプ(1.ボム2.カッター
	float fSpeed;
	int nLife;
	bool bUse;
}CRYSTAL;

#define Crystal_WIDTH (30.0f)		//ポリゴンの幅
#define Crystal_HEIGHT (30.0f)		//ポリゴンの高さ

//プロトタイプ
HRESULT InitCrystal(void);
void UninitCrystal(void);
void UpdateCrystal(void);
void DrawCrystal(void);
void SetCrystal(float x, float y, float w, float h, float fSpeed);
CRYSTAL *GetCrystal(void);

#endif