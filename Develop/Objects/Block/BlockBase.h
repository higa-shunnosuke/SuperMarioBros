#pragma once

#include "../GameObject.h"
#include "../../Utility/ResourceManager.h"

class BlockBase :public GameObject
{
public:
	int image;

public:
	BlockBase();
	~BlockBase();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void SetBlockData();
};