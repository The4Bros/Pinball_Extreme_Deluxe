#pragma once
#include "Application.h"


#define BOUNCER_TIME 200
#define BLINK_MULTIPLIER 4
#define LIGHT_RADIUS 6

class Item
{
public:
	Item() : body(NULL), texture(NULL), fx(0), score_bonus(0), x(0), y(0)
	{}
	Item(SDL_Texture* texture, uint fx, uint score_bonus, int x, int y) :
		body(NULL),
		texture(texture),
		fx(fx),
		score_bonus(score_bonus),
		x(x),
		y(y)
	{}

	virtual ~Item()
	{}

	virtual int Update() { return 0; }
	virtual bool CheckCollision(PhysBody* body1) { return true; }

	virtual int GetPrinting_X() { return 0; }
	virtual int GetPrinting_Y() { return 0; }

	PhysBody* body;
	SDL_Texture* texture;
	uint fx;
	uint score_bonus;
	int x, y;
};


class ItemList
{
public:
	ItemList() : app(NULL)
	{}
	ItemList(Application* app) : app(app)
	{}

	virtual ~ItemList()
	{}

	virtual void Update()
	{
		return;
	}

	virtual void CheckCollision(PhysBody* body)
	{
		return;
	}

public:
	Application* app;
};


