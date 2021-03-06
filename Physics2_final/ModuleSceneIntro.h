#pragma once
#include "Module.h"


#define VOLTORB_SCORE 50
#define BUMPER_SCORE 50
#define DIGLET_SCORE 50
#define LIGHT_SCORE 50

#define VOLTORB_TICKER 75

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
	Uint32 hit_timer = 0;
	SDL_Texture* texture;
	PhysBody* body;
	int x, y;
};

struct VoltorbAnim
{
	VoltorbAnim() : x(6), y(6), counter(0)
	{}

	void Update()
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), hit_timer))
		{
			hit_timer = SDL_GetTicks() + VOLTORB_TICKER;

			if (counter >= 2)
				counter = 0;
			else
				counter++;

			switch (counter)
			{
			case 0: x = 6; y = -6; break;
			case 1: x = 6; y = 6; break;
			case 2: x = -6; y = 6; break;
				//case 3: x = -6; y = -6; break;
			default: break;
			}

			LOG("%i", counter);
		}
	}

	Uint32 hit_timer = 0;
	int counter = 0;
	bool hit = false;
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

	VoltorbAnim volt[3];

	Bouncer voltorbs[3];
	Bouncer bumpers[4];

	Light lights_up[7];

	bool lights_up_animated;
	int lights_up_counter;
	uint lights_up_hit_timer;

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