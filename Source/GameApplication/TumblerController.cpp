#include "GameApplicationPCH.h"
#include "TumblerController.h"

//Constructor
TumblerController::TumblerController(void)
{
	//Grabs the Tumbler and camera from vForge
	VisBaseEntity_cl *pCamera = Vision::Game.SearchEntity("CameraPosition");
	Vision::Camera.AttachToEntity(pCamera, hkvVec3::ZeroVector());
	//VisBaseEntity_cl *vTumbler = Vision::Game.SearchEntity("TumblerMachine");
#if defined(_VISION_ANDROID)
	pMod = static_cast<vHavokPhysicsModule*>(vHavokPhysicsModule::GetInstance());
#endif
}

//Deconstructor
TumblerController::~TumblerController(void)
{
}

//Runtime logic
void TumblerController::Run(VInputMap* inputMap)
{
	//static vector to set rotation for the tumbler
	//hkvVec3 torqueValue = hkvVec3(0, 100, 0);

	//Adding ragdolls and spheres and removing them
	if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE))
	{
		//this->AddCube();
		this->RemoveLast();
	}
	if(inputMap->GetTrigger(CUSTOM_CONTROL_THREE))
	{
		this->AddSphere();
		//this->RemoveLast();
	}
	/*if(inputMap->GetTrigger(CUSTOM_CONTROL_THREE))
	{
		this->AddRagdoll();
	}*/

}

//Input
void TumblerController::MapTriggers(VInputMap* inputMap){

#if defined(WIN32)
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, V_KEYBOARD, VInputControl::CT_KB_UP, VInputOptions::Once());
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, V_KEYBOARD, VInputControl::CT_KB_KP_DOWN, VInputOptions::Once());
	inputMap->MapTrigger(CUSTOM_CONTROL_THREE, V_KEYBOARD, VInputControl::CT_KB_LEFT, VInputOptions::Once());
#endif

#if defined(_VISION_ANDROID)
	int width = Vision::Video.GetXRes();
	int height = Vision::Video.GetYRes();
	VTouchArea* addRagdollArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef((float)width * .65f, (float)height * .70f, (float)width, (float)height), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_ONE, addRagdollArea, CT_TOUCH_ANY);
	VTouchArea* addCubeArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef(0.0f, (float)height*.70f, (float)width*.35f, (float)height), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_TWO, addCubeArea, CT_TOUCH_ANY);
	VTouchArea* addSphereArea = new VTouchArea(VInputManager::GetTouchScreen(),VRectanglef((float)width * .65f, 0.0f, (float)width, (float)height * .35f), -900.0f);
	inputMap->MapTrigger(CUSTOM_CONTROL_THREE, addSphereArea, CT_TOUCH_ANY);
#endif
}