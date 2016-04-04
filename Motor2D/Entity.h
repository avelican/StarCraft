#include "SDL\include\SDL_render.h"
#include "Textures.h"
#include "Render.h"
#include "Map.h"
#include "App.h"
#include "Animation.h"

enum ENTITY_TYPE
{
	//Units
	MARINE,
	ZERGLING,
	//Buildings
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

	SDL_Rect		dim;
	SDL_Rect		spritesheet_section;
	ENTITY_TYPE		type;
	SDL_Texture		*tex;   
	Animation*		current_animation;
	uint			id;
	iPoint			tile_pos;
	unsigned int    hp;
	vector<iPoint>  path;

	// Constructors
	Entity(const iPoint &p)
	{
		iPoint tmp = app->map->worldToMap(app->map->data.back(), p.x, p.y);
		tile_pos = tmp;
		tmp = app->map->mapToWorld(app->map->data.back(), tmp.x, tmp.y);
		dim.x = tmp.x;
		dim.y = tmp.y;
	};

	// Destructor
	~Entity()
	{
		SDL_DestroyTexture(tex);
	}

	void draw()
	{
		app->render->blit(tex, dim.x, dim.y, &(current_animation->getCurrentFrame()));
	}

	

};

class Marine : public Entity
{
public:
	
	Animation idle;
	SDL_Rect section;
	FACTION faction;
	unsigned int hp = 10;

	Marine(iPoint &p) : Entity(p)
	{
		
		tex = app->tex->loadTexture("Units/Marine.png"); //Sprites/Animations etc..

		//--TEST TO TRY THE ANIMATION MODULE----
		idle.frames.push_back({ 0, 0, 64, 64 });
		idle.frames.push_back({ 64, 0, 64, 64 });
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
		idle.frames.push_back({ 960, 0, 64, 64 });
		idle.frames.push_back({ 0, 0, 64, 64 });

		idle.speed = 0.05f;
		idle.loop = false; // IPL: if you put this true, the animation doesn't work well, try it!

		current_animation = &idle;
		//-------------------------------------
		dim.w = current_animation->getCurrentFrame().w;
		dim.h = current_animation->getCurrentFrame().h;
		type = MARINE;
		faction = PLAYER;
	
	}
};



class CommandCenter : public Entity
{
public:
	FACTION faction;
	Animation idle;
	SDL_Rect section;
	unsigned int hp = 1000;

public:


	CommandCenter(iPoint &p) : Entity(p)
	{
		
		SDL_QueryTexture(tex, NULL, NULL, &dim.w, &dim.h);
		
		tex = app->tex->loadTexture("temporaryTextures/commandCenter.png"); //Sprites/Animations etc..
		//--TEST TO TRY THE ANIMATION MODULE----
		idle.frames.push_back({ 0, 27, 128, 100});
		
		idle.speed = 1.0f;
		idle.loop = false; // IPL: if you put this true, the animation doesn't work well, try it!
		current_animation = &idle;
		//-------------------------------------
		dim.w = current_animation->getCurrentFrame().w;
		dim.h = current_animation->getCurrentFrame().h;
		
		type = MARINE;

		faction = PLAYER;
	}

};


/*
class Item : public Entity
{
	ENTITY_TYPE iType;

public:

	Item(iPoint &p, uint id, ITEM_TYPE) : Entity(p,id)
	{
		tex;//Sprites/Animations etc..;
		SDL_QueryTexture(tex, NULL, NULL, &dim.w, &dim.h);
		
		type = iType;
	}

};
*/
