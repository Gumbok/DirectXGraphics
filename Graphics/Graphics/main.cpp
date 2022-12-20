#include "GraphicsPCH.h"
#include "CGame.h"

int WINAPI wWinMain(HINSTANCE _hInstance, HINSTANCE _prevHInstance, LPWSTR _cmdLineArgV, int _cmdLineArgC)
{
	UNREFERENCED_PARAMETER(_prevHInstance);
	UNREFERENCED_PARAMETER(_cmdLineArgV);
	UNREFERENCED_PARAMETER(_cmdLineArgC);

	int value = CGame::Get()->Initialize(_hInstance);
	if (FAILED(value))
	{
		return value;
	}
	value = CGame::Get()->Run();

	CGame::Get()->Finalize();

	return value;
}