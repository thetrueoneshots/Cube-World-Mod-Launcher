#pragma once
#include <string>
#include "cwsdk.h"
#include "../ModWidget.h"

//plasma::TextShape* shape;

/*void Stub(cube::Game* game)
{
	wchar_t buff[250];
	std::wstring wstr_aura_bullwark(L"aura:bulwark");
	plasma::Map<long long, plasma::Node*>* map = &game->gui.icon_node_map;
	
	swprintf_s(buff, 250, L"Size of map: %d\n", map->size);
	game->PrintMessage(buff);

	plasma::Map<long long, plasma::Node*>::Result r;
	map->FindOrCreateNode(&r, 16);
	r.node->val->name = L"not flamerush xD";

	swprintf_s(buff, 250, L"Size of map: %d\n", game->gui.icon_node_map.size);
	game->PrintMessage(buff);

	if (game->gui.icon_node_map.size > 0)
	{
		plasma::Map<long long, plasma::Node*>::Node* node = game->gui.icon_node_map.head->parent;

		while (node->isnil == 0)
		{
			swprintf_s(buff, 250, L"Key: %d\n", node->key);
			game->PrintMessage(buff);
			swprintf_s(buff, 250, L"Val: %s\n", node->val->name.c_str());
			game->PrintMessage(buff);
			node = node->right;
		}
	}

	shape = game->plasma_engine->CreateTextShape();

	shape->colors.data[shape->colors.current_frame] = FloatRGBA(1, 1, 1, 1);
	shape->strokeColors.data[shape->strokeColors.current_frame] = FloatRGBA(0, 0, 0, 1);
	shape->extrusionColors.data[shape->extrusionColors.current_frame] = FloatRGBA(0, 0, 0, 1);

	shape->text_size = 100.0f;
	shape->stroke_size = 2.0f;
	shape->horizontal_spacing = 3.0f;
	shape->vertical_spacing = 3.0f;

	shape->string.data[shape->string.current_frame] = L"Wollayy!!!\n Newline?? :D";

	shape->font_file_name = L"resource1.dat";

	shape->text_pivot = 0;

	shape->Load(true);

	std::wstring name(L"RandomText");
	std::wstring empty(L"");
	plasma::Node* node = game->plasma_engine->CreateNode(nullptr, shape, nullptr, game->plasma_engine->root_node, &name);
	node->Translate(game->width / 2, game->height / 2, 0, 0);
	plasma::Node* blackwidget = game->gui.blackwidget_node_0->CreateCopy(node);
	plasma::Node* blackwidget2 = blackwidget->CreateDeepCopy(nullptr);
	blackwidget2->SetParent(blackwidget);//game->gui.button2_node->CreateCopy(blackwidget);//blackwidget->CreateDeepCopy(blackwidget); //
	blackwidget->AddChild(blackwidget2);
	
	//blackwidget->widget1->some_size = FloatVector2(500, 500);
	// For now just the name
	plasma::TextShape* shape2 = shape->CreateCopy();
	shape2->text_size = 12;
	shape2->stroke_size = 1;
	plasma::Node* textNode = game->plasma_engine->CreateNode(nullptr, shape2, nullptr, blackwidget, &empty);
	// textNode->Translate(blackwidget->widget1->matrix._14 * blackwidget->widget1->scale, blackwidget->widget1->matrix._24, 0, 0);

	textNode->SetText(&name);

	//blackwidget2->transformation->base_transformation.scale(1.0f, 1.0f, 1.0f);
	//blackwidget2->transformation->local_transformation.scale(2.0f, 1.0f, 1.0f);
	//blackwidget2->Translate(0, 0, 100, 100);
	//blackwidget2->widget1->matrix.scale(0.5f, 0.33f, 1.0f);
	float size_x = 800;
	float size_y = 300;
	blackwidget2->Translate(game->width / 2, game->height / 2, -100, 100);
	blackwidget->Translate(game->width / 2, game->height / 2, 0, 0);
	//blackwidget2->widget1->SetSize(size_x, size_y);
	blackwidget2->widget1->SetSize(blackwidget2->widget1->GetXSize() * 2, blackwidget2->widget1->GetYSize() * 0.5f);
	//blackwidget2->widget1->matrix.scale(-1.0f, 1.0f, 1.0f);
	//blackwidget2->widget1->matrix.m[0] = 1.0f;
	//blackwidget2->widget1->matrix.m[1] = 1.0f;
	blackwidget2->widget1->CW_32B0C0();


	//m->scale(2.0f);
	//TransformationMatrix* m = (TransformationMatrix*)&blackwidget2->transformation->some_matrix;
	//m->_sx = 0.1f;
	//Matrix4* m = &blackwidget2->widget1->matrix;
	//m->_41 = 50;
	//m->_42 = 50;
	//m->_33 = 50;
	//m->_34 = 50;
	//m->_44 = 50;
	//blackwidget2->widget1->matrix = Matrix4(200.0f);

	//TransformationMatrix* matrix = &blackwidget2->widget1->base_transformation;
	//matrix->_tx -= 100;
	//matrix->_ty = 0;

	/*
	TransformationMatrix* matrix2 = &blackwidget2->widget1->local_transformation;
	matrix2->_tx = 0;
	matrix2->_ty = 0;
	matrix2->_sx = 2;
	matrix2->_sy = 2;
	*/

	/*plasma::Node* blackwidget3 = game->gui.blackwidget_node_0->CreateCopy(blackwidget2);

	TransformationMatrix* matrix3 = &blackwidget3->widget1->base_transformation;
	matrix3->_tx = 0;
	matrix3->_ty = 0;
	TransformationMatrix* matrix4 = &blackwidget3->widget1->local_transformation;
	matrix4->_tx = 0;
	matrix4->_ty = 0;
	*/

