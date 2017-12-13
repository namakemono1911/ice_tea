/*==============================================================================

     [fade.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ��Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//�w�b�_�[
////////////////////////////////////
#include "main.h"
#include "fade.h"
#include "input.h"
#include <math.h>

#define Fade_POSX (450.0f)		//�|���S���̕\���ʒuX
#define Fade_POSY (180.0f)		//�|���S���̕\���ʒuY
#define Fade_WIDTH (200.0f)		//�|���S���̕�
#define Fade_HEIGHT (200.0f)	//�|���S���̍���

//05/27 texture
#define Fade_TEXTURENAM "data/TEXTURE/akira001.png"

#define FADE_RATE (0.2f);

//////////////////////////////////
//�v���g�^�C�v
/////////////////////////////////
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);
void SetColorFade(D3DXCOLOR color);

/////////////////////////////
//�O���[�o��
////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//���_���i�[�p�z��
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;	//�e�N�X�`���|�C���^�t�F�[�X�ւ̃|�C���^�[
//0603 ���_�p�b�t�@�Ǘ��C���^�[�t�F�[�X�|�C���^��錾����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferFade = NULL;

//�t�F�[�h
D3DXCOLOR g_colorFade;
FADE g_fade = FADE_IN;
MODE g_modeNext = MODE_TITLE;

///////////////////////////
//����������
//////////////////////////////////
HRESULT InitFade(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//�|���S��
	//�G���[, �e�N�X�`���̓ǂݍ���
	if(FAILED(D3DXCreateTextureFromFile(pDevice,Fade_TEXTURENAM,&g_pTextureFade)))
	{
		MessageBox(NULL,"dekinai","�I�����b�Z�[�W",MB_YESNO | MB_DEFBUTTON1);
	}
	//���_�̍쐬����
	if(FAILED(MakeVertexFade(pDevice)))
	{
		return E_FAIL;
	}

	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	g_fade = FADE_IN;

	return S_OK;
}

//////////////////////////////////
//�I������
//////////////////////////////////
void UninitFade(void)
{
	if(g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();			//�e�N�X�`���C���^�[�t�F�[�X�̉��
		g_pTextureFade = NULL;
	}

	if(g_pVtxBufferFade != NULL)
	{
		g_pVtxBufferFade->Release();		//���C�N���@�[�e�b�N�X
		g_pVtxBufferFade = NULL;
	}
}

//////////////////////////////////
//�X�V����
//////////////////////////////////
void UpdateFade(void)
{
	VERTEX_2D* pVtx = NULL;

	g_pVtxBufferFade->Lock(0,0,(void**)&pVtx,0);

	if(g_fade == FADE_NONE)
	{
		return;
	}
	if(g_fade == FADE_IN)
	{
		g_colorFade.a -= FADE_RATE;	//a�l�����Z���Č��̉�ʂ𕂂��オ�点��
		if(g_colorFade.a <= 0.0f)
		{
			g_colorFade.a = 0.0f;
			g_fade = FADE_NONE;
		}
	}
	else if(g_fade == FADE_OUT)
	{
		g_colorFade.a += FADE_RATE;
		if(g_colorFade.a >= 1.0f)
		{
			g_colorFade.a = 1.0f;
			g_fade = FADE_IN;
			SetMode(g_modeNext);
		}
	}
	SetColorFade(g_colorFade);
	g_pVtxBufferFade->Unlock();
}

//////////////////////////////////
//�`�揈��
//////////////////////////////////
void DrawFade(void)
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//0607 �p�C�v���C��
	pDevice->SetStreamSource(0,g_pVtxBufferFade,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);
	//05/27
	pDevice->SetTexture(0,g_pTextureFade);		//�e�N�X�`���̐ݒ�

	//�v���~�e�B�u�̕`��
//	g_pD3Device->DrawPrimitiveUP(		D3DPT_TRIANGLELIST,NUM_Fade,&g_aVertex[0],sizeof(VERTEX_2D));
	//�v���~�e�B�u�̎��   //�v���~�e�B�u�̐�   //���_�f�[�^�̐擪�A�h���X   //���_�f�[�^�P�����̃T�C�Y
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_Fade,&g_aVertex[0],sizeof(VERTEX_2D));

	//0607
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
											0,	//�I�t�Z�b�g�i���_���j
											NUM_POLYGON);//�v���~�e�B�u��
}

//////////////////////////////////
//���_�̍쐬
//////////////////////////////////
HRESULT MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)  //void�ς���
{
	//0603 ���_�o�b�t�@
	//�h��G���[�`�F�b�N����return E_FALL   hresult�^
	if(FAILED(	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,		//�쐬���������_�o�b�t�@�̃T�C�Y�i�P���_�T�C�Y�����_��
								D3DUSAGE_WRITEONLY,					//�g�p�@�@�i�������݂̂�
								FVF_VERTEX_2D,						//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,					//�������Ǘ����@�i�f�o�C�X�ɂ��܂���
								&g_pVtxBufferFade,				//								�h�肠�Ƃ�����������I�I
								NULL)))
	{
		return E_FAIL;
	}
	//�G���[����Ȃ�������
	VERTEX_2D* pVtx;			//���z�A�h���X�p�̃|�C���^

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferFade->Lock(0,0,(void**)&pVtx,0);

	//���_���W�̐ݒ�(2D���W �E���)
	pVtx[0].pos = D3DXVECTOR3(Fade_POSX, Fade_POSY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Fade_POSX +Fade_WIDTH, Fade_POSY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Fade_POSX, Fade_POSY +Fade_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Fade_POSX +Fade_WIDTH, Fade_POSY +Fade_HEIGHT, 0.0f);

	//rhw�̐ݒ�i�K�� 1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ� ( 0�`255�̐����l)
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//uv
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBufferFade->Unlock();

	return S_OK;
}

//////////////////////////////////
//�Z�b�g
//////////////////////////////////
void SetFade(FADE fade, MODE modeNext)	//�ǉ��ŃJ���[�w��A�e�N�X�`���w��A�t�F�[�h�X�s�[�h
{

}

//////////////////////////////////
//�Z�b�g�J���[
//////////////////////////////////
void SetColorFade(D3DXCOLOR color)
{

}

//////////////////////////////////
//
//////////////////////////////////
FADE GetFade(void)
{
	return g_fade;
}