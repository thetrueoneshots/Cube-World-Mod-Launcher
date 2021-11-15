#pragma once
#include "../../CWSDK/cwsdk.h"

extern "C" void cube__GUI__Load(cube::GUI * gui, void* db)
{
	cube::Game* game = gui->game;
	plasma::D3D11Engine* plasma_engine = game->plasma_engine;
	plasma::Node* root_node = plasma_engine->root_node;
	plasma::Map<plasma::Node>::Result res;

	// Node names
	std::wstring wstr_textFX(L"textFX");
	std::wstring wstr_lifebars(L"lifebars");
	std::wstring wstr_weaponrarity_0(L"weaponrarity0");
	std::wstring wstr_weaponrarity_1(L"weaponrarity1");
	std::wstring wstr_weaponrarity_2(L"weaponrarity2");
	std::wstring wstr_weaponrarity_3(L"weaponrarity3");
	std::wstring wstr_weaponrarity_4(L"weaponrarity4");
	std::wstring wstr_weaponrarity_5(L"weaponrarity5");
	std::wstring wstr_armorrarity_0(L"armorrarity0");
	std::wstring wstr_armorrarity_1(L"armorrarity1");
	std::wstring wstr_armorrarity_2(L"armorrarity2");
	std::wstring wstr_armorrarity_3(L"armorrarity3");
	std::wstring wstr_armorrarity_4(L"armorrarity4");
	std::wstring wstr_armorrarity_5(L"armorrarity5");
	std::wstring wstr_empty(L"");

	// Files
	std::wstring file_icon(L"icons.plx");

	// String key for loading plx files
	std::string str_plasmaXGraphics("PlasmaXGraphics");

	// Aura icons
	const static int aura_cnt = 24;
	const static std::pair<int, std::wstring> auras[aura_cnt] = {
		{1, L"aura:bulwark"},				//01
		{2, L"aura:warfrenzy"},				//02
		{3, L"aura:camouflage"},			//03
		{4, L"aura:poisoned"},				//04
		{6, L"aura:manashield"},			//06
		{9, L"aura:instantfire"},			//09
		{10, L"aura:instantshoot"},			//10
		{11, L"aura:dodge"},				//11
		{12, L"aura:swiftness"},			//12
		{13, L"aura:ninjutsu"},				//13
		{15, L"aura:shadowclone"},			//15
		{16, L"aura:flamerush"},			//16
		{17, L"aura:regeneration"},			//17
		{19, L"aura:spiritworld"},			//19
		{22, L"aura:lifeflask"},			//22
		{23, L"aura:attackflask"},			//23
		{24, L"aura:armorflask"},			//24
		{25, L"aura:resistanceflask"},		//25
		{27, L"aura:coldresistance"},		//27
		{26, L"aura:heatresistance"},		//26
		{28, L"aura:plagueresistance"},		//28
		{29, L"aura:frozen"},				//29
		{33, L"aura:ancientpower"},			//33
		{34, L"aura:manaabsorption"}		//34
	};

	// Create nodes
	gui->textFX_node = plasma_engine->CreateNode(root_node, &wstr_textFX);
	gui->lifebars_node = plasma_engine->CreateNode(root_node, &wstr_lifebars);
	gui->interface_elements_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->startmenu_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->character_selection_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->character_creation_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->world_selection_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	gui->world_creation_node = plasma_engine->CreateNode(root_node, &wstr_empty);

	// Set visibilities
	gui->startmenu_node->SetVisibility(true);
	gui->character_selection_node->SetVisibility(false);
	gui->character_creation_node->SetVisibility(false);
	gui->world_selection_node->SetVisibility(false);
	gui->world_creation_node->SetVisibility(false);


	// Load aura icon nodes into a map
	gui->icon_plx_node = plasma_engine->CreateNode(root_node, &wstr_empty);
	plasma_engine->LoadNodeFromFile(&file_icon, gui->icon_plx_node, 32, 0);
	for (int i = 0; i < aura_cnt; i++)
	{
		gui->icon_node_map.FindOrCreateNode(&res, auras[i].first)->node->val = gui->icon_plx_node->FindChildByName(&(auras[i].second));
	}


	// Load weapon rarity nodes
	gui->weaponrarity0_node = gui->icon_plx_node->FindChildByName(&wstr_weaponrarity_0);
	gui->weaponrarity1_node = gui->icon_plx_node->FindChildByName(&wstr_weaponrarity_1);
	gui->weaponrarity2_node = gui->icon_plx_node->FindChildByName(&wstr_weaponrarity_2);
	gui->weaponrarity3_node = gui->icon_plx_node->FindChildByName(&wstr_weaponrarity_3);
	gui->weaponrarity4_node = gui->icon_plx_node->FindChildByName(&wstr_weaponrarity_4);
	gui->weaponrarity5_node = gui->icon_plx_node->FindChildByName(&wstr_weaponrarity_5);

	// Load armor rarity nodes
	gui->armorrarity0_node = gui->icon_plx_node->FindChildByName(&wstr_armorrarity_0);
	gui->armorrarity1_node = gui->icon_plx_node->FindChildByName(&wstr_armorrarity_1);
	gui->armorrarity2_node = gui->icon_plx_node->FindChildByName(&wstr_armorrarity_2);
	gui->armorrarity3_node = gui->icon_plx_node->FindChildByName(&wstr_armorrarity_3);
	gui->armorrarity4_node = gui->icon_plx_node->FindChildByName(&wstr_armorrarity_4);
	gui->armorrarity5_node = gui->icon_plx_node->FindChildByName(&wstr_armorrarity_5);

	return;
}

overwrite_function(0xF9AC0, cube__GUI__Load);
