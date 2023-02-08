#include "GraphicsPCH.h"
#include "Game.h"

// Entry point of the application.
int WINAPI wWinMain(HINSTANCE _hInstance, HINSTANCE _prevHInstance, LPWSTR _cmdLineArgV, int _cmdLineArgC)
{
	// Unreference unused parameters to suppress warnings.
	UNREFERENCED_PARAMETER(_prevHInstance);
	UNREFERENCED_PARAMETER(_cmdLineArgV);
	UNREFERENCED_PARAMETER(_cmdLineArgC);

	// Call the Initialize method of the CGame singleton object.
	int value = CGame::Get()->Initialize(_hInstance);

	// If Initialize returns a failure code, return it.
	if (FAILED(value))
	{
		return value;
	}

	// Call the Run method of the CGame singleton object.
	value = CGame::Get()->Run();

	// Call the Finalize method of the CGame singleton object.
	CGame::Get()->Finalize();

	// Return the result of the Run method.
	return value;
}