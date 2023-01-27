#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//Ball
	Sphere s(3);
	s.color = Green;
	s.SetPos(0, 0, 30);
	Ball = App->physics->AddBody(s, 100);
	
	//Map
	Cube c(1000, 5, 1000);
	c.color = White;
	Ground = App->physics->AddBody(c, 0.0f);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();

	Sphere s(3);
	s.color = Green;
	s.SetPos(0, 0, 30);
	Ball->GetTransform(&s.transform);
	s.Render();

	Cube c(1000, 5, 1000);
	c.color = White;
	c.Render();

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		App->camera->first = !App->camera->first;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}


