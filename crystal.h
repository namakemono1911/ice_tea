//////////////////////////////
//�w�b�_�[ 
/////////////////////////////
#ifndef _CRYSTAL_H_

#define _CRYSTAL_H_

//�e�\����
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR2 size;
	int nTypeCrystal;		//�o���b�g�^�C�v(1.�{��2.�J�b�^�[
	float fSpeed;
	int nLife;
	bool bUse;
}CRYSTAL;

#define Crystal_WIDTH (30.0f)		//�|���S���̕�
#define Crystal_HEIGHT (30.0f)		//�|���S���̍���

//�v���g�^�C�v
HRESULT InitCrystal(void);
void UninitCrystal(void);
void UpdateCrystal(void);
void DrawCrystal(void);
void SetCrystal(float x, float y, float w, float h, float fSpeed);
CRYSTAL *GetCrystal(void);

#endif