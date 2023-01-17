#pragma once

// System Includes
#include <Windows.h>		// Fenstererzeugung und Konfiguration

// DirectX
#include <d3d11.h>			// Hauptheaderfile
#include <d3dcompiler.h>	// Läd und kompiliert Shader
#include <DirectXMath.h>	// Matrix- und Vektormathe
#include <DirectXColors.h>	// Liefert schöne Farben!

// STL includes
#include <string>
#include <iostream>
#include <list>

// Mathe
#include <algorithm>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "winmm.lib")

#include <WICTextureLoader.h>
#include <SpriteFont.h>
#include <SpriteBatch.h>

using namespace DirectX;

template<typename T>
inline void SafeRelease(T& _ptr)
{
	if (_ptr != nullptr)
	{
		_ptr->Release();
		_ptr = nullptr;
	}
}