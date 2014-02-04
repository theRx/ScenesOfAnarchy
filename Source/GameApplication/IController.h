#pragma once
#include "Constants.h"
class IController
{
public:
	IController(void);
	virtual ~IController(void);
	virtual void MapTriggers(VInputMap* inputMap){}
	virtual void Run(VInputMap* inputMap){}
};

