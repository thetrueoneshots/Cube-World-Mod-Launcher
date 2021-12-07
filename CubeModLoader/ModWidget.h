#pragma once

#include "CWSDK/cwsdk.h"
#include "DLL.h"

namespace mod {
	class ModWidget : public cube::BaseWidget
	{
	public:
		enum HoverState
		{
			None = 0,
			Exit = 1,
			Next = 2,
			Previous = 3,
			Toggle = 4
		};
		cube::Game* game;
		int hover_state;
		int selected;
		plasma::Node* background;
		std::vector<DLL*>* mods;
		void* artificial_vtable[43];


		ModWidget* ctor(cube::Game* game, plasma::Node* node, plasma::Node* background, std::vector<DLL*>* mods);

		void MouseUp(cube::MouseButton mouse_button);

		static void Draw(ModWidget* widget);
		static void Init();
		static void LoadSave(std::vector<DLL*>* mods);
		static void StoreSave(std::vector<DLL*>* mods);
	};
}