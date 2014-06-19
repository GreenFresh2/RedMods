/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Defining public Havok Kore Script patches.
	Initial author: Convery
	Started: 2014-06-19
*/

void InitHKS();

// Not really a HKS struct.
struct RawFile
{
  const char *Name;
  int Length;
  const char *Buffer;
};