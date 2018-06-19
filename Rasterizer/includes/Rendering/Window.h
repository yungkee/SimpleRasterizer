#pragma once
#include <Rendering/SDL_Manager.h>
#include <SceneObjects/Scene.h>
#include <Rendering/Rasterizer.h>

using namespace SceneObjects;

namespace Rendering
{
	class Window
	{
	private:
		SDL_Manager m_graphics;

	public:
		Window();
		~Window();
	
	};
}
