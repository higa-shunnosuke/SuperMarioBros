#pragma once

#include "../../Objects/Character/Player/Player.h"

class Camera
{
private:
	Player* player;
	Vector2D location;

public:
	Camera();
	~Camera();

public:
	void Initialize();
	void Update();
	Vector2D GetCameraPos();
	void SetPlayer(Player* player);
};

