#pragma once
#include "../../CWSDK/cwsdk.h"

extern "C" void cube__GUI__Load(cube::GUI * gui, void* db)
{
	cube::Game* game = gui->game;
	plasma::D3D11Engine* plasma_engine = game->plasma_engine;
	plasma::Node* root_node = plasma_engine->root_node;
	plasma::Node* icon_plx_node; 
	plasma::Map<long long, plasma::Node*>::Result res;
	plasma::Map<long long, plasma::Node*>* icon_map = &gui->icon_node_map;

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
	std::wstring file_gui(L"gui.plx");
	std::wstring file_quest(L"quest-tag.plx");

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

	const static int skill_cnt = 4;
	const static std::pair<int, std::wstring> skills[skill_cnt] = {
		{55, L"smash"},
		{95, L"cyclone"},
		{114, L"warfrenzy"},
		{148, L"rock-fist"}
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
	icon_plx_node = gui->icon_plx_node;
	plasma_engine->LoadNodeFromFile(&file_icon, gui->icon_plx_node, 32, 0);
	for (int i = 0; i < aura_cnt; i++)
	{
		icon_map->FindOrCreateNode(&res, auras[i].first)->node->val = gui->icon_plx_node->FindChildByName(&(auras[i].second));
	}

	// Load weapon rarity nodes
	gui->weaponrarity0_node = icon_plx_node->FindChildByName(&wstr_weaponrarity_0);
	gui->weaponrarity1_node = icon_plx_node->FindChildByName(&wstr_weaponrarity_1);
	gui->weaponrarity2_node = icon_plx_node->FindChildByName(&wstr_weaponrarity_2);
	gui->weaponrarity3_node = icon_plx_node->FindChildByName(&wstr_weaponrarity_3);
	gui->weaponrarity4_node = icon_plx_node->FindChildByName(&wstr_weaponrarity_4);
	gui->weaponrarity5_node = icon_plx_node->FindChildByName(&wstr_weaponrarity_5);

	// Load armor rarity nodes
	gui->armorrarity0_node = icon_plx_node->FindChildByName(&wstr_armorrarity_0);
	gui->armorrarity1_node = icon_plx_node->FindChildByName(&wstr_armorrarity_1);
	gui->armorrarity2_node = icon_plx_node->FindChildByName(&wstr_armorrarity_2);
	gui->armorrarity3_node = icon_plx_node->FindChildByName(&wstr_armorrarity_3);
	gui->armorrarity4_node = icon_plx_node->FindChildByName(&wstr_armorrarity_4);
	gui->armorrarity5_node = icon_plx_node->FindChildByName(&wstr_armorrarity_5);

	// Load skill icons into the skill_node_map
	for (int i = 0; i < skill_cnt; i++)
	{
		gui->skill_node_map.FindOrCreateNode(&res, skills[i].first)->node->val = gui->icon_plx_node->FindChildByName(&(skills[i].second));
	}

	// Load gui related plx files
	plasma::Node* plx_node = plasma_engine->CreateNode(nullptr, &wstr_empty);
	plasma_engine->LoadNodeFromFile(&file_gui, plx_node, 32, 0);
	plasma_engine->LoadNodeFromFile(&file_quest, plx_node, 32, 0);

	gui->startmenu_buttons_node = plasma_engine->CreateNode(gui->startmenu_node, &wstr_empty);

	cube::StartMenuWidget* startmenu_widget = (cube::StartMenuWidget*)new char[sizeof(cube::StartMenuWidget)];
	gui->start_menu_widget = startmenu_widget->ctor(game, gui->startmenu_buttons_node);
	startmenu_widget->Translate(200.0f, 100.0f, 1);

	plasma::TextShape* text_shape = plasma_engine->CreateTextShape();

	// White
	text_shape->colors.data[text_shape->colors.current_frame] = FloatRGBA(1);
	// Set string size to 12?
	text_shape->text_size = 12.0f;
	// Black
	text_shape->strokeColors.data[text_shape->strokeColors.current_frame] = FloatRGBA(0, 0, 0, 1);
	// Set stroke size to 3?
	text_shape->stroke_size = 3.0f;
	text_shape->vertical_spacing = 3.0f;
	text_shape->string.data[text_shape->string.current_frame] = L"Please wait...";
	text_shape->font_file_name = L"resource1.dat";
	text_shape->int_2F8 = 1;

	std::wstring wstr_wait = L"wait";
	gui->wait_node = plasma_engine->CreateNode(nullptr, text_shape, nullptr, root_node, &wstr_wait);

	return;
}

overwrite_function(0xF9AC0, cube__GUI__Load);
