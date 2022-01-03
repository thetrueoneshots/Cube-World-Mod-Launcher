#pragma once
#include "../../CWSDK/cwsdk.h"

float SUB_A7A0(float x0, float x1)
{
	return ((float (*)(float, float))CWOffset(0xA7A0))(x0, x1);
}

plasma::Matrix<float>* Matrix4__Multiply(plasma::Matrix<float>* a1, plasma::Matrix<float>* a2)
{
	return ((plasma::Matrix<float> * (*)(plasma::Matrix<float>*, plasma::Matrix<float>*))CWOffset(0x173E0))(a1, a2);
}

extern "C" void cube__CharacterPreviewWidget__Draw(cube::CharacterPreviewWidget * widget)
{
	std::wstring wstr_newcharacter(L"New character");

	FloatVector2 vec;

	FloatRGBA text_color(1, 1, 1, 1);
	FloatRGBA border_color(0, 0, 0, 1);

	cube::Creature* creature = widget->creature;
	cube::Creature::EntityData* entity_data = &creature->entity_data;
	plasma::D3D11Engine* engine = widget->d3d11_engine;

	widget->SetTextSize(15);
	widget->SetBorderSize(3);
	widget->SetTextColor(&text_color);
	widget->SetBorderColor(&border_color);

	
	if (creature == nullptr)
	{
		widget->SetTextPivot((plasma::TextPivot)5);
		widget->DrawString(&vec, &wstr_newcharacter, widget->GetXSize() * 0.5f, 30.0f);
		return;
	}

	entity_data->roll_time = 0;
	entity_data->stun_time = 0;
	entity_data->binary_toggles = 0;
	entity_data->flags = 0;
	entity_data->current_ability = 0;

	// Maybe engine->float_190 is ~Time.deltaTime
	// and creature->float_99C is the z rotation of the player.
	creature->float_99C += engine->float_190 * 0.0075f;
	
	/*float xmm10 = 0.01f;
	if (!widget->CW_32B0C0())
	{
		// More evidence that engine->float_190 is maybe ~Time.deltaTime
		creature->float_B3C -= engine->float_190 * 0.05f;
		creature->float_998 = 0.2f;

		FloatVector3* acceleration = &entity_data->acceleration;
		FloatVector3* velocity = &entity_data->velocity;

		float scalar = SUB_A7A0(engine->float_190, 0.01f);

		acceleration->x += scalar * (-acceleration->x);
		acceleration->y += scalar * (8 - acceleration->y);
		acceleration->z += scalar * (-acceleration->z);

		velocity->x += scalar * (-velocity->x);
		velocity->y += scalar * (-velocity->y);
		velocity->z += scalar * (-velocity->z);
	}*/

	/*
	// loc_26F093 Load some matrix otherwise
	plasma::Matrix<float> a2 = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	plasma::Node* node = widget->node;
	Matrix4__Multiply(&node->transformation->base_transformation, &a2);
	*/

	// This is crashing somehow?
	widget->game->renderer->CW_DB630(&creature->animation_state, 100, 100);
	((void (*)(plasma::D3D11Engine*))(*(int*)widget->d3d11_engine + 0x80))(widget->d3d11_engine);
}

overwrite_function(0x26EBA0, cube__CharacterPreviewWidget__Draw);