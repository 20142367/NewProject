#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {


	start = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, false);
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
		}
		m_bRunning = true;
		//	SDL_Surface* PlayerSurface = SDL_LoadBMP("assets/animate.bmp");
		SDL_Surface* PlayerSurface = IMG_Load("Assets/player.png");
		PlayerTexture = SDL_CreateTextureFromSurface(m_pRenderer, PlayerSurface);
		SDL_FreeSurface(PlayerSurface);

		SDL_Surface* MapSurface = IMG_Load("Assets/map.png");
		MapTexture = SDL_CreateTextureFromSurface(m_pRenderer, MapSurface);
		SDL_FreeSurface(MapSurface);

		SDL_Surface* PooSurface = IMG_Load("Assets/poo.png");
		PooTexture = SDL_CreateTextureFromSurface(m_pRenderer, PooSurface);
		SDL_FreeSurface(PooSurface);

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

		m_srcPlayer.w = 100;
		m_srcPlayer.h = 100;
		m_srcMap.w = 500;
		m_srcMap.h = 500;
		m_srcPoo.w = 50;
		m_srcPoo.h = 50;

		m_dstPlayer.x = 200;
		m_dstPlayer.y = 300;
		m_srcPlayer.x = 0;
		m_srcPlayer.y = 0;
		m_dstPlayer.w = m_srcPlayer.w;
		m_dstPlayer.h = m_srcPlayer.h;

		m_dstMap.x = 0;
		m_dstMap.y = 0;
		m_srcMap.x = 0;
		m_srcMap.y = 0;
		m_dstMap.w = m_srcMap.w;
		m_dstMap.h = m_srcMap.h;

		m_dstPoo.x = 0;
		m_dstPoo.y = 0;
		m_srcPoo.x = 0;
		m_srcPoo.y = 0;
		m_dstPoo.w = m_srcPoo.w;
		m_dstPoo.h = m_srcPoo.h;
	}
	else
	{
		return false;
	}
	return true;
}

void Game::render() {
	// clear the renderer to the draw color
	SDL_RenderClear(m_pRenderer);	// draw color로 render 지우기
	
	// 원본 사각형과 대상 사각형의 위치와 크기에 따라 화면에 다르게 나타남
	SDL_RenderCopy(m_pRenderer, MapTexture, &m_srcMap, &m_dstMap);
	SDL_RenderCopy(m_pRenderer, PlayerTexture, &m_srcPlayer, &m_dstPlayer);
	SDL_RenderCopy(m_pRenderer, PooTexture, &m_srcPoo, &m_dstPoo);

	SDL_RenderPresent(m_pRenderer);	// 화면 제시하기
}


void Game::update() {
	float delay = 0;
	float speed = 0;

	m_srcPlayer.y = 100 * int((SDL_GetTicks() / 100) % 2);


	// 오브젝트와 플레이어가 충돌 시 게임 종료
	if (m_dstPlayer.x < m_dstPoo.x + 50 && m_dstPlayer.x + 100 > m_dstPoo.x && m_dstPlayer.y < m_dstPoo.y + 50)
		m_bRunning = false;

	//	x값이 랜덤하게 오브젝트 생성
//		m_dstPoo.x = rand() % 400;

	// 오류 : 천천히 내려가지만, 오브젝트가 맨위가 아닌 중간부터 떨어짐
//	m_dstPoo.y += 1 * int((SDL_GetTicks() / 10));


	//	오브젝트가 점점 밑으로 내려가게끔 설정 -> 딜레이 필요
	if (SDL_GetTicks() / 5000)
		m_dstPoo.y += 1;

	//	오브젝트가 땅에 닿으면 사라지도록 설정
//	if (m_dstPoo.y > 400)	PooTexture == NULL;

//	Sleep(100);
}

void Game::clean() {
	cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::handleEvents() {

	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym) {

			case SDLK_RIGHT:	// 오른쪽 방향키를 누르면
				m_dstPlayer.x += 15;
				break;

			case SDLK_LEFT:		// 왼쪽 방향키를 누르면
				m_dstPlayer.x -= 15;
				break;

			case SDLK_ESCAPE:	// esc를 누르면 종료
				m_bRunning = false;
				break;
			}
		}

		/*
		if (event.type == SDL_MOUSEBUTTONDOWN) {	// 마우스 버튼을 클릭하면

			SDL_SetRenderDrawColor(m_pRenderer, 100, 200, 0, 255);
		}
		*/

		switch (event.type) {

		case SDL_QUIT:		// 프로그램 창을 끄면(?)
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}