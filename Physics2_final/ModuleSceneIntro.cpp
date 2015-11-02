#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
}

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
	graphics = App->textures->Load("pinball/field_empty_b.png");

	bouncer1.texture = App->textures->Load("pinball/Bumper_izq.png");
	bouncer2.texture = App->textures->Load("pinball/Bumper_der.png");

	voltorb_bouncer1.texture = voltorb_bouncer2.texture = voltorb_bouncer3.texture =
		App->textures->Load("pinball/electrode_hit.png");

	// FX's
	bouncer1.fx = bouncer2.fx = App->audio->LoadFx("pinball/ding_short.wav");
	voltorb_bouncer1.fx = voltorb_bouncer2.fx = voltorb_bouncer3.fx = App->audio->LoadFx("pinball/ring.wav");

	player_lose_fx = App->audio->LoadFx("pinball/long_bonus.wav");
	player_restart_fx = App->audio->LoadFx("pinball/long_bonus2.wav");

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

	// Two big bouncers on top
	voltorb_bouncer1.body = App->physics->AddBody(232, 286, 42, b_static, 1.0f, 1.5f);
	voltorb_bouncer1.body->listener = this;

	voltorb_bouncer2.body = App->physics->AddBody(178, 235, 42, b_static, 1.0f, 1.5f);
	voltorb_bouncer2.body->listener = this;

	voltorb_bouncer3.body = App->physics->AddBody(247, 209, 42, b_static, 1.0f, 1.5f);
	voltorb_bouncer3.body->listener = this;
	// Bouncers on the sides
	
	// Pivot 0, 0
	int b1[8] = {
		99, 568,
		125, 622,
		135, 616,
		108, 563
	};

	bouncer1.body = App->physics->AddBody({ 0, 0, 517, 751 }, b1, 8, b_static, 1.0f, 1.0f, false);
	bouncer1.body->listener = this;

	// Pivot 0, 0
	int b2[8] = {
		289, 625,
		299, 629,
		329, 570,
		317, 562
	};

	bouncer2.body = App->physics->AddBody({ 0, 0, 517, 751 }, b2, 8, b_static, 1.0f, 1.0f, false);
	bouncer2.body->listener = this;

	// Sensors (blue lights on the floor)
	tex_light = App->textures->Load("pinball/sensor_tiny.png");
	fx_light = App->audio->LoadFx("pinball/bonus2.wav");

	/*
	lights.PushBack(Light(this, 422, 140, lightTypes::tiny));
	lights.PushBack(Light(this, 451, 159, lightTypes::tiny));
	lights.PushBack(Light(this, 481, 179, lightTypes::tiny));

	lights.PushBack(Light(this, 220, 514, lightTypes::tiny));
	lights.PushBack(Light(this, 251, 530, lightTypes::tiny));
	lights.PushBack(Light(this, 73, 525, lightTypes::tiny));
	lights.PushBack(Light(this, 61, 556, lightTypes::tiny));
	*/
	
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
	App->textures->Unload(bouncer1.texture); // same as bouncer2.texture

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	App->renderer->Blit(graphics, 0, 0);

	if(bouncer1.hit_timer > 0)
	{
		if(SDL_TICKS_PASSED(SDL_GetTicks(), bouncer1.hit_timer) == false)
			App->renderer->Blit(bouncer1.texture, 92, 563);
		else
		{
			bouncer1.hit_timer = 0;
			score += 10;
		}
	}

	if(bouncer2.hit_timer > 0)
	{
		if(SDL_TICKS_PASSED(SDL_GetTicks(), bouncer2.hit_timer) == false)
			App->renderer->Blit(bouncer2.texture, 292, 563);
		else
		{
			bouncer2.hit_timer = 0;
			score += 10;
		}
	}

	
	if (voltorb_bouncer1.hit_timer > 0)
	{
		if (SDL_TICKS_PASSED(SDL_GetTicks(), voltorb_bouncer1.hit_timer) == false)
			App->renderer->Blit(voltorb_bouncer1.texture, 232, 286);
		else
		{
			voltorb_bouncer1.hit_timer = 0;
			score += 10;
		}
	}

	


	for(uint i = 0; i < lights.Count(); ++i)
	{
		if(lights[i].on == true)
		{
			App->renderer->Blit(lights[i].texture, lights[i].x, lights[i].y);
		}
	}

	// Update title with score
	char title[50];
	sprintf_s(title, "Balls: %d Score: %06d Last Score: %06d", lives, score, last_score);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}


void ModuleSceneIntro::OnCollision(PhysBody* body1, PhysBody* body2)
{
	if(bouncer1.body == body1)
	{
		bouncer1.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer1.fx);
		return;
	}
	
	if(bouncer2.body == body1)
	{
		bouncer2.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(bouncer2.fx);
		return;
	}

	if (voltorb_bouncer1.body == body1)
	{
		voltorb_bouncer1.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(voltorb_bouncer1.fx);
		return;
	}

	if (voltorb_bouncer2.body == body1)
	{
		voltorb_bouncer2.hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		App->audio->PlayFx(voltorb_bouncer1.fx);
		return;
	}

	for(uint i = 0; i < lights.Count(); ++i)
	{
		if(body1 == lights[i].body)
		{
			if(lights[i].on == false)
			{
				lights[i].on = true;
				App->audio->PlayFx(lights[i].fx);
				score += 100;
			}
			return;
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

Light::Light(ModuleSceneIntro* scene, int x, int y) :x(x), y(y)
{
	int radius = 6;

	body = scene->App->physics->AddBody(x + radius, y + radius, radius * 2, b_static, 1.0f, 1.0f, false, true);
	body->listener = scene;
	on = false;
}