/*
	Matrix4* m = (Matrix4*)&blackwidget2->widget1->matrix;
	wchar_t buffer[250];
	swprintf_s(buffer, 250, L"{%.4f, %.4f, %.4f, %.4f}\n", m->_11, m->_12, m->_13, m->_14);
	game->PrintMessage(buffer);
	swprintf_s(buffer, 250, L"{%.4f, %.4f, %.4f, %.4f}\n", m->_21, m->_22, m->_23, m->_24);
	game->PrintMessage(buffer);
	swprintf_s(buffer, 250, L"{%.4f, %.4f, %.4f, %.4f}\n", m->_31, m->_32, m->_33, m->_34);
	game->PrintMessage(buffer);
	swprintf_s(buffer, 250, L"{%.4f, %.4f, %.4f, %.4f}\n", m->_41, m->_42, m->_43, m->_44);
	game->PrintMessage(buffer);
}
*/
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


	//blackwidget->SetParent(nullptr);
	plasma::Node* blackwidget_cpy = blackwidget->CreateCopy(game->plasma_engine->root_node);
	blackwidget->SetVisibility(true);

	cube::OptionsWidget* widget = (cube::OptionsWidget*)new char[sizeof(cube::OptionsWidget)];
	widget->ctor(game, blackwidget_cpy, left_button, right_button, button2);

	// Most likely widget scale
	// widget->Translate(game->width, game->height, 0);


	//game->plasma_engine->root_node->SetParent(blackwidget);
	//blackwidget->Translate(0, 0, game->width / 2, game->height / 2);
}

void DrawModWidget(cube::BaseWidget* widget)
{
	const static float text_size = 18.0f; // Original	18.0f
	const static float border_size = 4.0f; // Original	4.0f

	FloatRGBA text_color(1.0f, 1.0f, 1.0f, 1.0f);
	FloatRGBA hover_color(0.2f, 1.0f, 1.0f, 1.0f);
	FloatRGBA disabled_color(1.0f, 1.0f, 1.0f, 0.2f);
	FloatRGBA border_color(0.0f, 0.0f, 0.0f, 1.0f);

	FloatVector2 pos(0, 0);
	std::wstring title(L"Do you want to run with mods?");
	std::wstring wstr_yes(L"Yes");
	std::wstring wstr_no(L"No");
	widget->SetTextSize(text_size);
	widget->SetBorderSize(border_size);
	widget->SetTextPivot(plasma::TextPivot::Center);
	widget->SetBorderColor(&border_color);
	widget->DrawString(&pos, &title, widget->GetXSize() / 2 + 100, 150);

	widget->SetTextColor(&hover_color);
	widget->DrawString(&pos, &wstr_yes, widget->GetXSize() / 2 + 50, 200);
	widget->SetTextColor(&text_color);
	widget->DrawString(&pos, &wstr_no, widget->GetXSize() / 2 + 150, 200);
	return;
}

