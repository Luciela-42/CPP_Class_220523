#pragma once
#include "Actor.h"

//2���� ��ǥ�� �ڽ��� �������ϰ� �浹 �� ó��.
//�Է��� ó���Ѵ�.
class APlayer : public AActor
{
public:
	APlayer();
	APlayer(int NewX, int NewY, char NewShape, bool bNewCollision = false, int NewSortOrder = 4);
	virtual ~APlayer();

	virtual void Tick() override;

	bool IsGoal();
};

