#pragma once
#include <string>
#include "SpriteType.h"
#include "SDL.h"

using namespace std;

//2���� ��ǥ�� �ڽ��� �������ϰ� �浹�ϰ� ó���Ѵ�.
class AActor
{
public:
	AActor();
	AActor(int NewX, int NewY, char NewShape, bool bNewCollision = false, int NewSortOrder = 1);
	virtual ~AActor();

	//ESpriteType Type;
	char Shape;
	int X;
	int Y;
	bool bCollision;
	int SortOrder;

	int R = 0;
	int G = 0;
	int B = 0;
	int A = 255;

	SDL_Color ColorKey;

	void LoadBMP(string Filename);

	SDL_Surface* MySurface = nullptr;
	SDL_Texture* MyTexture = nullptr;

	int Size = 60;

	virtual void Tick();
	virtual void Render();

	static bool compare(AActor* First, AActor* Second)
	{
		return First->SortOrder < Second->SortOrder;
	}

	bool PredictCollision(int PredictX, int PredictY);


};
