#pragma once
#include <Windows.h>


#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>


//windows.h���� tchar.h�� framework.h���� ������
//framework.h�� include�Ȱ� �ּ�ó����
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