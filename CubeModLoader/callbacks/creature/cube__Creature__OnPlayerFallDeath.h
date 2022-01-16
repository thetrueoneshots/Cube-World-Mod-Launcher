#pragma once

extern "C" void cube__Creature__OnPlayerFallDeath(cube::Creature * player)
{
	if (player->entity_data.HP > 0)
		return;

	player->entity_data.HP = 0;
	
	cube::Game* game = cube::GetGame();

	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnPlayerDeathPriority == (GenericMod::Priority)priority) {
				dll->mod->OnPlayerDeath(game, player, GenericMod::DeathType::FALL);
			}
		}
	}
}

GETTER_VAR(void*, ASM_cube__Creature__OnPlayerFallDeath_JMPBACK);
__attribute__((naked)) void ASM_cube__Creature__OnPlayerFallDeath() {
	asm(".intel_syntax \n"

		// r13: player
		// r15: world
		"mov rcx, r13 \n"
		"call cube__Creature__OnPlayerFallDeath \n"

		DEREF_JMP(ASM_cube__Creature__OnPlayerFallDeath_JMPBACK)
	);
}

void setup_cube__Creature__OnPlayerFallDeath() {
	WriteFarJMP(CWOffset(0x2BECFD), (void*)&ASM_cube__Creature__OnPlayerFallDeath);
	ASM_cube__Creature__OnPlayerFallDeath_JMPBACK = CWOffset(0x2BED0E);
}