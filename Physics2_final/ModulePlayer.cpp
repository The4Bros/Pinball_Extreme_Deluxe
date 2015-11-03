#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	ball.graphic = App->textures->Load("game/pinball/ball_small.png");
	flipper1.graphic = App->textures->Load("game/pinball/Flipper_izq.png");
	flipper2.graphic = App->textures->Load("game/pinball/Flipper_der.png");
	flipper1.fx = flipper2.fx = App->audio->LoadFx("game/pinball/flipper.wav");

	spring.graphic = App->textures->Load("game/pinball/spring.png");
	spring.fx = App->audio->LoadFx("game/pinball/spring2.wav");

	ball.body = App->physics->AddBody(450, 655, 29, b_dynamic, 1.0f, 0.3f, true);/*___________*/
	ball.fx = App->audio->LoadFx("game/pinball/ball_bounce.wav");
	ball.body->listener = this;
	
	// Pivot 0, 0
	int f1[20] = {
		0, 14,
		6, 24,
		19, 23,
		36, 22,
		62, 19,
		65, 15,
		63, 10,
		49, 7,
		11, 2,
		0, 9
	};

	flipper1.body = App->physics->AddBody({140, 686, 0, 0}, f1, 16, b_dynamic);/*___________*/
	flipper1_wheel = App->physics->AddBody(140+11, 686+14, 10, b_static);
	App->physics->CreateRevoluteJoint(flipper1.body, flipper1_wheel, 11, 14, 0, 0, 30, -30);

	// Pivot 0, 0
	int f2[22] = {
		66, 15,
		61, 24,
		52, 25,
		48, 22,
		30, 23,
		5, 20,
		0, 13,
		16, 7,
		29, 6,
		55, 3,
		65, 8
	};
	
	flipper2.body = App->physics->AddBody({225, 682, 0, 0}, f2, 16, b_dynamic);/*___________*/
	flipper2_wheel = App->physics->AddBody(225+55, 682+14, 10, b_static);
	App->physics->CreateRevoluteJoint(flipper2.body, flipper2_wheel, 55, 14, 0, 0, 30, -30);

	// Others
	spring.body = App->physics->AddBody({565, 943, 45, 47}, b_dynamic);/*___________*/
	spring_wheel = App->physics->AddBody(535, 907, 10, b_static);
	App->physics->CreateLineJoint(spring.body, spring_wheel, 0, 0, 0, 0, 20.0f, 1.0f);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;

	App->textures->Unload(ball.graphic);
	App->textures->Unload(flipper1.graphic);
	App->textures->Unload(flipper2.graphic);

	App->physics->DestroyBody(ball.body);
	App->physics->DestroyBody(flipper1.body);
	App->physics->DestroyBody(flipper2.body);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	static float spring_push = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_UP)
	{
		ball.body->Push(0.0f, -400.0f);
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		App->audio->PlayFx(flipper1.fx);
	}

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		flipper1.body->Turn(-360);
	}

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		flipper2.body->Turn(360);
	}

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		spring_push += 175.0f;
		spring.body->Push(0, spring_push);
	}
	else
		spring_push = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{
		App->audio->PlayFx(spring.fx);
	}

	int x, y;

	ball.body->GetPosition(x, y);
	App->renderer->Blit(ball.graphic, x, y, NULL, 1.0f);//, ball.body->GetAngle());
	
	flipper1.body->GetPosition(x, y);
	App->renderer->Blit(flipper1.graphic, x , y, NULL, 1.0f, flipper1.body->GetAngle(), 0, 0);

	flipper2.body->GetPosition(x, y);
	App->renderer->Blit(flipper2.graphic, x, y, NULL, 1.0f, flipper2.body->GetAngle(), 0, 0);
	
	spring.body->GetPosition(x, y);
	App->renderer->Blit(spring.graphic, x, y, NULL, 1.0f, spring.body->GetAngle());
	
	return UPDATE_CONTINUE;
}



