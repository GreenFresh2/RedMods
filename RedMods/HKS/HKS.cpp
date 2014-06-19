/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Implementing public HKS patches.
	Initial author: Convery
	Started: 2014-06-19
*/

#include "..\STDInclude.h"

// Finding assets in the FS.
typedef void *(__cdecl * DB_FindXAssetHeader_)(int Type, const char* Name, int a3, int a4);
DB_FindXAssetHeader_ DB_FindXAssetHeader = (DB_FindXAssetHeader_)0x00;

// Loading textures from FS.
StompHook HKS_MaterialHook;
bool HKS_RegisterMaterial(const char *Name, void **Out)
{
	if(isMultiplayer)
	{
		// Main menu background.
		if(strstr(Name, "menu_mp_soldiers"))
		{
			*Out = DB_FindXAssetHeader(0x6, Background2Name, 1, -1);
			return true;
		}

		// Default background / Lobby.
		if(strstr(Name, "lui_bkg"))
		{
			*Out = DB_FindXAssetHeader(0x6, Background1Name, 1, -1);
			return true;
		}
	}
	else
	{
		// Main menu overlay.
		if(!strcmp(Name, "lui_bkg_zm_sun"))
		{
			*Out = DB_FindXAssetHeader(0x6, "menu_zm_cac_backing", 1, -1);
			return true;
		}
	}

	// Uncomment if you want to log.
	//DBG("%s ( \"%s\" )\n", __FUNCTION__, Name);

	// Return the requested texture.
	*Out = DB_FindXAssetHeader(0x6, Name, 1, -1);
	return true;
}

// Loading scripts from FS.
StompHook HKS_RawfileHook;
void *HKS_LoadRawfile(const char *Filename)
{
	RawFile *Result = nullptr;
	char FilePath[256];

	// Lowercase to make it easier for check.
	for (size_t i = 0; i < strlen(Filename) + 1; i++)
		FilePath[i] = tolower(Filename[i]);

	// If the path contains 'redacted' then we'll load it from disk.
	if(strstr(FilePath, "redacted"))
	{
		FILE *F = NULL;

		// Open the requested file or die.
		F = fopen(Filename, "rb");
		if(F == NULL) return Result;

		// As the file exists, create our result.
		Result = new RawFile;
		Result->Name;
		Result->Length = 0;
		Result->Buffer = nullptr;

		// Get filesize.
		fseek(F, 0, SEEK_END);
		Result->Length = ftell(F);
		rewind(F);

		// Allocate the buffer in memory.
		// As we don't have a file management system in this DLL
		// there will be some memory leaks =(
		Result->Buffer = (const char *)GlobalAlloc(GPTR, Result->Length);

		// Read and close the file.
		fread((void *)Result->Buffer, 1, Result->Length, F);
		fclose(F);
	}
	else
	{
		Result = (RawFile *)DB_FindXAssetHeader(41, Filename, 0, 0);
	}

	return Result;
}

// Install our hooks.
void InitHKS()
{
	if(isMultiplayer)
	{
		DB_FindXAssetHeader = (DB_FindXAssetHeader_)0x00526800;

		HKS_MaterialHook.initialize(0x004863E0, HKS_RegisterMaterial);
		HKS_MaterialHook.installHook();

		HKS_RawfileHook.initialize(0x00494BA0, HKS_LoadRawfile);
		HKS_RawfileHook.installHook();
	}
	else
	{
		DB_FindXAssetHeader = (DB_FindXAssetHeader_)0x006653A0;

		HKS_MaterialHook.initialize(0x005BFA20, HKS_RegisterMaterial);
		HKS_MaterialHook.installHook();

		HKS_RawfileHook.initialize(0x006F6BA0, HKS_LoadRawfile);
		HKS_RawfileHook.installHook();
	}
}