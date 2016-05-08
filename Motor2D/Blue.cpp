#include "Blue.h"
#include "p2Log.h"

Blue::Blue(iPoint &p)
{
	// Positions and dimensions
	center = { (float)p.x, (float)p.y };

	tex_width = 96;
	tex_height = 128;
	collider_offset.set(0, 36);
	pos = { (float)p.x - (tex_width / 2), (float)p.y - (tex_height / 2) };
	tile_pos = app->map->worldToMap(app->map->data.front(), center.x, center.y);

	// Animations and FX
	tex = app->tex->loadTexture("Building/Blue.png"); //Sprites/Animations etc..
	idle.frames.push_back({ 0, 0, 96, 128 });
	idle.speed = 1.0f;
	idle.loop = false;
	current_animation = &idle;

	// Colliders
	coll = app->collision->addCollider({ pos.x + collider_offset.x, pos.y + collider_offset.y, 96, 59 }, COLLIDER_BUILDING);

	// Another stuff
	specialization = BLUE;
	max_hp = 350;
	current_hp = 350.0f;
	max_hp_bars = 10;
	offset_life = { -23, 35 };

	range_of_vision = range_to_attack = 150;
	damage = 0.0f; //we change it according to the amount of marines inside;
	attack_frequency = 200.0f;

	state = IDLE;
	faction = PLAYER;
	selection_type = { 261, 1, 94, 56 };
	circle_selection_offset = { 0, 25 };
}

Blue::~Blue()
{
	SDL_DestroyTexture(tex);
}

bool Blue::update(float dt)
{
	switch (state)
	{
	case IDLE:
		if (timer_attack.read() >= (attack_frequency * attack_frequency_multiplier))
		{
			buff();
			timer_attack.start();
		}
		break;
	case MOVE:
		break;
	case MOVE_ALERT:
		break;
	case MOVE_ALERT_TO_ATTACK:
		break;
	case ATTACK:
		break;
	case DYING:
		//current_animation = &dead;
		if (timer_to_check.read() >= time_to_die)
		{
			to_delete = true;
			coll->to_delete = true;
		}
		break;
	case WAITING_PATH_MOVE:
		break;
	case WAITING_PATH_MOVE_ALERT:
		break;
	case WAITING_PATH_MOVE_ALERT_TO_ATTACK:
		break;
	}
	return true;
}

void Blue::buff()
{
	list<Entity*> last_targets = targets;
	targets = searchEntitiesInRange(this, range_to_attack);
	
	for (list<Entity*>::iterator it = last_targets.begin(); it != last_targets.end(); it++)
	{
		it._Ptr->_Myval->speed_multiplier /= 1.2f;
	}
	for (list<Entity*>::iterator it = targets.begin(); it != targets.end(); it++)
	{
		it._Ptr->_Myval->speed_multiplier *= 1.2f;
	}
}