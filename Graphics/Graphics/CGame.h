#pragma once
#include "WindowSettings.h"
#include "DirectXSettings.h"
#include "ConstantBuffer.h"
#include "CEntity.h"
#include "CContentManager.h"

#define WDS (*(CGame::Get()->GetWindowSettings()))
#define DXS (*(CGame::Get()->GetDirectXSettings()))
#define CTM (*(CGame::Get()->GetContentManager()))

#define FAILHR(errorcode) if (FAILED(hr)) { return errorcode; }

class CGame
{
private:
	CGame();
public:
	~CGame();


public:
	static CGame* Get()
	{
		static CGame* instance = new CGame();	// Diese Zeile wird nur beim ersten Mal ausgeführt
		return instance;						// Diese immer
	}

	// Beschreibt wie der Speicher allokiert werden soll, hier wird dafür gesorgt 
	// dass die adresse durch 16 teilbar ist (Notwendig später für Kommunikation mit der Grafikkarte)
	static void* operator new(size_t _size)
	{
		return _aligned_malloc(_size, 16);
	}

	static void operator delete(void* _memory)
	{
		_aligned_free(_memory);
	}

private:
	SWindowSettings m_windowSettings;
	SDirectXSettings m_directXSettings;
	CContentManager m_contentManager;
	XMFLOAT3 m_camPos;
	XMFLOAT3 m_camRot;

	SStandardConstantBuffer m_applicationConstantBuffer;
	SStandardConstantBuffer m_frameConstantBuffer;
	SLightConstantBuffer m_lightConstantBuffer;

	bool m_isRunning;

public:
	int Initialize(HINSTANCE _hInstance);
	int Run();
	void Finalize();

	inline SWindowSettings* GetWindowSettings() { return &m_windowSettings; }
	inline SDirectXSettings* GetDirectXSettings() { return &m_directXSettings; }
	inline CContentManager* GetContentManager() { return &m_contentManager; }

private:
	int InitApplication(HINSTANCE _hInstance);
	int InitDirectX();
	int InitConstantBuffers();
	int LoadLevel();

	int CreateSimpleShader();

	void ClearBackBuffer(const float _clearColor[4], float _clearDepth, UINT8 _clearStencil);

	void Update(float _deltaTime);
	void Render();

};

