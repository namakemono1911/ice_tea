//////////////////////////////
//ヘッダー 
/////////////////////////////
#ifndef _ORAORA_H_

#define _ORAORA_H_

//弾構造体
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nTypeOraora;		//バレットタイプ(1.ボム2.カッター
	float fSpeed;
	int nLife;
	bool bUse;
}ORAORA;

#define Oraora_WIDTH (30.0f)		//ポリゴンの幅
#define Oraora_HEIGHT (30.0f)		//ポリゴンの高さ

//プロトタイプ
HRESULT InitOraora(void);
void UninitOraora(void);
void UpdateOraora(void);
void DrawOraora(void);
void SetOraora(float x, float y, float w, float h, float fSpeed);
ORAORA *GetOraora(void);

#endif