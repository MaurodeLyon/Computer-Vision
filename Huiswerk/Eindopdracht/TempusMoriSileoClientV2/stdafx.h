// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <list>

#include "include/Leap/Leap.h"
#include "include/GL/freeglut.h"
#include "irrKlang/irrKlang.h"

//Entity Engine
#include "Component.h"
#include "Entity.h"
#include "CollisionComponent.h"
#include "AttackComponent.h"
#include "ObjModelComponent.h"
#include "MenuComponent.h"
#include "UnitComponent.h"
#include "NPCComponent.h"

#include "PlayerComponent.h"

#include "SpellAreaComponent.h"
#include "SpellMoveComponent.h"
#include "Spawner"

#include "AudioComponent.h"
#include "CursorComponent.h"


//Audio Engine
#include "UserInterfaceComponent.h"
#include "UnitComponent.h"
#include "stb_image.h"

//Network Engine
#include "Client.h"
#include "packet.h"
#include "MobPacket.h"
#include "Loginpacket.h"
#include "SpellPacket.h"


//Game Engine
#include "Engine.h"

//Render Engine
#include "ObjLibrary.h"
#include "ObjModel.h"
#include "Window.h"

//Input Engine
#include "LeapController.h"
// TODO: reference additional headers your program requires here
