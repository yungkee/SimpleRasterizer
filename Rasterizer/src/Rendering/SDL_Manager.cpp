#include <Rendering/SDL_Manager.h>

using namespace Rendering;

SDL_Manager::SDL_Manager() : m_window{ nullptr }, m_renderer{ nullptr }, m_activeBuffer(nullptr)
{
}


bool SDL_Manager::Init(int p_w, int p_h)
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER | SDL_INIT_EVENTS))
	{
		this->m_window = SDL_CreateWindow(
			"Rasterizer",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			p_w,
			p_h,
			SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);

		if (this->m_window)
		{
			this->m_renderer = SDL_CreateRenderer(this->m_window, -1, SDL_RENDERER_PRESENTVSYNC);

			if (this->m_renderer)
			{
				this->m_activeBuffer = new Texture(p_w, p_h);
				return true;
			}
			else
			{
				SDL_Log("SDL Failed to create renderer, SDL_Error: %s\n", SDL_GetError());
				this->Close();
				return false;
			}
		}
		else
		{
			SDL_Log("SDL Failed to create window, SDL_Error: %s\n", SDL_GetError());
			this->Close();
			return false;
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

Texture* SDL_Manager::GetBuffer() const
{
	return this->m_activeBuffer;
}

SDL_Manager::~SDL_Manager()
{
	if (this->m_window || this->m_renderer)
		this->Close();
}

void SDL_Manager::ClearBuffer(const Color& c)
{
	if (this->m_activeBuffer)
		this->m_activeBuffer->Clear(c);
}

void SDL_Manager::UpdateWindow()
{
	if (this->m_activeBuffer)
	{
		Color* pixels = this->m_activeBuffer->GetPixels();
		for (int i = 0; i < this->m_activeBuffer->Width() * this->m_activeBuffer->Height(); ++i)
		{
			SDL_SetRenderDrawColor(this->m_renderer, pixels[i].m_r, pixels[i].m_g, pixels[i].m_b, pixels[i].m_a);
			SDL_RenderDrawPoint(this->m_renderer, i % this->m_activeBuffer->Width(), i / this->m_activeBuffer->Width());

		}
		SDL_RenderPresent(this->m_renderer);
	}

}
