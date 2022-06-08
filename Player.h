#pragma once
#include "Actor.h"

//2차원 좌표에 자신을 렌더링하고 충돌 및 처리.
//입력을 처리한다.
class APlayer : public AActor
{
public:
	APlayer();
	APlayer(int NewX, int NewY, char NewShape, bool bNewCollision = false, int NewSortOrder = 4);
	virtual ~APlayer();

	virtual void Tick() override;
	virtual void Render() override;

	bool IsGoal();

	Uint64 ElapsedTime = 0;
	Uint64 ProcessTime = 300;

	int SpriteIndex = 0;
	int SpriteDirection = 0;
};




