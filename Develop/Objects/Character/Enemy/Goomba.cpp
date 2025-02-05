#include "Goomba.h"

Goomba::Goomba():
	camera()
{

}

Goomba::~Goomba()
{

}

void Goomba::Initialize()
{
	// �摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	animation1 = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	g_velocity = 0.0f;
	velocity = Vector2D(-200.0f, 0.0f);
	on_ground = true;
	is_mobility = true;
	z_layer = 2;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(25.0f, 25.0f);

	image = animation1[0];
	anim_count = 0.0f;
}

void Goomba::Update(float delta_second)
{

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

void Goomba::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// �N���{�[�̕`��(�摜�߂荞�ݖh�~�̂���y���W�̂�-3.0f�̕␳�l�ǉ�)
	DrawRotaGraph(position.x, position.y-3, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// �����蔻��\��
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0xff0000, FALSE);
#endif
}

void Goomba::Finalize()
{

}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Goomba::OnHitCollision(GameObject* hit_object)
{
	// �����蔻������擾���āA��`������ʒu�����߂�
	Collision hc = hit_object->GetCollision();

	// �Q�_�Ԃ̋������v�Z
	Vector2D distance;
	distance = this->location - hit_object->GetLocation();

	// ���������A�I�u�W�F�N�g���ǂ�������
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
					velocity.x *= -1;
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

	// �v���C���[�ɓ��������Ƃ��̏���
	if (hc.object_type==eObjectType::ePlayer)
	{
		// �v���C���[���ォ�瓖�������̂Ȃ�
		if (distance.y >= collision.box_size.y/2.0f)
		{
			velocity = 0;
			image = animation1[2];
		}
	}
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Goomba::Movement(float delta_second)
{
	location.x += velocity.x * delta_second;
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Goomba::AnimationControl(float delta_second)
{
	anim_count += delta_second;

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

/// <summary>
/// �J�����̏����擾
/// </summary>
void Goomba::SetCamera(Camera* camera)
{
	this->camera = camera;
}