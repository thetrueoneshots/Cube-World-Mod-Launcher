#pragma once
#include "../../CWSDK/cwsdk.h"

bool cube__Item__ClassCanWearItem(cube::Item* item, int classType)
{
    return ((bool(*)(cube::Item*, int))CWOffset((size_t)0x1094D0))(item, classType);
}

float cube__Item__GetArmor(cube::Item* item, cube::Creature* creature)
{
    return ((float(*)(cube::Item*, cube::Creature*))CWOffset((size_t)0x108D50))(item, creature);
}

bool cube__Item__IsValidEquipment(cube::Item* item, int category, cube::Creature* creature)
{
    if (item->category != category)
    {
        return false;
    }

    if (creature->entity_data.hostility_type != 0 || cube__Item__ClassCanWearItem(item, creature->entity_data.classType))
    {
        return true;
    }

    return false;
}

// Todo: Maybe add macro that makes the map.find unnecessary. (E.g. storning the vector of "cube::Creature::OnGetArmor" once before running.
overwrite_function(0x4F080, cube__Creature__GetArmor)
extern "C" float cube__Creature__GetArmor(cube::Creature * creature)
{
    float armor = 0;

    cube::Item* chest = &creature->entity_data.equipment.chest;
    if (cube__Item__IsValidEquipment(chest, 4, creature))
    {
        armor += cube__Item__GetArmor(chest, creature);
    }

    cube::Item* feet = &creature->entity_data.equipment.feet;
    if (cube__Item__IsValidEquipment(feet, 6, creature))
    {
        armor += cube__Item__GetArmor(feet, creature);
    }

    cube::Item* hands = &creature->entity_data.equipment.hands;
    if (cube__Item__IsValidEquipment(hands, 5, creature))
    {
        armor += cube__Item__GetArmor(hands, creature);
    }

    cube::Item* shoulder = &creature->entity_data.equipment.shoulder;
    if (cube__Item__IsValidEquipment(shoulder, 7, creature))
    {
        armor += cube__Item__GetArmor(shoulder, creature);
    }

    auto flags2 = creature->entity_data.appearance.flags2;
    if (flags2 & 0x20200)
    {
        armor *= (float)0x3F99999A;
    }

    if ((flags2 >> 12) & 1)
    {
        armor += armor;
    }

    for (auto& buff : creature->buffs)
    {
        if (buff.type == 0x0E)
        {
            armor *= (float)0x3E800000;
        }
        if (buff.type == 0x18)
        {
            armor *= buff.unk;
        }
    }

    auto it = g_Subscriptions->find("cube::Creature::OnGetArmor");
    if (it != g_Subscriptions->end())
    {
        for (auto& func : it->second)
        {
            ((void (*)(cube::Creature*, float*))func)(creature, &armor);
        }
    }

    return armor;
}