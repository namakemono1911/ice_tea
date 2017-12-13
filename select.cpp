/*==============================================================================

     [Select.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ��Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//�w�b�_�[
////////////////////////////////////
#include "main.h"
#include "select.h"
#include "menubar.h"
#include "polygon.h"
#include "bg.h"
#include "input.h"
#include "fade.h"
#include <math.h>

//////////////////////////////////
//�v���g�^�C�v
/////////////////////////////////
HRESULT MakeVertexSelect(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////
//�O���[�o��
////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//���_���i�[�p�z��

LPDIRECT3DTEXTURE9 g_pTextureSelect = NULL;	//�e�N�X�`���|�C���^�t�F�[�X�ւ̃|�C���^�[

//0603 ���_�p�b�t�@�Ǘ��C���^�[�t�F�[�X�|�C���^��錾����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferSelect = NULL;

//////////////////////////////////
//����������
//////////////////////////////////
void InitSelect(void)
{
	InitBG();
	InitMenubar();
}

//////////////////////////////////
//�I������
//////////////////////////////////
void UninitSelect(void)
{
	UninitBG();
	UninitMenubar();
}

//////////////////////////////////
//�X�V����
//////////////////////////////////
void UpdateSelect(void)
{
	UpdateBG();
	UpdateMenubar();

	if(GetKeyboardTrigger(DIK_SPACE))
	{
		//PlaySound(SOUND_LABEL_BGM001);
		SetMode(MODE_GAME);
	}
}

//////////////////////////////////
//�`�揈��
//////////////////////////////////
void DrawSelect(void)
{
	DrawBG();
	DrawMenubar();
}
