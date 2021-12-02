#include "ModWidget.h"

void* VTABLE[43];

mod::ModWidget* mod::ModWidget::ctor(cube::Game* game, plasma::Node* node)
{
	// Construct basewidget
	std::wstring wstr_empty(L"");
	((cube::BaseWidget*)this)->ctor(game->plasma_engine, node, &wstr_empty);

	// Set fields
	this->game = game;
	this->hover_state = 0;

	// Set scalable font
	std::wstring fontName(L"resource1.dat");
	this->SetScalableFont(&fontName);
	this->Translate(100, 200, 1);

	// Manually set vtable
	size_t* vptr = (size_t*)this;
	*vptr = (size_t)VTABLE; //(size_t)CWOffset(0x46CED8);

	return this;
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

	FloatRGBA text_color(1.0f, 1.0f, 1.0f, 1.0f);
	FloatRGBA hover_color(0.2f, 1.0f, 1.0f, 1.0f);
	FloatRGBA disabled_color(1.0f, 1.0f, 1.0f, 0.2f);
	FloatRGBA border_color(0.0f, 0.0f, 0.0f, 1.0f);

	FloatVector2 mouse_pos;
	FloatVector2 pos(0, 0);

	std::wstring title(L"Do you want to run with mods?");
	std::wstring wstr_yes(L"Yes");
	std::wstring wstr_no(L"No");

	// Translate to center
	widget->node->Translate(widget->game->width / 2, widget->game->height / 2, -150, -175);

	// Get mouse
	mouse_pos = *widget->GetRelativeMousePosition(&mouse_pos);

	// Set hover to 0
	widget->hover_state = 0;

	// Text settings
	widget->SetTextSize(text_size);
	widget->SetTextColor(&text_color);
	widget->SetBorderSize(border_size);
	widget->SetBorderColor(&border_color);
	widget->SetTextPivot(plasma::TextPivot::Center);
	widget->DrawString(&pos, &title, widget->GetXSize() / 2 + 100, 150);

	// Draw yes option
	widget->SetTextColor(&text_color);
	if (BtnIsHovered(&mouse_pos, 0, widget->GetXSize() / 2 + 100, 200))
	{
		widget->SetTextColor(&hover_color);
		widget->hover_state = 1;
	}
	widget->DrawString(&pos, &wstr_yes, widget->GetXSize() / 2 + 50, 200);
	
	// Draw no option
	widget->SetTextColor(&text_color);
	if (BtnIsHovered(&mouse_pos, widget->GetXSize() / 2 + 100, widget->GetXSize() + 200, 200))
	{
		widget->SetTextColor(&hover_color);
		widget->hover_state = 2;
	}
	widget->DrawString(&pos, &wstr_no, widget->GetXSize() / 2 + 150, 200);
}

void mod::ModWidget::Init()
{
	void* NULLSUB = CWOffset(0xE8A20);
	void* RETZERO = CWOffset(0x368230);

	void* vtab[43] = {
	CWOffset(0x268B40),
	&Draw,				// void Draw(plasma::Widget*)
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
