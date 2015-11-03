#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) :
	Module(app, start_enabled),
	graphics(NULL),
	voltorb1(NULL),
	voltorb2(NULL),
	bumper1(NULL),
	bumper2(NULL),
	diglet1(NULL),
	diglet2(NULL),
	tex_light(NULL),
	lights_up_animated(false),
	lights_up_counter(0),
	lights_up_hit_timer(0),
	lights_down_animated(false),
	lights_down_counter(0),
	lights_down_hit_timer(0)
{}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Music
	//App->audio->PlayMusic("pinball/Rhinoceros2.ogg", 0.0f);

	// Graphics
	graphics = App->textures->Load("game/pinball/field_empty_b.png");

	voltorb1 = App->textures->Load("game/pinball/electrode.png");
	voltorb2 = App->textures->Load("game/pinball/electrode_hit.png");

	bumper1 = App->textures->Load("game/pinball/Bumper_izq.png");
	bumper2 = App->textures->Load("game/pinball/Bumper_der.png");

	diglet1 = App->textures->Load("game/pinball/diglet_hit.png");
	diglet2 = App->textures->Load("game/pinball/diglet_hit.png");

	tex_light = App->textures->Load("game/pinball/sensor_tiny.png");

	// FX's
	fx_bumper1 = App->audio->LoadFx("game/pinball/ding_short.wav");
	fx_bumper2 = App->audio->LoadFx("game/pinball/ring.wav");

	fx_light = App->audio->LoadFx("game/pinball/bonus2.wav");

	player_lose_fx = App->audio->LoadFx("game/pinball/long_bonus.wav");
	player_restart_fx = App->audio->LoadFx("game/pinball/long_bonus2.wav");

	// Pivot 0, 0
	int pinball[114] = {
		148, 749,
		100, 723,
		54, 692,
		18, 673,
		14, 562,
		24, 532,
		58, 517,
		63, 471,
		71, 451,
		60, 433,
		32, 336,
		23, 248,
		24, 221,
		25, 158,
		40, 117,
		70, 78,
		121, 40,
		170, 24,
		219, 19,
		272, 20,
		322, 29,
		379, 63,
		429, 113,
		457, 154,
		472, 251,
		471, 750,
		429, 750,
		425, 226,
		414, 178,
		395, 140,
		351, 101,
		312, 80,
		265, 66,
		216, 60,
		158, 71,
		104, 111,
		154, 93,
		193, 80,
		243, 84,
		283, 87,
		328, 105,
		383, 161,
		401, 228,
		396, 323,
		372, 421,
		353, 453,
		362, 464,
		366, 468,
		371, 518,
		397, 521,
		412, 542,
		410, 671,
		374, 689,
		369, 690,
		280, 749,
		273, 818,
		156, 823
	};

	App->physics->AddEdge({0, 0, 517, 751}, pinball, 114);

	// Pivot 0, 0
	int pinball2[26] = {
		157, 349,
		142, 343,
		129, 321,
		118, 288,
		117, 245,
		121, 204,
		130, 181,
		134, 202,
		124, 227,
		135, 265,
		155, 286,
		174, 312,
		177, 326
	};

	App->physics->AddEdge({0, 0, 517, 751}, pinball2, 26);
	
	// Pivot 0, 0
	int pinball3[26] = {
		77, 231,
		66, 255,
		64, 308,
		65, 325,
		68, 340,
		73, 355,
		85, 383,
		104, 409,
		119, 395,
		119, 386,
		91, 344,
		76, 284,
		81, 236
	};

	App->physics->AddEdge({0, 0, 0, 0}, pinball3, 26);
	
	// Pivot 0, 0
	int pinball4[50] = {
		280, 315,
		284, 291,
		280, 271,
		288, 254,
		295, 250,
		293, 228,
		297, 225,
		297, 131,
		321, 151,
		347, 180,
		360, 213,
		365, 220,
		364, 310,
		354, 355,
		338, 393,
		325, 408,
		309, 394,
		331, 361,
		340, 331,
		354, 273,
		352, 246,
		315, 247,
		308, 297,
		293, 328,
		283, 321
	};

	App->physics->AddEdge({0, 0, 0, 0}, pinball4, 50);
	
	// Pivot 0, 0
	int pinball5[12] = {
		51, 559,
		53, 645,
		140, 698,
		136, 685,
		58, 631,
		57, 558
	};

	App->physics->AddEdge({0, 0, 0, 0}, pinball5, 12);
	
	// Pivot 0, 0
	int pinball6[12] = {
		292, 688,
		369, 630,
		370, 564,
		377, 563,
		374, 643,
		294, 701
	};

	App->physics->AddEdge({0, 0, 0, 0}, pinball6, 12);
	
	// Pivot 0, 0
	int pinball7[10] = {
		100, 565,
		131, 628,
		128, 636,
		96, 615,
		95, 566
	};

	App->physics->AddEdge({0, 0, 0, 0}, pinball7, 10);

	// Pivot 0, 0
	int pinball8[8] = {
		330, 610,
		331, 570,
		299, 630,
		324, 616
	};
	
	App->physics->AddEdge({0, 0, 0, 0}, pinball8,8);
	
	// Pivot 0, 0
	int pinball9[8] = {
		177, 130,
		178, 170,
		189, 166,
		191, 128
	};

	App->physics->AddEdge({0, 0, 0, 0}, pinball9, 8);

	// Pivot 0, 0
	int pinball10[8] = {
		237, 118,
		237, 146,
		249, 148,
		250, 117
	};

	App->physics->AddEdge({0, 0, 0, 0}, pinball10, 8);

	// Other elements ------------------------------------------------

	// Small bouncy ball bottom center under flippers
	App->physics->AddBody(216, 745,5, b_static, 1.0f, 0.8f);

	// Bouncers on the sides
	// Pivot 0, 0
	int b1[8] = {
		99, 568,
		125, 622,
		135, 616,
		108, 563
	};

	// Pivot 0, 0
	int b2[8] = {
		289, 625,
		299, 629,
		329, 570,
		317, 562
	};


	// VOLTORBS
	voltorbs[0].texture = voltorb2;
	voltorbs[0].body = App->physics->AddBody(232, 286, 42, b_static, 1.0f, 1.5f);
	voltorbs[0].body->GetPosition(voltorbs[0].x, voltorbs[0].y);


	// BOUNCERS




	

	// LIGHTS UP
	int light_radius = 6;

	lights_up[0].on = false;
	lights_up[0].body = App->physics->AddBody(0 + light_radius, 0 + light_radius, light_radius * 2, b_static, 1.0f, 1.0f, false, true);
	lights_up[0].body->GetPosition(lights_up[0].x, lights_up[0].y);


	// LIGHTS DOWN
	
	
	// Sensor for player losing (under flippers)
	player_lose = App->physics->AddBody({245, 1080, 200, 50}, b_static, 1.0f, 0.0f, false, true);
	player_lose->listener = this;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);
	App->textures->Unload(voltorb1);
	App->textures->Unload(voltorb2);
	App->textures->Unload(bumper1);
	App->textures->Unload(bumper2);
	App->textures->Unload(diglet1);
	App->textures->Unload(diglet2);
	App->textures->Unload(tex_light);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(graphics, 0, 0);

	// bouncers up
	for (unsigned int i = 0; i < 3; i++)
	{
		switch (voltorbs[i].Update())
		{
		case 0: break;
		case 1: App->renderer->Blit(voltorbs[i].texture, voltorbs[i].x, voltorbs[i].y); break;
		case 2: App->scene_intro->score += VOLTORB_SCORE; break;
		default: break;
		}
	}

	// bouncers down
	for (unsigned int i = 0; i < 4; i++)
	{
		switch (bumpers[i].Update())
		{
		case 0: break;
		case 1: App->renderer->Blit(bumpers[i].texture, bumpers[i].x, bumpers[i].y); break;
		case 2: App->scene_intro->score += BUMPER_SCORE; break;
		default: break;
		}
	}

	// lights up
	for (unsigned int i = 0; i < 3; i++)
	{
		if (!lights_up_animated)
		{
			if (lights_up[i].on)
				App->renderer->Blit(tex_light, lights_up[i].x, lights_up[i].y); break;
		}
		else
		{
			if (lights_up_counter < 2 * BLINK_MULTIPLIER)
			{
				if (lights_up_counter % 2 == 0) // on
				{
					if (SDL_TICKS_PASSED(SDL_GetTicks(), lights_up_hit_timer) == false)
					{
						App->renderer->Blit(tex_light, lights_up[i].x, lights_up[i].y);
					}
					else
					{
						lights_up_hit_timer = SDL_GetTicks() + BOUNCER_TIME;
						lights_up_counter++;
					}
				}
				else //off
				{
					if (SDL_TICKS_PASSED(SDL_GetTicks(), lights_up_hit_timer))
					{
						lights_up_hit_timer = SDL_GetTicks() + BOUNCER_TIME;
						lights_up_counter++;
					}
				}
			}
			else
			{
				lights_up_animated = false;
				lights_up[i].on = false;
			}
		}
	}

	// lights down
	for (unsigned int i = 0; i < 4; i++)
	{
		if (!lights_down_animated)
		{
			if (lights_down[i].on)
				App->renderer->Blit(tex_light, lights_down[i].x, lights_down[i].y); break;
		}
		else
		{
			if (lights_down_counter < 2 * BLINK_MULTIPLIER)
			{
				if (lights_down_counter % 2 == 0) // on
				{
					if (SDL_TICKS_PASSED(SDL_GetTicks(), lights_down_hit_timer) == false)
					{
						App->renderer->Blit(tex_light, lights_down[i].x, lights_down[i].y);
					}
					else
					{
						lights_down_hit_timer = SDL_GetTicks() + BOUNCER_TIME;
						lights_down_counter++;
					}
				}
				else //off
				{
					if (SDL_TICKS_PASSED(SDL_GetTicks(), lights_down_hit_timer))
					{
						lights_down_hit_timer = SDL_GetTicks() + BOUNCER_TIME;
						lights_down_counter++;
					}
				}
			}
			else
			{
				lights_down_animated = false;
				lights_down[i].on = false;
			}
		}
	}

	// check animation
	unsigned int size = 0;
	for (unsigned int i = 0; i < 3; i++)
	{
		if (lights_up[i].on)
			size++;
	}
	lights_up_animated = (size == 3);
	if (lights_up_animated)
	{
		lights_up_hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		lights_up_counter = 0;
	}


	size = 0;
	for (unsigned int i = 0; i < 4; i++)
	{
		if (lights_down[i].on)
			size++;
	}
	lights_down_animated = (size == 4);
	if (lights_down_animated)
	{
		lights_down_hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		lights_down_counter = 0;
	}

	// Update title with score
	char title[50];
	sprintf_s(title, "Balls: %d Score: %06d Last Score: %06d", lives, score, last_score);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::OnCollision(PhysBody* body1, PhysBody* body2)
{

	for (unsigned int i = 0; i < 3; i++)
	{
		if (voltorbs[i].body == body1)
		{
			voltorbs[i].hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		}
	}
	
	for (unsigned int i = 0; i < 4; i++)
	{
		if (bumpers[i].body == body1)
		{
			bumpers[i].hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		}
	}

	// lights up
	if (!lights_up_animated)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if (lights_up[i].CheckCollision(body1))
			{
				if (!lights_up[i].on)
				{
					App->audio->PlayFx(fx_light);
					App->scene_intro->score += LIGHT_SCORE;
					lights_up[i].on = true;
				}
				return;
			}
		}
	}

	// lights down
	if (!lights_down_animated)
	{
		for (unsigned int i = 0; i < 4; i++)
		{
			if (lights_down[i].CheckCollision(body1))
			{
				if (!lights_down[i].on)
				{
					App->audio->PlayFx(fx_light);
					App->scene_intro->score += LIGHT_SCORE;
					lights_down[i].on = true;
				}
				return;
			}
		}
	}


	if(player_lose == body1)
	{
		App->player->ball.body->SetLinearSpeed(0, 0);
		App->player->ball.body->SetAngularSpeed(0);
		App->player->ball.body->SetPosition(563, 582);
		lives--;

		if(lives <= 0)
		{
			last_score = score;
			score = 0;
			lives = 3;
			App->audio->PlayFx(player_restart_fx);
		}
		else
		{
			App->audio->PlayFx(player_lose_fx);
		}

		return;
	}
}



Bouncer::Bouncer() : body(NULL), texture(NULL), x(0), y(0)
{}

int Bouncer::Update()
{
	int ret = 0;
	if (hit_timer > 0)
	{
		ret++;
		if (!(SDL_TICKS_PASSED(SDL_GetTicks(), hit_timer) == false))
		{
			ret++;
			hit_timer = 0;
		}
	}
	return ret;
}


bool Bouncer::CheckCollision(PhysBody* body1)
{
	bool ret = (body == body1);
	if (ret) hit_timer = SDL_GetTicks() + BOUNCER_TIME;
	return ret;
}

Light::Light() : on(false), body(NULL), x(0), y(0)
{}

int Light::Update()
{
	return (on ? 1 : 0);
}

bool Light::CheckCollision(PhysBody* body1)
{
	return (body == body1);
}