#pragma once
#include "IController.h"
class GravityRoomController : public IController{
public:
	GravityRoomController(void);
	virtual ~GravityRoomController(void);
	virtual void MapTriggers(VInputMap* inputMap) HKV_OVERRIDE;
	virtual void Run(VInputMap* inputMap) HKV_OVERRIDE;
};

