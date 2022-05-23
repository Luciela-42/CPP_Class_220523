#pragma once
#include "World.h"
#include <string>

using namespace std;

class Engine
{
public:
	Engine();
	virtual ~Engine();

	World* MyWorld;
	bool bRunning;

	void Initialize();
	void Load(string MapFilename);
	void Run();
	void Terminate();
};

