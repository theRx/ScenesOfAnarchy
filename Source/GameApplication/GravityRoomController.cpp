#include "GameApplicationPCH.h"
#include "GravityRoomController.h"
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokPhysicsModule.hpp>
#include <Vision/Runtime/EnginePlugins/Havok/HavokPhysicsEnginePlugin/vHavokRagdoll.hpp>

GravityRoomController::GravityRoomController(void)
{
	VisBaseEntity_cl *pCamera  = Vision::Game.SearchEntity("CameraPosition");
	Vision::Camera.AttachToEntity(pCamera, hkvVec3::ZeroVector());
}


GravityRoomController::~GravityRoomController(void)
{
}

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
void GravityRoomController::Run(VInputMap* inputMap){
		if(inputMap->GetTrigger(CUSTOM_CONTROL_ONE)){
			AddCube();
		}
		if(inputMap->GetTrigger(CUSTOM_CONTROL_TWO)){
			AddSphere();
		}
		if(inputMap->GetTrigger(CUSTOM_CONTROL_THREE)){
			AddRagdoll();
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