//void* VTABLE[43];

void RenderGUI(cube::Game* game)
{
	/*void* NULLSUB = CWOffset(0xE8A20);
	void* RETZERO = CWOffset(0x368230);

	void *vtab[43] = {
	CWOffset(0x268B40),
	&DrawModWidget,				// void Draw(plasma::Widget*)
	CWOffset(0x26A720),
	CWOffset(0x26A720),
	RETZERO,
	RETZERO,
	NULLSUB,
	CWOffset(0x32B830),
	CWOffset(0x32BFD0),
	CWOffset(0x32BD70),
	NULLSUB,
	CWOffset(0x32B990),
	CWOffset(0x32BB40),
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	CWOffset(0x32BB80),		// void OnMouseOver(plasma::Widget*)
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	NULLSUB,
	CWOffset(0x32B5A0),
	CWOffset(0x32B6B0),
	NULLSUB,
	NULLSUB,
	CWOffset(0x32B6E0),
	CWOffset(0x32A2C0),		// plasma::Widget* CreateCopy(plasma::Widget*);
	CWOffset(0x32A8D0),
	NULLSUB
	};

	for (int i = 0; i < 43; ++i)
	{
		VTABLE[i] = vtab[i];
	}
	*/

	// Variables
	FloatVector2 size(500, 150);
	std::wstring name(L"mod-node");
	std::wstring w_name(L"mod-widget");

	// Create node to add to the engine root node (automatically gets drawn)
	plasma::Node* node = game->plasma_engine->CreateNode(game->plasma_engine->root_node, &name);
	node->text_shape = game->gui.start_menu_widget->node->text_shape;
	// Create a deep copy of the blackwidget (background node)
	plasma::Node* background = game->gui.blackwidget_node_0->CreateDeepCopy(node);

	// Translate the node to the center
	node->Translate(game->width / 2, game->height / 2, -size.x / 2 + 100, -size.y / 2 - 100);
	//background->Translate(game->width / 2, game->height / 2, -size.x / 2, -size.y / 2);

	// Set node (indirectly) size
	
	if (background->widget1 != nullptr)
	{
		background->widget1->SetSize(&size);
		background->widget1->field_1A0 = 0;
	}
	else
	{
		background->transformation->local_transformation.scale(2.0f, 1.0f, 1.0f);//SetSize(&size, true);
	}


	mod::ModWidget::Init();
	mod::ModWidget* widget = (mod::ModWidget*)new char[sizeof(mod::ModWidget)];
	widget->ctor(game, node);

	//cube::BaseWidget* basewidget = (cube::BaseWidget*)new char[sizeof(cube::BaseWidget)];
	/*basewidget = basewidget->ctor(game->plasma_engine, node, &w_name);

	std::wstring fontName(L"resource1.dat");
	basewidget->SetScalableFont(&fontName);
	basewidget->Translate(100, 200, 1);
	
	// Manually set vtable
	size_t* vptr = (size_t*)basewidget;
	*vptr = (size_t)VTABLE; //(size_t)CWOffset(0x46CED8);
	*/

	//game->PrintMessage(node->widget1->name.c_str());
}

extern "C" void GameTickHandler(cube::Game* game) {
	static bool init = false;
	if (!init)
	{
		init = true;

		RenderGUI(game);
		//DrawPLXOnScreen(game);
	}

	// Constantly flickering text
	std::wstring name(L"RandomText");
	plasma::Node* node = game->plasma_engine->root_node->FindChildByName(&name);
	if (node != nullptr)
	{
		node->Translate(0, 0, game->width / 2, game->height / 2);
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
