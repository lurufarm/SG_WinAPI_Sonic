#pragma once
#include <Windows.h>


#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>


//windows.h부터 tchar.h는 framework.h에서 가져옴
//framework.h에 include된건 주석처리함
#include <string>
#include <vector>
#include <list>
#include <map>
#include <functional>
#include <filesystem>

#pragma comment(lib, "Msimg32.lib")

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dsound.lib")

#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64