#pragma once
# include "Common.hpp"
# include "mainscene.hpp"
# include "pricesetting.hpp"
# include "keysetting.hpp"


void Main()
{
	Scene::SetBackground(ColorF{ 0.8,0.8, 0.8 });
	Window::SetFullscreen(true);
	Scene::SetResizeMode(ResizeMode::Keep);
	Scene::Resize(1920, 1080);

	App manager;

	manager.add<mainscene>(State::mainscene);
	manager.add<pricesetting>(State::pricesetting);
	manager.add<keysetting>(State::keysetting);


	while (System::Update())
	{
		ClearPrint();
		if (not manager.update())
		{
			break;
		}
	}
}
