#pragma once

//2���� ��ǥ�� �ڽ��� �������ϰ� �浹 �� ó��.
class AActor
{
public:
	AActor();
	AActor(int NewX, int NewY, char NewShape, bool bNewCollision = false);
	virtual ~AActor();

	char Shape;
	int X;
	int Y;
	bool bCollision;

	virtual void Tick();
	virtual void Render();
};

