#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "SceneItems.h"

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(PhysBody* body1, PhysBody* body2);

public:

	SDL_Texture* graphics;
	PhysBody* background;

	ItemList<Bouncer*> bouncers;
	ItemList<Light*> lights_up;
	ItemList<Light*> lights_down;

	SDL_Texture* voltorb1;
	SDL_Texture* voltorb2;
	SDL_Texture* bumper1;
	SDL_Texture* bumper2;
	SDL_Texture* diglet;
	SDL_Texture* tex_light;

	uint fx_bumper1;
	uint fx_bumper2;
	uint fx_light;

	PhysBody* player_lose;
	uint player_lose_fx;
	uint player_restart_fx;
	uint last_score = 0;
	uint score = 0;
	uint lives = 3;
};
