#include "Player.h"
#include "Factory/PlayerStateFactory.h"
#include "../../../Utility/Input/InputEventManager.h"
#include "../../../Utility/Camera/Camera.h"

#define D_PLAYER_SPEED 400.0f

Player::Player() :
	is_run(false),
	is_star(false),
	state(nullptr),
	next_state(ePlayerState::NONE),
	friction(0.0f),
	camera(nullptr)
{

}

Player::~Player()
{
	
}

void Player::Initialize()
{
	state = PlayerStateFactory::Get((*this), ePlayerState::NOMAL);
	next_state = ePlayerState::NONE;
	g_velocity = 0.0f;
	velocity = Vector2D(0.0f);
	on_ground = true;
	is_mobility = true;
	z_layer = 3;

	//���̓C�x���g�̓o�^
	InputEventManager* input_event = InputEventManager::GetInstance();
	input_event->ActionKeyBind(KEY_INPUT_W, eInputState::Pressed, this, &Player::Jump);

	input_event->ActionKeyBind(KEY_INPUT_A, -1, this, &Player::Movement);
	input_event->ActionKeyBind(KEY_INPUT_D, 1, this, &Player::Movement);

	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eItem);
}

void Player::Update(float delta_second)
{
	//�����蔻��̐ݒ�
	collision.box_size = state->GetPlayerSize();

	//state�̕ύX����
	if (next_state != ePlayerState::NONE)
	{
		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

	//��ԕʂ̍X�V�������s��
	state->Update();

	if (on_ground == true)
	{
		if (velocity.y > 0)
		{
			g_velocity = 0.0f;
			velocity.y = 0.0f;
		}
	}
	else
	{
		//�d�͉����x�̌v�Z
		if (g_velocity)
		{
			g_velocity += D_GRAVITY / 1500;				//(9807),
		}
		else
		{
			g_velocity += D_GRAVITY / 1600;				//(9807),
		}
		g_velocity += D_GRAVITY / 800;				//(9807),
		velocity.y += g_velocity;
	}

	//�ړ��̎��s
	location += velocity * D_PLAYER_SPEED * delta_second;

	on_ground = false;
	velocity.x = 0.0f;

	// ��ʊO�ɂ����Ȃ��悤�ɂ���
	float left;
	left = camera->GetCameraPos().x - D_WIN_MAX_X / 2 + collision.box_size.x / 2;
	if (left > location.x)
	{
		location.x = left;
	}

	// ��ʊO�ɗ�����Ǝ���
	if (D_WIN_MAX_Y < location.y)
	{
		is_death = true;
		location.y = D_WIN_MAX_Y;
		on_ground = true;
	}
}

void Player::Draw(const Vector2D camera_pos) const
{
	//��ԕʂ̕`�揈�����s��
	state->Draw(camera_pos);

#ifdef DEBUG
	// ���W�\��
	DrawFormatString(10, 90, 0xffffff, "X:%f", location.x);
	DrawFormatString(10, 120, 0xffffff, "Y:%f", location.y);
	DrawFormatString(250, 90, 0xffffff, "VX:%f", velocity.x);
	DrawFormatString(250, 120, 0xffffff, "VY:%f", velocity.y);
	DrawFormatString(490, 90, 0xffffff, ":%d", on_ground);

	// �����蔻��\��
	if (camera_pos.x <= location.x)
	{
		DrawBox(D_WIN_MAX_X / 2 - collision.box_size.x / 2, location.y - collision.box_size.y / 2,
				D_WIN_MAX_X / 2 + collision.box_size.x / 2, location.y + collision.box_size.y / 2, 0xff0000, FALSE);
	}
	else
	{
		float diff = camera_pos.x - location.x;
		DrawBox((D_WIN_MAX_X / 2) - diff - collision.box_size.x / 2, location.y - collision.box_size.y / 2,
				(D_WIN_MAX_X / 2) - diff + collision.box_size.x / 2, location.y + collision.box_size.y / 2, 0xff0000, FALSE);
	}
#endif

}

void Player::Finalize()
{
	PlayerStateFactory::Finalize();
}

/// <summary>
/// �����蔻��ʒm����
/// </summary>
/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
void Player::OnHitCollision(GameObject* hit_object)
{
	// �����蔻������擾���āA��`������ʒu�����߂�
	Collision hc = hit_object->GetCollision();

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
					location.x -= diff.x;
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
					location.x -= diff.x;
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
					location.x -= diff.x;
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
					location.x -= diff.x;
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

///<summary>
///����State��ݒ�
/// </summary>
/// <param name="init_location>����State</param>
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::Movement(float param)
{
	velocity.x += param;
}

/// <summary>
/// �W�����v����
/// </summary>
void Player::Jump()
{
	if (on_ground == true)
	{
		velocity.y = -3.5f;
	}

	on_ground = false;
}

/// <summary>
/// ���Ⴊ�ݏ���
/// </summary>
void Player::Squt()
{

}

/// <summary>
/// ���鏈��
/// </summary>
void Player::Run()
{
	InputManager* input = InputManager::GetInstance();

	if (input->GetKeyState(KEY_INPUT_LSHIFT) == eInputState::Hold)
	{
		
	}
}

/// <summary>
/// �A�j���[�V��������
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
void Player::AnimationControl(float delta_second)
{

}

/// <summary>
/// �v���C���[���X�^�[��Ԃ��m�F����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
bool Player::GetIsStar()
{
	return is_star;
}

/// <summary>
/// �v���C���[������ł��邩�m�F����
/// </summary>
/// <returns>�v���C���[�̏��</returns>
bool Player::GetIsDeath()
{
	return is_death;
}

/// <summary>
/// �J�����̏����擾
/// </summary>
void Player::SetCamera(Camera* camera)
{
	this->camera = camera;
}