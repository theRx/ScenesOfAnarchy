#include "GameApplicationPCH.h"
#include "GravityRoomController.h"

GravityRoomController::GravityRoomController(void)
{
	VisBaseEntity_cl *pCamera  = Vision::Game.SearchEntity("CameraPosition");
	Vision::Camera.AttachToEntity(pCamera, hkvVec3::ZeroVector());
}


GravityRoomController::~GravityRoomController(void)
{
}

void GravityRoomController::Run(VInputMap* inputMap){
		if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE)){
			GravityRoomController::AddCube();
		}
		if(inputMap->GetTrigger(CUSTOM_CONTROL_TWO)){
			GravityRoomController::AddSphere();
		}
		if(inputMap->GetTrigger(CUSTOM_CONTROL_THREE)){
			GravityRoomController::AddRagdoll();
		}
}

void GravityRoomController::MapTriggers(VInputMap* inputMap){

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