#include "Mushrooms.h"
#include "../GameObjectManager.h"

Mushrooms::Mushrooms() :
	anim_time(),
	spawn_anim(true),
	spawn_count(),
	velocity(),
	on_ground(true)
{

}

Mushrooms::~Mushrooms()
{

}

void Mushrooms::Initialize()
{
	// �摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Item/mushroom.png")[0];

	is_mobility = true;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eMushrooms;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(32.0f, 32.0f);
	z_layer = 1;
}

void Mushrooms::Update(float delta_second)
{
	if (spawn_anim == false)
	{
		if (on_ground == true)
		{
			velocity.y = 0.0f;
		}
		else
		{
			//�d�͉����x�̌v�Z
			velocity.y += D_GRAVITY / 1000;
		}

		//�����̎��s
		location.y += velocity.y;

		on_ground = false;

		location.x += velocity.x * delta_second;
	}

	// �ޗ��ɗ������玀��
	if (location.y >= 500.0f)
	{
		GameObjectManager* object = GameObjectManager::GetInstance();
		object->DestroyObject(this);
	}

	AnimationControl(delta_second);
}

void Mushrooms::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// �X�[�p�[�L�m�R�̕`��
	if (spawn_count > 1)
	{
		DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);
	}

#ifdef DEBUG
	// �����蔻��\��
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Mushrooms::Finalize()
{

}

void Mushrooms::OnHitCollision(GameObject* hit_object)
{
	// �����蔻������擾���āA��`������ʒu�����߂�
	Collision hc = hit_object->GetCollision();

	// ���������A�I�u�W�F�N�g���v���C���[��������
	if (hc.object_type == eObjectType::ePlayer)
	{
		GameObjectManager* object = GameObjectManager::GetInstance();
		object->DestroyObject(this);
	}

	if (spawn_anim == false)
	{
		// ���������A�I�u�W�F�N�g���ǂ�������
		if (hc.object_type == eObjectType::eBlock)
		{
			Vector2D diff;	// �߂荞��

			// �Q�_�Ԃ̋������v�Z
			Vector2D distance;
			distance = this->location - hit_object->GetLocation();

			// �Փ˖ʂ����߂�
			if (distance.x <= 0)
			{
				if (distance.y <= 0)
				{
					// �v���C���[�̉E�ӂƉ��ӁA�u���b�N�̍��ӂƏ�ӂ̂߂荞�݂��v�Z
					diff = (this->location + collision.box_size / 2)
						- (hit_object->GetLocation() - hc.box_size / 2);

					// �����߂�����
					if (diff.x <= diff.y)
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
	}
	
}

void Mushrooms::AnimationControl(float delta_second)
{
	anim_time += delta_second;

	if (anim_time >= 0.1f)
	{
		anim_time = 0.0f;
		
		if (spawn_count < 8)
		{
			location.y -= 4;
			spawn_count++;
		}
		else
		{
			if (spawn_anim == true)
			{
				spawn_anim = false;
				velocity.x = 100;
			}
		}
	}
}