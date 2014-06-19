/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Implementing GSC patches.
	Initial author: Convery, based on research by Kokole.
	Started: 2014-06-19
*/

#include "..\STDInclude.h"

// Add the asset to FS.
typedef int (__cdecl* DB_AddXAsset_t)(int Type, int Header);
DB_AddXAsset_t DB_AddXAsset = (DB_AddXAsset_t)0x00;

// Modify asset before adding.
StompHook ScriptParseHook;
void Load_ScriptParseTreeAsset(ScriptParseTree** scriptParseTree)
{
#pragma region ZOMBIES8PLAYER
	if (!strcmp((*scriptParseTree)->name, "maps/mp/zombies/_zm.gsc"))
	{
		BYTE* gscBuffer = (*scriptParseTree)->buffer;
		COD9_GSC* gsc = (COD9_GSC*)gscBuffer;

		gscFunction* currentFunction = (gscFunction*)(gscBuffer + gsc->gscFunctions);
		for (WORD i = 0; i < gsc->numOfFunctions; currentFunction++, i++)
		{
			if (!strcmp((const char*)(gscBuffer + currentFunction->name), "player_too_many_players_check"))
			{
				// Return player_too_many_players_check.
				*(BYTE*)(gscBuffer + currentFunction->start) = 0x00; // = OP_End

				break;
			}
		}
	}
#pragma endregion

	// Uncomment if you want to log.
	//DBG("%s ( \"%s\" )\n", __FUNCTION__, (*scriptParseTree)->name);

	// Return the requested GSC.
	*scriptParseTree = (ScriptParseTree*)DB_AddXAsset(0x30, (int)scriptParseTree);
}

void InitGSC()
{
	if(isMultiplayer)
	{
		DB_AddXAsset = (DB_AddXAsset_t)0x007FBCB0;
		ScriptParseHook.initialize(0x005E7060, Load_ScriptParseTreeAsset);
		ScriptParseHook.installHook();
	}
	else
	{
		DB_AddXAsset = (DB_AddXAsset_t)0x007F3A10;
		ScriptParseHook.initialize(0x00555F40, Load_ScriptParseTreeAsset);
		ScriptParseHook.installHook();
	}

}
void PostInitGSC()
{
	// Extra changes.
	if(isMultiplayer)
	{
	}
	else
	{
		// Set tu9_rerunPlaylistRulesOnHost to 0.
		if (*(DWORD*)0x1239A20)
			*(DWORD*)(*(DWORD*)0x1239A20 + 24) = 0;

		// Set party_maxplayers to 8.
		if (*(DWORD*)0x1239478)
			*(DWORD*)(*(DWORD*)0x1239478 + 24) = 8;

		// Set party_minplayers to 8.
		if (*(DWORD*)0x1239988)
			*(DWORD*)(*(DWORD*)0x1239988 + 24) = 8;
	}
}