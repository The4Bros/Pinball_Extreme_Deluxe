#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2D/Box2D.h"
#pragma comment (lib,"Box2D/libx86/Debug/Box2D.lib")

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled),world(NULL)
{
	
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
			
	b2Vec2 gravity(0.0f, -10.0f);
	world = new b2World(gravity);

	b2BodyDef bodydef;
	bodydef.type = b2_staticBody; // or b2_dynamicBody;;;;;;
	bodydef.position.Set(PIXEL_TO_METER(500), PIXEL_TO_METER(320));
	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METER(250.0f);

	b2Body* body = world->CreateBody(&bodydef);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	body->CreateFixture(&fixture);
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// TODO 3: Update the simulation ("step" the world)

	world->Step(STEP1);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METER_TO_PIXEL(pos.x), METER_TO_PIXEL(pos.y), METER_TO_PIXEL(shape->m_radius), 255, 255, 255);
				}
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");
	delete world;
	// Delete the whole physics world!

	return true;
}
