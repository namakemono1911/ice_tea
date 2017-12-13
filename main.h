//////////////////////////////
//�w�b�_�[
/////////////////////////////
#ifndef _MAIN_H_

#define _MAIN_H_

#include <Windows.h>
#include <d3dx9.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include <stdio.h>
#include <string.h>

//���C�u�����̃����N
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")		//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")

//�E�B���h�E�T�C�Y
#define SCREEN_WIDTH (800)					//�E�B���h��
#define SCREEN_HEIGHT (600)					//�E�B���h����

#define NUM_VERTEX (4)		//���_��
#define NUM_POLYGON (2)		//�|���S����

//�|���S����
//���_�t�H�[�}�b�g
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//���W�ϊ��ςݒ��_���W | ���_�J���[

//���_���\����(��̒��_�t�H�[�}�b�g�ƍ��킹��)
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR color;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//��ʑJ��
typedef enum
{
	MODE_TITLE,
	MODE_SELECT,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX,
}MODE;

//�_�C���N�g�RD�f�o�C�X�̎擾
LPDIRECT3DDEVICE9 GetDevice(void);
//��ʑJ��
void SetMode(MODE mode);
MODE GetMode(void);
#endif