/*==============================================================================

    �|���S�� [icetea.cpp]
                                                       Author : Norihiro Hayashi
                                                       Date   : 2016/05/31
--------------------------------------------------------------------------------
    ��Update : 2016/07/25

==============================================================================*/

/*******************************************************************************
* �C���N���[�h�t�@�C��
*******************************************************************************/
#include "main.h"
#include "input.h"
#include "Icetea.h"
#include "hit.h"

/*******************************************************************************
* �}�N����`
*******************************************************************************/


#define POLYGON_POS_X (200.0f)							// �|���S���̍���X���W
#define POLYGON_POS_Y (300.0f)							// �|���S���̍���Y���W
#define POLYGON_WIDTH (256.0f)							//SIZE_X �|���S���̉���
#define POLYGON_HEIGHT (256.0f)							//SIZE_Y �|���S���̍���
#define POLYGON_TEXTURENAME "data/TEXTURE/Icetea.png"	//�e�N�X�`���̖��O

#define NUM_VERTEX (4)	//���_��
#define NUM_POLYGON (2)	//�|���S����

/*******************************************************************************
* �\���̒�`
*******************************************************************************/

/*******************************************************************************
* �v���g�^�C�v�錾
*******************************************************************************/
void MakeVertexIcetea ( LPDIRECT3DDEVICE9 pDevice );

/*******************************************************************************
* �O���[�o���ϐ�
*******************************************************************************/
bool g_bflag ;				//�ړ��t���O,true�Ȃ�E��false�Ȃ獶�Ɉړ�
D3DXVECTOR2 g_posIcetea ;	//�|���S���̒��S���W
float g_rotIcetea ;			//�|���S���̉�]��(���W�A��)
float g_fLengthIcetea ;		//�|���S���̑Ίp���̒���
float g_fAngleIcetea ;		//�|���S���̑Ίp���̊p�x

//VERTEX_2D g_aVertex[NUM_VERTEX];	//���_���i�[�p�z��

LPDIRECT3DTEXTURE9 g_pTextureIcetea = NULL ;	//�e�N�X�`���[�C���^�[�t�F�[�X

//���_�o�b�t�@�Ǘ��p�C���^�[�t�F�[�X�|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferIcetea = NULL ;

void InitIcetea (void)	//����������
{
	g_bflag = false;
	g_rotIcetea  = 0;			//�|���S���̉�]��(���W�A��)
	g_fLengthIcetea = 0;		//�|���S���̑Ίp���̒���
	g_fAngleIcetea = 0;		//�|���S���̑Ίp���̊p�x


	g_posIcetea = D3DXVECTOR2( (POLYGON_POS_X + POLYGON_WIDTH *0.5 )  , (POLYGON_POS_Y +POLYGON_HEIGHT *0.5) );

	g_rotIcetea = 0.0f ;

	//�Ίp���̒����̎Z�o
	g_fLengthIcetea = sqrt ( POLYGON_WIDTH * POLYGON_WIDTH + POLYGON_HEIGHT * POLYGON_HEIGHT) / 2.0f ;

	g_fAngleIcetea = atan2( POLYGON_HEIGHT , POLYGON_WIDTH) ;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃A�h���X���擾

	MakeVertexIcetea (  pDevice );	//���_�̍쐬

	g_bflag = true ;

	//�e�N�X�`���[�̓ǂݍ���
	//FAIFED(�t�F�C���h�}�N��)�G���[�`�F�b�N
	if( FAILED( D3DXCreateTextureFromFile ( pDevice , POLYGON_TEXTURENAME , &g_pTextureIcetea ) ) )
	{
		MessageBox(NULL,"�A�C�X�e�B�[�̃e�N�X�`���ǂݍ��݃G���[","�G���[�I",MB_OK | MB_ICONQUESTION );//����
	}

//if( FAILED( D3DXCreateTextureFromFile( g_pD3DDevice , POLYGON_TEXTURENAME , &g_pTextureIcetea ) );
//	{
//		return E_FAIL;
//	}
}

void UninitIcetea (void)	//�I������
{
	if( g_pTextureIcetea != NULL )
	{
		g_pTextureIcetea -> Release();
		g_pTextureIcetea = NULL ;
	}

	if( g_pVtxBufferIcetea != NULL)
	{
		g_pVtxBufferIcetea -> Release();
		g_pVtxBufferIcetea = NULL ;
	}
	g_bflag = false;
	g_rotIcetea  = 0;			//�|���S���̉�]��(���W�A��)
	g_fLengthIcetea = 0;		//�|���S���̑Ίp���̒���
	g_fAngleIcetea = 0;		//�|���S���̑Ίp���̊p�x

}

