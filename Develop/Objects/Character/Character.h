#pragma once

#include "../GameObject.h"
#include "../../Utility/ResourceManager.h"

// �J�����N���X�ւ̎Q��
class Camera;

#define D_GRAVITY (9.807f)		//�d�͉����x(m/ss)

class Character : public GameObject
{
protected:
	int image;
	float g_velocity;
	Vector2D velocity;
	int hit_point;
	bool on_ground;
	bool direction;
	bool is_death;					//����ł��邩�H

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
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObject* hit_object)
	{

	}
};