/*==============================================================================

     [main.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ��Update : 2016/6/28
  
==============================================================================*/

/////////////////////////////
//�w�b�_�[
/////////////////////////////
#include "main.h"
#include "polygon.h"
#include "bg.h"
#include "input.h"
#include "fade.h"
#include "title.h"
#include "select.h"
#include "game.h"
#include "result.h"
#include "Icetea.h"
#include "ton.h"
#include "hit.h"

/////////////////////////////
//�萔��`
/////////////////////////////
#define CLASS_NAME "�T���v��"				//�E�B���h�N���X�̂Ȃ܂�
#define WINDOW_NAME "�E�B���h�E�\������"	//�E�B���h�E�̂Ȃ܂�

/////////////////////////////
//�v���g�^�C�v
/////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
//FPS
#ifdef _DEBUG
void DrawFPS(void);
#endif
//05/20
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWndow);
//05/24
void Uninit(void);
void Update(void);
void Draw(void);

/////////////////////////////
//�O���[�o��
/////////////////////////////
//05/20
LPDIRECT3D9 g_pD3D = NULL;				//Direct3D�C���^�[�t�F�[�X�i�|�C���^�j
LPDIRECT3DDEVICE9 g_pD3Device= NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
int g_nCountFPS = 0;	//FPS�J�E���^
POINT mousePos;			//�}�E�X
#ifdef _DEBUG
LPD3DXFONT g_pFont = NULL;				//�t�H���g�ւ̃C���^�[�t�F�[�X
#endif	//_DEBUG

//��ʑJ�ڂŎg��
MODE g_mode = MODE_TITLE;				//�f�o�b�N�ő��̂Ƃ��납��g�����

/////////////////////////////
//winmain
/////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//UNREFERENCED_PARAMETER(hinstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	//UNREFERENCED_PARAMETER(nCmdShow);

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.cbWndExtra = 0;		//�ʏ�͎g�p���Ȃ��̂łO
	wcex.cbClsExtra = 0;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = CLASS_NAME;	//�E�B���h�N���X�̖��O
	wcex.lpszMenuName = NULL;
	wcex.style = CS_CLASSDC;		//�\������E�B���h�E�̃X�^�C����ݒ�

	//�E�B���h�E�v���V�[�W���̃A�h���X�i�֐����j���w��
	//�A�C�R���w��
	//�}�E�X�J�[�\���w��
	//�E�B���h�E�̃N���C�A���g�̈�̔w�i�F�ݒ�

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	HWND hWnd;
	MSG msg;

	//0607 ����
	DWORD dwFrameCount;
	DWORD dwCurrentTime;		//���̃^�C��
	DWORD dwExecLastTime;		//���s�I�����̃^�C��
	DWORD dwFPSLastTime;

	//�E�B���h�E�T�C�Y 05/13
	RECT cr = {
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
	};

	AdjustWindowRect (&cr,WS_OVERLAPPEDWINDOW,FALSE);

	int ww = cr.right-cr.left;
	int wh = cr.bottom-cr.top;

	//05/17 �����ɃE�B���h�E
	RECT dr = {
		0,0,SCREEN_WIDTH, SCREEN_HEIGHT
	};

	GetWindowRect(GetDesktopWindow(),&dr);

	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;
	int wx = ww > dw?0 : (dw - ww)/2 ;
	int wy = wh > dh?0 : (dh - wh)/2;

	//�E�B���h�E�쐬
	hWnd = CreateWindowEx(0,		//�g���E�B���h�E�X�^�C��
		CLASS_NAME,					//�E�B���g�E�N���X�̖��O
		WINDOW_NAME,				//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW &~ (WS_MAXIMIZEBOX | WS_THICKFRAME),		//�E�B���h�E�X�^�C���i��؁j
		//WS_POPUPWINDOW,
		wx,							//�E�B���h�E�̍��゘���W
		wy,							//�E�B���h�E�̍��゙���W
		ww,							//�E�B���h�E�̕�
		wh,							//�E�B���h�E�̍���
		NULL,						//�e�E�B���h�E�̃n���h���i�|�C���^�j
		NULL,						//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,					//�C���X�^���X�n���h��
		NULL);						//�E�B���h�E�쐬�f�[�^

	//�E�B���h�E�̕\��
	ShowWindow(hWnd,nCmdShow);		//�w�肳�ꂽ
	UpdateWindow(hWnd);				//�E�B���h�E

	//0607 ����\��ݒ�
	timeBeginPeriod(1);
	//�e�J�E���^�[������
	dwCurrentTime = 0;
	dwFrameCount = 0;
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();		// �� �ꏏ�̎��Ԃɂ���I�I �V�X�e���������~���b�P�ʂŎ擾

	//���b�Z�[�W���[�v05/24
	//������
	Init( hInstance,  hWnd, 1);
	for(;;)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE)!=0)
		{
			if(msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();		//���݂̎��������
			if((dwCurrentTime - dwFPSLastTime) >= 500)//�������̌v�����O�D�T�b���ƂɎ��s
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;		//���ݎ��Ԃ����Z�b�g
			}
			if((dwCurrentTime - dwExecLastTime) >= (1000/60 ))		// 1�t���[������莞�Ԃ����Ă���
			{
				dwExecLastTime = dwCurrentTime;	//������������
				//DirectX�̏���
				Update();
				Draw();

				GetCursorPos(&mousePos);
				ScreenToClient(hWnd, &mousePos);
				//mousePos.x;

				dwFrameCount ++;
			}
		}
	}
	//�E�B���h�E�N���X�̓o�^����
	//��P�����@�ڃN���X��
	//��Q�����@
	//UnregisterClass(CLASS_NAME,wcex.hInstance)

	//�I��
	Uninit();

	return (int)msg.wParam;
}

