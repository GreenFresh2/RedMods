/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Define GSC structs.
	Initial author: Convery, based on research by Kokole.
	Started: 2014-06-19
*/

#pragma once

void InitGSC();
void PostInitGSC();

typedef struct _gscFunction
{
        DWORD crc32;							// 0x00 - CRC32 of function bytecode
        DWORD start;							// 0x04 - A relative pointer to the GSC bytecode start of this function
        WORD name;                              // 0x08 - A relative pointer to the name of this function
        BYTE numOfParameters;					// 0x0A -
        BYTE flag;                              // 0x0B -
        /*
                Possible flag values (not sure if all of them):
 
                - If flag & 1, function loaded (I think?)
        */
} gscFunction;
 
typedef struct _COD9_GSC
{
        BYTE identifier[8];                     // 0x00 - It's the same always
        BYTE unknown1[4];                       // 0x08 - I think it's some kind of checksum
        DWORD includeStructs;					// 0x0C - A relative pointer to an array of includeStruct structs, amount = numOfIncludes
        DWORD usinganimtreeStructs;				// 0x10 - A relative pointer to an array of usinganimtreeStruct structs, amount = numOfUsinganimtree
        DWORD codeSectionStart;					// 0x14 - A relative pointer to where the GSC bytecode starts (gscFunctions)
        DWORD gscStrings;                       // 0x18 - A relative pointer to an array of gscString structs, amount = numOfStrings
        DWORD gscFunctions;                     // 0x1C - A relative pointer to an array of gscFunction structs, amount = numOfFunctions
        DWORD externalFunctions;				// 0x20 - A relative pointer to an array of externalFunction structs, amount = numOfExternalFunctions
        DWORD gscRelocations;					// 0x24 - A relative pointer to an array of gscRelocation structs, amount = numOfRelocations
        DWORD size;                             // 0x28 -
        DWORD codeSectionSize;					// 0x2C - Size of the executable bytecode
        WORD name;                              // 0x30 - A relative pointer to the name of this gsc (with full path and extension, null terminated)
        WORD numOfStrings;                      // 0x32 - IMPORTANT: Includes everything except #include strings, #using_animtree strings and function name strings
        WORD numOfFunctions;					// 0x34 - Number of functions in this script file
        WORD numOfExternalFunctions;			// 0x36 - Number of functions imported
        WORD numOfRelocations;					// 0x38 - Number of patches in the GSC code/file
        BYTE unknown4[2];                       // 0x3A - ?
        BYTE numOfIncludes;                     // 0x3C - Number of included source files
        BYTE numOfUsinganimtree;				// 0x3D - Number of included animation trees
        BYTE _padding[2];                       // 0x3E - Struct padding
} COD9_GSC; // size: 64 bytes
 
struct ScriptParseTree
{
        const char *name;
        int len;
        BYTE *buffer;
};