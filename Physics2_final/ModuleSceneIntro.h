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

struct VoltorbAnim
{
	VoltorbAnim() : x(0), y(0), counter(0)
	{}

	void Update()
	{
		counter = (counter == 3 ? 0 : counter++);

		switch (counter)
		{
		case 0: x = 1; y = -1; break;
		case 1: x = 1; y = 1; break;
		case 2: x = -1; y = 1; break;
		case 3: x = -1; y = -1; break;
		default: break;
		}
	}

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

/*
// bouncers up
for (unsigned int i = 0; i < 3; i++)
{
	volt[i].Update();

	switch (voltorbs[i].Update())
	{
	case 0: App->renderer->Blit(voltorb1, voltorbs[i].x + volt[i].x, voltorbs[i].y + volt[i].y);
	case 1: App->renderer->Blit(voltorb2, voltorbs[i].x, voltorbs[i].y); break;
	case 2: App->scene_intro->score += VOLTORB_SCORE; break;
	default: break;
	}
}
*/