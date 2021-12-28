#pragma once

extern "C" float cube__Creature__GetArmor(cube::Creature * creature)
{
    float armor = 0;

    cube::Item* chest = &creature->entity_data.equipment.chest;
    if (chest->IsValidEquipmentForCreature(creature, 4))
    {
        armor += chest->GetArmor(creature);
    }

    cube::Item* feet = &creature->entity_data.equipment.feet;
    if (feet->IsValidEquipmentForCreature(creature, 6))
    {
        armor += feet->GetArmor(creature);
    }

    cube::Item* hands = &creature->entity_data.equipment.hands;
    if (hands->IsValidEquipmentForCreature(creature, 5))
    {
        armor += hands->GetArmor(creature);
    }

    cube::Item* shoulder = &creature->entity_data.equipment.shoulder;
    if (shoulder->IsValidEquipmentForCreature(creature, 7))
    {
        armor += shoulder->GetArmor(creature);
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

    for (uint8_t priority = 0; priority <= 4; priority += 1) {
        for (DLL* dll : modDLLs) {
            if (dll->mod->OnCreatureArmorCalculatedPriority == (GenericMod::Priority)priority) {
                dll->mod->OnCreatureArmorCalculated(creature, &armor);
            }
        }
    }

    return armor;
}

overwrite_function(0x4F080, cube__Creature__GetArmor)