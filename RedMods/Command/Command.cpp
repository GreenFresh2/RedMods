/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Simple wrapper to add custom commands
	Initial author: momo5502
	Started: 2014-07-31
*/

#include "..\STDInclude.h"

Cmd_AddCommandInternal_t  Cmd_AddCommandInternal = (Cmd_AddCommandInternal_t)0x667FA0;
Cbuf_AddText_t Cbuf_AddText = (Cbuf_AddText_t)0x4F43F0;

DWORD cmd_argc = 0x25087DC;
DWORD cmd_argv = 0x25087FC;

// Return command parameter count
int Cmd_ArgC()
{
	return *(int*)cmd_argc;
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
		return (*(char***)cmd_argv)[index];
	}
}

void InitCommands()
{
	// Assign zombie stuff
	if(!isMultiplayer)
	{
		Cmd_AddCommandInternal = (Cmd_AddCommandInternal_t)0x489D80;
		Cbuf_AddText = (Cbuf_AddText_t)0x5FC050;

		cmd_argc = 0x24C4A5C;
		cmd_argv = 0x24C4A7C;
	}
}