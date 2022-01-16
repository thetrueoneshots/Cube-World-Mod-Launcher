#pragma once

extern "C" void cube__Creature__OnCreatureDeath(cube::Creature* creature)
{
	cube::Game* game = cube::GetGame();
	creature->entity_data.HP = 0;

	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnCreatureDeathPriority == (GenericMod::Priority)priority) {
				dll->mod->OnCreatureDeath(game, creature);
			}
		}
	}
}

GETTER_VAR(void*, ASM_cube__Creature__OnCreatureDeath_JMPBACK);
__attribute__((naked)) void ASM_cube__Creature__OnCreatureDeath() {
	asm(".intel_syntax \n"

		// Move current cube::Game* to the first argument. 
		// This does not have to be restored, because rcx is set to a value afterwards anyways
		"mov rcx, r13 \n"
		"call cube__Creature__OnCreatureDeath \n"

		// Old code
		"xor r15d, r15d \n"
		"mov dword ptr [rbp - 0x41], 0x3F800000 \n"
		DEREF_JMP(ASM_cube__Creature__OnCreatureDeath_JMPBACK)
	);
}

void setup_cube__Creature__OnCreatureDeath() {
	WriteFarJMP(CWOffset(0x29E494), (void*)&ASM_cube__Creature__OnCreatureDeath);
	ASM_cube__Creature__OnCreatureDeath_JMPBACK = CWOffset(0x29E4A5);
}