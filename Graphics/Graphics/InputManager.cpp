#include "GraphicsPCH.h"
#include "InputManager.h"
#include "Game.h"
#include "Helper.h"

CInputManager::CInputManager()
{
}

CInputManager::~CInputManager()
{

}

// This function initializes the DirectInput API for keyboard and mouse input
int CInputManager::InitDirectInput(HINSTANCE _hInstance)
{
	// Create an instance of DirectInput
	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&m_directInput, nullptr);

	// Check if the DirectInput instance was created successfully
	if (FAILED(hr))
	{
		// Return error code -100 if the instance creation failed
		return -100;
	}

	// Create the keyboard device
	hr = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, nullptr);
	if (FAILED(hr))
	{
		// Return error code -101 if the keyboard device creation failed
		return -101;
	}

	// Create the mouse device
	hr = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, nullptr);
	if (FAILED(hr))
	{
		// Return error code -102 if the mouse device creation failed
		return -102;
	}

	// Set the data format for the keyboard
	hr = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr))
	{
		// Return error code -103 if setting the data format for the keyboard failed
		return -103;
	}

	// Set the cooperative level for the keyboard
	hr = m_keyboard->SetCooperativeLevel(WDS.m_WindowHandle, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		// Return error code -104 if setting the cooperative level for the keyboard failed
		return -104;
	}

	// Set the data format for the mouse
	hr = m_mouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr))
	{
		// Return error code -105 if setting the data format for the mouse failed
		return -105;
	}

	// Set the cooperative level for the mouse
	hr = m_mouse->SetCooperativeLevel(WDS.m_WindowHandle, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	if (FAILED(hr))
	{
		// Return error code -106 if setting the cooperative level for the mouse failed
		return -106;
	}

	// Initialize the mouse position and keyboard/mouse state arrays
	m_mousePos = XMFLOAT2(WDS.m_WindowWidth * 0.5f, WDS.m_WindowHeigth * 0.5f);
	ZeroMemory(m_currentKeyboardState, sizeof(m_currentKeyboardState));
	ZeroMemory(&m_currentMouseState, sizeof(m_currentMouseState));


	ZeroMemory(m_lastKeyboardState, sizeof(m_lastKeyboardState));
	ZeroMemory(&m_lastMouseState, sizeof(m_lastMouseState));

	return 0;
}

void CInputManager::DetectInput()
{
	// Werte vom letzten Frame sichern
	m_lastMouseState = m_currentMouseState;
	memcpy(m_lastKeyboardState, m_currentKeyboardState, sizeof(m_currentKeyboardState));

	// Holen der Daten aus der Hardware
	m_keyboard->Acquire();
	m_mouse->Acquire();

	m_keyboard->GetDeviceState(sizeof(m_currentKeyboardState), m_currentKeyboardState);
	m_mouse->GetDeviceState(sizeof(m_currentMouseState), &m_currentMouseState);

	m_mousePos = XMFLOAT2(m_mousePos.x + GetMouseMovement().x, m_mousePos.y + GetMouseMovement().y);
	m_mousePos = Clamp(m_mousePos, XMFLOAT2(-20,-20), XMFLOAT2(WDS.m_WindowWidth, WDS.m_WindowHeigth));
}

void CInputManager::CleanUp()
{
}

bool CInputManager::GetKey(int _keyID)
{
	return m_currentKeyboardState[_keyID] & 0x80;
}

bool CInputManager::GetKeyUp(int _keyID)
{
	return !(m_currentKeyboardState[_keyID] & 0x80) &&
		(m_lastKeyboardState[_keyID] & 0x80);
}

bool CInputManager::GetKeyDown(int _keyID)
{
	return (m_currentKeyboardState[_keyID] & 0x80) &&
		!(m_lastKeyboardState[_keyID] & 0x80);
}

XMFLOAT2 CInputManager::GetMouseMovement()
{
	return XMFLOAT2(m_currentMouseState.lX, m_currentMouseState.lY);
}

float CInputManager::GetMouseWheel()
{
	return m_currentMouseState.lZ;
}

bool CInputManager::GetMouseKey(int _keyID)
{
	return m_currentMouseState.rgbButtons[_keyID] && 0x80;
}

bool CInputManager::GetMouseKeyUp(int _keyID)
{
	return !(m_currentMouseState.rgbButtons[_keyID] & 0x80) &&
		(m_lastMouseState.rgbButtons[_keyID] & 0x80);
}

bool CInputManager::GetMouseKeyDown(int _keyID)
{
	return (m_currentMouseState.rgbButtons[_keyID] & 0x80) &&
		!(m_lastMouseState.rgbButtons[_keyID] & 0x80);
}
