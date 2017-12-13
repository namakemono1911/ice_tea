/*==============================================================================

     [main.cpp]
                                                       Author : hosoyama shinchi
                                                       Date   : 2016/6/28
--------------------------------------------------------------------------------
    ■Update : 2016/6/28
  
==============================================================================*/

/////////////////////////////
//ヘッダー
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
//定数定義
/////////////////////////////
#define CLASS_NAME "サンプル"				//ウィンドクラスのなまえ
#define WINDOW_NAME "ウィンドウ表示処理"	//ウィンドウのなまえ

/////////////////////////////
//プロトタイプ
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
//グローバル
/////////////////////////////
//05/20
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dインターフェース（ポインタ）
LPDIRECT3DDEVICE9 g_pD3Device= NULL;	//Direct3Dデバイスへのポインタ
int g_nCountFPS = 0;	//FPSカウンタ
POINT mousePos;			//マウス
#ifdef _DEBUG
LPD3DXFONT g_pFont = NULL;				//フォントへのインターフェース
#endif	//_DEBUG

//画面遷移で使う
MODE g_mode = MODE_TITLE;				//デバックで他のところから使えるよ

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
	wcex.cbWndExtra = 0;		//通常は使用しないので０
	wcex.cbClsExtra = 0;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;
	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = CLASS_NAME;	//ウィンドクラスの名前
	wcex.lpszMenuName = NULL;
	wcex.style = CS_CLASSDC;		//表じするウィンドウのスタイルを設定

	//ウィンドウプロシージャのアドレス（関数名）を指定
	//アイコン指定
	//マウスカーソル指定
	//ウィンドウのクライアント領域の背景色設定

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	HWND hWnd;
	MSG msg;

	//0607 時間
	DWORD dwFrameCount;
	DWORD dwCurrentTime;		//今のタイム
	DWORD dwExecLastTime;		//実行終了時のタイム
	DWORD dwFPSLastTime;

	//ウィンドウサイズ 05/13
	RECT cr = {
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
	};

	AdjustWindowRect (&cr,WS_OVERLAPPEDWINDOW,FALSE);

	int ww = cr.right-cr.left;
	int wh = cr.bottom-cr.top;

	//05/17 中央にウィンドウ
	RECT dr = {
		0,0,SCREEN_WIDTH, SCREEN_HEIGHT
	};

	GetWindowRect(GetDesktopWindow(),&dr);

	int dw = dr.right - dr.left;
	int dh = dr.bottom - dr.top;
	int wx = ww > dw?0 : (dw - ww)/2 ;
	int wy = wh > dh?0 : (dh - wh)/2;

	//ウィンドウ作成
	hWnd = CreateWindowEx(0,		//拡張ウィンドウスタイル
		CLASS_NAME,					//ウィントウクラスの名前
		WINDOW_NAME,				//ウィンドウの名前
		WS_OVERLAPPEDWINDOW &~ (WS_MAXIMIZEBOX | WS_THICKFRAME),		//ウィンドウスタイル（大切）
		//WS_POPUPWINDOW,
		wx,							//ウィンドウの左上ｘ座標
		wy,							//ウィンドウの左上ｙ座標
		ww,							//ウィンドウの幅
		wh,							//ウィンドウの高さ
		NULL,						//親ウィンドウのハンドル（ポインタ）
		NULL,						//メニューハンドルまたは子ウィンドウID
		hInstance,					//インスタンスハンドル
		NULL);						//ウィンドウ作成データ

	//ウィンドウの表示
	ShowWindow(hWnd,nCmdShow);		//指定された
	UpdateWindow(hWnd);				//ウィンドウ

	//0607 分解能を設定
	timeBeginPeriod(1);
	//各カウンター初期化
	dwCurrentTime = 0;
	dwFrameCount = 0;
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();		// ↑ 一緒の時間にしろ！！ システム時刻をミリ秒単位で取得

	//メッセージループ05/24
	//初期化
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
			dwCurrentTime = timeGetTime();		//現在の時刻を取る
			if((dwCurrentTime - dwFPSLastTime) >= 500)//ｆｐｓの計測を０．５秒ごとに実行
			{
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;		//現在時間をリセット
			}
			if((dwCurrentTime - dwExecLastTime) >= (1000/60 ))		// 1フレームが一定時間たってたら
			{
				dwExecLastTime = dwCurrentTime;	//処理した時間
				//DirectXの処理
				Update();
				Draw();

				GetCursorPos(&mousePos);
				ScreenToClient(hWnd, &mousePos);
				//mousePos.x;

				dwFrameCount ++;
			}
		}
	}
	//ウィンドウクラスの登録解除
	//第１引数　目クラス名
	//第２引数　
	//UnregisterClass(CLASS_NAME,wcex.hInstance)

	//終了
	Uninit();

	return (int)msg.wParam;
}

