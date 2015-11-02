#pragma once
#include "Module.h"
#include "Animation.h"
#include "p2DynArray.h"
#include "Globals.h"

#define BOUNCER_TIME 200

struct Bouncer
{
	Bouncer() : body(NULL), texture(NULL), hit_timer(0), fx(0)
	{}

	PhysBody* body;
	SDL_Texture* texture;
	Uint32 hit_timer;
	uint fx;
};

class ModuleSceneIntro;

struct Light
{
	Light() : body(NULL), texture(NULL), on(false), fx(0)
	{}

	Light(ModuleSceneIntro* physics, int x, int y);

	PhysBody* body;
	SDL_Texture* texture;
	bool on;
	uint fx;
	int x, y;

};

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

	Bouncer bouncer1;
	Bouncer bouncer2;
	Bouncer bouncer3;

	Bouncer voltorb_bouncer1;
	Bouncer voltorb_bouncer2;
	Bouncer voltorb_bouncer3;

	Bouncer diglet_bouncer1;
	Bouncer diglet_bouncer2;

	SDL_Texture* tex_light;
	uint fx_light;

	p2DynArray<Light> lights;

	PhysBody* player_lose;
	uint player_lose_fx;
	uint player_restart_fx;
	uint last_score = 0;
	uint score = 0;
	uint lives = 3;
};
