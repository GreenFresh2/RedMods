/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Finally, bot spawning through command :D
	Initial author: momo5502
	Started: 2014-07-31
*/

#include "..\STDInclude.h"

SV_AddTestClient_t SV_AddTestClient = (SV_AddTestClient_t)0x62C140;
SV_Loaded_t SV_Loaded = (SV_Loaded_t)0x580AA0;

void SpawnBots(int amount)
{
	if(!isMultiplayer)
		return;

	// Add desired amount of bots
	std::vector<g_entity_s*> entRefs;

	for(int i = 0; i < amount; i++)
	{
		g_entity_s* entRef = SV_AddTestClient();

		if(entRef)
		{
			entRefs.push_back(entRef);
		}
		else
		{
			break;
		}
	}

	// Wait 1 second for the bots to join the game
	Cbuf_AddText(0, "wait 100;");

	for(int i = 0; i < entRefs.size(); i++)
	{
		// Change bot class
		Cbuf_AddText(0, va("autoChangeClass %d;", entRefs[i]->clientNum));
	}
}

void spawnBot_f()
{
	int count = (Cmd_ArgC() > 1 ? atoi(Cmd_ArgV(1)) : 1);

	// Check if ingame and host
	if(SV_Loaded())
	{
		SpawnBots(count);
	}
}

void autoChangeClass_f()
{
	if(Cmd_ArgC() != 2)
		return;

	int client = atoi(Cmd_ArgV(1));

	// TODO: Probably add different class types? Or do bots automatically pick different weapons anyways?
	NotifyPush("class_assault");
	NotifyPush("changeclass");
	Notify(client, "menuresponse");
}

void InitBots()
{
	if(!isMultiplayer)
		return;

	// Add necessary commands
	static cmd_function_s spawnBot_cmd;
	static cmd_function_s autoChangeClass_cmd;
	Cmd_AddCommandInternal("spawnBot", spawnBot_f, &spawnBot_cmd);
	Cmd_AddCommandInternal("autoChangeClass", autoChangeClass_f, &autoChangeClass_cmd);
}