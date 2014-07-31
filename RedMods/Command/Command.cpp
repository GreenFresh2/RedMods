/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Simple wrapper to add custom commands
	Initial author: momo5502
	Started: 2014-07-31
*/

#include "..\STDInclude.h"

Cmd_AddCommandInternal_t  Cmd_AddCommandInternal = (Cmd_AddCommandInternal_t)0x667FA0;
Cbuf_AddText_t Cbuf_AddText = (Cbuf_AddText_t)0x4F43F0;

// Return command parameter count
int Cmd_ArgC()
{
	return *(int*)0x25087DC;
}

// Return command parameter value for the given index
char* Cmd_ArgV(int index)
{
	if(index >= Cmd_ArgC())
	{
		return "";
	}
	else
	{
		return (*(char***)0x25087FC)[index];
	}
}

void InitCommands()
{
	if(!isMultiplayer)
	{
		// TODO: Re-assign functions
	}
}