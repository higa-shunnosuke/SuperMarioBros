#pragma once

#include "../GameObject.h"
#include "../../Utility/ResourceManager.h"

class BlockBase :public GameObject
{
public:
	int image;
	bool is_collapse;

public:
	BlockBase();
	~BlockBase();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;
	bool GetIsCollapse();

private:
	void SetBlockData();
};