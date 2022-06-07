#pragma once
#include <string>
#include "SpriteType.h"

class World;

using namespace std;

class Engine
{
public:
	Engine();
	virtual ~Engine();


	void Initialize();
	void Load(string MapFilename);
	void Run();
	void Terminate();
	void Input();

	void QuitGame() { bRunning = false; }

	inline static int GetKeyCode() { return Engine::KeyCode; }

	inline static Engine* GetEngine() { return Instance; }

	inline World* GetWorld() const { return MyWorld; }

protected:
	World* MyWorld;

	static int KeyCode;

	static Engine* Instance;

	bool bRunning;
};
#define GEngine Engine::GetEngine()