/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Defining public hud element stuff.
	Initial author: momo5502
	Started: 2014-08-04
*/

typedef struct HudElem
{
	float x;
	float y;
	float z;
	float fontScale;
	float fromFontScale;
	int fontScaleStartTime;
	char color[4];
	char fromColor[4];
	int fadeStartTime;
	int scaleStartTime;
	float fromX;
	float fromY;
	int moveStartTime;
	int time;
	int duration;
	int value;
	float sort;
	char glowColor[4];
	int fxBirthTime;
	int flags;
	short targetEntNum;
	short fontScaleTime;
	short fadeTime;
	short label;
	short width;
	short height;
	short fromWidth;
	short fromHeight;
	short scaleTime;
	short moveTime;
	short text;
	short fxLetterTime;
	short fxDecayStartTime;
	short fxDecayDuration;
	short fxRedactDecayStartTime;
	short fxRedactDecayDuration;
	char type;
	char font;
	char alignOrg;
	char alignScreen;
	char materialIndex;
	char offscreenMaterialIdx;
	char fromAlignOrg;
	char fromAlignScreen;
	char soundID;
	char ui3dWindow;
	short flag2;
	int playerInd;
	int team;
	int abilityFlag;
};

enum HudElemAlign
{
	TOP_LEFT_COMPASS,	// Show the element next to the minimap
	TOP_LEFT,
	TOP_RIGHT,
	TOP_CENTER,

	CENTER_LEFT,
	CENTER_RIGHT,
	CENTER_CENTER,

	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	BOTTOM_CENTER
};

typedef HudElem* (__cdecl * HudElem_Alloc_t)(int, int);
extern HudElem_Alloc_t HudElem_Alloc;

typedef short (__cdecl * G_LocalizedStringIndex_t)(const char* text);
extern G_LocalizedStringIndex_t G_LocalizedStringIndex;

typedef short (__cdecl * G_MaterialIndex_t)(const char* material);
extern G_MaterialIndex_t G_MaterialIndex;

void InitHudElem();

HudElem* HudElem_Allocate();
void HudElem_Free(HudElem* elem);
void HudElem_Init(HudElem* elem, int client);
void HudElem_SetAlign(HudElem* elem, HudElemAlign align);
void HudElem_SetText(HudElem* elem, const char* text);
void HudElem_SetIcon(HudElem* elem, const char* material);
void HudElem_SetColor(HudElem* elem, char r, char g, char b, char a);
void HudElem_SetGlow(HudElem* elem, char r, char g, char b, char a);