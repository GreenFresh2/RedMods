/*
	The Redacted T6 project uses research by Bas Timmer, the OpenSteamworks project and codresearch(.com). 

	Purpose of this file: Standard header.
	Initial author: Convery
	Started: 2014-06-18
*/

#pragma once

// Warnings should not be needed.
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#define STRSAFE_NO_DEPRECATE
#define STRSAFE_NO_CCH_FUNCTIONS
#define WIN32_LEAN_AND_MEAN

// This should be updated for every release.
#define DEBUG // Debug output

#ifdef DEBUG
	#define DBG(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
	#define DBG(fmt, ...)
#endif

// C++ headers.
#include <sdkddkver.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <intrin.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// C headers.
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <queue>
#include <list>
#include <map>

// Our headers.
#include "GlobalVariables.h"
#include "Utility\Utility.h"
#include "GSC\GSC.h"
#include "HKS\HKS.h"













