#pragma once

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <gl\GL.h>

#include "hook.h"
#include "mem.h"
#include "proc.h"
#include "glDraw.h"
#include "gltext.h"

struct vec3 { float x, y, z; };