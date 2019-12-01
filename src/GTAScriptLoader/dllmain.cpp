#define WIN32_LEAN_AND_MEAN
#include <windows.h>

static HMODULE hLibrary;

BOOL APIENTRY DllMain (HINSTANCE hInstance, DWORD reason, LPVOID reserved) {
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			hLibrary = LoadLibrary(L"GTAScriptHook.dll");
		break;
		case DLL_PROCESS_DETACH:
			FreeLibrary(hLibrary);
		break;
	}

	return true;
}