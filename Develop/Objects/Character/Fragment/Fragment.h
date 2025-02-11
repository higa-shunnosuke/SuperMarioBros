#pragma once

#include "../Character.h"

class Fragment : public Character
{
public:
	int type;

public:
	Fragment();
	~Fragment();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;

	void SetType(int type);
};

