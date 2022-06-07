#include "Engine.h"
#include "SDL.h"

#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2.lib")

using namespace std;

//int main()
//{
//	//Engine* MyEngine = new Engine();
//	//MyEngine->Load("Level01.map");
//
//	//MyEngine->Run();
//	//
//	//delete MyEngine;
//	//MyEngine = nullptr;
//
//	return 0;
//}

int SDL_main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO)) //�׷���ī��(HW) �ʱ�ȭ
	{
		SDL_Log("SDL_INIT_ERROR");
		return -1;
	}

	//������ â �����
	SDL_Window* MyWindow = SDL_CreateWindow("Maze", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
	SDL_Renderer* MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_TARGETTEXTURE);

	bool bRunning = true;
	SDL_Event MyEvent;
	int X = 0;
	while (bRunning)
	{
		SDL_PollEvent(&MyEvent);

		switch (MyEvent.type)
		{
		case SDL_QUIT:
			bRunning = false;
			break;
		case SDL_KEYDOWN:
			SDL_Log("Pressed Key Down");
			break;
		}

		//�׷��� ī�尡 �� �� ���
		SDL_SetRenderDrawColor(MyRenderer, 0xff, 0x00, 0xff, 0xff);
		SDL_RenderClear(MyRenderer);

		//Actor���� �׸���
		SDL_SetRenderDrawColor(MyRenderer, 0x00, 0x00, 0x00, 0xff);
		if (X > 800)
		{
			X = 0;
		}
		else
		{
			X++;
		}
		SDL_RenderFillRect(MyRenderer, new SDL_Rect{ X++, 0, 100, 100 });

		//��ϵ� �� ����
		SDL_RenderPresent(MyRenderer);
	}

	SDL_DestroyRenderer(MyRenderer);

	SDL_DestroyWindow(MyWindow);

	SDL_Quit();

	return 0;
}