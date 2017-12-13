/*==============================================================================

     [Result.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ��Update : 2016/6/28
  
==============================================================================*/


////////////////////////////////////
//�w�b�_�[
////////////////////////////////////
#include "main.h"
#include "result.h"
#include "input.h"
#include "fade.h"
#include <math.h>

#define Result_POSX (0.0f)			//�|���S���̕\���ʒuX
#define Result_POSY (0.0f)			//�|���S���̕\���ʒuY
#define Result_WIDTH (800.0f)		//�|���S���̕�
#define Result_HEIGHT (600.0f)		//�|���S���̍���

//05/27 texture
#define Result_TEXTURENAM "data/TEXTURE/RESULT.jpg"

//////////////////////////////////
//�v���g�^�C�v
/////////////////////////////////
HRESULT MakeVertexResult(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////
//�O���[�o��
////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//���_���i�[�p�z��

LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;	//�e�N�X�`���|�C���^�t�F�[�X�ւ̃|�C���^�[

//0603 ���_�p�b�t�@�Ǘ��C���^�[�t�F�[�X�|�C���^��錾����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferResult = NULL;

///////////////////////////
//����������
//////////////////////////////////
HRESULT InitResult(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//�|���S��
	//�G���[, �e�N�X�`���̓ǂݍ���
	if(FAILED(D3DXCreateTextureFromFile(pDevice,Result_TEXTURENAM,&g_pTextureResult)))
	{
		MessageBox(NULL,"dekinaiRESULT","�I�����b�Z�[�W",MB_YESNO | MB_DEFBUTTON1);
	}
	//���_�̍쐬����
	if(FAILED(MakeVertexResult(pDevice)))
	{
		return E_FAIL;
	}
	return S_OK;
}

//////////////////////////////////
//�I������
//////////////////////////////////
void UninitResult(void)
{
	if(g_pTextureResult != NULL)
	{
		g_pTextureResult->Release();			//�e�N�X�`���C���^�[�t�F�[�X�̉��
		g_pTextureResult = NULL;
	}

	if(g_pVtxBufferResult != NULL)
	{
		g_pVtxBufferResult->Release();			//���C�N���@�[�e�b�N�X
		g_pVtxBufferResult = NULL;
	}
}

//////////////////////////////////
//�X�V����
//////////////////////////////////
void UpdateResult(void)
{
	VERTEX_2D* pVtx = NULL;

	g_pVtxBufferResult->Lock(0,0,(void**)&pVtx,0);

	g_pVtxBufferResult->Unlock();

	if(GetKeyboardTrigger(DIK_RETURN))
	{
		
		SetMode(MODE_TITLE);
	}
}

//////////////////////////////////
//�`�揈��
//////////////////////////////////
void DrawResult(void)
{
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//0607 �p�C�v���C��
	pDevice->SetStreamSource(0,g_pVtxBufferResult,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);
	//05/27
	pDevice->SetTexture(0,g_pTextureResult);		//�e�N�X�`���̐ݒ�

	//�v���~�e�B�u�̕`��
//	g_pD3Device->DrawPrimitiveUP(		D3DPT_TRIANGLELIST,NUM_Result,&g_aVertex[0],sizeof(VERTEX_2D));
	//�v���~�e�B�u�̎��   //�v���~�e�B�u�̐�   //���_�f�[�^�̐擪�A�h���X   //���_�f�[�^�P�����̃T�C�Y
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_Result,&g_aVertex[0],sizeof(VERTEX_2D));

	//0607
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
											0,	//�I�t�Z�b�g�i���_���j
											NUM_POLYGON);//�v���~�e�B�u��
}

//////////////////////////////////
//���_�̍쐬
//////////////////////////////////
HRESULT MakeVertexResult(LPDIRECT3DDEVICE9 pDevice)  //void�ς���
{
	//0603 ���_�o�b�t�@
	//�h��G���[�`�F�b�N����return E_FALL   hresult�^
	if(FAILED(	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX,		//�쐬���������_�o�b�t�@�̃T�C�Y�i�P���_�T�C�Y�����_��
								D3DUSAGE_WRITEONLY,					//�g�p�@�@�i�������݂̂�
								FVF_VERTEX_2D,						//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,					//�������Ǘ����@�i�f�o�C�X�ɂ��܂���
								&g_pVtxBufferResult,				//								�h�肠�Ƃ�����������I�I
								NULL)))
	{
		return E_FAIL;
	}
	//�G���[����Ȃ�������
	VERTEX_2D* pVtx;			//���z�A�h���X�p�̃|�C���^

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferResult->Lock(0,0,(void**)&pVtx,0);

	//���_���W�̐ݒ�(2D���W �E���)
	pVtx[0].pos = D3DXVECTOR3(Result_POSX, Result_POSY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Result_POSX +Result_WIDTH, Result_POSY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Result_POSX, Result_POSY +Result_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Result_POSX +Result_WIDTH, Result_POSY +Result_HEIGHT, 0.0f);

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
	g_pVtxBufferResult->Unlock();

	return S_OK;
}