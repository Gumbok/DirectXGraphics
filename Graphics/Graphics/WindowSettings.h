#pragma once

struct SWindowSettings
{
	const long m_WindowWidth = 800;
	const long m_WindowHeigth = 600;

	LPCSTR m_WindowClassName = L"Graphics Class";
	LPCSTR m_WindowName = L"Willkommen einfach nur Willkommen";
	HWND m_WindowHandle = nullptr;

	const bool m_enableVSync = false;
};