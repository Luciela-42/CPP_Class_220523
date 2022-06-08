#include "Player.h"
#include "Engine.h"
#include "World.h"
#include "Goal.h"
#include "SDL.h"

APlayer::APlayer()
	: AActor()
{
	R = 0;
	G = 0;
	B = 255;

	ColorKey = SDL_Color{ 255, 0, 255, 0 };

	LoadBMP("Data/player2.bmp");
}

APlayer::APlayer(int NewX, int NewY, char NewShape, bool bNewCollision, int NewSortOrder)
	: AActor(NewX, NewY, NewShape, bNewCollision, NewSortOrder)
{
	R = 0;
	G = 0;
	B = 255;

	ColorKey = SDL_Color{ 255, 0, 255, 0 };

	LoadBMP("Data/player2.bmp");
}

APlayer::~APlayer()
{
}

void APlayer::Tick()
{
	ElapsedTime += GEngine->GetWorldDeltaSeconds();
	if (ElapsedTime >= ProcessTime)
	{
		SpriteIndex++;
		SpriteIndex = SpriteIndex % 5;
		ElapsedTime = 0;
	}

	switch (GEngine->MyEvent.type)
	{
	case SDL_QUIT:
		GEngine->QuitGame();
		break;
	case SDL_KEYDOWN:
		switch (GEngine->MyEvent.key.keysym.sym)
		{
		case SDLK_w:
			Y = (PredictCollision(X, Y - 1) == false) ? Y - 1 : Y;
			SpriteDirection = 3;
			break;
		case SDLK_s:
			Y = (PredictCollision(X, Y + 1) == false) ? Y + 1 : Y;
			SpriteDirection = 0;
			break;
		case SDLK_a:
			X = (PredictCollision(X - 1, Y) == false) ? X - 1 : X;
			SpriteDirection = 1;
			break;
		case SDLK_d:
			X = (PredictCollision(X + 1, Y) == false) ? X + 1 : X;
			SpriteDirection = 2;
			break;
		}

	}

	if (IsGoal())
	{
		GEngine->QuitGame();
	}
}

void APlayer::Render()
{
	if (MyTexture == nullptr)
	{
		SDL_SetRenderDrawColor(GEngine->MyRenderer, R, G, B, A);
		SDL_RenderFillRect(GEngine->MyRenderer, new SDL_Rect{ X * Size, Y * Size, Size, Size });
	}
	else
	{
		int SpriteWidth = MySurface->w / 6;
		int SpriteHeight = MySurface->h / 8;

		SDL_Rect SourceRect{ SpriteIndex * SpriteWidth, SpriteDirection * SpriteHeight, SpriteWidth, SpriteHeight };
		//VRAM ±×·Á¶ó
		SDL_RenderCopy(GEngine->MyRenderer, MyTexture, &SourceRect, new SDL_Rect{ X * Size, Y * Size, Size, Size });
	}
}

bool APlayer::IsGoal()
{
	for (auto Actor : GEngine->GetWorld()->MyActors)
	{

		if (Actor->X == X && Actor->Y == Y)
		{
			AGoal* Goal = dynamic_cast<AGoal*>(Actor);
			if (Goal != nullptr)
			{
				return true;
			}
		}
	}

	return false;
}
