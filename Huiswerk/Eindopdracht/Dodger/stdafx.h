// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <list>
#include <mutex>

#include "include/Leap/Leap.h"
#include "include/GL/freeglut.h"
#include "include/irrKlang/irrKlang.h"

//Entity Engine
#include "Component.h"
#include "Entity.h"

#include "UserInterfaceComponent.h"

#include "ObjModelComponent.h"
#include "AudioComponent.h"

#include "CollisionComponent.h"
#include "SpawnerComponent.h"
#include "ShipComponent.h"
#include "AstroidComponent.h"

//Audio Engine
#include "Audio.h"
#include "stb_image.h"

//Game Engine
#include "Engine.h"

//Render Engine
#include "ObjLibrary.h"
#include "ObjModel.h"
#include "Window.h"

//Input Engine
#include "LeapController.h"

// TODO: reference additional headers your program requires here
