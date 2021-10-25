#pragma once
#include "../../CWSDK/cwsdk.h"

bool BtnIsHovered(FloatVector2* mouse_pos, float width, int height)
{
	if (mouse_pos->x < 0 || width <= mouse_pos->x || mouse_pos->y < height - 20 || height + 10 <= mouse_pos->y)
	{
		return false;
	}
	return true;
}

// Todo: Using time constraints and not instructions
void DrawModdedText(cube::StartMenuWidget* widget)
{
	// Color rotation of the modded text
	static float i = 0;
	static int dir = 0;
	int height;

	if (dir == 0)
	{
		i += 0.01f;
		if (i >= 1.0f)
		{
			dir = 1;
			i = 1.0f;
		}
	}
	else {
		i -= 0.01f;
		if (i <= 0.0f)
		{
			dir = 0;
			i = 0.0f;
		}
	}

	FloatRGBA border_color(0.0f, 0.0f, 0.0f, 1.0f);
	FloatRGBA modded_color(i, 1.0f - i, 0.5f + 0.5f * i, 1.0f);
	FloatVector2 pos = FloatVector2(0, 0);
	std::wstring txt_modded = L"Modded";

	height = - widget->game->height / 3;

	// Draw modded text
	widget->SetTextSize(200.0f);
	widget->SetBorderSize(18.0f);
	widget->SetTextPivot(cube::TextPivot::Center);
	widget->SetBorderColor(&border_color);
	widget->SetTextColor(&modded_color);
	widget->DrawBaseWidgetText(&pos, &txt_modded, 0.5* widget->GetXSize(), height);
}

// Todo: Game version
// Todo: Picroma credits
// Todo: Show modloader version
// Todo: Render credits chris & me
// Todo: Link to bagel his youtube?
extern "C" void cube__StartMenuWidget__Draw(cube::StartMenuWidget * widget)
{
	const static float text_size = 36.0f; // Original	18.0f
	const static float border_size = 4.0f; // Original	4.0f
	const int num_btns = 4;

	float width;
	int y_offset = -20;
	int btn_height = 50;
	bool options_active;

	FloatVector2 pos = FloatVector2(0, 0);
	FloatVector2 mouse_pos;
	FloatRGBA text_color(1.0f, 1.0f, 1.0f, 1.0f);
	FloatRGBA hover_color(0.2f, 1.0f, 1.0f, 1.0f);
	FloatRGBA disabled_color(1.0f, 1.0f, 1.0f, 0.2f);
	FloatRGBA border_color(0.0f, 0.0f, 0.0f, 1.0f);

	std::wstring font = L"resource2.dat";
	
	std::wstring btn_txt[num_btns] = {
		L"Start Game",
		L"Continue",
		L"Options",
		L"Exit",
	};

	cube::StartMenuWidget::HoverState states[num_btns] = {
		cube::StartMenuWidget::HoverState::StartGame,
		cube::StartMenuWidget::HoverState::Continue,
		cube::StartMenuWidget::HoverState::Options,
		cube::StartMenuWidget::HoverState::Exit,
	};

	DrawModdedText(widget);

	mouse_pos = *widget->GetRelativeMousePosition(&mouse_pos);
	width = widget->GetXSize();
	options_active = widget->game->gui.options_widget->node->display->IsVisible();

	widget->SetScalableFont(&font);
	widget->SetTextSize(text_size);
	widget->SetBorderSize(border_size);
	widget->SetTextPivot(cube::TextPivot::Center);
	widget->SetBorderColor(&border_color);
	widget->hover_state = cube::StartMenuWidget::HoverState::None;

	// Render all buttons
	for (int i = 0; i < num_btns; i++)
	{
		int btn_y = y_offset + i * btn_height;
		if (!BtnIsHovered(&mouse_pos, width, btn_y) || options_active)
		{
			widget->SetTextColor(&text_color);
		}
		else
		{
			widget->hover_state = states[i];
			widget->SetTextColor(&hover_color);
		}

		if (states[i] == cube::StartMenuWidget::HoverState::Continue)
		{
			int character_slot = widget->game->current_character_slot;
			int character_count = widget->game->saved_characters.size();

			if (character_slot < 0 || character_slot >= character_count)
			{
				if (BtnIsHovered(&mouse_pos, width, btn_y))
				{
					widget->hover_state = cube::StartMenuWidget::HoverState::None;
				}
				widget->SetTextColor(&disabled_color);
			}
		}

		widget->DrawBaseWidgetText(&pos, &btn_txt[i], 0.5 * width, btn_y);
	}
};

overwrite_function(0x291210, cube__StartMenuWidget__Draw);