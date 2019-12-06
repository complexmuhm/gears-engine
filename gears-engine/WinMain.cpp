#include "WinException.h"
#include "Engine.h"

int WINAPI 
WinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR pCmdLine, 
	int nCmdShow)
{
	try
	{
		Engine e({ 1280, 720 }, L"Gears");
		e.run();
	}
	catch (const BaseException& e)
	{
		MessageBoxA(nullptr, e.what(), e.get_type(), MB_OK | MB_ICONERROR);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONERROR);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "An Unknown Error occured.", "Unknown Error", MB_OK | MB_ICONERROR);
	}

	return 0;
}