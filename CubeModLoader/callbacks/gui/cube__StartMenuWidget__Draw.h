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

	// Draw modded text
	widget->SetTextSize(100.0f);
	widget->SetBorderSize(18.0f);
	widget->SetTextPivot(cube::TextPivot::Center);
	widget->SetBorderColor(&border_color);
	widget->SetTextColor(&modded_color);
	widget->DrawBaseWidgetText(&pos, &txt_modded, 0.5* widget->GetXSize(), -300);
}

// Todo: Game version
// Todo: Picroma credits
// Todo: Show modloader version
// Todo: Render credits chris & me
// Todo: Link to bagel his youtube?
extern "C" void cube__StartMenuWidget__Draw(cube::StartMenuWidget * widget)
{
	float width;
	int num_btns = 5;
	int y_offset = -20;
	int btn_height = 50;

	FloatVector2 pos = FloatVector2(0, 0);
	FloatVector2 mouse_pos;
	FloatRGBA text_color(1.0f, 1.0f, 1.0f, 1.0f);
	FloatRGBA hover_color(0.2f, 1.0f, 1.0f, 1.0f);
	FloatRGBA disabled_color(1.0f, 1.0f, 1.0f, 0.2f);
	FloatRGBA border_color(0.0f, 0.0f, 0.0f, 1.0f);

	DrawModdedText(widget);
	
	std::wstring btn_txt[5] = {
		L"Start Game",
		L"Mods",
		L"Continue",
		L"Options",
		L"Exit"
	};
	cube::StartMenuWidget::HoverState states[5] = {
		cube::StartMenuWidget::HoverState::StartGame,
		cube::StartMenuWidget::HoverState::Mods,
		cube::StartMenuWidget::HoverState::Continue,
		cube::StartMenuWidget::HoverState::Options,
		cube::StartMenuWidget::HoverState::Exit,
	};

	mouse_pos = *widget->GetRelativeMousePosition(&mouse_pos);
	width = widget->GetXSize();

	widget->SetTextSize(18.0f);
	widget->SetBorderSize(4.0f);
	widget->SetTextPivot(cube::TextPivot::Center);
	widget->SetBorderColor(&border_color);
	widget->hover_state = cube::StartMenuWidget::HoverState::None;

	// Render all buttons
	for (int i = 0; i < num_btns; i++)
	{
		int btn_y = y_offset + i * btn_height;
		if (!BtnIsHovered(&mouse_pos, width, btn_y))
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