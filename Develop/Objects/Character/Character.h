#pragma once

#include "../GameObject.h"
#include "../../Utility/ResourceManager.h"

// カメラクラスへの参照
class Camera;

#define D_GRAVITY (9.807f)		//重力加速度(m/ss)

class Character : public GameObject
{
protected:
	int image;
	float g_velocity;
	Vector2D velocity;
	int hit_point;
	bool on_ground;
	bool direction;
	bool is_death;					//死んでいるか？

	float anim_count;

public:
	Character() :
		image(),
		g_velocity(0.0f),
		velocity(0.0f),
		hit_point(),
		on_ground(false),
		direction(false),
		is_death(),
		anim_count(0)
	{

	}

	virtual ~Character()
	{

	}

public:
	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object)
	{

	}
};