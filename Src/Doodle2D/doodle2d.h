#ifndef _D2D_DOOLE2D_H_
#define _D2D_DOOLE2D_H_

// 0x00 HI ME LO
// 00   02 00 00
#define	DOODLE2D_VERSION 0x00000001

//
// all doodle2d include files
//

#include "common/config.h"

// common

#include "common/context.h"
#include "common/Log.h"
#include "common/Resource.h"
#include "common/types.h"
#include "common/math.h"
#include "common/Vector.h"
#include "common/tools.h"
#include "common/string_tools.h"
#include "common/DrawingPrimitives.h"
#include "common/math.h"
#include "common/AABB.h"
#include "common/Object.h"

// modules

#include "modules/filesystem/FileSystem.h"
#include "modules/filesystem/PhysicsParser.h"

#include "modules/graphics/GraphicsService.h"
#include "modules/graphics/FrameAnimSprite.h"
#include "modules/graphics/Texture.h"
#include "modules/graphics/TextureInfo.h"
#include "modules/graphics/TileMap.h"
#include "modules/graphics/SpriteBatch.h"
#include "modules/graphics/MeshBatch.h"
#include "modules/graphics/TileStencilBatch.h"
#include "modules/graphics/Quad.h"
#include "modules/graphics/Mesh.h"
#include "modules/graphics/IDrawable.h"
#include "modules/graphics/Camera.h"
#include "modules/graphics/Color.h"

#include "modules/input/InputHandler.h"
#include "modules/input/InputService.h"
#include "modules/input/Sensor.h"
#include "modules/input/EventList.h"

#include "modules/sound/Sound.h"
#include "modules/sound/SoundService.h"

#include "modules/physics/PhysicsService.h"
#include "modules/physics/PhysicsBody.h"
#include "modules/physics/BodyFactory.h"
#include "modules/physics/JointFactory.h"
#include "modules/physics/IContactListenerImpl.h"

#include "modules/timer/TimeService.h"

#include "modules/ui/Game.h"
#include "modules/ui/Scene.h"
#include "modules/ui/Actor.h"
#include "modules/ui/Button.h"
#include "modules/ui/ChangeScene.h"
#include "modules/ui/ScaleSize.h"

#include "modules/test/b2GLESRender.h"

// platform

#include "platform/android_native/ActivityHandler.h"
#include "platform/android_native/EventLoop.h"

#include "platform/android_jni/ActivityHandler.h"

#include "platform/windows/ActivityHandler.h"

// libraries

#include "libraries/cocos2d-x/JniHelper.h"

#endif // _D2D_DOOLE2D_H_