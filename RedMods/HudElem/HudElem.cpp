/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Custom hud element spawning
	Initial author: momo5502
	Started: 2014-08-04
*/

#include "..\STDInclude.h"

HudElem_Alloc_t HudElem_Alloc = (HudElem_Alloc_t)0x4E3120;
G_LocalizedStringIndex_t G_LocalizedStringIndex = (G_LocalizedStringIndex_t)0x44F6B0;
G_MaterialIndex_t G_MaterialIndex = (G_MaterialIndex_t)0x542C10;

HudElem* HudElem_Allocate()
{
	HudElem* elem = HudElem_Alloc(1023, 0);
	memset(elem, 0, sizeof(HudElem));
	return elem;
}

void HudElem_Init(HudElem* elem, int client)
{
	elem->color[0] = 255;
	elem->color[1] = 255;
	elem->color[2] = 255;
	elem->color[3] = 255;

	elem->playerInd = client;
	elem->fontScale = 1.0f;
	elem->font = 0;
	elem->ui3dWindow = 0xFF;
}

void HudElem_Free(HudElem* elem)
{
	memset(elem, 0, sizeof(HudElem));
}

void HudElem_SetAlign(HudElem* elem, HudElemAlign align)
{
	// Probably there are more accurate values, but these will work for now
	switch(align)
	{
		// TOP
		case TOP_LEFT_COMPASS:
			elem->alignScreen = 0;
			elem->alignOrg = 0;
			break;

		case TOP_LEFT:
			elem->alignScreen = 96;
			elem->alignOrg = 0;
			break;

		case TOP_RIGHT:
			elem->alignScreen = 60;
			elem->alignOrg = 0;
			break;

		case TOP_CENTER:
			elem->alignScreen = 40;
			elem->alignOrg = 20;
			break;


		// CENTER
		case CENTER_LEFT:
			elem->alignScreen = 66;
			elem->alignOrg = 1;
			break;

		case CENTER_RIGHT:
			elem->alignScreen = 55;
			elem->alignOrg = 1;
			break;

		case CENTER_CENTER:
			elem->alignScreen = 34;
			elem->alignOrg = 5;
			break;


		// BOTTOM
		case BOTTOM_LEFT:
			elem->alignScreen = 83;
			elem->alignOrg = 0;
			break;

		case BOTTOM_RIGHT:
			elem->alignScreen = 51;
			elem->alignOrg = 0;
			break;

		case BOTTOM_CENTER:
			elem->alignScreen = 35;
			elem->alignOrg = 7;
			break;
	}
}

void HudElem_SetText(HudElem* elem, const char* text)
{
	elem->type = 1;
	elem->text = G_LocalizedStringIndex(text);
}

void HudElem_SetIcon(HudElem* elem, const char* material)
{
	elem->type = 8;
	elem->materialIndex = G_MaterialIndex(material);
}

void HudElem_SetColor(HudElem* elem, char r, char g, char b, char a)
{
	elem->color[0] = r;
	elem->color[1] = g;
	elem->color[2] = b;
	elem->color[3] = a;
}

void HudElem_SetGlow(HudElem* elem, char r, char g, char b, char a)
{
	elem->glowColor[0] = r;
	elem->glowColor[1] = g;
	elem->glowColor[2] = b;
	elem->glowColor[3] = a;
}

void testHudElems_f();

void InitHudElem()
{
	if(!isMultiplayer)
	{
		HudElem_Alloc = (HudElem_Alloc_t)0x445570;
		G_LocalizedStringIndex = (G_LocalizedStringIndex_t)0x5058C0;
		G_MaterialIndex = (G_MaterialIndex_t)0x5FA2F0;

		// Remove shader precache limitation
		*(BYTE*)0x5FA369 = 0xEB;
	}
	else
	{
		// Remove shader precache limitation
		*(BYTE*)0x542C89 = 0xEB;
	}
	

	static cmd_function_s testHudElems_cmd;
	Cmd_AddCommandInternal("testHudElems", testHudElems_f, &testHudElems_cmd);
}

// -------------------------
// TESTING AND DEMONSTRATION
// -------------------------

void spawnTestElem(int client)
{
	// Text
	HudElem* elem = HudElem_Allocate();
	HudElem_Init(elem, client);
	HudElem_SetText(elem, "Momo5502 owns you!");
	HudElem_SetAlign(elem, TOP_CENTER);
	HudElem_SetColor(elem, 0, 0, 0, 255);
	HudElem_SetGlow(elem, 255, 0, 0, 80);

	elem->fontScale = 2.0f;

	// Icon
	HudElem* material = HudElem_Allocate();
	HudElem_Init(material, client);
	HudElem_SetIcon(material, "hud_medals_nuclear");
	HudElem_SetAlign(material, TOP_CENTER);

	material->width = 60;
	material->height = 60;
	material->y = 30;
}

void spawnTestElemZombie(int client)
{
	// Text
	HudElem* elem = HudElem_Allocate();
	HudElem_Init(elem, client);
	HudElem_SetText(elem, "Momo5502 owns zombies as well!");
	HudElem_SetAlign(elem, CENTER_LEFT);
	HudElem_SetColor(elem, 0, 0, 0, 255);
	HudElem_SetGlow(elem, 0, 255, 255, 40);

	elem->fontScale = 2.0f;
}

void testHudElems_f()
{
	for(int i = 0; i < (isMultiplayer ? 18 : 4); i++)
	{
		if(isMultiplayer) spawnTestElem(i);
		else spawnTestElemZombie(i);
	}
}