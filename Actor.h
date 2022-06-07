#pragma once
#include "SpriteType.h"

//2���� ��ǥ�� �ڽ��� �������ϰ� �浹�ϰ� ó���Ѵ�.
class AActor
{
public:
	AActor();
	AActor(int NewX, int NewY, char NewShape, bool bNewCollision = false, int NewSortOrder = 1	);
	virtual ~AActor();

	//ESpriteType Type;
	char Shape;
	int X;
	int Y;
	bool bCollision;
	int SortOrder;

	virtual void Tick();
	virtual void Render();

	static bool compare(AActor* First, AActor* Second)
	{
		return First->SortOrder < Second->SortOrder;
	}
};
