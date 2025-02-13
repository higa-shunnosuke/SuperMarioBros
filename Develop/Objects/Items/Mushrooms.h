#pragma once

#include "../GameObject.h"

class Mushrooms : public GameObject
{
public:
	float anim_time;
	bool spawn_anim;
	int spawn_count;
	Vector2D velocity;
	bool on_ground;

public:
	Mushrooms();
	~Mushrooms();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;

protected:
	virtual void AnimationControl(float delta_second);
};

