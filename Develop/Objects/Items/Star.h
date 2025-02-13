#pragma once

#include "../GameObject.h"

class Star : public GameObject
{
public:
	std::vector<int> anim_img;		// アニメーション画像
	float anim_time;
	int anim_count;
	bool spawn_anim;
	int spawn_count;
	Vector2D velocity;
	bool on_ground;

public:
	Star();
	~Star();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void AnimationControl(float delta_second);
};

