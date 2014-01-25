/*
*
* Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
* prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
* Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2013 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
*
*/


// Basic template to base a project EXE on.
//
//


#include "GameApplicationPCH.h"
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokPhysicsModule.hpp>
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokRagdoll.hpp>


//============================================================================================================
// Properties for start up. Some of the settings are not relevant for mobile devices
//============================================================================================================
int windowSizeX    = 1024;               // Set the Window size X if not in fullscreen.
int windowSizeY    = 768;                // Set the Window size Y if not in fullscreen.
int windowPosX    = 500;                 // Set the Window position X if not in fullscreen.
int windowPosy    = 50;                  // Set the Window position Y if not in fullscreen.

char name[]      = "Scenes of Anarchy";  // Name to be displayed in the windows title bar.
char StartUpScene[]  = "Scenes\\GravityRoom.vscene";   // Set the location of your start up scene.

float cameraInitX = 0;                    //
float cameraInitY = 0;                    //
float cameraInitZ = 1000;                  // Set our camera above the ground so that we can see 
// the ground.
IVMultiTouchInput* touchscreen;
// Use the following line to initialize a plugin that is statically linked. 
// Note that only Windows platform links plugins dynamically (on Windows you can comment out this line).
VIMPORT IVisPlugin_cl* GetEnginePlugin_GamePlugin();

VisSampleAppPtr spApp;

//Width and Height of Screen
int width;
int height;

int bodyCount = 0;

//Define additional inputs over what VisSampleApp.cpp does
enum CUSTOM_INPUT_CONTROL{
	VICLE = VISION_INPUT_CONTROL_LAST_ELEMENT,
#if defined(WIN32)
	LEFT_CLICK,
#endif
#if defined(_VISION_ANDROID)
	TAP_BOTTOM_RIGHT,
	TAP_BOTTOM_LEFT,
	TAP_TOP_RIGHT,
	TAP_TOP_LEFT,
#endif
	CUSTOM_INPUT_CONTROL_LAST_ELEMENT
};


#if defined(_VISION_ANDROID)
//Pointer to accelerometer
VMotionInputAndroid* pMotionInput = NULL;
//Pointer to physics module
vHavokPhysicsModule* pMod;
#endif
//---------------------------------------------------------------------------------------------------------
// Init function. Here we trigger loading our scene
//---------------------------------------------------------------------------------------------------------
VISION_INIT
{
	// Create our new application.
	spApp = new VisSampleApp();

	// set the initial starting position of our game window
	// and other properties if not in fullscreen. This is only relevant on windows
#if defined(WIN32)
	spApp->m_appConfig.m_videoConfig.m_iXPos = windowPosX;
	spApp->m_appConfig.m_videoConfig.m_iYPos = windowPosy;
	spApp->m_appConfig.m_videoConfig.m_szWindowTitle = name;
#endif

	// Set the executable directory the current directory
	VisionAppHelpers::MakeEXEDirCurrent();

	// Set the paths to our stand alone version to override the VisSAampleApp paths.
	// The paths are platform dependent
#if defined(WIN32)
	const VString szRoot = "..\\..\\..\\..";
	Vision::File.AddDataDirectory( szRoot + "\\Assets" );
	Vision::File.AddDataDirectory( szRoot + "\\Data\\Vision\\Base" );

#elif defined(_VISION_ANDROID)
	VString szRoot = VisSampleApp::GetApkDirectory();
	szRoot += "?assets";
	Vision::File.AddDataDirectory( szRoot + "\\Assets" );
	// "/Data/Vision/Base" is always added by the sample app

#elif defined(_VISION_TIZEN)
	VString szRoot = VisSampleApp::GetDataRootDirectory();
	Vision::File.AddDataDirectory( szRoot + "\\Assets" );
	// "/Data/Vision/Base" is always added by the sample app

#elif defined(_VISION_IOS)
	// setup directories, does nothing on platforms other than iOS,
	// pass true if you want load from the documents directory
	VISION_SET_DIRECTORIES(false);
	VString szRoot = VisSampleApp::GetRootDirectory();
	// our deploy script always copies the asset data below the "Data" folder
	Vision::File.AddDataDirectory( szRoot + "/Data/Assets" );
	// "/Data/Vision/Base" is always added by the sample app

#endif

#if defined(VISION_OUTPUT_DIR)
	// Set the output directory manually since VSAMPLE_CUSTOMDATADIRECTORIES was specified
	// at the initialization.
	Vision::File.SetOutputDirectory(VISION_OUTPUT_DIR);
	Vision::File.AddDataDirectory(VISION_OUTPUT_DIR);
#endif

	spApp->LoadVisionEnginePlugin();

	// Use the following line to load a plugin. Remember that, except on Windows platform, in addition
	// you still need to statically link your plugin library (e.g. on mobile platforms) through project
	// Properties, Linker, Additional Dependencies.
	VISION_PLUGIN_ENSURE_LOADED(GamePlugin);

	// Init the application and point it to the start up scene.
	if (!spApp->InitSample( "", StartUpScene, VSampleFlags::VSAMPLE_INIT_DEFAULTS|VSampleFlags::VSAMPLE_CUSTOMDATADIRECTORIES,windowSizeX,windowSizeY))
		return false;

	return true;
}

