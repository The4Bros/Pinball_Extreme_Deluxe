#pragma once
#include "Application.h"

class Application;

class Bouncer
{
public:
	Bouncer();
	Bouncer(Application* app, int x, int y, int d, SDL_Texture* texture, uint fx, uint score_bonus);
	Bouncer(Application* app, const SDL_Rect &rect, int *points, uint count, SDL_Texture* texture, uint fx, uint score_bonus);

	int Update();
	bool CheckCollision(PhysBody* body1);

public:
	int printing_x, printing_y;
	Uint32 hit_timer;

	PhysBody* body;
	SDL_Texture* texture;
	uint fx;
	uint score_bonus;
	int x, y;
};

class BouncerList
{
public:
	BouncerList() : app(NULL), itemList(new p2List<Bouncer*>())
	{}
	BouncerList(Application* app) : app(app), itemList(new p2List<Bouncer*>())
	{}

	~BouncerList()
	{
		CleanUp();
	}

	bool AddItem(Bouncer* b)
	{
		bool ret = (b != NULL);
		if (ret) itemList->add(b);
		return ret;
	}

	bool CleanUp()
	{
		bool ret = (itemList != NULL);
		if (ret) delete[] itemList;
		return ret;
	}

	void Update()
	{
		p2List_item<Bouncer*>* tmp = itemList->getFirst();
		while (tmp != NULL)
		{
			switch (tmp->data->Update())
			{
			case 0: break;
			case 1: app->renderer->Blit(tmp->data->texture, tmp->data->printing_x, tmp->data->printing_y); break;
			case 2: app->scene_intro->score += tmp->data->score_bonus; break;
			default: break;
			}

			tmp = tmp->next;
		}
	}

	void CheckCollision(PhysBody* body)
	{
		p2List_item<Bouncer*>* tmp = itemList->getFirst();
		while (tmp != NULL)
		{
			if (tmp->data->CheckCollision(body))
			{
				app->audio->PlayFx(tmp->data->fx);
				app->scene_intro->score += tmp->data->score_bonus;
			}
			tmp = tmp->next;
		}
	}

public:
	Application* app;
	p2List<Bouncer*>* itemList;

};