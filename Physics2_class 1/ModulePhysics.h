#pragma once
#include "Module.h"
#include "Globals.h"

#define STEP1 1.0f/60.0f,8,3
#define PIXEL_TO_METER(n)  (n/102.4f)
#define METER_TO_PIXEL(n)  (n*102.4f)

class b2World;


class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:

	b2World* world;
	bool debug;
};