#include "Floor.h"

AFloor::AFloor()
	: AActor()
{
}

AFloor::AFloor(int NewX, int NewY, char NewShape, bool bNewCollision)
	: AActor(NewX, NewY, NewShape, bNewCollision)
{
}

AFloor::~AFloor()
{
}
