#include "GraphicsPCH.h"
#include "CGame.h"

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam);

CGame::CGame()
{
}

CGame::~CGame()
{
}

int CGame::Initialize(HINSTANCE _hInstance)
{
	if (!XMVerifyCPUSupport())
	{
		MessageBox(nullptr, L"Failed to load DirectXMathLibrary", L"Error", MB_OK);
		return -1;
	}

	// Windows Fenster erstellen
	int returnValue = InitApplication(_hInstance);
	if (FAILED(returnValue))
	{
		MessageBox(nullptr, L"Failed to create Window", L"Error", MB_OK);
		return returnValue;
	}

	// DirectX initialisieren
	returnValue = InitDirectX();
	if (FAILED(returnValue))
	{
		MessageBox(nullptr, L"Failed to initialize DirectX", L"Error", MB_OK);
		return returnValue;
	}

	// DirectX initialisieren
	returnValue = InitConstantBuffers();
	if (FAILED(returnValue))
	{
		MessageBox(nullptr, L"Failed to initialize Constant Buffers", L"Error", MB_OK);
		return returnValue;
	}

	m_isRunning = true;

	return 0;
}

int CGame::Run()
{
	MSG msg = { 0 };

	static DWORD prevTime = timeGetTime();
	static const float targetFrameRate = 30.0f;
	static const float maxTimeStep = 1.0f / targetFrameRate;
	static DWORD currentTime;
	float deltaTime;

	while (m_isRunning && msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			currentTime = timeGetTime();
			deltaTime = (currentTime - prevTime) * 0.001f;		// Angabe in Sekunden

			deltaTime = std::min<float>(deltaTime, maxTimeStep);
			prevTime = currentTime;

			Update(deltaTime);
			Render();
		}
	}

	return 0;
}

void CGame::Finalize()
{
}

int CGame::InitApplication(HINSTANCE _hInstance)
{
	WNDCLASSEX wndClass = { 0 };
	//ZeroMemory(&wndClass, sizeof(WNDCLASSEX)); // oldschool weg um Speicher zu leeren

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = &WndProc;
	wndClass.hInstance = _hInstance;
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 9);
	wndClass.lpszClassName = m_windowSettings.m_WindowClassName;

	if (!RegisterClassEx(&wndClass))
	{
		return -2;
	}

	RECT windowRect = { 0,0, m_windowSettings.m_WindowWidth, m_windowSettings.m_WindowHeigth };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	m_windowSettings.m_WindowHandle = CreateWindowA(m_windowSettings.m_WindowClassNameShort,
		m_windowSettings.m_WindowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		nullptr,
		nullptr,
		_hInstance,
		nullptr);

	if (!m_windowSettings.m_WindowHandle)
	{
		return -3;
	}

	ShowWindow(m_windowSettings.m_WindowHandle, 0);
	UpdateWindow(m_windowSettings.m_WindowHandle);

	return 0;
}

int CGame::InitDirectX()
{
	RECT clientRect;
	GetClientRect(m_windowSettings.m_WindowHandle, &clientRect);

	unsigned long clientWidth = clientRect.right - clientRect.left;
	unsigned long clientHeight = clientRect.bottom - clientRect.top;

	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0 };
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = clientWidth;
	swapChainDesc.BufferDesc.Height = clientHeight;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = m_windowSettings.m_WindowHandle;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;


	unsigned int createDeviceFlags = 0;

