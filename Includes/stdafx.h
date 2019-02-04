// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers



// reference additional headers your program requires here
// Windows
#include <windows.h>
#include <wrl.h>
#include <objbase.h>

// Standard
#include <exception>
#include <cassert>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <stack>
#include <cstdint>
#include <iomanip>
#include <codecvt>
#include <algorithm>
#include <functional>
#include <iterator>
#include <comdef.h>
#include <Shlwapi.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <d3d11_2.h>
#include <d3dx11Effect.h>
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <GamePad.h>



#include "EngineEnums.h"
#include "StringEncryptionRC4.h"
#include "D3DCompiler.h"
#include "EngineUtility.h"
#include <dinput.h>
#include "EngineRTTI.h"
#include "EngineException.h"
#include "EngineClock.h"
#include "EngineTime.h"
#include "EngineServiceContainer.h"
#include "EngineComponent.h"
#include "Engine.h"
#include "DrawableComponent.h"
#include "FramesPerSecond.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"
#include "ColorHelper.h"
#include "MatrixHelper.h"
#include "VectorHelper.h"
#include "MathHelper.h"
#include "Camera.h"
#include "FirstPersonCamera.h"
#include "OrthographicCamera.h"
#include "Grid.h"
#include "RenderStateHelper.h"
#include "EngineStructs.h"