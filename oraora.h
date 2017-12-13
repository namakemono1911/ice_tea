//////////////////////////////
//�w�b�_�[ 
/////////////////////////////
#ifndef _ORAORA_H_

#define _ORAORA_H_

//�e�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nTypeOraora;		//�o���b�g�^�C�v(1.�{��2.�J�b�^�[
	float fSpeed;
	int nLife;
	bool bUse;
}ORAORA;

#define Oraora_WIDTH (30.0f)		//�|���S���̕�
#define Oraora_HEIGHT (30.0f)		//�|���S���̍���

//�v���g�^�C�v
HRESULT InitOraora(void);
void UninitOraora(void);
void UpdateOraora(void);
void DrawOraora(void);
void SetOraora(float x, float y, float w, float h, float fSpeed);
ORAORA *GetOraora(void);

#endif