/*****************************************************************************
ton.cpp
Aythor	: ���@��
Data	: 2016_08_30
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "ton.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define TON_POS_X			(SCREEN_WIDTH * 0.5f)	//�|���S���̕\���ʒuX
#define TON_POS_Y			(SCREEN_HEIGHT * 0.5f)	//�|���S���̕\���ʒuY

#define TON_WIDTH			(30)					//�|���S���̕�
#define TON_HEIGHT			(30)					//�|���S���̍���

#define	MAX_TON				(100)					//�������E���x��

#define TEXTURE_WIDTH		(1.0f)					//�e�N�X�`������̕�
#define TEXTURE_HEIGHT		(1.0f)					//�e�N�X�`������̍���

#define FALL_SPEED			(0.98f)					//�������x

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef	enum
{
	ICE01 = 0,
	ICE02,
	ICE03,
	ICE_MAX
}TON_TYPE;

typedef	struct
{
	ROTPOLYGON	conf;		//TON�̒��S���W�Ƃ�����Ȃ�
	TON_TYPE	type;		//TON�̃^�C�v
	bool		alive;		//true�Ő����Ă�؋�����I
}TON;


TON			ton[MAX_TON];	//TON�̊e��ݒ�
TON_TYPE	tonType;		//TON�̃^�C�v

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT		makeVertexTon	( LPDIRECT3DDEVICE9 pDevice );
D3DXVECTOR3	invisibleTon	( void );

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9		g_pTextureTon[ICE_MAX]	= {};		//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTon = NULL;		//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
char	*tonTexAdd[] =
{
	"data/TEXTURE/ice01.png",
	"data/TEXTURE/ice02.png",
	"data/TEXTURE/ice03.png"
};

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: initTon
// �Ԃ�l	:
// ����		: �������͐�y�܂����ł���I
//////////////////////////////////////////////////////////////////////////////
void	initTon	( void )
{
	//�ϐ��錾
	int		i;		//loop
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�|�C���^�擾

	//�f�o�C�X�擾
	makeVertexTon(pDevice);

	//�|���S��������
	for( i = 0; i < MAX_TON; i++ )
	{
		initRotPolygon(&ton[i].conf,
			invisibleTon(),
			D3DXVECTOR3(TON_WIDTH, TON_HEIGHT, 0.f));
		ton[i].alive = false;
	}

	//�e�N�X�`���̓ǂݍ���
	for(i = 0; i < ICE_MAX; i++)
	{
		if(FAILED(D3DXCreateTextureFromFile(pDevice, tonTexAdd[i], &g_pTextureTon[i])))
		{
			MessageBox(NULL, "ton", "�G���[", MB_OK);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: uninitTon
// �Ԃ�l	:
// ����		: �I�������͐�y�܂����ł���I
//////////////////////////////////////////////////////////////////////////////
void	uninitTon	( void )
{
	//�ϐ��錾
	int		i;		//loop

	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	for(i = 0; i < ICE_MAX; i++)
	{
		if(g_pTextureTon[i] != NULL)
		{
			g_pTextureTon[i]->Release();
			g_pTextureTon[i] = NULL;
		}
	}

	//���_�o�b�t�@�Ǘ��̉��
	if(g_pVtxBufferTon != NULL)
	{
		g_pVtxBufferTon->Release();
		g_pVtxBufferTon = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: updateTon
// �Ԃ�l	:
// ����		: �X�V�����͐�y�܂����ł���I
//////////////////////////////////////////////////////////////////////////////
void	updateTon	( void )
{
	//�ϐ��錾
	int		i;		//loop
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�|�C���^�擾
	VERTEX_2D	*pVtx = NULL;

	//--------------------------------------
	//���W�X�V
	//--------------------------------------
	//true�̕X�𗎉�������
	for(i = 0; i < MAX_TON; i++)
	{
		if(ton[i].alive == true)
		{
			//���ȏ㗎�����Ă�����False
			if(ton[i].conf.conf.pos.y >= SCREEN_HEIGHT + TON_HEIGHT)
			{
				ton[i].conf.conf.pos = invisibleTon();
				ton[i].alive = false;
			}

			ton[i].conf.conf.pos.y += FALL_SPEED;
		}
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferTon->Lock(0, 0, (void**)&pVtx, 0);

	//�o�b�t�@�ɍ��W�o�^
	for(i = 0; i < MAX_TON; i++)
	{
		setRotBuffer(pVtx, ton[i].conf);

		if(i < MAX_TON - 1)
		{
			setDegenerate(pVtx, ton[i].conf.conf.pos, ton[i + 1].conf.conf.pos);
		}

		pVtx += NUM_VERTEX + 2;
	}

	//�o�b�t�@�A�����b�N
	g_pVtxBufferTon->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
// �ϐ���	: drawTon
// �Ԃ�l	:
// ����		: �`�揈���͐�y�܂����ł���I
//////////////////////////////////////////////////////////////////////////////
void	drawTon	( void )
{
	//�ϐ��錾
	int		i;		//loop
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferTon, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	//�|���S���̕`��
	for(i = 0; i < MAX_TON; i++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0,g_pTextureTon[ton[i].type]);

		pDevice->DrawPrimitive
			(
			D3DPT_TRIANGLESTRIP,		//�|���S���̎��
			i * (NUM_VERTEX + 2),		//�I�t�Z�b�g(���_��)
			NUM_POLYGON * MAX_TON * 2	//�|���S���̐�
			);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexTon
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexTon ( LPDIRECT3DDEVICE9 pDevice )
{
	//�ϐ��錾
	int		i;		//loop
	VERTEX_2D	*pVtx = NULL;;		//���z�A�h���X�p�|�C���^

	//���_�o�b�t�@�̐ݒ�
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX_2D) * (NUM_VERTEX + 2) * MAX_TON,	//���_�o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,				//���_�o�b�t�@�̎g�p���@
			FVF_VERTEX_2D,					//
			D3DPOOL_MANAGED,				//�������Ǘ����@
			&g_pVtxBufferTon,				//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferTon->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < MAX_TON; i++)
	{
		//���_���W�̐ݒ�(2D���W�E�E���)
		pVtx[0].pos = D3DXVECTOR3(TON_POS_X, TON_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TON_WIDTH, TON_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TON_POS_X, TON_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TON_WIDTH, TON_HEIGHT, 0.0f);

		//rhw�̐ݒ�(�K��1.0f)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0~155�̐����l)
		pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	
		//�e�N�X�`�����_���W�̐ݒ�(0~1)
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�|�C���^�ړ�
		pVtx += NUM_VERTEX;
	}
	//���̂�����A�[�����b�N��
	g_pVtxBufferTon->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: invisibleTon
//�Ԃ�l	: 
//����		: TON�������Ȃ�����
//////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3	invisibleTon	( void )
{
	return D3DXVECTOR3(
		SCREEN_WIDTH + TON_WIDTH,
		SCREEN_HEIGHT + TON_HEIGHT,
		0.f);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: visibleTon
//�Ԃ�l	: 
//����		: TON��������悤�ɂ���
//////////////////////////////////////////////////////////////////////////////
void	visibleTon	( TON *ton, D3DXVECTOR3 pos )
{
	ton->conf.conf.pos = pos;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setTon
//�Ԃ�l	: 
//����		: TON�𒲋�����
//////////////////////////////////////////////////////////////////////////////
void	setTon	( D3DXVECTOR3 pos )
{
	//�ϐ��錾
	int		i;		//loop

	for(i = 0; i < MAX_TON; i++)
	{
		if(ton[i].alive == false)
		{
			ton[i].conf.conf.pos = pos;
			ton[i].alive = true;
			break;
		}
	}
}