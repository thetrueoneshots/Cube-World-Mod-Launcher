#pragma once

extern "C" void cube__Creature__OnPlayerDeath(cube::Game* game)
{
	cube::Creature* player = game->world->local_creature;
	player->entity_data.HP = 0;

	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnPlayerDeathPriority == (GenericMod::Priority)priority) {
				dll->mod->OnPlayerDeath(game, player);
			}
		}
	}
}

extern "C" void SoundPacket__ctor(void* a1)
{
	((void (*)(void*))CWOffset(0x80270))(a1);
}

GETTER_VAR(void*, ASM_cube__Creature__OnPlayerDeath_JMPBACK);
__attribute__((naked)) void ASM_cube__Creature__OnPlayerDeath() {
		asm(".intel_syntax \n"
			
			// Move current cube::Game* to the first argument. 
			// This does not have to be restored, because rcx is set to a value afterwards anyways
			"mov rcx, r13 \n"
			"call cube__Creature__OnPlayerDeath \n"

			// Old code
			"lea  rcx, [rbp+0x0A20] \n"
			"call SoundPacket__ctor \n"
			DEREF_JMP(ASM_cube__Creature__OnPlayerDeath_JMPBACK)
		);
}

void setup_cube__Creature__OnPlayerDeath() {
		WriteFarJMP(CWOffset(0xA8EE7), (void*)&ASM_cube__Creature__OnPlayerDeath);
		ASM_cube__Creature__OnPlayerDeath_JMPBACK = CWOffset(0xA8EFA);
}