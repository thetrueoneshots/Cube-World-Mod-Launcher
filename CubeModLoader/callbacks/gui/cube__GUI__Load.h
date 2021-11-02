#pragma once
#include "../../CWSDK/cwsdk.h"

extern "C" void cube__GUI__Load(cube::GUI * gui, void* db)
{
	cube::Game* game = gui->game;
	plasma::D3D11Engine* plasma_engine = game->plasma_engine;
	plasma::Node* root_node = plasma_engine->root_node;

	std::wstring wstr_textFX(L"textFX");
	std::wstring wstr_lifebars(L"lifebars");
	std::wstring wstr_empty(L"");
	std::string str_plasmaXGraphics("PlasmaXGraphics");

	gui->textFX_node = plasma_engine->CreateNode(root_node, &wstr_textFX);
	gui->lifebars_node = plasma_engine->CreateNode(root_node, &wstr_lifebars);
	gui->interface_elements_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->startmenu_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->character_selection_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->character_creation_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->world_selection_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->world_creation_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->plasma_node_54 = plasma_engine->CreateNode(root_node, &wstr_empty);



	gui->startmenu_node->SetVisibility(true);
	gui->character_selection_node->SetVisibility(false);
	gui->character_creation_node->SetVisibility(false);
	gui->world_selection_node->SetVisibility(false);
	gui->world_creation_node->SetVisibility(false);

	return;
}

overwrite_function(0xF9AC0, cube__GUI__Load);
