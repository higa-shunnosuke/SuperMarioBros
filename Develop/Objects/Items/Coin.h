#pragma once

#include "../GameObject.h"

class Coin : public GameObject
{
public:
	std::vector<int> anim_img1;		// �A�j���[�V�����摜
	std::vector<int> anim_img2;		// �A�j���[�V�����摜
	float anim_time;
	int anim_count;
	bool is_item;
	int count;

public:
	Coin();	//�����ʒu 0, ���x 1
	~Coin();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;
	void SetType(bool is_item);

private:
	void AnimationControl(float delta_second);

};

