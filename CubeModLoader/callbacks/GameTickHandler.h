#pragma once
#include <string>
#include "cwsdk.h"

void Stub(cube::Game* game)
{
	wchar_t buff[250];
	std::wstring wstr_aura_bullwark(L"aura:bulwark");
	plasma::Map<plasma::Node>* map = &game->gui.icon_node_map;
	
	swprintf_s(buff, 250, L"Size of map: %d\n", map->size);
	game->PrintMessage(buff);

	plasma::Map<plasma::Node>::Result r;
	map->FindOrCreateNode(&r, 16);
	r.node->val->name = L"not flamerush xD";

	swprintf_s(buff, 250, L"Size of map: %d\n", game->gui.icon_node_map.size);
	game->PrintMessage(buff);

	if (game->gui.icon_node_map.size > 0)
	{
		plasma::Map<plasma::Node>::Node* node = game->gui.icon_node_map.head->parent;

		while (node->isnil == 0)
		{
			swprintf_s(buff, 250, L"Key: %d\n", node->key);
			game->PrintMessage(buff);
			swprintf_s(buff, 250, L"Val: %s\n", node->val->name.c_str());
			game->PrintMessage(buff);
			node = node->right;
		}
	}
}

// Todo: Remove from callback
void DrawPLXOnScreen(cube::Game* game)
{
	std::wstring wstr_empty(L"");
	std::wstring wstr_guiPLX(L"gui.plx");
	//plasma::Node* guiNode = game->plasma_engine->CreateNode(game->plasma_engine->root_node, &wstr_empty);
	plasma::Node* guiNode = game->plasma_engine->CreateNode(nullptr, &wstr_empty);
	game->plasma_engine->LoadNodeFromFile(&wstr_guiPLX, guiNode, 32, 0);

	std::wstring wstr_blackwidget(L"blackwidget");
	std::wstring wstr_left_button(L"leftbutton");
	std::wstring wstr_right_button(L"rightbutton");
	std::wstring wstr_button2(L"button2");
	plasma::Node* blackwidget = guiNode->FindChildByName(&wstr_blackwidget);
	plasma::Node* left_button = guiNode->FindChildByName(&wstr_left_button);
	plasma::Node* right_button = guiNode->FindChildByName(&wstr_right_button);
	plasma::Node* button2 = guiNode->FindChildByName(&wstr_button2);


	//blackwidget->cw_3347F0(nullptr);
	plasma::Node* blackwidget_cpy = blackwidget->CreateCopy(game->plasma_engine->root_node);
	blackwidget->SetVisibility(true);

	cube::OptionsWidget* widget = (cube::OptionsWidget*)new char[sizeof(cube::OptionsWidget)];
	widget->ctor(game, blackwidget_cpy, left_button, right_button, button2);

	// Most likely widget scale
	// widget->Translate(game->width, game->height, 0);


	//game->plasma_engine->root_node->cw_3347F0(blackwidget);
	//blackwidget->Translate(0, 0, game->width / 2, game->height / 2);
}

extern "C" void GameTickHandler(cube::Game* game) {
	static bool init = false;
	if (!init)
	{
		init = true;

		Stub(game);
		//DrawPLXOnScreen(game);
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
