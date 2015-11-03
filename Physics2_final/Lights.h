#pragma once
#include "Application.h"

class Application;

class Light
{
public:
	Light();
	Light(Application* app, int x, int y, int radius, SDL_Texture* texture, uint fx, uint score_bonus);

	int Update();
	bool CheckCollision(PhysBody* body1);

public:
	bool on;

	PhysBody* body;
	SDL_Texture* texture;
	uint fx;
	uint score_bonus;
	int x, y;
};


class LightList
{
public:
	LightList() : app(NULL), itemList(new p2List<Light*>()), animated(false), animation_counter(0), hit_timer(0)
	{}
	LightList(Application* app) : app(app), itemList(new p2List<Light*>()), animated(false), animation_counter(0), hit_timer(0)
	{}

	~LightList()
	{
		CleanUp();
	}

	bool AddItem(Light* b)
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
		if (!animated)
		{
			p2List_item<Light*>* tmp = itemList->getFirst();
			while (tmp != NULL)
			{
				if (tmp->data->on)
					app->renderer->Blit(tmp->data->texture, tmp->data->x, tmp->data->y); break;

				tmp = tmp->next;
			}
		}
		else
		{
			if (animation_counter < 2 * BLINK_MULTIPLIER)
			{
				if (animation_counter % 2 == 0) // on
				{
					if (SDL_TICKS_PASSED(SDL_GetTicks(), hit_timer) == false)
					{
						p2List_item<Light*>* tmp = itemList->getFirst();
						while (tmp != NULL)
						{
							app->renderer->Blit(tmp->data->texture, tmp->data->x, tmp->data->y);
							tmp = tmp->next;
						}
					}
					else
					{
						hit_timer = SDL_GetTicks() + BOUNCER_TIME;
						animation_counter++;
					}
				}
				else //off
				{
					if (SDL_TICKS_PASSED(SDL_GetTicks(), hit_timer))
					{
						hit_timer = SDL_GetTicks() + BOUNCER_TIME;
						animation_counter++;
					}
				}
			}
			else
			{
				animated = false;
				p2List_item<Light*>* tmp = itemList->getFirst();
				while (tmp != NULL)
				{
					tmp->data->on = false;
					tmp = tmp->next;
				}
			}
		}
	}

	void CheckCollision(PhysBody* body)
	{
		if (!animated)
		{
			p2List_item<Light*>* tmp = itemList->getFirst();
			while (tmp != NULL)
			{
				if (tmp->data->CheckCollision(body))
				{
					if (!tmp->data->on)
					{
						app->audio->PlayFx(tmp->data->fx);
						app->scene_intro->score += tmp->data->score_bonus;
						tmp->data->on = true;
					}
					return;
				}
				tmp = tmp->next;
			}
		}
	}

	void CheckAnimation()
	{
		p2List_item<Light*>* tmp = itemList->getFirst();
		unsigned int size = 0;

		while (tmp != NULL)
		{
			if (tmp->data->on)
				size++;

			tmp = tmp->next;
		}

		animated = (size == itemList->count());

		if (animated)
		{
			hit_timer = SDL_GetTicks() + BOUNCER_TIME;
			animation_counter = 0;
		}
	}

public:
	Application* app;
	p2List<Light*>* itemList;

	bool animated;
	unsigned int animation_counter;
	Uint32 hit_timer;
};





