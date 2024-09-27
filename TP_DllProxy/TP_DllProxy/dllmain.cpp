#include <Windows.h>
#include <thread>
#include "tpextended.h"

#pragma region Proxy
struct ddraw_dll {
	HMODULE dll;
	FARPROC oAcquireDDThreadLock;
	FARPROC oCompleteCreateSysmemSurface;
	FARPROC oD3DParseUnknownCommand;
	FARPROC oDDGetAttachedSurfaceLcl;
	FARPROC oDDInternalLock;
	FARPROC oDDInternalUnlock;
	FARPROC oDSoundHelp;
	FARPROC oDirectDrawCreate;
	FARPROC oDirectDrawCreateClipper;
	FARPROC oDirectDrawCreateEx;
	FARPROC oDirectDrawEnumerateA;
	FARPROC oDirectDrawEnumerateExA;
	FARPROC oDirectDrawEnumerateExW;
	FARPROC oDirectDrawEnumerateW;
	FARPROC oDllCanUnloadNow;
	FARPROC oDllGetClassObject;
	FARPROC oGetDDSurfaceLocal;
	FARPROC oGetOLEThunkData;
	FARPROC oGetSurfaceFromDC;
	FARPROC oRegisterSpecialCase;
	FARPROC oReleaseDDThreadLock;
	FARPROC oSetAppCompatData;
} ddraw;

extern "C" {
	void fAcquireDDThreadLock() {  _asm jmp[ddraw.oAcquireDDThreadLock] }
	void fCompleteCreateSysmemSurface() {  _asm jmp[ddraw.oCompleteCreateSysmemSurface] }
	void fD3DParseUnknownCommand() {  _asm jmp[ddraw.oD3DParseUnknownCommand] }
	void fDDGetAttachedSurfaceLcl() {  _asm jmp[ddraw.oDDGetAttachedSurfaceLcl] }
	void fDDInternalLock() {  _asm jmp[ddraw.oDDInternalLock] }
	void fDDInternalUnlock() {  _asm jmp[ddraw.oDDInternalUnlock] }
	void fDSoundHelp() {  _asm jmp[ddraw.oDSoundHelp] }
	void fDirectDrawCreate() {  _asm jmp[ddraw.oDirectDrawCreate] }
	void fDirectDrawCreateClipper() {  _asm jmp[ddraw.oDirectDrawCreateClipper] }
	void fDirectDrawCreateEx() {  _asm jmp[ddraw.oDirectDrawCreateEx] }
	void fDirectDrawEnumerateA() {  _asm jmp[ddraw.oDirectDrawEnumerateA] }
	void fDirectDrawEnumerateExA() {  _asm jmp[ddraw.oDirectDrawEnumerateExA] }
	void fDirectDrawEnumerateExW() {  _asm jmp[ddraw.oDirectDrawEnumerateExW] }
	void fDirectDrawEnumerateW() {  _asm jmp[ddraw.oDirectDrawEnumerateW] }
	void fDllCanUnloadNow() {  _asm jmp[ddraw.oDllCanUnloadNow] }
	void fDllGetClassObject() {  _asm jmp[ddraw.oDllGetClassObject] }
	void fGetDDSurfaceLocal() {  _asm jmp[ddraw.oGetDDSurfaceLocal] }
	void fGetOLEThunkData() {  _asm jmp[ddraw.oGetOLEThunkData] }
	void fGetSurfaceFromDC() {  _asm jmp[ddraw.oGetSurfaceFromDC] }
	void fRegisterSpecialCase() {  _asm jmp[ddraw.oRegisterSpecialCase] }
	void fReleaseDDThreadLock() {  _asm jmp[ddraw.oReleaseDDThreadLock] }
	void fSetAppCompatData() {  _asm jmp[ddraw.oSetAppCompatData] }
}

