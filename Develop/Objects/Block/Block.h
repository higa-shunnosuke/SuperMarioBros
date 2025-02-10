#pragma once

#include "BlockBase.h"

class Block :public BlockBase
{
public:
	float anim_time;
	int anim_count;
	bool is_animation;
public:
	Block();
	~Block();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void AnimationControl(float delta_second);

};

