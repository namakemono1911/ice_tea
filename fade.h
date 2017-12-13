//////////////////////////////
//�w�b�_�[ FADE
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

//�v���g�^�C�v
HRESULT InitFade(void);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);
void SetFade(FADE fade, MODE modeNext);	//�ǉ��ŃJ���[�w��A�e�N�X�`���w��A�t�F�[�h�X�s�[�h
FADE GetFade(void);

#endif