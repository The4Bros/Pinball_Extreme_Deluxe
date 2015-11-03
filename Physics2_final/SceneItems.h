#pragma once
#include "Module.h"
#include "Globals.h"

#define BOUNCER_TIME 200
#define BLINK_MULTIPLIER 4

template<class Item>
class ItemList
{
public:
	ItemList() : app(NULL), itemList(new p2List<Item*>()), aniamted(false)
	{}
	ItemList(Application* app) : app(app), itemList(new p2List<Item*>()), aniamted(false)
	{}
	ItemList(Application* app, p2List<Item*>* list) : app(app), itemList(list), aniamted(false)
	{}

	~ItemList() CleanUp();

	bool AddItem(Item* b)
	{
		bool ret = (b != NULL);
		if(ret) itemList->add(b);
		return ret;
	}

	bool CleanUp()
	{
		bool ret = (b_list != NULL);
		if (ret) delete[] b_list;
		return ret;
	}

	void Update()
	{
		if (!animated)
		{
			p2List_item<Item*>* tmp = itemList->getFirst();
			while (tmp != NULL)
			{
				switch (tmp->data->Update())
				{
				case 0: break;
				case 1: app->renderer->Blit(tmp->data->texture, tmp->data->GetPrinting_X(), tmp->data->GetPrinting_Y()); break;
				case 2: app->scene_intro->score += tmp->data->score_bonus; break;
				default: break;
				}

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
						p2List_item<Item*>* tmp = itemList->getFirst();
						while (tmp != NULL)
						{
							app->renderer->Blit(tmp->data->texture, tmp->data->GetPrinting_X(), tmp->data->GetPrinting_Y());
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
				p2List_item<Item*>* tmp = itemList->getFirst();
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
			p2List_item<Item*>* tmp = itemList->getFirst();
			while (tmp != NULL)
			{
				if (tmp->data->CheckCollision(PhysBody* body))
				{
					app->audio->PlayFx(tmp->data->fx);
					app->scene_intro->score += tmp->data->score_bonus;
				}
				tmp = tmp->next;
			}
		}
	}

	void CheckAnimation()
	{
		p2List_item<Item*>* tmp = itemList->getFirst();
		unsigned int size = 0;

		while (tmp != NULL)
		{
			if (tmp->data->on)
				size++;

			tmp = tmp->next;
		}

		animated = (size == itemList->size);

		if (animated)
		{
			hit_timer = SDL_GetTicks() + BOUNCER_TIME;
			animation_counter = 0;
		}
	}

public:
	Application* app;
	p2List<Item*>* itemList;

	bool animated;
	unsigned int animation_counter;
	Uint32 hit_timer;
};



class Bouncer
{
public:
	Bouncer() : body(NULL), texture(NULL), fx(0), score_bonus(0), x(0), y(0), printing_x(0), printing_y(0), hit_timer(0)
	{}
	Bouncer() : body(NULL), texture(NULL), fx(0), score_bonus(0), x(0), y(0), printing_x(0), printing_y(0), hit_timer(0)
	{}

	int Update()
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

	bool CheckCollision(PhysBody* body1)
	{
		bool ret = (body == body1);
		if (ret) hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		return ret;
	}

	int GetPrinting_X()
	{
		return printing_x;
	}

	int GetPrinting_Y()
	{
		return printing_y;
	}

public:
	PhysBody* body;
	SDL_Texture* texture;
	uint fx;
	uint score_bonus;
	int x, y;
	int printing_x, printing_y;
	Uint32 hit_timer;
};

class Light
{
public:
	Light() : body(NULL), texture(NULL), on(false), fx(0)
	{}

	Light(ModuleSceneIntro* scene, int x, int y) :x(x), y(y)
	{
		int radius = 6;

		body = scene->App->physics->AddBody(x + radius, y + radius, radius * 2, b_static, 1.0f, 1.0f, false, true);
		body->listener = scene;
		on = false;
	}

	int Update()
	{
		return (on ? 1 : 0);
	}

	bool CheckCollision(PhysBody* body1)
	{
		bool ret = (body == body1);
		if (ret) hit_timer = SDL_GetTicks() + BOUNCER_TIME;
		return ret;
	}

	int GetPrinting_X()
	{
		return x;
	}

	int GetPrinting_Y()
	{
		return y;
	}
		

public:
	PhysBody* body;
	SDL_Texture* texture;
	uint fx;
	uint score_bonus;
	int x, y;
	Uint32 hit_timer;

	bool on;
};

