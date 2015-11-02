#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "PhysBody.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	ball.graphic = App->textures->Load("pinball/ball.png");
	flipper1.graphic = App->textures->Load("pinball/flipper1.png");
	flipper2.graphic = App->textures->Load("pinball/flipper2.png");
	flipper1.fx = flipper2.fx = App->audio->LoadFx("pinball/flipper.wav");

	spring.graphic = App->textures->Load("pinball/spring.png");
	spring.fx = App->audio->LoadFx("pinball/spring2.wav");

	ball.body = App->physics->AddBody(563, 582, 28, b_dynamic, 1.0f, 0.3f, true);/*___________*/
	ball.fx = App->audio->LoadFx("pinball/ball_bounce.wav");
	ball.body->listener = this;
	
	// Pivot 0, 0
	int f1[16] = {
		0, 18,
		4, 5,
		15, 0,
		91, 9,
		96, 18,
		89, 27,
		13, 34,
		5, 30
	};

	flipper1.body = App->physics->AddBody({132, 918, 0, 0}, f1, 16, b_dynamic);/*___________*/
	flipper1_wheel = App->physics->AddBody(132+14, 918+17, 10, b_static);
	App->physics->CreateRevoluteJoint(flipper1.body, flipper1_wheel, 14, 17, 0, 0, 30, -30);

	// Pivot 0, 0
	int f2[16] = {
		81, 0,
		6, 8,
		0, 17,
		6, 26,
		83, 35,
		91, 28,
		95, 17,
		91, 5
	};
	
	flipper2.body = App->physics->AddBody({273, 920, 0, 0}, f2, 16, b_dynamic);/*___________*/
	flipper2_wheel = App->physics->AddBody(273 + 80, 920 + 17, 10, b_static);
	App->physics->CreateRevoluteJoint(flipper2.body, flipper2_wheel, 80, 17, 0, 0, 30, -30);

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



