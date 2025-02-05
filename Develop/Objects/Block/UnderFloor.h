#pragma once

#include "BlockBase.h"

class UnderFloor :public BlockBase
{
public:

public:
	UnderFloor();
	~UnderFloor();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
};

