#pragma once
#include "../../CWSDK/cwsdk.h"

extern "C" void cube__Game__Update(cube::Game * game)
{
	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnGameUpdatePriority == (GenericMod::Priority)priority) {
				dll->mod->OnGameUpdate(game);
			}
		}
	}
}

GETTER_VAR(void*, ASM_cube__Game__Update_jmpback);
GETTER_VAR(void*, ASM_cube__Game__Update_bail);
__attribute__((naked)) void ASM_cube__Game__Update() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, r13 \n"
		PREPARE_STACK
		"call cube__Game__Update \n"
		RESTORE_STACK
		POP_ALL

		// Old code
		"mov rdx, [r13 + 0x08] \n"
		"mov eax, [rdx + 0x220] \n"
		"cmp [r13 + 0x206C], eax \n"
		"jnz 1f \n"
		DEREF_JMP(ASM_cube__Game__Update_jmpback)

		"1: \n"
		DEREF_JMP(ASM_cube__Game__Update_bail)
	);
}
void setup_cube__Game__Update() {
	WriteFarJMP(CWOffset(0xAD724), (void*)&ASM_cube__Game__Update);
	ASM_cube__Game__Update_jmpback = CWOffset(0xAD737);
	ASM_cube__Game__Update_bail = CWOffset(0xAD74E);
}