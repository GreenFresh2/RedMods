/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Interact with the game's notification system
	Initial author: momo5502
	Started: 2014-07-31
*/

#include "..\STDInclude.h"

// Assign necessary functions
SL_GetString_t SL_GetString = (SL_GetString_t)0x6F5A50;
SL_ConvertToString_t SL_ConvertToString = (SL_ConvertToString_t)0x4FE530;
Scr_NotifyNum_t Scr_NotifyNum = (Scr_NotifyNum_t)0x53D5D0;
Scr_AddString_t Scr_AddString = (Scr_AddString_t)0x6AB5E0;
Scr_AddEntity_t Scr_AddEntity = (Scr_AddEntity_t)0x5C9580;
Scr_AddInt_t Scr_AddInt = (Scr_AddInt_t)0x4E1C20;
Scr_GetString_t Scr_GetString = (Scr_GetString_t)0x6608D0;

int scr_numParams = 0;

// Push functions
// TODO: Add arrays and vectors

void NotifyPush(char* value)
{
	// Push string onto the script stack
	Scr_AddString(0, value);
	scr_numParams++;
}

void NotifyPush(g_entity_s* value)
{
	// Push entity onto the script stack
	Scr_AddEntity(0, value);
	scr_numParams++;
}

void NotifyPush(int value)
{
	// Push integer onto the script stack
	Scr_AddInt(0, value);
	scr_numParams++;
}

void Notify(int clientNum, char* notify)
{
	// Convert notify command into a string reference
	short s_notify = SL_GetString(notify, 0);

	// Notify with pushed params for given client
	Scr_NotifyNum(clientNum, 0, s_notify, scr_numParams);

	// Reset param count
	scr_numParams = 0;
}

void InitNotify()
{
	if(!isMultiplayer)
	{
		// TODO: Re-assign functions
	}
}