#include "GraphicsPCH.h"
#include "InputManager.h"
#include "Game.h"

CInputManager::CInputManager()
{
}

CInputManager::~CInputManager()
{
	
}

int CInputManager::InitDirectInput(HINSTANCE _hInstance)
{
	HRESULT hr = DirectInput8Create(_hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*) & m_directInput, nullptr);
	FAILHR(-100);

	hr = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, nullptr);
	FAILHR(-101);

	hr = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, nullptr);
	FAILHR(-102);

	hr = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	FAILHR(-103);

	hr = m_keyboard->SetCooperativeLevel(WDS.m_WindowHandle, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	FAILHR(-104);

	hr = m_mouse->SetDataFormat(&c_dfDIMouse);
	FAILHR(-105);

	hr = m_mouse->SetCooperativeLevel(WDS.m_WindowHandle, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	FAILHR(-106);

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
	//m_mousePos = TODO: Mathehilfsfunktionen schreiben!
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
