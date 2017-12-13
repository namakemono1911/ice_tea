//////////////////////////////
//ヘッダー FADE
/////////////////////////////
#ifndef _FADE_H_

#define _FADE_H_

typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX,
}FADE;

//プロトタイプ
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(FADE fade, MODE modeNext);	//追加でカラー指定、テクスチャ指定、フェードスピード
FADE GetFade(void);

#endif