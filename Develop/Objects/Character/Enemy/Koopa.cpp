#include "Koopa.h"

Koopa::Koopa() :
	camera(),
	is_shell(false),
	is_hit(false)
{

}

Koopa::~Koopa()
{

}

void Koopa::Initialize()
{
	// �摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	animation1 = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	animation2 = rm->GetImages("Resource/Images/Enemy/nokonoko_revival.png", 2, 2, 1, 32, 32);

	g_velocity = 0.0f;
	velocity = Vector2D(-200.0f,0.0f);
	on_ground = true;
	is_mobility = true;
	z_layer = 2;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(32.0f, 39.0f);

	image = animation1[0];
}

void Koopa::Update(float delta_second)
{
	is_hit = false;

	if (on_ground == true)
	{
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}
	else
	{
		//�d�͉����x�̌v�Z
		g_velocity += D_GRAVITY / 9807;
		velocity.y += g_velocity;
	}

	//�����̎��s
	location.y += velocity.y;

	on_ground = false;

	if (location.x < camera->GetCameraPos().x + D_WIN_MAX_X / 2)
	{
		Movement(delta_second);

		if (location.x < camera->GetCameraPos().x - D_WIN_MAX_X / 2)
		{
			is_death = true;
		}
	}

	AnimationControl(delta_second);
}

void Koopa::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// �m�R�m�R���b����ԂȂ�
	if (image == animation2[0] || image == animation2[1])
	{
		DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);
	}
	// �m�R�m�R�����s��ԂȂ�
	else
	{
		DrawRotaGraph(position.x, position.y - 12.0f, 1.0, 0.0, image, TRUE);
	}

#ifdef DEBUG
	// �����蔻��\��
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0xff0000, FALSE);
#endif
}

void Koopa::Finalize()
{

}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Koopa::OnHitCollision(GameObject* hit_object)
{
	// �����蔻������擾���āA��`������ʒu�����߂�
	Collision hc = hit_object->GetCollision();

	// �Q�_�Ԃ̋������v�Z
	Vector2D distance;
	distance = this->location - hit_object->GetLocation();

	// ���������I�u�W�F�N�g���ǂ�������
	if (hc.object_type == eObjectType::eBlock)
	{
		Vector2D diff;	// �߂荞��

		// �Փ˖ʂ����߂�
		if (distance.x <= 0)
		{
			if (distance.y <= 0)
			{
				// �v���C���[�̉E�ӂƉ��ӁA�u���b�N�̍��ӂƏ�ӂ̂߂荞�݂��v�Z
				diff = (this->location + collision.box_size / 2)
					- (hit_object->GetLocation() - hc.box_size / 2);

				// �����߂�����
				if (diff.x < diff.y)
				{
					// ����
					velocity.x *= -1;
				}
				else
				{
					// ���
					location.y -= diff.y;
					on_ground = true;
				}
			}
			else
			{
				// �v���C���[�̉E�ӂƏ�ӁA�u���b�N�̍��ӂƉ��ӂ̂߂荞�݂��v�Z
				diff = Vector2D((this->location.x + collision.box_size.x / 2),
					(this->location.y - collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x - hc.box_size.x / 2),
						(hit_object->GetLocation().y + hc.box_size.y / 2));

				// �����߂�����
				if (diff.x < -diff.y)
				{
					// ����
					//velocity.x *= -1;
				}
				else
				{
					// ����
					location.y -= diff.y;
					velocity.y = 0;
				}
			}
		}
		else
		{
			if (distance.y >= 0)
			{
				// �v���C���[�̍��ӂƏ�ӁA�u���b�N�̉E�ӂƉ��ӂ̂߂荞�݂��v�Z
				diff = (this->location - collision.box_size / 2)
					- (hit_object->GetLocation() + hc.box_size / 2);

				// �����߂�����
				if (-diff.x < -diff.y || distance.y == 0)
				{
					// �E��
					velocity.x *= -1;
				}
				else
				{
					// ����
					location.y -= diff.y;
					velocity.y = 0;
				}
			}
			else
			{
				// �v���C���[�̍��ӂƉ��ӁA�u���b�N�̉E�ӂƏ�ӂ̂߂荞�݂��v�Z
				diff = Vector2D((this->location.x - collision.box_size.x / 2),
					(this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + hc.box_size.x / 2),
						(hit_object->GetLocation().y - hc.box_size.y / 2));

				// �����߂�����
				if (-diff.x < diff.y)
				{
					// �E��
					velocity.x *= -1;
				}
				else
				{
					// ���
					location.y -= diff.y;
					on_ground = true;
				}
			}
		}
	}

	// ���������I�u�W�F�N�g���v���C���[�Ȃ�
	if (hc.object_type == eObjectType::ePlayer)
	{
		if (is_hit == false)
		{
			// �m�R�m�R���b����Ԃ��ǂ���
			if (is_shell == true)
			{
				// �v���C���[�̈ʒu���m�R�m�R���E
				if (location.x < hit_object->GetLocation().x)
				{
					this->velocity.x = -500.0f;
				}
				// �v���C���[�̈ʒu���m�R�m�R��荶
				else if (location.x >= hit_object->GetLocation().x)
				{
					this->velocity.x = 500.0f;
				}
			}
			else if(is_shell==false)
			{
				// �v���C���[���ォ�瓖�������̂Ȃ�
				if (distance.y >= collision.box_size.y / 2.0f)
				{
					velocity = 0;
					image = animation2[0];
					is_shell = true;
					collision.box_size = Vector2D(32.0f, 32.0f);
				}
			}
			is_hit = true;
		}
	}

	// �G�l�~�[�ɓ��������Ƃ�
	if (hc.object_type == eObjectType::eEnemy)
	{
		if (is_hit == false)
		{
			velocity.x = -velocity.x;
			is_hit = true;
		}
	}
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Koopa::Movement(float delta_second)
{
	location.x += velocity.x * delta_second;
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Koopa::AnimationControl(float delta_second)
{
	anim_count += delta_second;

	// �b����Ԃ̃A�j���[�V����
	if (is_shell == true)
	{
		if (velocity.x == 0.0f)
		{
			if (anim_count >= 0.05f)
			{
				if (image == animation2[0])
				{
					image = animation2[1];
				}
				else if (image == animation2[1])
				{
					image = animation2[0];
				}
				anim_count = 0;
			}
		}
	}
	// ���s��Ԃ̃A�j���[�V����
	else
	{
		if (anim_count >= 0.1f)
		{
			if (image == animation1[0])
			{
				image = animation1[1];
			}
			else if (image == animation1[1])
			{
				image = animation1[0];
			}
			anim_count = 0;
		}
	}
}

/// <summary>
/// �J�����̏����擾
/// </summary>
void Koopa::SetCamera(Camera* camera)
{
	this->camera = camera;
}