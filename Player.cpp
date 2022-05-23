#include "Player.h"

APlayer::APlayer()
	: AActor()
{
}

APlayer::APlayer(int NewX, int NewY, char NewShape, bool bNewCollision)
	: AActor(NewX, NewY, NewShape, bNewCollision)
{
}

APlayer::~APlayer()
{
}

void APlayer::Tick()
{
}
