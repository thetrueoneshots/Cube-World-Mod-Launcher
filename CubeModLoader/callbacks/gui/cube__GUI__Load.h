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
	text_shape->text_pivot = 1;

	std::wstring wstr_wait = L"wait";
	gui->wait_node = plasma_engine->CreateNode(nullptr, text_shape, nullptr, root_node, &wstr_wait);

	gui->plasma_node_21 = plasma_engine->CreateNode(gui->interface_elements_node, &wstr_empty);
	std::wstring wstr_combopoints = L"combopoints";
	gui->combopoints_node = plx_node->FindChildByName(&wstr_combopoints);
	gui->combopoints_node->SetParent(gui->interface_elements_node);
	
	std::wstring wstr_enemy = L"enemy";
	std::wstring wstr_monster = L"monster";
	std::wstring wstr_crystal = L"crystal";
	std::wstring wstr_brazier = L"brazier"; 
	std::wstring wstr_manapump = L"manapump";
	std::wstring wstr_npc = L"npc";
	std::wstring wstr_static = L"static";
	std::wstring wstr_object = L"object";
	std::wstring wstr_star = L"star";
	std::wstring wstr_cross = L"cross";
	std::wstring wstr_flightpoint = L"flight-point";
	std::wstring wstr_unkflightpoint = L"unknown-flight-point";
	std::wstring wstr_home = L"home";
	std::wstring wstr_mapposition = L"mapposition";
	std::wstring wstr_direction = L"direction";
	std::wstring wstr_armor_shop = L"armor-shop";
	std::wstring wstr_weapon_shop = L"weapon-shop";
	std::wstring wstr_item_shop = L"item-shop";
	std::wstring wstr_identifier = L"identifier";
	std::wstring wstr_smithy = L"smithy";
	std::wstring wstr_carpenters_shop = L"carpenters-shop";
	std::wstring wstr_tailors_shop = L"tailors-shop";
	std::wstring wstr_inn = L"inn";
	std::wstring wstr_shrine = L"shrine";
	std::wstring wstr_spirit = L"spirit";
	std::wstring wstr_bell = L"bell";

	std::wstring wstr_harp = L"harp";
	std::wstring wstr_whistle = L"whistle";
	std::wstring wstr_solved = L"solved";
	std::wstring wstr_gnome = L"gnome";
	std::wstring wstr_hangglider = L"hangglider";
	std::wstring wstr_boat = L"boat";
	std::wstring wstr_climbingspikes = L"climbingspikes";
	std::wstring wstr_reins = L"reins";
	std::wstring wstr_destination = L"destination";
	std::wstring wstr_crafting1 = L"crafting1";

	gui->enemy_node = plx_node->FindChildByName(&wstr_enemy);
	gui->monster_node = plx_node->FindChildByName(&wstr_monster);
	gui->crystal_node = plx_node->FindChildByName(&wstr_crystal);
	gui->brazier_node = plx_node->FindChildByName(&wstr_brazier);
	gui->brazier_node = plx_node->FindChildByName(&wstr_manapump);
	gui->npc_node = plx_node->FindChildByName(&wstr_npc);
	gui->static_node = plx_node->FindChildByName(&wstr_static);
	gui->object_node = plx_node->FindChildByName(&wstr_object); 
	gui->star_node = plx_node->FindChildByName(&wstr_star);
	gui->cross_node = plx_node->FindChildByName(&wstr_cross);
	gui->flight_point_node = plx_node->FindChildByName(&wstr_flightpoint);
	gui->unknown_flight_point_node = plx_node->FindChildByName(&wstr_unkflightpoint);
	gui->home_node = plx_node->FindChildByName(&wstr_home);
	gui->mapposition_node = plx_node->FindChildByName(&wstr_mapposition);
	gui->direction_node = plx_node->FindChildByName(&wstr_direction);
	gui->armor_shop_node = plx_node->FindChildByName(&wstr_armor_shop);
	gui->weapon_shop_node = plx_node->FindChildByName(&wstr_weapon_shop);
	gui->item_shop_node = plx_node->FindChildByName(&wstr_item_shop);
	gui->identifier_node = plx_node->FindChildByName(&wstr_identifier);
	gui->smithy_node = plx_node->FindChildByName(&wstr_smithy);
	gui->carpenters_shop_node = plx_node->FindChildByName(&wstr_carpenters_shop);
	gui->tailors_shop_node = plx_node->FindChildByName(&wstr_tailors_shop);
	gui->inn_node = plx_node->FindChildByName(&wstr_inn);
	gui->shrine_node = plx_node->FindChildByName(&wstr_shrine);
	gui->spirit_node = plx_node->FindChildByName(&wstr_spirit);
	gui->bell_node = plx_node->FindChildByName(&wstr_bell);

	gui->harp_node = plx_node->FindChildByName(&wstr_harp);
	gui->whistle_node = plx_node->FindChildByName(&wstr_whistle);
	gui->solved_node = plx_node->FindChildByName(&wstr_solved);
	gui->gnome_node = plx_node->FindChildByName(&wstr_gnome);
	gui->hangglider_node = plx_node->FindChildByName(&wstr_hangglider);
	gui->boat_node = plx_node->FindChildByName(&wstr_boat);
	gui->climbingspikes_node = plx_node->FindChildByName(&wstr_climbingspikes);
	gui->reins_node = plx_node->FindChildByName(&wstr_reins);
	gui->destination_node = plx_node->FindChildByName(&wstr_destination);
	gui->crafting1_node = plx_node->FindChildByName(&wstr_crafting1);

	// loc_FC16E
	return;
}

overwrite_function(0xF9AC0, cube__GUI__Load);
