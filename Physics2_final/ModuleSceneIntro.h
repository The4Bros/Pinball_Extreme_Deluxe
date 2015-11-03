#pragma once
#include "Module.h"

#define VOLTORB_SCORE 50
#define BUMPER_SCORE 50
#define DIGLET_SCORE 50
#define LIGHT_SCORE 50

#define BOUNCER_TIME 200
#define BLINK_MULTIPLIER 4
#define LIGHT_RADIUS 6

struct Bouncer
{
public:
	Bouncer();
	int Update();
	bool CheckCollision(PhysBody* body1);

public:
	Uint32 hit_timer;
	SDL_Texture* texture;
	PhysBody* body;
	int x, y;
};

struct Light
{
public:
	Light();
	int Update();
	bool CheckCollision(PhysBody* body1);

public:
	bool on;
	PhysBody* body;
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

	Bouncer voltorbs [3];
	Bouncer bumpers[4];

	Light lights_up[3];
	Light lights_down[4];

	bool lights_up_animated;
	int lights_up_counter;
	uint lights_up_hit_timer;

	bool lights_down_animated;
	int lights_down_counter;
	uint lights_down_hit_timer;

	SDL_Texture* voltorb1;
	SDL_Texture* voltorb2;
	SDL_Texture* bumper1;
	SDL_Texture* bumper2;
	SDL_Texture* diglet1;
	SDL_Texture* diglet2;
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




