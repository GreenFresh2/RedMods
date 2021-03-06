/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Defining public bot stuff.
	Initial author: momo5502
	Started: 2014-07-31
*/

struct g_entity_s
{
	int clientNum;
	char pad[0x318];
};

typedef g_entity_s* (__cdecl * SV_AddTestClient_t)();
extern SV_AddTestClient_t SV_AddTestClient;

typedef bool (__cdecl * SV_Loaded_t)();
extern SV_Loaded_t SV_Loaded;

void SpawnBots(unsigned int amount);
void InitBots();

extern g_entity_s* g_entities;