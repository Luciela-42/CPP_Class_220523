#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>

#include "Engine.h"
#include "World.h"
#include "Wall.h"
#include "Goal.h"
#include "Player.h"
#include "Floor.h"
#include "Monster.h"

int Engine::KeyCode = 0;

Engine* Engine::Instance = nullptr;

Engine::Engine()
{
	Instance = this;
	Initialize();
}

Engine::~Engine()
{
	Terminate();
}

void Engine::Initialize()
{
	bRunning = true;
	MyWorld = new World();

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) //그래픽카드(HW) 초기화
	{
		SDL_Log("SDL_INIT_ERROR");
	}

	//윈도우 창 만들기
	MyWindow = SDL_CreateWindow("Maze", 100, 100, 800, 600, SDL_WINDOW_VULKAN);
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_TARGETTEXTURE);
}

void Engine::Load(string MapFilename)
{
	// load
	ifstream MapFile(MapFilename);

	int Y = 0;
	while (MapFile.peek() != EOF)
	{
		char Buffer[1024] = { 0, };
		MapFile.getline(Buffer, 1024);

		for (size_t X = 0; X < strlen(Buffer); ++X)
		{
			char Cursor = Buffer[X];
			switch (Cursor)
			{
			case '#':
				MyWorld->SpawnActor(new AWall((int)X, Y, '#', true));
				break;
			case 'P':
				MyWorld->SpawnActor(new APlayer((int)X, Y, 'P', false));
				break;
			case 'G':
				MyWorld->SpawnActor(new AGoal((int)X, Y, 'G', false));
				break;
			case 'M':
				MyWorld->SpawnActor(new AMonster((int)X, Y, 'M', false));
				break;
			}
			

			MyWorld->SpawnActor(new AFloor((int)X, Y, ' ', false));
		}


		Y++;
	}

	//그리는 순서를 변경
	sort(MyWorld->MyActors.begin(), MyWorld->MyActors.end(), AActor::compare);

	MapFile.close();
}

void Engine::Run()
{
	while (bRunning) // 1 Frame
	{
		DeltaSeconds = SDL_GetTicks64() - LastTick;
		Input();
		MyWorld->Tick();
		//그래픽 카드가 할 일 등록
		SDL_SetRenderDrawColor(MyRenderer, 0xff, 0x00, 0xff, 0xff);
		SDL_RenderClear(MyRenderer);

		MyWorld->Render(); //그릴 액터 등록

		LastTick = SDL_GetTicks64();

		//등록된 일 시작
		SDL_RenderPresent(MyRenderer);
	}
}

void Engine::Terminate()
{
	delete MyWorld;
	MyWorld = nullptr;

	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
	SDL_Quit();
}

void Engine::Input()
{
	//Engine::KeyCode = _getch();
	SDL_PollEvent(&MyEvent); //Input
}
