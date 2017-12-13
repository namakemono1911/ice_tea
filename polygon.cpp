/*****************************************************************************
polygon.cpp
Aythor	: ���@��
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: initDevice
// �Ԃ�l	:
// ����		: �f�o�C�X�̏�����
//////////////////////////////////////////////////////////////////////////////
void initDevice ( void )
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initPolygon
//����		: *polygon	������������POLYGON�ϐ�
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initPolygon ( POLYGON *polygon, D3DXVECTOR3 pos, D3DXVECTOR3 size )
{
	polygon->pos = pos;
	polygon->size = size;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	initRotPolygon
//
//����		:	*polygon	������������POLYGON�ϐ�
//				pos			�ݒ肵�����摜�̍��W
//				size		�ݒ肵�����摜�̃T�C�Y
//
//�Ԃ�l	:	
//����		:	 ��]�|���S��������
//////////////////////////////////////////////////////////////////////////////
void initRotPolygon ( ROTPOLYGON *polygon, D3DXVECTOR3 pos, D3DXVECTOR3 size )
{
	//���S���W������
	polygon->conf.pos = pos;

	//�T�C�Y������
	polygon->conf.size = size;

	//�|���S���̊p�x
	polygon->rot = 0.0f;

	//�Ίp���̒���
	polygon->length = sqrt(polygon->conf.size.x * polygon->conf.size.x + polygon->conf.size.y * polygon->conf.size.y) * 0.5f;

	//�|���S���̑Ίp���̊p�x
	polygon->angle = atan2(polygon->conf.size.y, polygon->conf.size.x);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	setTexture
//
//����		:	*pVtx	�ݒ肵�����摜�̃o�b�t�@�A�h���X
//				texture	�ݒ肵����TEXTURE�^�̕ϐ�
//
//�Ԃ�l	: 
//����		:	�|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void setTexture ( VERTEX_2D *pVtx, TEXTURE texture )
{
	//����UV
	pVtx[0].tex = D3DXVECTOR2(
		texture.pos.x,
		texture.pos.y);

	//�E��UV
	pVtx[1].tex = D3DXVECTOR2(
		texture.pos.x + texture.size.x,
		texture.pos.y);

	//����UV
	pVtx[2].tex = D3DXVECTOR2(
		texture.pos.x,
		texture.pos.y + texture.size.y);

	//�E��UV
	pVtx[3].tex = D3DXVECTOR2(
		texture.pos.x + texture.size.x,
		texture.pos.y + texture.size.y);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setBuffer
//
//����		:	*pVtx	�ݒ肵�����摜�̃o�b�t�@�A�h���X
//				polygon	�o�b�t�@�ɐݒ肵����POLYGON�^�ϐ�
//
//�Ԃ�l	: 
//����		: �o�b�t�@�ɍ��W��ݒ�
//////////////////////////////////////////////////////////////////////////////
void setBuffer ( VERTEX_2D *pVtx, POLYGON polygon )
{
	//������W
	pVtx[0].pos = D3DXVECTOR3(
		polygon.pos.x - (polygon.size.x * 0.5f),
		polygon.pos.y - (polygon.size.y * 0.5f),
		0.f);
	
	//�E����W
	pVtx[1].pos = D3DXVECTOR3(
		polygon.pos.x + (polygon.size.x * 0.5f),
		polygon.pos.y - (polygon.size.y * 0.5f),
		0.f);

	//�������W
	pVtx[2].pos = D3DXVECTOR3(
		polygon.pos.x - (polygon.size.x * 0.5f),
		polygon.pos.y + (polygon.size.y * 0.5f),
		0.f);
	
	//�E�����W
	pVtx[3].pos = D3DXVECTOR3(
		polygon.pos.x + (polygon.size.x * 0.5f),
		polygon.pos.y + (polygon.size.y * 0.5f),
		0.f);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setListBuffer
//
//����		:	*pVtx	�ݒ肵�����摜�̃o�b�t�@�A�h���X
//				polygon	�o�b�t�@�ɐݒ肵����POLYGON�^�ϐ�
//
//�Ԃ�l	: 
//����		: �o�b�t�@�Ƀg���C�A���O�����X�g�̍��W��ݒ�
//////////////////////////////////////////////////////////////////////////////
void setListBuffer ( VERTEX_2D *pVtx, POLYGON polygon )
{
	//������W
	pVtx[0].pos = D3DXVECTOR3(
		polygon.pos.x - (polygon.size.x * 0.5f),
		polygon.pos.y - (polygon.size.y * 0.5f),
		0.f);
	
	//�E����W
	pVtx[1].pos = D3DXVECTOR3(
		polygon.pos.x + (polygon.size.x * 0.5f),
		polygon.pos.y - (polygon.size.y * 0.5f),
		0.f);

	//�������W
	pVtx[2].pos = D3DXVECTOR3(
		polygon.pos.x - (polygon.size.x * 0.5f),
		polygon.pos.y + (polygon.size.y * 0.5f),
		0.f);

	//�E����W
	pVtx[3].pos = D3DXVECTOR3(
		polygon.pos.x + (polygon.size.x * 0.5f),
		polygon.pos.y - (polygon.size.y * 0.5f),
		0.f);

	//�E�����W
	pVtx[4].pos = D3DXVECTOR3(
		polygon.pos.x + (polygon.size.x * 0.5f),
		polygon.pos.y + (polygon.size.y * 0.5f),
		0.f);

	//�������W
	pVtx[5].pos = D3DXVECTOR3(
		polygon.pos.x - (polygon.size.x * 0.5f),
		polygon.pos.y + (polygon.size.y * 0.5f),
		0.f);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setRotBuffer
//
//����		:	*pVtx	�ݒ肵�����摜�̃o�b�t�@�A�h���X
//				polygon	�o�b�t�@�ɐݒ肵������]�摜
//
//�Ԃ�l	: 
//����		: �o�b�t�@�ɉ�]���W��ݒ�
//////////////////////////////////////////////////////////////////////////////
void setRotBuffer ( VERTEX_2D *pVtx, ROTPOLYGON polygon )
{
	//������W
	pVtx[0].pos = D3DXVECTOR3(
		-cos(polygon.rot + polygon.angle) * polygon.length + polygon.conf.pos.x,
		-sin(polygon.rot + polygon.angle) * polygon.length + polygon.conf.pos.y,
		0.0f);

	//�E����W
	pVtx[1].pos = D3DXVECTOR3(
		cos(polygon.rot - polygon.angle) * polygon.length + polygon.conf.pos.x,
		sin(polygon.rot - polygon.angle) * polygon.length + polygon.conf.pos.y,
		0.0f);

	//�������W
	pVtx[2].pos = D3DXVECTOR3(
		-cos(polygon.rot - polygon.angle) * polygon.length + polygon.conf.pos.x,
		-sin(polygon.rot - polygon.angle) * polygon.length + polygon.conf.pos.y,
		0.0f);

	//�E�����W
	pVtx[3].pos = D3DXVECTOR3(
		cos(polygon.rot + polygon.angle) * polygon.length + polygon.conf.pos.x,
		sin(polygon.rot + polygon.angle) * polygon.length + polygon.conf.pos.y,
		0.0f);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setDegenerate
//�Ԃ�l	: 
//����		: �k�ރ|���S���ݒ�
//////////////////////////////////////////////////////////////////////////////
void setDegenerate ( VERTEX_2D *pVtx, D3DXVECTOR3 pos, D3DXVECTOR3 nextPos )
{
	//�k�ރ|���S���ݒ�
	pVtx[4].pos = D3DXVECTOR3(
		pos.x,
		pos.y,
		0.f);

	pVtx[5].pos = D3DXVECTOR3(
		nextPos.x,
		nextPos.y,
		0.f);
}