void UpdateIcetea(void)	//�X�V����
{
	VERTEX_2D* pVtx;

	if(g_bflag == true)
	{
		g_posIcetea.x += 5.0f ;
		if(g_posIcetea.x >= 700)
		{
			g_bflag = false ;
		}
	}
	if(g_bflag == false)
	{
		g_posIcetea.x -= 5.0f ;
		if(g_posIcetea.x <= 100)
		{
			g_bflag = true ;
		}
	}

	g_pVtxBufferIcetea ->Lock( 0 , 0 , (void**)&pVtx , 0 );//���_�o�b�t�@�����b�N�����z�A�h���X���擾

	SetVertexIcetea(pVtx);

	g_pVtxBufferIcetea -> Unlock();//�A�����b�N

}

void DrawIcetea(void)	//�`�揈��
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̃A�h���X���擾

	pDevice ->SetStreamSource( 0 ,
								g_pVtxBufferIcetea ,
								0 ,//�I�t�Z�b�g(�o�C�g)
								sizeof(VERTEX_2D)/*�X�g���C�h�l*/ );

	//�|���S���̕`������鐡�O
	//�e�N�X�`���[�̐ݒ�
	pDevice -> SetTexture( 0 , g_pTextureIcetea );

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_2D);

	//�v���~�e�B�u�̕`��
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP ,	//�v���~�e�B�u�̎��
							0 ,						//�I�t�Z�b�g(���_��)
							NUM_POLYGON ) ;			//�v���~�e�B�u��

}

//���_�̍쐬
void MakeVertexIcetea ( LPDIRECT3DDEVICE9 pDevice )
{
	pDevice ->CreateVertexBuffer( sizeof(VERTEX_2D) * NUM_VERTEX , //�쐬���������_�o�b�t�@�T�C�Y
													D3DUSAGE_WRITEONLY,
													FVF_VERTEX_2D,
													D3DPOOL_MANAGED,
													&g_pVtxBufferIcetea,
													NULL);

	// FAILED�}�N��������

	VERTEX_2D* pVtx;	//���z�A�h���X�̃|�C���^

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾����
	g_pVtxBufferIcetea -> Lock( 0 , 0 , (void**)&pVtx , 0 );

	SetVertexIcetea( pVtx );

	g_pVtxBufferIcetea -> Unlock();//�A�����b�N

}
///////
//�X�V�������W�̐ݒ�
////////
void SetVertexIcetea ( VERTEX_2D *pVtx )
{

	//���_���W�̐ݒ�(2D���W�E�E���)
	pVtx[0].pos = D3DXVECTOR3(	g_posIcetea.x + cosf( g_fAngleIcetea + D3DX_PI + g_rotIcetea ) * g_fLengthIcetea ,//X
								g_posIcetea.y + sinf( g_fAngleIcetea + D3DX_PI + g_rotIcetea ) * g_fLengthIcetea ,//Y
								0.0f );
	//�E��
	pVtx[1].pos = D3DXVECTOR3(	g_posIcetea.x + cosf( - g_fAngleIcetea + g_rotIcetea) * g_fLengthIcetea ,//X
								g_posIcetea.y + sinf( - g_fAngleIcetea + g_rotIcetea) * g_fLengthIcetea ,//Y
								0.0f );
	//����
	pVtx[2].pos = D3DXVECTOR3(	g_posIcetea.x + cosf( - g_fAngleIcetea - D3DX_PI + g_rotIcetea) * g_fLengthIcetea ,//X
								g_posIcetea.y + sinf( - g_fAngleIcetea - D3DX_PI + g_rotIcetea) * g_fLengthIcetea ,//Y
								0.0f );
	//�E��
	pVtx[3].pos = D3DXVECTOR3(	g_posIcetea.x + cosf( g_fAngleIcetea + g_rotIcetea) * g_fLengthIcetea ,//X
								g_posIcetea.y + sinf( g_fAngleIcetea + g_rotIcetea) * g_fLengthIcetea ,//Y
								0.0f );
	//rhw�̐ݒ�(�K��1.0f)
	pVtx[0].rhw=1.0f ;
	pVtx[1].rhw=1.0f ;
	pVtx[2].rhw=1.0f ;
	pVtx[3].rhw=1.0f ;

	//���_�f�[�^��UV�f�[�^�̒ǉ�
	pVtx[0].tex = D3DXVECTOR2(0,0) ;
	pVtx[1].tex = D3DXVECTOR2(1,0) ;
	pVtx[2].tex = D3DXVECTOR2(0,1) ;
	pVtx[3].tex = D3DXVECTOR2(1,1) ;

	//���_�J���[�̐ݒ�(0�`255�̐����l)
	pVtx[0].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ) ;
	pVtx[1].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ) ;
	pVtx[2].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ) ;
	pVtx[3].color = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ) ;

}