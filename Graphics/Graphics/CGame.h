#pragma once
#include "WindowSettings.h"
#include "DirectXSettings.h"

#define WDS (*(CGame::Get()->GetWindowSettings()))
#define DXS (*(CGame::Get()->GetDirectXSettings()))

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

	bool m_isRunning;

public:
	int Initialize(HINSTANCE _hInstance);
	int Run();
	void Finalize();

	inline SWindowSettings* GetWindowSettings() { return &m_windowSettings; }
	inline SDirectXSettings* GetDirectXSettings() { return &m_directXSettings; }

private:
	int InitApplication(HINSTANCE _hInstance);
	int InitDirectX();
	int InitConstantBuffers();

	void Update(float _deltaTime);
	void Render();
};

