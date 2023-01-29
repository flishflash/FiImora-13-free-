#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePlayer.h"
#include "ModulePhysics3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

void ModuleSceneIntro::AddCube(vec3 position, vec3 size, int angle, bool rotateX, bool rotateY, bool rotateZ)
{
	Cube cubeToAdd;

	cubeToAdd.color = Blue;

	cubeToAdd.SetPos(position.x, position.y, position.z);

	cubeToAdd.size = size;

	// angle, XYZ
	if (rotateX == true) {
		cubeToAdd.SetRotation(angle, { 1, 0, 0 });
	}
	if (rotateY == true) {
		cubeToAdd.SetRotation(angle, { 0, 1, 0 });
	}
	if (rotateZ == true) {
		cubeToAdd.SetRotation(angle, { 0, 0, 1 });
	}

	App->physics->AddBody(cubeToAdd, 0);

	sceneryCubes.add(cubeToAdd);
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	//Ball
	Sphere s(3);
	s.color = Green;
	s.SetPos(0, 0, 30);
	Ball = App->physics->AddBody(s, 50.0f);
	Ball->collision_listeners.add(this);
	//Map
	Cube c(500, 5, 500);
	c.color = White;
	Ground = App->physics->AddBody(c, 0.0f);

	Cube w(500, 500, 5);
	w.SetPos(0, 5, 250);
	Ground = App->physics->AddBody(w, 0.0f);
	sceneryCubes.add(w);

	Cube we(500, 500, 5);
	we.SetPos(0, 5, -250);
	Ground = App->physics->AddBody(we, 0.0f);
	sceneryCubes.add(we);

	Cube wi(5, 500, 500);
	wi.SetPos(250, 5, 0);
	Ground = App->physics->AddBody(wi, 0.0f);
	sceneryCubes.add(wi);

	Cube wo(5, 500, 500);
	wo.SetPos(-250, 5, 0);
	Ground = App->physics->AddBody(wo, 0.0f);
	sceneryCubes.add(wo);

	AddCube({ 0, 5, 150 }, { 100 , 5, 50 }, -45, true, false, false);
	AddCube({ 0, 20.0f, 225 }, { 100 , 5, 80 }, 0, false, false, false);

	AddCube({ 0, 5, -150 }, { 100 , 5, 50 }, 45, true, false, false);
	AddCube({ 0, 20.0f, -225 }, { 100 , 5, 80 }, 0, false, false, false);

	//PORTERIAS
	Cube porteria;
	porteria.size = { 50, 30, 5 };
	porteria.SetPos(0, 20, 245);
	porteria.color = Red;
	sceneryCubes.add(porteria);

	porteriaB;
	porteriaB.body = App->physics->AddBody(porteria, 0.0f);
	porteriaB.body->SetAsSensor(true);
	porteriaB.gol = false;
	porteriaB.colorBody = porteria;
	porteriaB.body->collision_listeners.add(this);

	Cube porteria2;
	porteria2.size = { 50, 30, 5 };
	porteria2.SetPos(0, 20, -245);
	porteria2.color = Red;
	sceneryCubes.add(porteria2);

	porteriaA;
	porteriaA.body = App->physics->AddBody(porteria2, 0.0f);
	porteriaA.body->SetAsSensor(true);
	porteriaA.gol = false;
	porteriaA.colorBody = porteria2;
	porteriaA.body->collision_listeners.add(this);

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

	p2List_item<Cube>* cube = sceneryCubes.getFirst();
	while (cube != NULL) {
		cube->data.Render();
		cube = cube->next;
	}

	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		App->camera->first = !App->camera->first;
	}
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) App->camera->focus = 0;
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) App->camera->focus = 1;

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		App->player->win = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		App->player->lose = true;
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2 == porteriaB.body && body1 == Ball)
	{
		App->player->win = true;
	}
	if (body2 == porteriaA.body && body1 == Ball)
	{
		App->player->win = true;
	}
}