/*-----------------------------------------------
	ウィンドウプロシージャ
	（CALLBACK　：　Win32API関数を呼び出すとき

		ｈWnd　：　ウィンドウのはんどる
		uMsg　:　メッセージの識別子
		wParam : メッセージ最初のパラメータ
		lParam : メッセージ2番目のパラメータ
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
			nID = MessageBox(NULL,"終了しますか?","終了メッセージ",MB_YESNO | MB_DEFBUTTON1);
			if(nID == IDNO)
			{
				return 0;
			}
			break;

	case WM_KEYDOWN:
			switch(wParam)
			{
				case (VK_ESCAPE):
					UINT nID = MessageBox(NULL,"終了しますか?","終了メッセージ",MB_YESNO | MB_DEFBUTTON1);
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
//初期化
/////////////////////////////
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWndow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if( g_pD3D ==NULL )
	{
		return E_FAIL;
	}

	if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのパラメーターの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));		//0で初期化

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//変えるD24???
	d3dpp.Windowed = true;//bWindow					//WSROPUPでfalseで
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;/////////////////////////////////////////

	//ダイレクト3Dデバイスの作成
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
	g_pD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//（裏カリング設定、逆時計回りが裏面）
	//g_pD3Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		//（塗りつぶし設定、ワイヤーフレームで描画）

	//aブレンド
	g_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);			//半透明
	g_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);			
	g_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	

	//06/03 サンプラーステート リニアフィルタリング
	g_pD3Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);		//縮小時
	g_pD3Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);		//拡大時
	g_pD3Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
	g_pD3Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	//

	//テクスチャステージステート
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	#ifdef _DEBUG
	D3DXCreateFont(g_pD3Device,
							18,//文字の高さ
							0,//文字の幅
							0,
							0,//みっぷマップ
							FALSE,//イタリック融無
							SHIFTJIS_CHARSET,
							OUT_DEFAULT_PRECIS,
							DEFAULT_QUALITY,
							DEFAULT_PITCH,
							"Terminal",
							&g_pFont);
	#endif	//_DEBUG

	InitKeyboard( hInstance, hWnd);

	//画面遷移
	SetMode(g_mode);		//イニットの一番下

	return S_OK;
}

/////////////////////////////
//終了処理
/////////////////////////////
void Uninit(void)
{
	if(g_pD3D != NULL)
	{
		g_pD3Device->Release();		//Direct3Dデバイスの解放
		g_pD3Device = NULL;
	}
	if(g_pD3D != NULL)
	{
		g_pD3D->Release();			//Direct3Dインターフェースの解放
		g_pD3D = NULL;
	}

	UninitKeyboard();


	#ifdef _DEBUG
	if(g_pFont != NULL)
	{
		g_pFont->Release();			//フォントの解放
		g_pFont = NULL;
	}

	#endif	//_DEBUG
}

/////////////////////////////
//更新処理
/////////////////////////////
void Update(void)
{
	//更新処理
	switch(g_mode)
	{
	case MODE_TITLE:
			UpdateTitle();		//初期化されていなくても安全に実行できるように実装する
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
//描画処理
/////////////////////////////
void Draw(void)
{
	//画面（バックバッファ）ターゲットはカラー
	g_pD3Device->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_RGBA(255,0,255,255), 1.0f, 0);

	//描画の開始
	if(SUCCEEDED(g_pD3Device->BeginScene()))
	{
		//描画処理
		switch(g_mode)
		{
		case MODE_TITLE:
				DrawTitle();		//初期化されていなくても安全に実行できるように実装する
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

		g_pD3Device->EndScene();		//描画の終了
	}
	g_pD3Device->Present(NULL,NULL,NULL,NULL);	//バックバッファとの入れ替え
}

/////////////////////////////
//ＧＥＴ関数
/////////////////////////////
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3Device;
}

/////////////////////////////////////
//画面遷移SET
/////////////////////////////////////
void SetMode(MODE mode)
{
	//終了処理
	switch(g_mode)
	{
	case MODE_TITLE:
			UninitTitle();		//初期化されていなくても安全に実行できるように実装する
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

	//初期化
	switch(mode)		// g_ じゃないよ
	{
	case MODE_TITLE:
			InitTitle();		//初期化されていなくても安全に実行できるように実装する
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
//画面遷移GET
/////////////////////////////////////
MODE GetMode(void)
{
	return g_mode;
}

/////////////////////////////
//ＦＰＳ
/////////////////////////////
#ifdef _DEBUG
void DrawFPS(void)
{
	//窓枠
	RECT rc = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	char aStr[256];
	sprintf(&aStr[0],"FPS: %d\n",g_nCountFPS);
	g_pFont ->DrawText(NULL, &aStr[0], -1, &rc, DT_LEFT,D3DCOLOR_RGBA(255, 255, 0, 255));
}
#endif	//_DEBUG
