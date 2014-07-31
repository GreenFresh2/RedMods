/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Public command definitions
	Initial author: momo5502
	Started: 2014-07-31
*/

typedef void (__cdecl * CommandCB_t)(void);

typedef struct cmd_function_s
{
	cmd_function_s* nextCmd;
	const char* name;
	char pad[8];
	CommandCB_t callback;
	DWORD pad2;
};

typedef void (__cdecl * Cmd_AddCommandInternal_t)(const char* name, CommandCB_t callback, cmd_function_s *);
extern Cmd_AddCommandInternal_t Cmd_AddCommandInternal;

typedef void (__cdecl * Cbuf_AddText_t)(int, const char* cmd);
extern Cbuf_AddText_t Cbuf_AddText;

int Cmd_ArgC();
char* Cmd_ArgV(int index);
void InitCommands();

// Print to external console in zombies and multiplayer
#define Com_Printf(fmt, ...) ((void(*)(const char*))(isMultiplayer ? 0x452300 : 0x6C8380))(va(fmt, ##__VA_ARGS__))
