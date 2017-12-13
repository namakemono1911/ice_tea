/*==============================================================================

     [Crystal.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ��Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//�w�b�_�[
////////////////////////////////////
#include "main.h"
#include "crystal.h"
#include "input.h"
#include "ton.h"
#include <math.h>

#define CrystalMAX (1)				//�e�̍ő�
//05/27 texture
#define Crystal_TEXTURENAMCUT "data/TEXTURE/koorisenpai.png"

//////////////////////////////////
//�v���g�^�C�v
/////////////////////////////////
HRESULT MakeVertexCrystal(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////////
//�O���[�o��
/////////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//���_���i�[�p�z��
LPDIRECT3DTEXTURE9 g_pTextureCrystal = NULL;	//�e�N�X�`���|�C���^�t�F�[�X�ւ̃|�C���^�[
//0603 ���_�p�b�t�@�Ǘ��C���^�[�t�F�[�X�|�C���^��錾����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferCrystal = NULL;
//crystal
CRYSTAL g_Crystal[CrystalMAX];
//�A�ŃJ�E���g
int g_Crystal_tapCount = 0;
//�Ђъ���J�E���g
int g_Crystal_tapCount2 = 0;
//�j��t���O
bool g_CrystalBreak = false;
//�I���J�E���g
int g_Crystal_tapCount3 = 0;

////////////////////////////////
//����������
////////////////////////////////
HRESULT InitCrystal(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�G���[, �e�N�X�`���̓ǂݍ���
	if(FAILED(D3DXCreateTextureFromFile(pDevice,Crystal_TEXTURENAMCUT,&g_pTextureCrystal)))
	{
		MessageBox(NULL,"dekinai","�I�����b�Z�[�W",MB_YESNO | MB_DEFBUTTON1);
	}

	//���_�̍쐬����
	if(FAILED(MakeVertexCrystal(pDevice)))
	{
		return E_FAIL;
	}

	for(int i = 0; i < CrystalMAX ; i ++)
	{
		g_Crystal[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Crystal[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Crystal[i].nTypeCrystal = 0;
		g_Crystal[i].fSpeed = 0;
		g_Crystal[i].nLife = 0;
		g_Crystal[i].bUse = false;

	}
	//�A�ŃJ�E���g
	g_Crystal_tapCount = 0;
	//�Ђъ���J�E���g
	g_Crystal_tapCount2 = 0;
	//�j��t���O
	g_CrystalBreak = false;
	//�I���J�E���g
	g_Crystal_tapCount3 = 0;
	//�Z�b�g
	SetCrystal(270.0f, 30.0f, 230.0f, 300.0f, 0.0f);
	return S_OK;
}

//////////////////////////////////
//�I������
//////////////////////////////////
void UninitCrystal(void)
{
	for(int i = 0; i < CrystalMAX ; i ++)
	{
		g_Crystal[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Crystal[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Crystal[i].nTypeCrystal = 0;
		g_Crystal[i].fSpeed = 0;
		g_Crystal[i].nLife = 0;
		g_Crystal[i].bUse = false;
	}

	if(g_pTextureCrystal != NULL)
	{
		g_pTextureCrystal->Release();			//�e�N�X�`���C���^�[�t�F�[�X�̉��
		g_pTextureCrystal = NULL;
	}

	if(g_pVtxBufferCrystal != NULL)
	{
		g_pVtxBufferCrystal->Release();			//���C�N���@�[�e�b�N�X
		g_pVtxBufferCrystal = NULL;
	}
	//�A�ŃJ�E���g
	g_Crystal_tapCount = 0;
	//�Ђъ���J�E���g
	g_Crystal_tapCount2 = 0;
	//�j��t���O
	g_CrystalBreak = false;
	//�I���J�E���g
	g_Crystal_tapCount3 = 0;
}

//////////////////////////////////
//�X�V����
//////////////////////////////////
void UpdateCrystal(void)
{
	VERTEX_2D* pVtx = NULL;

	for(int i = 0; i < CrystalMAX; i ++)
	{
		if(g_Crystal[i].bUse == true)
		{
			g_pVtxBufferCrystal->Lock(0,0,(void**)&pVtx,0);
			
			pVtx += NUM_VERTEX * i;
			
			pVtx[0].pos = D3DXVECTOR3(g_Crystal[i].pos.x, g_Crystal[i].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Crystal[i].pos.x + g_Crystal[i].size.x, g_Crystal[i].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Crystal[i].pos.x, g_Crystal[i].pos.y + g_Crystal[i].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Crystal[i].pos.x + g_Crystal[i].size.x, g_Crystal[i].pos.y+ g_Crystal[i].size.y, 0.0f);
		
			//�Ђъ���J�E���g�����l
			if( g_Crystal_tapCount2 == 10)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f,1.0f);
			}
			//�Ђъ���J�E���g�����l
			if( g_Crystal_tapCount2 == 20)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.25f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.25f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f,1.0f);
			}
			//�Ђъ���J�E���g�����l
			if( g_Crystal_tapCount2 == 30)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.5f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.75f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.5f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.75f,1.0f);
			}
			//�Ђъ���J�E���g�����l
			if( g_Crystal_tapCount2 == 40)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.75f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.75f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);
			}
			//�Ђъ���J�E���g�����l
			if( g_Crystal_tapCount2 == 50)
			{
				for(int i = 0; i < CrystalMAX ; i ++)
				{
					g_Crystal[i].bUse = false;
				}
			}
			//�A�����b�N
 			g_pVtxBufferCrystal->Unlock();
		}
		if(g_Crystal_tapCount >= 5)
		{
			//�J�E���g���Z�b�g
			g_Crystal_tapCount = 0;
			//���ЃZ�b�g
			setTon	( D3DXVECTOR3(320.0f, 300.0f, 0.0f) );
			setTon	( D3DXVECTOR3 (460.0f, 250.0f, 0.0f));
			setTon	( D3DXVECTOR3 (430.0f, 320.0f, 0.0f) );

		//	SetBullet(150.0f, 300.0f, 50.0f, 50.0f, 0.0f);
			//���ЃZ�b�g
		//	SetBullet(350.0f, 300.0f, 50.0f, 50.0f, 0.0f);
			//���ЃZ�b�g
		//	SetBullet(450.0f, 300.0f, 50.0f, 50.0f, 0.0f);
		}
	}
	// �v���C���[�̃L�[���� /////////////////////
	if( ( GetKeyboardTrigger( DIK_SPACE ) ))
	{
		//�J�E���g
		g_Crystal_tapCount2 += 1;
		g_Crystal_tapCount +=1;
	}
	//���U���g��
	if( g_Crystal_tapCount2 == 50)
	{
		//�j��t���O
		g_CrystalBreak = true;
	}
	if( g_CrystalBreak == true)
	{
		//�I���J�E���g
		g_Crystal_tapCount3 += 1;
		if(g_Crystal_tapCount3 == 180)//3�b�o��
		{
		
			SetMode(MODE_RESULT);
		}
	}
}

//////////////////////////////////
//�`�揈��
//////////////////////////////////
void DrawCrystal(void)
{
	int j = 0;
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//0607 �p�C�v���C��
	pDevice->SetStreamSource(0,g_pVtxBufferCrystal,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);
	//05/27
	pDevice->SetTexture(0,g_pTextureCrystal);		//�e�N�X�`���̐ݒ�

	//�v���~�e�B�u�̕`��
//	g_pD3Device->DrawPrimitiveUP(		D3DPT_TRIANGLELIST,NUM_Crystal,&g_aVertex[0],sizeof(VERTEX_2D));
	//�v���~�e�B�u�̎��   //�v���~�e�B�u�̐�   //���_�f�[�^�̐擪�A�h���X   //���_�f�[�^�P�����̃T�C�Y
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_Crystal,&g_aVertex[0],sizeof(VERTEX_2D));
	//0607
	for(int i = 0; i < CrystalMAX * 4; i += 4 , j++)
	{
		if(g_Crystal[j].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
											i,	//�I�t�Z�b�g�i���_���j
											NUM_POLYGON);//�v���~�e�B�u��
		}
	}
}

//////////////////////////////////
//���_�̍쐬
//////////////////////////////////
HRESULT MakeVertexCrystal(LPDIRECT3DDEVICE9 pDevice)  //void�ς���
{
	//0603 ���_�o�b�t�@
	//�h��G���[�`�F�b�N����return E_FALL   hresult�^
	if(FAILED(	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * CrystalMAX,		//�쐬���������_�o�b�t�@�̃T�C�Y�i�P���_�T�C�Y�����_��
								D3DUSAGE_WRITEONLY,					//�g�p�@�@�i�������݂̂�
								FVF_VERTEX_2D,						//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,					//�������Ǘ����@�i�f�o�C�X�ɂ��܂���
								&g_pVtxBufferCrystal,				//								�h�肠�Ƃ�����������I�I
								NULL)))
	{
		return E_FAIL;
	}
	//�G���[����Ȃ�������
	VERTEX_2D* pVtx;			//���z�A�h���X�p�̃|�C���^

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferCrystal->Lock(0,0,(void**)&pVtx,0);

	for(int i = 0; i < CrystalMAX; i++)
	{
		//���_���W�̐ݒ�(2D���W �E���)
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f , 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f , 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f , 0.0f , 0.0f);
	
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
		pVtx[1].tex = D3DXVECTOR2(0.25f,0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f,1.0f);

		pVtx += NUM_VERTEX;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBufferCrystal->Unlock();

	return S_OK;
}

//******************************************************************************
// �ݒ菈���֐�
//******************************************************************************
void SetCrystal(float x, float y, float w, float h, float fSpeed)
{
	int nCuntCrystal;

	for(nCuntCrystal = 0; nCuntCrystal < CrystalMAX; nCuntCrystal ++)
	{
		if(g_Crystal[nCuntCrystal].bUse == false)
		{
			g_Crystal[nCuntCrystal].pos = D3DXVECTOR3(x,y,0.0f);
			g_Crystal[nCuntCrystal].size = D3DXVECTOR2(w,h);
			g_Crystal[nCuntCrystal].fSpeed = fSpeed;
			g_Crystal[nCuntCrystal].nLife = 10;
			g_Crystal[nCuntCrystal].bUse = true;
			break;
		}
	}
}
//******************************************************************************
// �e���擾�֐�
//******************************************************************************
CRYSTAL *GetCrystal(void)
{
	return &g_Crystal[0];
}