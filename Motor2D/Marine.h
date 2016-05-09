#ifndef __MARINE_H__
#define __MARINE_H__

#include "Unit.h"

class Marine : public Unit
{
public:
	
	// IDLE animations
	Animation	idle_up;
	Animation	idle_right_up;
	Animation   idle_right;
	Animation	idle_right_down;
	Animation	idle_down;
	Animation	idle_left_down;
	Animation	idle_left;
	Animation	idle_left_up;
	vector<Animation*>   idle_animation_pack;
	
	// MOVING animations
	Animation	walk_up;
	Animation   walk_right_up;
	Animation   walk_right;
	Animation   walk_right_down;
	Animation   walk_down;
	Animation   walk_left_down;
	Animation   walk_left;
	Animation   walk_left_up;
	vector<Animation*>   move_animation_pack;

	// ATTACK animations
	Animation	attack_up;
	Animation	attack_right_up;
	Animation	attack_right;
	Animation	attack_right_down;
	Animation	attack_down;
	Animation	attack_left_down;
	Animation	attack_left;
	Animation	attack_left_up;
	vector<Animation*>   attack_animation_pack;

	// Dead animation
	Animation	dead;	

	Bunker*			     bunker_to_fill = NULL;		// Bunker that can be access by the marine
	bool			     inside_bunker = false;		// It's inside?

	////Sounds
	//unsigned int fx_attack;
	//unsigned int fx_death_1;
	//unsigned int fx_death_2;

	//unsigned int fx_acknowledgement_1;
	//unsigned int fx_acknowledgement_2;
	//unsigned int fx_acknowledgement_3;
	//unsigned int fx_acknowledgement_4;

	//unsigned int fx_affirmation_1;
	//unsigned int fx_affirmation_2;
	//unsigned int fx_affirmation_3;
	//unsigned int fx_affirmation_4;

	//unsigned int fx_annoyance_1;
	//unsigned int fx_annoyance_2;
	//unsigned int fx_annoyance_3;
	//unsigned int fx_annoyance_4;
	//unsigned int fx_annoyance_5;
	//unsigned int fx_annoyance_6;
	//unsigned int fx_annoyance_7;

	//unsigned int fx_ready;

	Marine() {};
	Marine(iPoint &p);
	~Marine();

	//bool start();
	bool update(float dt);

	void move(float dt);
	void setAnimationFromDirection();
	
};

#endif __MARINE_H__