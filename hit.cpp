/*****************************************************************************
hit.cpp
Aythor	: ���@��
Data	: 2016_07_23
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "input.h"
#include "hit.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	PLAYER1 = 0,
	PLAYER2,
	PLAYER_MAX
}HIT_PLAYER;

typedef enum
{
	CAR1 = 0,
	CAR2,
	ENEMY_MAX
}HIT_ENEMY;

typedef enum
{
	MAP1 = 0,
	MAP_MAX
}HIT_MAP;

typedef struct
{
	POLYGON			conf;		//�����蔻��R���t�B�O
}HITBOX;

HITBOX hitBox;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
#ifdef	_DEBUG	//�����[�X���`��͍s��Ȃ��̂Ŗ�����
HRESULT makeVertexhitView ( LPDIRECT3DDEVICE9 pDevice );
#endif

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
#ifdef	_DEBUG	//�����[�X���`��͍s��Ȃ��̂Ŗ�����
LPDIRECT3DTEXTURE9	g_pTexturehitView = NULL;	//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferhitView = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
#endif

//////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
int	numHitBox = 0;		//�q�b�g�{�b�N�X�̐�

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	HitCheck
//�Ԃ�l	:	true	������L
//				false	�����薳
//����		:	�摜���m���Փ˂������̔���
//////////////////////////////////////////////////////////////////////////////
bool HitCheck ( POLYGON hitBox1, POLYGON hitBox2 )
{
	if(hitBox1.size.x > hitBox2.size.x)
	{
		if(	(hitBox1.pos.x - (hitBox1.size.x * 0.5f) < hitBox2.pos.x - (hitBox2.size.x * 0.5f) &&
			hitBox1.pos.x + (hitBox1.size.x * 0.5f) > hitBox2.pos.x - (hitBox2.size.x * 0.5f)) ||
			(hitBox1.pos.x - (hitBox1.size.x * 0.5f) < hitBox2.pos.x + (hitBox2.size.x * 0.5f) &&
			hitBox1.pos.x + (hitBox1.size.x * 0.5f) > hitBox2.pos.x + (hitBox2.size.x * 0.5f)))
		{
			if(hitBox1.size.y > hitBox2.size.y)
			{
				if(	(hitBox1.pos.y - (hitBox1.size.y * 0.5f) < hitBox2.pos.y - (hitBox2.size.y * 0.5f) &&
				hitBox1.pos.y + (hitBox1.size.y * 0.5f) > hitBox2.pos.y - (hitBox2.size.y * 0.5f)) ||
				(hitBox1.pos.y - (hitBox1.size.y * 0.5f) < hitBox2.pos.y + (hitBox2.size.y * 0.5f) &&
				hitBox1.pos.y + (hitBox1.size.y * 0.5f) > hitBox2.pos.y + (hitBox2.size.y * 0.5f)))
				{
					return true;
				}
			}
			else
			{
				if(	(hitBox2.pos.y - (hitBox2.size.y * 0.5f) < hitBox1.pos.y - (hitBox1.size.y * 0.5f) &&
				hitBox2.pos.y + (hitBox2.size.y * 0.5f) > hitBox1.pos.y - (hitBox1.size.y * 0.5f)) ||
				(hitBox2.pos.y - (hitBox2.size.y * 0.5f) < hitBox1.pos.y + (hitBox1.size.y * 0.5f) &&
				hitBox2.pos.y + (hitBox2.size.y * 0.5f) > hitBox1.pos.y + (hitBox1.size.y * 0.5f)))
				{
					return true;
				}
			}
		}
	}
	else
	{
		if(	(hitBox2.pos.x - (hitBox2.size.x * 0.5f) < hitBox1.pos.x - (hitBox1.size.x * 0.5f) &&
			hitBox2.pos.x + (hitBox2.size.x * 0.5f) > hitBox1.pos.x - (hitBox1.size.x * 0.5f)) ||
			(hitBox2.pos.x - (hitBox2.size.x * 0.5f) < hitBox1.pos.x + (hitBox1.size.x * 0.5f) &&
			hitBox2.pos.x + (hitBox2.size.x * 0.5f) > hitBox1.pos.x + (hitBox1.size.x * 0.5f)))
		{
			if(hitBox1.size.y > hitBox2.size.y)
			{
				if(	(hitBox1.pos.y - (hitBox1.size.y * 0.5f) < hitBox2.pos.y - (hitBox2.size.y * 0.5f) &&
				hitBox1.pos.y + (hitBox1.size.y * 0.5f) > hitBox2.pos.y - (hitBox2.size.y * 0.5f)) ||
				(hitBox1.pos.y - (hitBox1.size.y * 0.5f) < hitBox2.pos.y + (hitBox2.size.y * 0.5f) &&
				hitBox1.pos.y + (hitBox1.size.y * 0.5f) > hitBox2.pos.y + (hitBox2.size.y * 0.5f)))
				{
					return true;
				}
			}
			else
			{
				if(	(hitBox2.pos.y - (hitBox2.size.y * 0.5f) < hitBox1.pos.y - (hitBox1.size.y * 0.5f) &&
				hitBox2.pos.y + (hitBox2.size.y * 0.5f) > hitBox1.pos.y - (hitBox1.size.y * 0.5f)) ||
				(hitBox2.pos.y - (hitBox2.size.y * 0.5f) < hitBox1.pos.y + (hitBox1.size.y * 0.5f) &&
				hitBox2.pos.y + (hitBox2.size.y * 0.5f) > hitBox1.pos.y + (hitBox1.size.y * 0.5f)))
				{
					return true;
				}
			}
		}
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	setNumHitBox
//�Ԃ�l	:	
//����		:	�q�b�g�{�b�N�X��������
//////////////////////////////////////////////////////////////////////////////
void setNumHitBox ( int num )
{
	numHitBox += num;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	:	getNumHitBox
//�Ԃ�l	:	numHitBox
//����		:	�q�b�g�{�b�N�X�����̒l��Ԃ�
//////////////////////////////////////////////////////////////////////////////
int getNumHitBox ( void )
{
	return numHitBox;
}