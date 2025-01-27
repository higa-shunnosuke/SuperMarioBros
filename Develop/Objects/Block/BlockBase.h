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

private:
	void SetBlockData();
};