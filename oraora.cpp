/*==============================================================================

     [Oraora.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ��Update : 2016/6/28
  
==============================================================================*/

////////////////////////////////////
//�w�b�_�[
////////////////////////////////////
#include "main.h"
#include "oraora.h"
#include "input.h"
#include <math.h>

#define OraoraMAX (1)				//�e�̍ő�
//05/27 texture
#define Oraora_TEXTURENAMCUT "data/TEXTURE/oraora.png"

//////////////////////////////////
//�v���g�^�C�v
/////////////////////////////////
HRESULT MakeVertexOraora(LPDIRECT3DDEVICE9 pDevice);

/////////////////////////////////
//�O���[�o��
/////////////////////////////////
//VERTEX_2D g_aVertex [NUM_VERTEX];				//���_���i�[�p�z��
LPDIRECT3DTEXTURE9 g_pTextureOraora = NULL;	//�e�N�X�`���|�C���^�t�F�[�X�ւ̃|�C���^�[
//0603 ���_�p�b�t�@�Ǘ��C���^�[�t�F�[�X�|�C���^��錾����
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferOraora = NULL;
//Oraora
ORAORA g_Oraora[OraoraMAX];

//�A��tx�J�E���g
int g_Oraora_tx = 0;

////////////////////////////////
//����������
////////////////////////////////
HRESULT InitOraora(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�G���[, �e�N�X�`���̓ǂݍ���
	if(FAILED(D3DXCreateTextureFromFile(pDevice,Oraora_TEXTURENAMCUT,&g_pTextureOraora)))
	{
		MessageBox(NULL,"dekinai","�I�����b�Z�[�W",MB_YESNO | MB_DEFBUTTON1);
	}

	//���_�̍쐬����
	if(FAILED(MakeVertexOraora(pDevice)))
	{
		return E_FAIL;
	}

	for(int i = 0; i < OraoraMAX ; i ++)
	{
		g_Oraora[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Oraora[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Oraora[i].nTypeOraora = 0;
		g_Oraora[i].fSpeed = 0;
		g_Oraora[i].nLife = 0;
		g_Oraora[i].bUse = false;

	}
	//�A��tx�J�E���g
	g_Oraora_tx = 0;
	//�Z�b�g
	SetOraora(150.0f, 100.0f, 200.0f, 300.0f, 0.0f);
	return S_OK;
}

//////////////////////////////////
//�I������
//////////////////////////////////
void UninitOraora(void)
{
	for(int i = 0; i < OraoraMAX ; i ++)
	{
		g_Oraora[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Oraora[i].size = D3DXVECTOR2(0.0f, 0.0f);
		g_Oraora[i].nTypeOraora = 0;
		g_Oraora[i].fSpeed = 0;
		g_Oraora[i].nLife = 0;
		g_Oraora[i].bUse = false;
	}

	if(g_pTextureOraora != NULL)
	{
		g_pTextureOraora->Release();			//�e�N�X�`���C���^�[�t�F�[�X�̉��
		g_pTextureOraora = NULL;
	}

	if(g_pVtxBufferOraora != NULL)
	{
		g_pVtxBufferOraora->Release();			//���C�N���@�[�e�b�N�X
		g_pVtxBufferOraora = NULL;
	}
	//�A��tx�J�E���g
	g_Oraora_tx = 0;
}

//////////////////////////////////
//�X�V����
//////////////////////////////////
void UpdateOraora(void)
{

	VERTEX_2D* pVtx = NULL;

	for(int i = 0; i < OraoraMAX; i ++)
	{
		if(g_Oraora[i].bUse == true)
		{
			g_pVtxBufferOraora->Lock(0,0,(void**)&pVtx,0);
			
			pVtx += NUM_VERTEX * i;
			
			pVtx[0].pos = D3DXVECTOR3(g_Oraora[i].pos.x, g_Oraora[i].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Oraora[i].pos.x + g_Oraora[i].size.x, g_Oraora[i].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Oraora[i].pos.x, g_Oraora[i].pos.y + g_Oraora[i].size.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Oraora[i].pos.x + g_Oraora[i].size.x, g_Oraora[i].pos.y+ g_Oraora[i].size.y, 0.0f);
		
			//�I���I���J�E���g�����l
			if( g_Oraora_tx == 0)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.142f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.142f,1.0f);
			}
			//�I���I���J�E���g�����l
			if( g_Oraora_tx == 1)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.142f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.284f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.142f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.284f,1.0f);
			}
			//�I���I���J�E���g�����l
			if( g_Oraora_tx == 2)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.284f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.426f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.284f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.426f,1.0f);
			}
			//�I���I���J�E���g�����l
			if( g_Oraora_tx == 3)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.426f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.568f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.426f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.568f,1.0f);
			}
			//�I���I���J�E���g�����l
			if( g_Oraora_tx == 4)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.568f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.710f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.568f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.710f,1.0f);
			}
			//�I���I���J�E���g�����l
			if( g_Oraora_tx == 5)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.710f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.852f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.710f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.852f,1.0f);
			}
			//�I���I���J�E���g�����l
			if( g_Oraora_tx == 6)
			{
				//uv
				pVtx[0].tex = D3DXVECTOR2(0.852f,0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.852f,1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);
			}
			//�A�����b�N
 			g_pVtxBufferOraora->Unlock();
		}
		if(g_Oraora_tx > 6)
		{
			//�J�E���g���Z�b�g
			g_Oraora_tx = 0;
		}
	}
	// �v���C���[�̃L�[���� /////////////////////
	if( ( GetKeyboardTrigger( DIK_SPACE ) ))
	{
		//�J�E���g
		g_Oraora_tx += 1;
	}
}

