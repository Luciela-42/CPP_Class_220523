#include "Floor.h"


AFloor::AFloor()
{
	R = 0;
	G = 255; 
	B = 0;

	LoadBMP("Data/floor.bmp");

}

AFloor::AFloor(int NewX, int NewY, char NewShape, bool bNewCollision, int NewSortOrder)
	:AActor(NewX, NewY, NewShape, bNewCollision, NewSortOrder)
{
	R = 0;
	G = 255;
	B = 0;

	LoadBMP("Data/floor.bmp");
}

AFloor::~AFloor()
{
}