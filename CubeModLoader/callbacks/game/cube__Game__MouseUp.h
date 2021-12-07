#pragma once
#include "../../CWSDK/cwsdk.h"
#include "../ModWidget.h"

extern "C" void cube__Game__MouseUp(cube::Game* game, cube::MouseButton mouse_button)
{
	std::wstring wstr_mod_node(L"mod-node");
	plasma::Node* node = game->plasma_engine->root_node->FindChildByName(&wstr_mod_node);
	if (node != nullptr && node->IsVisible())
	{
		mod::ModWidget* widget = (mod::ModWidget*)node->widget1;
		widget->MouseUp(mouse_button);
		return;
	}

	if (game->gui.startmenu_node->display->IsVisible() && game->gui.startmenu_buttons_node->display->IsVisible())
	{
		if (mouse_button == cube::MouseButton::LeftMouseButton)
		{	
			switch (game->gui.start_menu_widget->hover_state)
			{
			case cube::StartMenuWidget::HoverState::Exit:
				game->shutdown = 1;
				break;
			case cube::StartMenuWidget::HoverState::Continue:
				game->MaybeLoadCharacter(game->current_character_slot, game->GetPlayer());
				game->gui.startmenu_node->display->SetVisibility(game->gui.startmenu_node->display->visibility.current_frame, 0);
				game->target_camera_distance = 8.0f;

				// Todo: Check if needed
				game->camera_distance = 8.0f;

				// Todo: Check if needed
				game->world->CW_2E0B50();
				break;
			case cube::StartMenuWidget::HoverState::Options:
				game->gui.options_widget->node->display->SetVisibility(game->gui.options_widget->node->display->visibility.current_frame, 1);
				break;
			case cube::StartMenuWidget::HoverState::StartGame:
				game->gui.startmenu_node->display->SetVisibility(game->gui.startmenu_node->display->visibility.current_frame, 0);
				game->gui.character_selection_node->display->SetVisibility(game->gui.character_selection_node->display->visibility.current_frame, 1);
				break;
			case cube::StartMenuWidget::HoverState::None:
			default:
				break;
			}
		}
	}

	// Calling this functions seems to crash and therefore I did only a partial hook here.
	//game->gui.MouseUp((int)mouse_button);
}

GETTER_VAR(void*, ASM_cube__Game__MouseUp_jmpback);
__attribute__((naked)) void ASM_cube__Game__MouseUp() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"push rbp \n"
		"mov rbp, rsp \n"
		PREPARE_STACK
		"call cube__Game__MouseUp \n"
		RESTORE_STACK
		"mov rsp, rbp \n"
		"pop rbp \n"
		POP_ALL
		DEREF_JMP(ASM_cube__Game__MouseUp_jmpback)
	);
}
void setup_cube__Game__MouseUp() {
		WriteFarJMP(CWOffset(0x96621), (void*)&ASM_cube__Game__MouseUp);
		ASM_cube__Game__MouseUp_jmpback = CWOffset(0x9675D);
}

//overwrite_function(0x965E0, cube__Game__MouseUp)