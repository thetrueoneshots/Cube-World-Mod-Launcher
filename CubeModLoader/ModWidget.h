#pragma once

#include "CWSDK/cwsdk.h"

namespace mod {
	class ModWidget : public cube::BaseWidget
	{
	public:
		cube::Game* game;
		int hover_state;

		ModWidget* ctor(cube::Game* game, plasma::Node* node);
		static void Draw(ModWidget* widget);
		static void Init();
	};
}