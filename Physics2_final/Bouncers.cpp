# include "Bouncers.h"

Bouncer::Bouncer() : body(NULL), texture(NULL), fx(0), score_bonus(0), x(0), y(0)
{}

Bouncer::Bouncer(Application* app, int x, int y, int d, SDL_Texture* texture, uint fx, uint score_bonus) :
texture(texture),
fx(fx),
score_bonus(score_bonus),
x(x),
y(y),
printing_x(x),
printing_y(y)
{
	body = app->physics->AddBody(x, y, d, b_static, 1.0f, 1.5f);
	body->listener = app->scene_intro;
}

Bouncer::Bouncer(Application* app, const SDL_Rect &rect, int *points, uint count, SDL_Texture* texture, uint fx, uint score_bonus) :
texture(texture),
fx(fx),
score_bonus(score_bonus),
x(x),
y(y),
printing_x(x),
printing_y(y)
{
	body = app->physics->AddBody(rect, points, count, b_static, 1.0f, 1.5f, false); //bumper2
	body->listener = app->scene_intro;
}

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