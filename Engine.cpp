#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>

#include "SDL_mixer.h"

#include "Engine.h"
#include "World.h"
#include "Wall.h"
#include "Goal.h"
#include "Player.h"
#include "Floor.h"
#include "Monster.h"
#include "Sound.h"
#include "Text.h"

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

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) //�׷���ī��(HW) �ʱ�ȭ
	{
		SDL_Log("SDL_INIT_ERROR");
	}

	//������ â �����
	MyWindow = SDL_CreateWindow("Maze", 100, 100, 800, 600, SDL_WINDOW_VULKAN);
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_TARGETTEXTURE);

	//���� �ʱ�ȭ
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	//��Ʈ �ʱ�ȭ
	TTF_Init();
}

void Engine::Load(string MapFilename)
{
	// load
	ifstream MapFile(MapFilename);

	int Y = 0;
	int MaxX = 0;
	while (MapFile.peek() != EOF)
	{
		char Buffer[1024] = { 0, };
		MapFile.getline(Buffer, 1024);
		MaxX = strlen(Buffer);
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

	SDL_SetWindowSize(MyWindow, MaxX * 60, Y * 60);

	//�׸��� ������ ����
	sort(MyWorld->MyActors.begin(), MyWorld->MyActors.end(), AActor::compare);

	MapFile.close();

	MyWorld->SpawnActor(new ASound(100, 100, "data/bgm.mp3", -1));
	MyWorld->SpawnActor(new AText(100, 100, "�ȳ��ϼ���, World", SDL_Color{ 0, 0, 0 }, 40));
}

void Engine::Run()
{
	//Run
	MyWorld->BeginPlay();

	while (bRunning) // 1 Frame
	{
		DeltaSeconds = SDL_GetTicks64() - LastTick;
		Input();
		MyWorld->Tick();
		//�׷��� ī�尡 �� �� ���
		SDL_SetRenderDrawColor(MyRenderer, 0xff, 0x00, 0xff, 0xff);
		SDL_RenderClear(MyRenderer);

		MyWorld->Render(); //�׸� ���� ���

		LastTick = SDL_GetTicks64();

		//��ϵ� �� ����
		SDL_RenderPresent(MyRenderer);
	}
}

void Engine::Terminate()
{
	delete MyWorld;
	MyWorld = nullptr;

	TTF_Quit();

	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
	SDL_Quit();
}

void Engine::Input()
{
	//Engine::KeyCode = _getch();
	SDL_PollEvent(&MyEvent); //Input
}
