#pragma once

// Todo: Maybe add macro that makes the map.find unnecessary. (E.g. storning the vector of "cube::Creature::OnGetArmor" once before running.
overwrite_function(0x4F080, cube__Creature__GetArmor)
extern "C" float cube__Creature__GetArmor(cube::Creature * creature)
{
    float armor = 100;

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