//////////////////////////////////
//�`�揈��
//////////////////////////////////
void DrawOraora(void)
{
	int j = 0;
	LPDIRECT3DDEVICE9  pDevice = GetDevice();

	//0607 �p�C�v���C��
	pDevice->SetStreamSource(0,g_pVtxBufferOraora,0,sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);
	//05/27
	pDevice->SetTexture(0,g_pTextureOraora);		//�e�N�X�`���̐ݒ�

	//�v���~�e�B�u�̕`��
//	g_pD3Device->DrawPrimitiveUP(		D3DPT_TRIANGLELIST,NUM_Oraora,&g_aVertex[0],sizeof(VERTEX_2D));
	//�v���~�e�B�u�̎��   //�v���~�e�B�u�̐�   //���_�f�[�^�̐擪�A�h���X   //���_�f�[�^�P�����̃T�C�Y
	//pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,NUM_Oraora,&g_aVertex[0],sizeof(VERTEX_2D));
	//0607
	for(int i = 0; i < OraoraMAX * 4; i += 4 , j++)
	{
		if(g_Oraora[j].bUse == true)
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
HRESULT MakeVertexOraora(LPDIRECT3DDEVICE9 pDevice)  //void�ς���
{
	//0603 ���_�o�b�t�@
	//�h��G���[�`�F�b�N����return E_FALL   hresult�^
	if(FAILED(	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX * OraoraMAX,		//�쐬���������_�o�b�t�@�̃T�C�Y�i�P���_�T�C�Y�����_��
								D3DUSAGE_WRITEONLY,					//�g�p�@�@�i�������݂̂�
								FVF_VERTEX_2D,						//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,					//�������Ǘ����@�i�f�o�C�X�ɂ��܂���
								&g_pVtxBufferOraora,				//								�h�肠�Ƃ�����������I�I
								NULL)))
	{
		return E_FAIL;
	}
	//�G���[����Ȃ�������
	VERTEX_2D* pVtx;			//���z�A�h���X�p�̃|�C���^

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferOraora->Lock(0,0,(void**)&pVtx,0);

	for(int i = 0; i < OraoraMAX; i++)
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
	g_pVtxBufferOraora->Unlock();

	return S_OK;
}

//******************************************************************************
// �ݒ菈���֐�
//******************************************************************************
void SetOraora(float x, float y, float w, float h, float fSpeed)
{
	int nCuntOraora;

	for(nCuntOraora = 0; nCuntOraora < OraoraMAX; nCuntOraora ++)
	{
		if(g_Oraora[nCuntOraora].bUse == false)
		{
			g_Oraora[nCuntOraora].pos = D3DXVECTOR3(x,y,0.0f);
			g_Oraora[nCuntOraora].size = D3DXVECTOR2(w,h);
			g_Oraora[nCuntOraora].fSpeed = fSpeed;
			g_Oraora[nCuntOraora].nLife = 10;
			g_Oraora[nCuntOraora].bUse = true;
			break;
		}
	}
}
//******************************************************************************
// �e���擾�֐�
//******************************************************************************
ORAORA *GetOraora(void)
{
	return &g_Oraora[0];
}