//---------------------------------------------------------------------------------------------------------
// Gets called after the scene has been loaded
//---------------------------------------------------------------------------------------------------------

VISION_SAMPLEAPP_AFTER_LOADING
{
	// define some help text
	spApp->AddHelpText( "" );
	spApp->AddHelpText( "How to use this demo :" );
	spApp->AddHelpText( "" );

	//Look for predefined camera and attach it
	VisBaseEntity_cl *pCamera  = Vision::Game.SearchEntity("CameraPosition");
	Vision::Camera.AttachToEntity(pCamera, hkvVec3::ZeroVector());

	//Get the width and height of the screen.
	 width = Vision::Video.GetXRes();
	 height = Vision::Video.GetYRes();

#if defined(_VISION_ANDROID)
	 //Grab the motion device for input and enable it
	pMotionInput = (VMotionInputAndroid*)(&VInputManager::GetInputDevice(INPUT_DEVICE_MOTION_SENSOR));
	pMotionInput->SetEnabled(true);
	//Grab the physics module from the spApp.
	pMod = static_cast<vHavokPhysicsModule*>(spApp->GetPhysicsModule());

	//register triggers
	VTouchArea* addRagdollArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef((float)width * .65f, (float)height * .70f, (float)width, (float)height), -900.0f);
	spApp->GetInputMap()->MapTrigger(TAP_BOTTOM_RIGHT, addRagdollArea, CT_TOUCH_ANY);
	VTouchArea* addCubeArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(0.0f, (float)height*.70f, (float)width*.35f, (float)height), -900.0f);
	spApp->GetInputMap()->MapTrigger(TAP_BOTTOM_LEFT, addCubeArea, CT_TOUCH_ANY);
	VTouchArea* addSphereArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef((float)width * .65f, 0.0f, (float)width, (float)height * .35f), -900.0f);
	spApp->GetInputMap()->MapTrigger(TAP_TOP_RIGHT, addSphereArea, CT_TOUCH_ANY);

#endif// Add other initial game code here
	// [...]
}

//---------------------------------------------------------------------------------------------------------
// main loop of the application until we quit
//---------------------------------------------------------------------------------------------------------

void AddRagdoll(){	
	VisBaseEntity_cl *ent2 = Vision::Game.CreateEntity("VisBaseEntity_cl", hkvVec3(-100.0f, 5, 100), "Models\\Warrior\\Warrior.model");
	vHavokRagdoll *ragdoll = new vHavokRagdoll();
	ragdoll->SetRagdollCollisionFile("Models\\Warrior\\WarriorRagdoll.hkt");
	ent2->AddComponent(ragdoll);

}
void AddCube(){

	VisBaseEntity_cl *ent2 = Vision::Game.CreateEntity("VisBaseEntity_cl", hkvVec3(-100.0f, 30, 100), "Models\\Misc\\Cube.Model");
	vHavokRigidBody *cube = new vHavokRigidBody();
	cube->Havok_TightFit = true;
	ent2->AddComponent(cube);

}
void AddSphere(){

	VisBaseEntity_cl *ent2 = Vision::Game.CreateEntity("VisBaseEntity_cl", hkvVec3(-100.0f, -30, 100), "Models\\Misc\\Sphere.Model");
	vHavokRigidBody *sphere = new vHavokRigidBody();
	sphere->Havok_TightFit = true;
	sphere->Havok_Restitution = 1.0f;
	ent2->AddComponent(sphere);

}


VISION_SAMPLEAPP_RUN
{ 
#if defined(_VISION_ANDROID)
	//Print out the bodycount 
	Vision::Message.Print(0,0,0,"Number of Bodies %d", bodyCount);
	//Grab the accel data
	hkvVec3 accel = pMotionInput->GetAcceleration();
	//Multiply it by 1K to increase the intensity
	accel = accel *1000;
	//Havok uses weird axises (axi?) so they had to be swapped and negated
	hkvVec3 gravity = hkvVec3(-1*accel.z,-1*accel.x,accel.y);
	//set the new gravity
	pMod->SetGravity(gravity);
	//Listen for triggers
	if(spApp->GetInputMap()->GetTrigger(TAP_BOTTOM_RIGHT)){
		AddRagdoll();
		bodyCount++;
	}
	if(spApp->GetInputMap()->GetTrigger(TAP_BOTTOM_LEFT)){
		AddCube();
		bodyCount++;
	}
	if(spApp->GetInputMap()->GetTrigger(TAP_TOP_RIGHT)){
		AddSphere();
		bodyCount++;
	}
#endif// Add other initial game co
	return spApp->Run();
}

VISION_DEINIT
{
	// Deinit the application
	spApp->DeInitSample();
	spApp = NULL;
	return true;
}

VISION_MAIN_DEFAULT

	/*
	* Havok SDK - Base file, BUILD(#20131022)
	* 
	* Confidential Information of Havok.  (C) Copyright 1999-2013
	* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
	* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
	* rights, and intellectual property rights in the Havok software remain in
	* Havok and/or its suppliers.
	* 
	* Use of this software for evaluation purposes is subject to and indicates
	* acceptance of the End User licence Agreement for this product. A copy of
	* the license is included with this software and is also available from salesteam@havok.com.
	* 
	*/
