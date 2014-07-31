/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Defining public notify stuff.
	Initial author: momo5502
	Started: 2014-07-31
*/

struct g_entity_s
{
	int clientNum;
};

typedef short (__cdecl * SL_GetString_t)(const char* string, int);
extern SL_GetString_t SL_GetString;

typedef char* (_cdecl* SL_ConvertToString_t)(short ref);
extern SL_ConvertToString_t SL_ConvertToString;

typedef void (__cdecl * Scr_NotifyNum_t)(int number, int type, short notify, int numArgs);
extern Scr_NotifyNum_t Scr_NotifyNum;

typedef int (__cdecl * Scr_AddString_t)(int, const char* value);
extern Scr_AddString_t Scr_AddString;

typedef int (__cdecl * Scr_AddEntity_t)(int, g_entity_s* value);
extern Scr_AddEntity_t Scr_AddEntity;

typedef int (__cdecl * Scr_AddInt_t)(int, int value);
extern Scr_AddInt_t Scr_AddInt;

typedef char* (_cdecl* Scr_GetString_t)(int, int argNum);
extern Scr_GetString_t Scr_GetString;

void NotifyPush(char* value);
void NotifyPush(g_entity_s* value);
void NotifyPush(int value);
void Notify(int clientNum, char* notify);
void InitNotify();