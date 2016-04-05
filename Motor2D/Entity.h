#include "SDL\include\SDL_render.h"
#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Vector2D.h"
#include "Animation.h"
#include "Collision.h"
#include "p2Log.h"

enum ENTITY_TYPE
{
	// Units
	MARINE,
	ZERGLING,
	// Buildings
	COMMANDCENTER
};

enum FACTION
{
	PLAYER,
	COMPUTER
};

class Entity
{

public:

	iPoint			pos;						// World position of Entity. Upper_left corner.
	iPoint			center;						// World positoin of Entity. Center
	iPoint			tile_pos;					// Map position (tiles) of Entity

	int		     	tex_width, tex_height;

	ENTITY_TYPE		type;
	SDL_Texture		*tex;   
	Animation		*current_animation;
	uint			id;
	
	Vector2D<int>   direction;

	unsigned int    hp;
	Collider*       coll;

	vector<iPoint>  path;


	// Constructors
	Entity()
	{};

	// Destructor
	~Entity()
	{
		SDL_DestroyTexture(tex);
	}

	virtual void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}
};

class Marine : public Entity
{
public:
	
	Animation	idle;
	FACTION		faction;

	Marine(iPoint &p) 
	{		
		// Positions and dimensions
		center = { p.x, p.y };

		tex_width = tex_height = 64;
		pos = { p.x - (tex_width / 2), p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Animations
		tex = app->tex->loadTexture("Units/Marine.png"); //Sprites/Animations etc..
		idle.frames.push_back({ 0, 0, 64, 64 });
		/*idle.frames.push_back({ 64, 0, 64, 64 });
		idle.frames.push_back({ 128, 0, 64, 64 });
		idle.frames.push_back({ 192, 0, 64, 64 });
		idle.frames.push_back({ 256, 0, 64, 64 });
		idle.frames.push_back({ 320, 0, 64, 64 });
		idle.frames.push_back({ 384, 0, 64, 64 });
		idle.frames.push_back({ 448, 0, 64, 64 });
		idle.frames.push_back({ 512, 0, 64, 64 });
		idle.frames.push_back({ 576, 0, 64, 64 });
		idle.frames.push_back({ 640, 0, 64, 64 });
		idle.frames.push_back({ 704, 0, 64, 64 });
		idle.frames.push_back({ 768, 0, 64, 64 });
		idle.frames.push_back({ 832, 0, 64, 64 });
		idle.frames.push_back({ 896, 0, 64, 64 });
		idle.frames.push_back({ 960, 0, 64, 64 });*/
		idle.speed = 0.0f;
		idle.loop = true;
		current_animation = &idle;

		// Colliders
		coll = app->collision->addCollider({ center.x, center.y, 30, 30 }, COLLIDER_BOMB);

		// Another stuff
		type = MARINE;
		faction = PLAYER;

		hp = 6;

		direction.create(1, 1, p.x, p.y);
		direction.setAngle(0.f);
	}

	void checkAngle()
	{
		float angle = direction.getAngle();

		if (angle >= 18)
		{
			idle.frames.push_back({ 64, 0, 64, 64 });
		}

	}

	void draw()
	{
		app->render->blit(tex, pos.x, pos.y, &(current_animation->getCurrentFrame()));
	}
};

class CommandCenter : public Entity
{
public:
	FACTION faction;
	Animation idle;
	
public:

	CommandCenter(iPoint &p)
	{
		// Positions and dimensions
		center = { p.x, p.y };

		tex_width = 128;
		tex_height = 100;
		pos = { p.x - (tex_width / 2), p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.front(), center.x, center.y);

		// Animations
		tex = app->tex->loadTexture("temporaryTextures/commandCenter.png"); //Sprites/Animations etc..
		idle.frames.push_back({ 0, 27, 128, 100 });
		idle.speed = 1.0f;
		idle.loop = false; 
		current_animation = &idle;

		// Colliders
		coll = app->collision->addCollider({ center.x, center.y, 128, 100 }, COLLIDER_BOMB);

		// Another stuff
		type = COMMANDCENTER;
		hp = 50;

		faction = PLAYER;
	}

};

class Zergling : public Entity
{
public:

	Animation idle;
	FACTION faction;

	Zergling(iPoint &p)
	{
		// Positions and dimensions
		center = { p.x, p.y };

		tex_width = tex_height = 128;		
		pos = { p.x - (tex_width / 2), p.y - (tex_height / 2) };
		tile_pos = app->map->worldToMap(app->map->data.back(), center.x, center.y);

		// Animation
		tex = app->tex->loadTexture("Units/Zergling.png");
		idle.frames.push_back({ 0, 0, 128, 128 });
		/*idle.frames.push_back({ 128, 0, 128, 128 });
		idle.frames.push_back({ 256, 0, 128, 128 });
		idle.speed = 0.05f;*/
		idle.loop = false; 	
		current_animation = &idle;

		// Collider
		coll = app->collision->addCollider({ center.x, center.y, 24, 24 }, COLLIDER_BOMB);

		// Another stuff
		type = ZERGLING;
		faction = COMPUTER;
		hp = 10;
	}
};