#if _DEBUG
	createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[]
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr,
									D3D_DRIVER_TYPE_HARDWARE,
									nullptr,
									createDeviceFlags,
									featureLevels,
									_countof(featureLevels),
									D3D11_SDK_VERSION,
									&swapChainDesc,
									&m_directXSettings.m_swapChain,
									&m_directXSettings.m_device,
									&featureLevel,
									&m_directXSettings.m_deviceContext);

	if (FAILED(hr))
	{
		return -10;
	}
	
	ID3D11Texture2D* backbuffer;
	hr = m_directXSettings.m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**) &backbuffer);
	if (FAILED(hr))
	{
		return -11;
	}
	
	hr = m_directXSettings.m_device->CreateRenderTargetView(backbuffer, nullptr, &m_directXSettings.m_renderTargetView);
	if (FAILED(hr))
	{
		return -12;
	}
	
	SafeRelease(backbuffer);
	
	D3D11_TEXTURE2D_DESC depthStencilViewDesc = {0};
	depthStencilViewDesc.ArraySize = 1;
	depthStencilViewDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilViewDesc.CPUAccessFlags = 0;
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;		// 24 bit Tiefe, 8 bit Stencil
	depthStencilViewDesc.Height = clientHeight;
	depthStencilViewDesc.Width = clientWidth;
	depthStencilViewDesc.MipLevels = 1;
	depthStencilViewDesc.SampleDesc.Count = 1;
	depthStencilViewDesc.SampleDesc.Quality = 0;
	depthStencilViewDesc.Usage = D3D11_USAGE_DEFAULT;

	hr = m_directXSettings.m_device->CreateTexture2D(&depthStencilViewDesc,
													nullptr,
													&m_directXSettings.m_depthStencilBuffer);

	if (FAILED(hr))
	{
		return -13;
	}

	hr = m_directXSettings.m_device->CreateDepthStencilView(m_directXSettings.m_depthStencilBuffer,
															nullptr, 
												&m_directXSettings.m_depthStencilView);

	if (FAILED(hr))
	{
		return -14;
	}

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = { 0 };
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;		// Nahe Objekte nehmen, ferne wegwerfen
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.StencilEnable = false;

	hr = m_directXSettings.m_device->CreateDepthStencilState(&depthStencilDesc, &m_directXSettings.m_depthStencilState);
	if (FAILED(hr))
	{
		return -15;
	}

	// Rasterizer Macht Vektor zu Pixel
	D3D11_RASTERIZER_DESC rasterdesc;
	ZeroMemory(&rasterdesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterdesc.AntialiasedLineEnable = false;
	rasterdesc.FillMode = D3D11_FILL_SOLID;		// Komplette dreiecke zeigen , rumspielen!
	rasterdesc.CullMode = D3D11_CULL_BACK;		// Rückseiten wegschneiden
	rasterdesc.DepthBias = 0;
	rasterdesc.DepthBiasClamp = 0.0f;
	rasterdesc.DepthClipEnable = true;
	rasterdesc.FrontCounterClockwise = false;		// Dreieckte im Uhrzeigersinn zeigen nach vorne
	rasterdesc.MultisampleEnable = false;
	rasterdesc.ScissorEnable = false;
	rasterdesc.SlopeScaledDepthBias = 0.0f;

	hr = m_directXSettings.m_device->CreateRasterizerState(&rasterdesc, &m_directXSettings.m_rasterrizerState);
	if (FAILED(hr))
	{
		return -36;
	}

	m_directXSettings.m_viewPort.Width = clientWidth;
	m_directXSettings.m_viewPort.Height = clientHeight;
	m_directXSettings.m_viewPort.TopLeftX = 0.0f;
	m_directXSettings.m_viewPort.TopLeftY = 0.0f;
	m_directXSettings.m_viewPort.MinDepth = 0.0f;
	m_directXSettings.m_viewPort.MaxDepth = 0.0f;


	return 0;
}

int CGame::InitConstantBuffers()
{
	return 0;
}

void CGame::Update(float _deltaTime)
{
}

void CGame::Render()
{
}

LRESULT CALLBACK WndProc(HWND _hwnd, UINT _message, WPARAM _wparam, LPARAM _lparam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (_message)
	{
		case WM_PAINT:
			hdc = BeginPaint(_hwnd, &ps);
			EndPaint(_hwnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(_hwnd, _message, _wparam, _lparam);
	}
	return 0;
}
