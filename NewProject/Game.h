#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

class Game
{

public:

	Game() {}
	~Game() {}
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running() { return m_bRunning; }

private:

	SDL_Window * m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_RendererFlip* m_pRendererFlip;

	SDL_Texture* PlayerTexture;	// the new SDL_Texture variable
	SDL_Texture* MapTexture;
	SDL_Texture* PooTexture;

	SDL_Rect m_srcPlayer;	// 캐릭터 사각형
	SDL_Rect m_dstPlayer;	// 대상 사각형
	SDL_Rect m_srcMap;	// 맵 사각형
	SDL_Rect m_dstMap;
	SDL_Rect m_srcPoo;
	SDL_Rect m_dstPoo;

	bool m_bRunning;
	bool start;
};