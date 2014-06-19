/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Setting the global variables, calling initializers and entrypoint.
	Initial author: Convery
	Started: 2014-06-19
*/

#include "STDInclude.h"

// Get our globals.
void ReadINI()
{
	GetPrivateProfileStringA("Material", "Background", "menu_mp_background_main", Background1Name, 64, ".\\Redacted\\Modding.ini");
	GetPrivateProfileStringA("Material", "Background2", "menu_mp_background_main2", Background2Name, 64, ".\\Redacted\\Modding.ini");

	// For verification.
	DBG("Set Background1 to \"%s\"\n", Background1Name);
	DBG("Set Background2 to \"%s\"\n", Background2Name);
}

// Called on startup.
void Init()
{
	// Get game version.
	if(*(BYTE*)0x401370 == 0xB8)
		isMultiplayer = true;
	else 
		if(*(BYTE*)0x401370 == 0x1D)
			isMultiplayer = false;
		else
			// If the client is using the wrong binary we just quit.
			ExitProcess(0xDEADC0DE);

	// Verify that we got the correct one.
	DBG("Main binary: %s\n", isMultiplayer ? "Multiplayer" : "Zombie");

	// Our public patches.
	InitGSC();
	InitHKS();
}

// Called after the game is started.
__declspec(dllexport) void PostInit()
{
	PostInitGSC();
}

BOOL __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
	#ifdef DEBUG
		AllocConsole();
		AttachConsole(GetCurrentProcessId());
		freopen("CON", "w", stdout);
	#endif

		DBG("Mod DLL starting up..\n");
		Init();
	}

	return TRUE;
}