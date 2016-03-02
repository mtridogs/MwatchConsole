#include <stdio.h>
#include <Windows.h>
#include "tlhelp32.h"
#include <list>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <vector>
#include "E:\tool\mytool\bin\libdasm-1.5\libdasm.h"
using namespace std;

typedef list<DWORD> LISTINT;
extern void EnableDebugPriv();
extern void init_printf();