/*-----------------------------------------------
	�E�B���h�E�v���V�[�W��
	�iCALLBACK�@�F�@Win32API�֐����Ăяo���Ƃ�

		��Wnd�@�F�@�E�B���h�E�̂͂�ǂ�
		uMsg�@:�@���b�Z�[�W�̎��ʎq
		wParam : ���b�Z�[�W�ŏ��̃p�����[�^
		lParam : ���b�Z�[�W2�Ԗڂ̃p�����[�^
-------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg, WPARAM wParam,LPARAM lParam)
{
	UINT nID = 0;
	//HDC hDC;
	//PAINTSTRUCT ps;

	switch(uMsg)
	{
	case WM_DESTROY:
			PostQuitMessage(0);
			break;

	case WM_CREATE:
			break;

	case WM_COMMAND:
			break;

	case WM_PAINT:
			break;

	case WM_CLOSE:
			nID = MessageBox(NULL,"�I�����܂���?","�I�����b�Z�[�W",MB_YESNO | MB_DEFBUTTON1);
			if(nID == IDNO)
			{
				return 0;
			}
			break;

	case WM_KEYDOWN:
			switch(wParam)
			{
				case (VK_ESCAPE):
					UINT nID = MessageBox(NULL,"�I�����܂���?","�I�����b�Z�[�W",MB_YESNO | MB_DEFBUTTON1);
					if(nID == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
			}
	default:
		break;
	}
	return DefWindowProc(hWnd,
	uMsg, wParam, lParam);
}

/////////////////////////////
//������
/////////////////////////////
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWndow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if( g_pD3D ==NULL )
	{
		return E_FAIL;
	}

	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃p�����[�^�[�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//0�ŏ�����

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//�ς���D24???
	d3dpp.Windowed = true;//bWindow					//WSROPUP��false��
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;/////////////////////////////////////////

	//�_�C���N�g3D�f�o�C�X�̍쐬
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp,&g_pD3Device)))
	{
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&g_pD3Device)))
		{
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&g_pD3Device)))
			{
				return E_FAIL;
			}
		}
	}
	g_pD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//�i���J�����O�ݒ�A�t���v��肪���ʁj
	//g_pD3Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		//�i�h��Ԃ��ݒ�A���C���[�t���[���ŕ`��j

	//a�u�����h
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//������
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	

	//06/03 �T���v���[�X�e�[�g ���j�A�t�B���^�����O
	g_pD3Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		//�k����
	g_pD3Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		//�g�厞
	g_pD3Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
	g_pD3Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//

	//�e�N�X�`���X�e�[�W�X�e�[�g
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	#ifdef _DEBUG
	D3DXCreateFont(g_pD3Device,
							18,//�����̍���
							0,//�����̕�
							0,
							0,//�݂��Ճ}�b�v
							FALSE,//�C�^���b�N�Z��
							SHIFTJIS_CHARSET,
							OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY,
							DEFAULT_PITCH,
							"Terminal",
							&g_pFont);
	#endif	//_DEBUG

	InitKeyboard( hInstance, hWnd);

	//��ʑJ��
	SetMode(g_mode);		//�C�j�b�g�̈�ԉ�

	return S_OK;
}

/////////////////////////////
//�I������
/////////////////////////////
void Uninit(void)
{
	if(g_pD3D != NULL)
	{
		g_pD3Device->Release();		//Direct3D�f�o�C�X�̉��
		g_pD3Device = NULL;
	}
	if(g_pD3D != NULL)
	{
		g_pD3D->Release();			//Direct3D�C���^�[�t�F�[�X�̉��
		g_pD3D = NULL;
	}

	UninitKeyboard();


	#ifdef _DEBUG
	if(g_pFont != NULL)
	{
		g_pFont->Release();			//�t�H���g�̉��
		g_pFont = NULL;
	}

	#endif	//_DEBUG
}

/////////////////////////////
//�X�V����
/////////////////////////////
void Update(void)
{
	//�X�V����
	switch(g_mode)
	{
	case MODE_TITLE:
			UpdateTitle();		//����������Ă��Ȃ��Ă����S�Ɏ��s�ł���悤�Ɏ�������
		break;

	case MODE_SELECT:
			UpdateSelect();
		break;

	case MODE_GAME:
			UpdateGame();
		break;

	case MODE_RESULT:
			UpdateResult();
		break;

	default:
		break;
	}
	UpdateKeyboard();
}

/////////////////////////////
//�`�揈��
/////////////////////////////
void Draw(void)
{
	//��ʁi�o�b�N�o�b�t�@�j�^�[�Q�b�g�̓J���[
	g_pD3Device->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(255,0,255,255), 1.0f, 0);

	//�`��̊J�n
	if(SUCCEEDED(g_pD3Device->BeginScene()))
	{
		//�`�揈��
		switch(g_mode)
		{
		case MODE_TITLE:
				DrawTitle();		//����������Ă��Ȃ��Ă����S�Ɏ��s�ł���悤�Ɏ�������
			break;

		case MODE_SELECT:
				DrawSelect();
			break;

		case MODE_GAME:
				DrawGame();
			break;
	
		case MODE_RESULT:
				DrawResult();
			break;
	
		default:
			break;
		}

		#ifdef _DEBUG
		DrawFPS();
		#endif	//_DEBUG

		g_pD3Device->EndScene();		//�`��̏I��
	}
	g_pD3Device->Present(NULL,NULL,NULL,NULL);	//�o�b�N�o�b�t�@�Ƃ̓���ւ�
}

/////////////////////////////
//�f�d�s�֐�
/////////////////////////////
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3Device;
}

/////////////////////////////////////
//��ʑJ��SET
/////////////////////////////////////
void SetMode(MODE mode)
{
	//�I������
	switch(g_mode)
	{
	case MODE_TITLE:
			UninitTitle();		//����������Ă��Ȃ��Ă����S�Ɏ��s�ł���悤�Ɏ�������
		break;
	
	case MODE_SELECT:
			UninitSelect();
		break;

	case MODE_GAME:
			UninitGame();
		break;

	case MODE_RESULT:
			UninitResult();
		break;

	default:
		break;
	}

	//������
	switch(mode)		// g_ ����Ȃ���
	{
	case MODE_TITLE:
			InitTitle();		//����������Ă��Ȃ��Ă����S�Ɏ��s�ł���悤�Ɏ�������
		break;
	
	case MODE_SELECT:
			InitSelect();
		break;

	case MODE_GAME:
			InitGame();
		break;

	case MODE_RESULT:
			InitResult();
		break;

	default:
		break;
	}
	g_mode = mode;
}

/////////////////////////////////////
//��ʑJ��GET
/////////////////////////////////////
MODE GetMode(void)
{
	return g_mode;
}

/////////////////////////////
//�e�o�r
/////////////////////////////
#ifdef _DEBUG
void DrawFPS(void)
{
	//���g
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	char aStr[256];
	sprintf(&aStr[0],"FPS: %d\n",g_nCountFPS);
	g_pFont ->DrawText(NULL, &aStr[0], -1, &rc, DT_LEFT,D3DCOLOR_RGBA(255, 255, 0, 255));
}
#endif	//_DEBUG
