#pragma once
#include "../../CWSDK/cwsdk.h"

extern "C" bool cube__Creature__CanEquipItem(cube::Creature* creature, cube::Item* item)
{
	if (creature->entity_data.hostility_type != cube::Creature::EntityBehaviour::Player)
	{
		return true;
	}

	bool equipable = item->ClassCanWearItem(creature->entity_data.classType);
	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnCreatureCanEquipItemPriority == (GenericMod::Priority)priority) {
				dll->mod->OnCreatureCanEquipItem(creature, item, &equipable);
			}
		}
	}
	return equipable;
}

overwrite_function(0x50640, cube__Creature__CanEquipItem)