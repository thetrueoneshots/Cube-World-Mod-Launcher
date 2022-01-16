#pragma once

extern "C" void cube__Creature__OnPlayerDrownDeath(cube::Creature * player)
{
	if (player->entity_data.HP > 0)
		return;

	player->entity_data.HP = 0;
	
	cube::Game* game = cube::GetGame();

	/*
	wchar_t buffer[250];
	std::string name = player->entity_data.name;
	std::wstring w_name = std::wstring(name.begin(), name.end());
	swprintf_s(buffer, L"Player %s drowned! \n", w_name.c_str());
	game->PrintMessage(buffer);
	*/

	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnPlayerDeathPriority == (GenericMod::Priority)priority) {
				dll->mod->OnPlayerDeath(game, player, GenericMod::DeathType::DROWN);
			}
		}
	}
}

GETTER_VAR(void*, ASM_cube__Creature__OnPlayerDrownDeath_JMPBACK);
__attribute__((naked)) void ASM_cube__Creature__OnPlayerDrownDeath() {
	asm(".intel_syntax \n"

		// r13: player
		// r12: world
		"mov rcx, r13 \n"
		"call cube__Creature__OnPlayerDrownDeath \n"
		
		//"comiss  xmm9, dword ptr [r15] \n"
		//"jbe 1f \n"
		//"mov     [r15], r14d \n"
		//"1: \n"

		// Old code
		"mov     qword ptr [rbp-0x48], 0 \n"

		DEREF_JMP(ASM_cube__Creature__OnPlayerDrownDeath_JMPBACK)
	);
}

void setup_cube__Creature__OnPlayerDrownDeath() {
	WriteFarJMP(CWOffset(0x2E049A), (void*)&ASM_cube__Creature__OnPlayerDrownDeath);
	ASM_cube__Creature__OnPlayerDrownDeath_JMPBACK = CWOffset(0x2E04AB);
}