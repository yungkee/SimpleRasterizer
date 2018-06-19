#include <Rendering/SDL_Manager.h>

using namespace Rendering;

SDL_Manager::SDL_Manager() : m_window{nullptr}, m_renderer{nullptr}, m_activeBuffer(nullptr)
{
}


bool SDL_Manager::Init(const int width, const int height)
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS))
	{
		this->m_window = SDL_CreateWindow(
			"Rasterizer",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_RESIZABLE);

		if (this->m_window)
		{
			this->m_renderer = SDL_CreateRenderer(this->m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		}
		else
		{

		}
	}
	else
	{
		SDL_Log("SDL Failed to initialize, SDL_Error: %s\n", SDL_GetError());
		return false;
	}
}

void SDL_Manager::Close()
{
	if (this->m_renderer)
	{
		SDL_DestroyRenderer(this->m_renderer);
		this->m_renderer = nullptr;
	}

	if (this->m_window)
	{
		SDL_DestroyWindow(this->m_window);
		this->m_window = nullptr;
	}	
	
	if (this->m_activeBuffer)
	{
		delete m_activeBuffer;
		this->m_activeBuffer = nullptr;
	}

	SDL_Quit();
}

SDL_Manager::~SDL_Manager()
{
	if (this->m_window || this->m_renderer)
		this->Close();
}


