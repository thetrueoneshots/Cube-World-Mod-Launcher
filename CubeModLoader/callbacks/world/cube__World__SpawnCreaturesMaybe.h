#pragma once
#include "../../CWSDK/cwsdk.h"

void cube__World__SpawnCreaturesMaybe(cube::World* world)
{
	if (world->field_358 != 0)
	{
		return;
	}

	// Check if needed
	std::map<void*, void*> var_200;
	std::list<cube::Creature*> var_230;
	std::map<void*, void*> var_218;
	std::map<void*, void*> var_210;

	
}