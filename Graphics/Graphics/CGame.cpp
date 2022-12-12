#include "GraphicsPCH.h"
#include "CGame.h"

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
	WNDCLASSEX wndClass = {0};
	//ZeroMemory(&wndClass, sizeof(WNDCLASSEX)); // oldschool weg um Speicher zu leeren

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = &WndProc;
	wndClass.hInstance = _hInstance;
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 9);
	wndClass.lpszClassName = m_windowSettings.m_WindowClassName;

	if (RegisterClassEx(&wndClass))
	{
		return -2;
	}

	RECT windowRect = { 0,0, m_windowSettings.m_WindowWidth, m_windowSettings.m_WindowHeigth };
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);

	m_windowSettings.m_WindowHandle = CreateWindowA(m_windowSettings.m_WindowClassName,
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

	return 0;
}

int CGame::InitDirectX()
{
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
