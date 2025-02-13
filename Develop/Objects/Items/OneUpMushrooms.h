#pragma once

#include "Mushrooms.h"

class OneUpMushrooms : public Mushrooms
{
public:

public:
	OneUpMushrooms();
	~OneUpMushrooms();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	virtual void AnimationControl(float delta_second) override;
};

