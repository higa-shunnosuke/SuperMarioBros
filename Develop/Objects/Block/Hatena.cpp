#include "Hatena.h"

Hatena::Hatena() :
	anim_time(),
	anim_count(),
	is_animation(false)
{

}

Hatena::~Hatena()
{

}

void Hatena::Initialize()
{
	// �摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/hatena.png",4,4,1,32,32)[0];

	is_mobility = false;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.box_size = Vector2D(32.0f, 32.0f);

}

void Hatena::Update(float delta_second)
{
	AnimationControl(delta_second);

}

void Hatena::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// �n�e�i�u���b�N�̕`��
	DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// �����蔻��\��
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Hatena::Finalize()
{

}

void Hatena::OnHitCollision(GameObject* hit_object)
{
	// �����蔻������擾���āA��`������ʒu�����߂�
	Collision hc = hit_object->GetCollision();

	// ���������A�I�u�W�F�N�g���v���C���[��������
	if (hc.object_type == eObjectType::ePlayer)
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
				// �u���b�N�̉E�ӂƉ��ӁA�v���C���[�̍��ӂƏ�ӂ̂߂荞�݂��v�Z
				diff = (this->location + collision.box_size / 2)
					- (hit_object->GetLocation() - hc.box_size / 2);

				// �A�j���[�V����
				if (diff.x > diff.y)
				{
					// ���
					is_animation = true;
				}
			}
		}
		else
		{
			if (distance.y < 0)
			{
				// �u���b�N�̍��ӂƉ��ӁA�v���C���[�̉E�ӂƏ�ӂ̂߂荞�݂��v�Z
				diff = Vector2D((this->location.x - collision.box_size.x / 2),
					(this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + hc.box_size.x / 2),
						(hit_object->GetLocation().y - hc.box_size.y / 2));

				// �A�j���[�V����
				if (-diff.x > diff.y)
				{
					// ���
					is_animation = true;
				}
			}
		}
	}
}

void Hatena::AnimationControl(float delta_second)
{
	anim_time += delta_second;

	if (anim_time >= 0.01f)
	{
		if (is_animation == true)
		{
			if (anim_count < 7)
			{
				location.y -= 1;
				anim_count++;
			}
			else if (anim_count < 16)
			{
				location.y += 1;
				anim_count++;
			}
			else if (anim_count < 18)
			{
				location.y -= 1;
				anim_count++;
			}
			else
			{
				anim_count = 0;
				is_animation = false;
			}
		}
		anim_time = 0;
	}
}