#pragma once

// Preprocessor directive ensuring this header file is included once in single compilation unit.
#include <Windows.h>		// Windows API for window creation and configuration.

// DirectX
#include <d3d11.h>			// Main DirectX header for Direct3D 11.
#include <d3dcompiler.h>	// DirectX header for loading and compiling shaders.
#include <DirectXMath.h>	// DirectX math library for matrix and vector math.
#include <DirectXColors.h>	// DirectX library for nice colors.

// STL includes
#include <string>			// String library.
#include <iostream>			// Input/output stream library.
#include <list>				// List library.

// Mathe
#include <algorithm>		// Algorithm library.

#pragma comment(lib, "d3d11.lib")			// Link Direct3D 11 library.
#pragma comment(lib, "dxgi.lib")			// Link DirectX Graphics Infrastructure library.
#pragma comment(lib, "d3dcompiler.lib")	// Link Direct3D shader compiler library.
#pragma comment(lib, "winmm.lib")			// Link Windows Multimedia library.

#include <WICTextureLoader.h>		// Windows Imaging Component texture loading library.
#include <SpriteFont.h>				// Sprite font library.
#include <SpriteBatch.h>			// Sprite batch library.

using namespace DirectX;			// Namespace for DirectX types and functions.

template<typename T>
inline void SafeRelease(T& _ptr)		// Template function to safely release pointer.
{
	if (_ptr != nullptr)			// If pointer is not null...
	{
		_ptr->Release();			// Release resource.
		_ptr = nullptr;				// Set pointer to null.
	}
}
