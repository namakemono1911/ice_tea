/*==============================================================================

     [game.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ��Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//�w�b�_�[
////////////////////////////////////
#include "main.h"
#include "game.h"
#include "input.h"
#include "polygon.h"
#include "bg.h"
#include "input.h"
#include "fade.h"
#include "crystal.h"
#include "oraora.h"
#include <math.h>
#include "Icetea.h"
#include "ton.h"
#include "hit.h"

//////////////////////////////////
//�v���g�^�C�v
/////////////////////////////////
HRESULT MakeVertexGame(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////
//�O���[�o��
////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//���_���i�[�p�z��

LPDIRECT3DTEXTURE9 g_pTextureGame = NULL;	//�e�N�X�`���|�C���^�t�F�[�X�ւ̃|�C���^�[

//0603 ���_�p�b�t�@�Ǘ��C���^�[�t�F�[�X�|�C���^��錾����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferGame = NULL;

//////////////////////////////////
//����������
//////////////////////////////////
void InitGame(void)
{
	InitBG();
	InitIcetea();
	//�|���S��
//	if(FAILED( InitPolygon() ))
//	{
//		MessageBox(NULL,"�C�j�b�g�|���S�����s","�C�j�b�g�|���S�����s",MB_OK);
	//	return E_FAIL;
//	}
//	if(FAILED( InitEnemy() ))
//	{
//		MessageBox(NULL,"�C�j�b�gENEMY���s","�C�j�b�gENEMY���s",MB_OK);
//		//return E_FAIL;
//	}
//	InitBullet();
	InitCrystal();
	InitOraora();
	initTon();
}

//////////////////////////////////
//�I������
//////////////////////////////////
void UninitGame(void)
{
	UninitBG();
	//UninitPolygon();
//	UninitEnemy();
	//UninitBullet();
	UninitCrystal();
	UninitOraora();
	UninitIcetea();
	uninitTon();
}

//////////////////////////////////
//�X�V����
//////////////////////////////////
void UpdateGame(void)
{
	UpdateBG();
	//UpdatePolygon();
//	UpdateEnemy();
	//UpdateBullet();
	UpdateOraora();
	UpdateIcetea();
	updateTon();
	UpdateCrystal();
}

//////////////////////////////////
//�`�揈��
//////////////////////////////////
void DrawGame(void)
{
	DrawBG();
	DrawCrystal();		//�N���X�^��
	//DrawPolygon();	//�|���S��
//	DrawEnemy();		//�G
	//DrawBullet();		//�e
	drawTon();
	DrawOraora();		//�I���I��
	DrawIcetea();

}
