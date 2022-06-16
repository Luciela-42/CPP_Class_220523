#include "Text.h"
#include "Engine.h"
#include <Windows.h>

AText::AText(int NewX, int NewY, string NewMessage, SDL_Color NewColor, int NewSize)
{
	X = NewX;
	Y = NewY;
	Message = NewMessage;
	Color = NewColor;
	Size = NewSize;
	SortOrder = 100;

	Font = TTF_OpenFont("C:/Windows/Fonts/DungGeunMo.ttf", Size);

	//RAM
	//MySurface = TTF_RenderText_Solid(Font, Message.c_str(), Color);
	
	wstring strUni(Message.length(), 0);
	MultiByteToWideChar(CP_ACP, 0, Message.c_str(), Message.length(), (LPWSTR)strUni.c_str(), Message.length() + 1);
	MySurface = TTF_RenderUNICODE_Solid(Font, (Uint16*)strUni.c_str(), Color);

	//VRAM
	MyTexture = SDL_CreateTextureFromSurface(GEngine->MyRenderer, MySurface);

	Width = MySurface->w;
	Height = MySurface->h;

	//SDL_QueryTexture(MyTexture, nullptr, nullptr, &Width, &Height);
	Destination = { X, Y, Width, Height };
}

AText::~AText()
{
	TTF_CloseFont(Font);
}

void AText::Render()
{
	SDL_RenderCopy(GEngine->MyRenderer, MyTexture, nullptr, &Destination);
}
