#include "ModWidget.h"
#include <iostream>
#include <fstream>

static std::string file_name = "mods-settings.cwb";
void* VTABLE[43];

mod::ModWidget* mod::ModWidget::ctor(cube::Game* game, plasma::Node* node, plasma::Node* background, std::vector<DLL*>* mods)
{
	// Construct basewidget
	std::wstring wstr_empty(L"");
	((cube::BaseWidget*)this)->ctor(game->plasma_engine, node, &wstr_empty);

	// Set fields
	this->game = game;
	this->hover_state = 0;
	this->background = background;
	this->mods = mods;

	// Set scalable font
	std::wstring fontName(L"resource1.dat");
	this->SetScalableFont(&fontName);
	this->Translate(100, 200, 1);

	for (int i = 0; i < 43; ++i)
	{
		this->artificial_vtable[i] = VTABLE[i];
	}

	// Manually set vtable
	size_t* vptr = (size_t*)this;
	*vptr = (size_t)this->artificial_vtable; //(size_t)CWOffset(0x46CED8);

	return this;
}

void mod::ModWidget::MouseUp(cube::MouseButton mouse_button)
{
	if (mouse_button != cube::MouseButton::LeftMouseButton)
	{
		return;
	}

	switch (this->hover_state)
	{
	case HoverState::Exit:
		this->node->SetVisibility(false);
		break;
	case HoverState::Toggle:
		if (this->selected < 0 || this->selected >= this->mods->size())
		{
			return;
		}
		this->mods->at(this->selected)->enabled = !this->mods->at(this->selected)->enabled;
		break;
	default:

		break;
	}
}

bool BtnIsHovered(FloatVector2* mouse_pos, float min_x, float max_x, int height)
{
	if (mouse_pos->x < min_x || max_x <= mouse_pos->x || mouse_pos->y < height - 20 || height + 10 <= mouse_pos->y)
	{
		return false;
	}
	return true;
}

void mod::ModWidget::Draw(ModWidget* widget)
{
	const static float text_size = 18.0f; // Original	18.0f
	const static float border_size = 4.0f; // Original	4.0f

	cube::Game* game = widget->game;

	FloatRGBA text_color(1.0f, 1.0f, 1.0f, 1.0f);
	FloatRGBA hover_color(0.2f, 1.0f, 1.0f, 1.0f);
	FloatRGBA disabled_color(1.0f, 1.0f, 1.0f, 0.2f);
	FloatRGBA border_color(0.0f, 0.0f, 0.0f, 1.0f);

	FloatVector2 mouse_pos;
	FloatVector2 pos(0, 0);
	FloatVector2 size(game->width-100, game->height-100);

	std::wstring title(L"Mods");
	std::wstring wstr_enable(L"Enable");
	std::wstring wstr_disable(L"Disable");
	std::wstring wstr_x(L"X");

	// Translate background and node
	widget->node->Translate(game->width/2, game->height/2, -size.x/2, -size.y/2);
	widget->background->Translate(game->width / 2, game->height / 2, -size.x / 2, -size.y / 2);

	// Scale background and node
	widget->SetSize(&size);
	widget->background->widget1->SetSize(&size);

	// Get mouse position in the widget
	mouse_pos = *widget->GetRelativeMousePosition(&mouse_pos);

	// Set hover to 0
	widget->hover_state = ModWidget::HoverState::None;

	// Text settings
	widget->SetTextSize(text_size);
	widget->SetTextColor(&text_color);
	widget->SetBorderSize(border_size);
	widget->SetBorderColor(&border_color);
	widget->SetTextPivot(plasma::TextPivot::Center);

	// Draw title
	widget->DrawString(&pos, &title, game->width / 2 - 50, 10 + text_size);

	// Draw x to exit
	widget->SetTextPivot(plasma::TextPivot::Right);
	if (BtnIsHovered(&mouse_pos, game->width - 130, game->width - 110, 10 + text_size))
	{
		widget->SetTextColor(&hover_color);
		widget->hover_state = ModWidget::HoverState::Exit;
	}
	widget->DrawString(&pos, &wstr_x, game->width - 110, 10 + text_size);

	// Draw horizontal line
	widget->SetTextPivot(plasma::TextPivot::Center);
	widget->SetTextColor(&text_color);
	std::wstring line;
	for (int i = 0; i < game->width / (text_size - 2); i++)
	{
		line.append(L"_");
	}
	widget->DrawString(&pos, &line, game->width / 2 - 50, 2 * (10 + text_size));

	// Draw vertical line
	line.clear();
	for (int i = 0; i < (game->height - 100) / text_size - 5; i++)
	{
		line.append(L"|\n");
	}
	widget->DrawString(&pos, &line, game->width / 2 - 50, 3 * (10 + text_size));

	// Draw mods
	

	int y_count = 0;
	int x_count = 0;
	int index = 0;

	for (DLL* dll : *widget->mods)
	{
		widget->SetTextPivot(plasma::TextPivot::Left);
		widget->SetTextColor(&text_color);
		if (!dll->enabled)
		{
			widget->SetTextColor(&disabled_color);
		}
		int y_pos = (4 + 2 * y_count) * (10 + text_size);
		std::wstring name = L"- " + std::wstring(dll->fileName.begin(), dll->fileName.end());
		widget->DrawString(&pos, &name, 50, y_pos);


		widget->SetTextPivot(plasma::TextPivot::Right);
		widget->SetTextColor(&text_color);

		if (BtnIsHovered(&mouse_pos, game->width / 2 - 50 - text_size * wstr_disable.size(), game->width / 2 - 50 - text_size, y_pos))
		{
			widget->SetTextColor(&hover_color);
			widget->hover_state = HoverState::Toggle;
			widget->selected = index;
		}
		if (!dll->enabled)
		{
			widget->DrawString(&pos, &wstr_enable, game->width/2 - 50 - text_size, y_pos);
		} 
		else
		{
			widget->DrawString(&pos, &wstr_disable, game->width / 2 - 50 - text_size, y_pos);
		}
			
		y_count++;
		index++;
	}

	ModWidget::StoreSave(widget->mods);
}

void mod::ModWidget::Init()
{
	void* NULLSUB = CWOffset(0xE8A20);
	void* RETZERO = CWOffset(0x368230);

	void* vtab[43] = {
	CWOffset(0x268B40),
	Draw,				// void Draw(plasma::Widget*)
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
}

void mod::ModWidget::LoadSave(std::vector<DLL*>* mods)
{
	std::ifstream in(file_name.c_str());
	std::string line;

	while (getline(in, line)) {
		auto pos = line.find(":");
		if (pos != std::string::npos)
		{
			std::string name(line.substr(0, pos));
			bool enabled = stoi(line.substr(pos + 1, line.size() - 1));
			for (DLL* dll : *mods)
			{
				if (!name.compare(dll->fileName))
				{
					dll->enabled = enabled;
				}
			}
		}
	}
}

void mod::ModWidget::StoreSave(std::vector<DLL*>* mods)
{
	std::ofstream out(file_name.c_str());
	for (DLL* dll : *mods)
	{
		out << dll->fileName << ":" << dll->enabled << "\n";
	}
	out.close();
}
