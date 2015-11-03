#pragma once
#include "Module.h"
#include "Globals.h"

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

class ModuleInput : public Module
{
public:
	
	ModuleInput(Application* app, bool start_enabled = true);
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	KEY_STATE GetKey(int id) const
	{
		return keyboard[id];
	}

	int GetMouseX() const
	{
		return mouse_x;
	}

	int GetMouseY() const
	{
		return mouse_y;
	}

	bool GetMouseDown() const
	{
		return mouse_down;
	}

private:
	KEY_STATE* keyboard;
	SDL_Event event;
	bool mouse_down;
	int mouse_x;
	int mouse_y;
};