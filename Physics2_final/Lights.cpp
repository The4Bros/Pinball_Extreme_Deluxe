#include "Lights.h"



Light::Light()
{}

Light::Light(Application* app, int x, int y, int radius, SDL_Texture* texture, uint fx, uint score_bonus) :
texture(texture),
fx(fx),
score_bonus(score_bonus),
x(x),
y(y),
on(false)
{
	body = app->physics->AddBody(x + radius, y + radius, radius * 2, b_static, 1.0f, 1.0f, false, true);
	body->listener = app->scene_intro;
}


int Light::Update()
{
	return (on ? 1 : 0);
}

bool Light::CheckCollision(PhysBody* body1)
{
	return (body == body1);
}