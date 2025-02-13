#pragma once

#include "../GameObject.h"

class FireFlower : public GameObject
{
public:
	std::vector<int> anim_img;		// アニメーション画像
	float anim_time;
	int anim_count;
	int spawn_count;

public:
	FireFlower();
	~FireFlower();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void AnimationControl(float delta_second);
};

