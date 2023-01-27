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
	Ball = App->physics->AddBody(s, 100.0f);

	//Map
	Cube c(500, 5, 500);
	c.color = White;
	Ground = App->physics->AddBody(c, 0.0f);

	Cube w(500, 500, 5);
	w.SetPos(0, 5, 250);
	Ground = App->physics->AddBody(w, 0.0f);

	Cube we(500, 500, 5);
	we.SetPos(0, 5, -250);
	Ground = App->physics->AddBody(we, 0.0f);

	Cube wi(5, 500, 500);
	wi.SetPos(250, 5, 0);
	Ground = App->physics->AddBody(wi, 0.0f);

	Cube wo(5, 500, 500);
	wo.SetPos(-250, 5, 0);
	Ground = App->physics->AddBody(wo, 0.0f);

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

	Cube c(500, 5, 500);
	c.color = White;
	c.SetPos(0, 0, 0);
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


