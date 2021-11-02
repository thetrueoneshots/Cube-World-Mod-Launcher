#pragma once
#include <string>
#include "cwsdk.h"
// Todo: Remove from callback
struct SomeStruct {
	char gap[0x200];
};

// Todo: Remove from callback
void DrawPLXOnScreen(cube::Game* game)
{
	std::string encode("PlasmaXGraphics");
	long long r8 = 0x3FFFFFFFFFFE5;
	size_t eax = encode.size();
	if (eax > 0)
	{
		size_t r10 = encode.capacity();
		int i = 0;
		while (i < eax)
		{
			r8 *= 31;
			r8 += encode[i];
			i++;
		}
	}

	SomeStruct s = {};
	((void (*)(void*, int, void*))CWOffset(0xF9110))(&s, 1, &r8);

	//plasma::Node* node = game->gui.blackwidget_node_0->CreateCopy(game->plasma_engine->root_node);
	//node->display->SetVisibility(true);
	std::wstring wstr_empty(L"");
	std::wstring wstr_iconsPLX(L"icons.plx");
	plasma::Node* node = game->plasma_engine->CreateNode(game->plasma_engine->root_node, &wstr_empty);
	game->plasma_engine->LoadNodeFromFile(&wstr_iconsPLX, node, 32, 0, &s);
}

extern "C" void GameTickHandler(cube::Game* game) {
	static bool init = false;
	if (!init)
	{
		init = true;

		DrawPLXOnScreen(game);
	}
	for (uint8_t priority = 0; priority <= 4; priority += 1) {
		for (DLL* dll : modDLLs) {
			if (dll->mod->OnGameTickPriority == (GenericMod::Priority)priority) {
				dll->mod->OnGameTick(game);
			}
		}
	}
}

GETTER_VAR(void*, ASMGameTickHandler_jmpback);
void ASMGameTickHandler() {
    asm(".intel_syntax \n"
		PUSH_ALL

        "mov rcx, rax \n" // cube::Game*

        PREPARE_STACK

        "call GameTickHandler \n"

        RESTORE_STACK

        POP_ALL

        // original code
        "mov [rsp+0x20], ebx \n"
        "xor r9d, r9d \n"
        "xor r8d, r8d \n"
		"xor edx, edx \n"
		"lea rcx, [rbp+0xB8] \n"

		DEREF_JMP(ASMGameTickHandler_jmpback)
       );
}
void SetupGameTickHandler() {
    WriteFarJMP(Offset(base, 0x136458), (void*)&ASMGameTickHandler);
	ASMGameTickHandler_jmpback = Offset(base, 0x13646B);
}
