#pragma once
#include "../../CWSDK/cwsdk.h"

extern "C" bool cube__Item__OnClassCanWearItem (cube::Item* item, int classType)
{
	bool retval = false;

	char category = item->category;

	if (category == 2) // Formulas
	{
		cube::Item copy;
		copy.Copy(item);
		copy.category = item->formula_category;
		copy.formula_category = 0;
		if (item->formula_category == 2)
		{
			retval = true;
		}
		else
		{
			retval = cube__Item__OnClassCanWearItem(&copy, classType);
		}
	}
	else if (category == 3) // Weapons
	{
		switch (item->id)
		{
			case 0:
			case 1:
			case 2:
			case 13:
			case 15:
			case 16:
			case 17:
				retval = classType == 1;
				break;
			case 3:
			case 4:
			case 5:
				retval = classType == 4;
				break;
			case 6:
			case 7:
			case 8:
			case 14:
				retval = classType == 2;
				break;
			case 10:
			case 11:
			case 12:
				retval = classType == 3;
				break;
			default:
				retval = true;
				break;
		}
	}
	else if (category <= 3) // Consumables basically
	{
		retval = true;
	}
	else if (category > 7) // Everything non-equipment + amulet and ring
	{
		retval = true;
	}
	else // Chest, gloves, boots and shoulders
	{
		switch (item->material - 1)
		{
		case cube::Item::MaterialType::Iron:
		case 3: // Undefined
		case cube::Item::MaterialType::Steel:
		case cube::Item::MaterialType::Copper:
		case cube::Item::MaterialType::Sandstone:
		case cube::Item::MaterialType::Plant:
		case cube::Item::MaterialType::Cotton:
			retval = (classType == cube::Creature::ClassType::Warrior);
			break;
		case cube::Item::MaterialType::Linnen:
		case cube::Item::MaterialType::Bronze:
		case cube::Item::MaterialType::Mail:
			retval = (classType == cube::Creature::ClassType::Rogue);
			break;
		case cube::Item::MaterialType::Saurian:
		case cube::Item::MaterialType::Silk:
		case cube::Item::MaterialType::Calcio:
		case cube::Item::MaterialType::Flannell:
			retval = (classType == cube::Creature::ClassType::Ranger);
			break;
		case cube::Item::MaterialType::Ice:
		case cube::Item::MaterialType::Glass:
		case cube::Item::MaterialType::Felt:
		case cube::Item::MaterialType::Rivet:
			retval = (classType == cube::Creature::ClassType::Mage);
			break;
		default:
			retval = true;
			break;
		}
	}

	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnClassCanWearItemPriority == (GenericMod::Priority)priority) {
				dll->mod->OnClassCanWearItem(item, classType, &retval);
			}
		}
	}

	return retval;
}

overwrite_function(0x1094D0, cube__Item__OnClassCanWearItem)