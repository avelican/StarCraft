#ifndef __GUI_H__
#define __GUI_H__

#include "App.h"
#include "Module.h"
#include "Render.h"
#include "Animation.h"
#include "EntityManager.h"

class GuiCursor;
class GuiImage;
using namespace std;


enum GUI_EVENTS
{
	LISTENING_ENDS,
	MOUSE_ENTERS,
	MOUSE_LEAVES,
	MOUSE_LCLICK_DOWN,
	MOUSE_LCLICK_DOWN_REPEAT,
	MOUSE_LCLICK_UP,
	MOUSE_RCLICK_DOWN,
	MOUSE_RCLICK_UP,
	GAIN_FOCUS,
	LOST_FOCUS,
    INPUT_CHANGED,
	INPUT_SUBMIT,
    VALUE_CHANGED,
	SAVE_POS_THUMB,
	LOAD_POS_THUMB
};

enum GUI_TYPES
{
	UNKNOWN,
	IMAGE,
	CURSOR,
};




// ---------------------------------------------------
class Gui : public Module
{
public:

	Gui();

	// Destructor
	virtual ~Gui();

	// Called when before render is available
	bool awake(pugi::xml_node&);

	// Call before first frame
	bool start();

	// Called before all Updates
	bool preUpdate();

	// Called each loop iteration
	bool update(float dt);

	// Called after all Updates
	bool postUpdate();

	// Called before quitting
	bool cleanUp();

	// Gui creation functions
	GuiImage* createImage(const char* filename);
	GuiImage* createImage(const SDL_Texture* texture, const SDL_Rect& atlas_section);
	GuiCursor* createCursor(const SDL_Texture* texture);

	const GuiElements* findMouseHover();
	const SDL_Texture* getAtlas() const;

	SDL_Rect mouseQuad(iPoint init_mouse);

	// Variables for Cursor
	GuiCursor *cursor;
	iPoint cursor_offset;
	iPoint map_limits;
	float scroll_speed;

	//HUD 
	GuiImage* ui_terran = nullptr;
	GuiImage* rectangle_map = nullptr;
	GuiImage* rectangle_command = nullptr;
	GuiImage* rectangle_command_2 = nullptr;

	//Command Center HUD
	GuiImage* ui_create_bot = nullptr;
	GuiImage* ui_create_builds = nullptr;

	//Variables for CircleSelection. There are 10 size selection
	/*W_22 = { 3, 4, 22, 13 };
	W_32 = { 28, 9, 32, 19 };
	W_48 = { 64, 5, 48, 29 };*/
	SDL_Texture*	circles_of_selection;

	// Variables for life of entities;
	SDL_Texture* lifes_tex;
	SDL_Rect	 life;
	SDL_Rect	 no_life;
	

private:
		
	bool debug = false;
	list<GuiElements*> elements;
	const GuiElements* focus = nullptr;
	SDL_Texture* atlas = nullptr;
	SDL_Texture* terran_console = nullptr;
	string atlas_file_name;
	void drawHudSelection(SPECIALIZATION  selection);

	SDL_Texture *path_walkability;
};

#endif