void setupFunctions() {
	ddraw.oAcquireDDThreadLock = GetProcAddress(ddraw.dll, "AcquireDDThreadLock");
	ddraw.oCompleteCreateSysmemSurface = GetProcAddress(ddraw.dll, "CompleteCreateSysmemSurface");
	ddraw.oD3DParseUnknownCommand = GetProcAddress(ddraw.dll, "D3DParseUnknownCommand");
	ddraw.oDDGetAttachedSurfaceLcl = GetProcAddress(ddraw.dll, "DDGetAttachedSurfaceLcl");
	ddraw.oDDInternalLock = GetProcAddress(ddraw.dll, "DDInternalLock");
	ddraw.oDDInternalUnlock = GetProcAddress(ddraw.dll, "DDInternalUnlock");
	ddraw.oDSoundHelp = GetProcAddress(ddraw.dll, "DSoundHelp");
	ddraw.oDirectDrawCreate = GetProcAddress(ddraw.dll, "DirectDrawCreate");
	ddraw.oDirectDrawCreateClipper = GetProcAddress(ddraw.dll, "DirectDrawCreateClipper");
	ddraw.oDirectDrawCreateEx = GetProcAddress(ddraw.dll, "DirectDrawCreateEx");
	ddraw.oDirectDrawEnumerateA = GetProcAddress(ddraw.dll, "DirectDrawEnumerateA");
	ddraw.oDirectDrawEnumerateExA = GetProcAddress(ddraw.dll, "DirectDrawEnumerateExA");
	ddraw.oDirectDrawEnumerateExW = GetProcAddress(ddraw.dll, "DirectDrawEnumerateExW");
	ddraw.oDirectDrawEnumerateW = GetProcAddress(ddraw.dll, "DirectDrawEnumerateW");
	ddraw.oDllCanUnloadNow = GetProcAddress(ddraw.dll, "DllCanUnloadNow");
	ddraw.oDllGetClassObject = GetProcAddress(ddraw.dll, "DllGetClassObject");
	ddraw.oGetDDSurfaceLocal = GetProcAddress(ddraw.dll, "GetDDSurfaceLocal");
	ddraw.oGetOLEThunkData = GetProcAddress(ddraw.dll, "GetOLEThunkData");
	ddraw.oGetSurfaceFromDC = GetProcAddress(ddraw.dll, "GetSurfaceFromDC");
	ddraw.oRegisterSpecialCase = GetProcAddress(ddraw.dll, "RegisterSpecialCase");
	ddraw.oReleaseDDThreadLock = GetProcAddress(ddraw.dll, "ReleaseDDThreadLock");
	ddraw.oSetAppCompatData = GetProcAddress(ddraw.dll, "SetAppCompatData");
}
#pragma endregion

bool isMulticlient;
int width = 1920;
int height = 1080;

void AsyncInit(TPEXTENDED* tp, bool isMulticlient, int width, int height) {
	tp->Init(isMulticlient, width, height);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
	{

		char path[MAX_PATH];
		GetWindowsDirectory(path, sizeof(path));

		// Change this to where you have your original ddraw.dll, usually it's already in System32.
		strcat_s(path, "\\System32\\ddraw.dll");
		ddraw.dll = LoadLibrary(path);
		if (NULL == ddraw.dll)
		{
			MessageBox(0, "Cannot load original ddraw.dll library", "TB Extended", MB_ICONERROR);
			ExitProcess(0);
		}

		setupFunctions();

		LPWSTR commandLine = GetCommandLineW();

		// Check for "-Multiclient"
		if (wcsstr(commandLine, L"-Multiclient") != NULL) {
			isMulticlient = true;
		}
		else {
			isMulticlient = false;
		}

		// Height
		LPWSTR heightParam = wcsstr(commandLine, L"-Height:");
		if (heightParam != NULL) {
			heightParam += wcslen(L"-Height:");
			height = wcstol(heightParam, NULL, 10);
		}

		// Width
		LPWSTR widthParam = wcsstr(commandLine, L"-Width:");
		if (widthParam != NULL) {
			widthParam += wcslen(L"-Width:");
			width = wcstol(widthParam, NULL, 10);
		}


		// Opens a Console Output.
		AllocConsole();
		FILE* stream;
		freopen_s(&stream, "CONOUT$", "w", stdout);
		std::cout << "Width: " << width << std::endl;
		std::cout << "Height: " << height << std::endl;


		TPEXTENDED* tp = new TPEXTENDED();

		std::thread preinitThread(AsyncInit, tp, isMulticlient, width, height);
		preinitThread.detach();

	}
		break;
	case DLL_PROCESS_DETACH:
		FreeLibrary(ddraw.dll);
		break;
	}
	return 1;
}
