#include "Fire.h"
#include "../Player.h"

///<summary>
///�R���X�g���N�^
///</summary>
///<param name="p">�v���C���[���</param>
Fire::Fire(class Player* p)
	:PlayerStateBase(p)
{

}

///<summary>
///�f�X�g���N�^
///</summary>
Fire::~Fire()
{

}

///<summary>
///����������
///</summary>
void Fire::Initialize()
{
	// �摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/Mario/faiyamario.png", 9, 9, 1, 32, 64);

	//// ���W�̏�����
	//Vector2D location = player->GetLocation();
	//location.y -= 16.0f;

	//player->SetLocation(location);

	// �����蔻�菉����
	box_size = Vector2D(32.0f, 64.0f);
}

///<summary>
///�I��������
///</summary>
void Fire::Finalize()
{
	
}

///<summary>
///�X�V����
///</summary>
void Fire::Update()
{
	InputManager* input = InputManager::GetInstance();
	//�ړ���ԂɑJ��
	if (input->GetKeyState(KEY_INPUT_Z) == eInputState::Pressed)
	{
		player->SetNextState(ePlayerState::NOMAL);
	}
}

///<summary>
///�`�揈��
///</summary>
void Fire::Draw(const Vector2D camera_pos) const
{
	// �v���C���[�̍��W���擾
	Vector2D location = player->GetLocation();
	float diff_x = location.x - camera_pos.x + D_WIN_MAX_Y / 2 + 80;
	float diff_y = camera_pos.y + location.y - D_WIN_MAX_Y / 2;

	// �v���C���[�̕`��
	if (player->GetIsUg() == true)
	{
		DrawRotaGraph(diff_x, diff_y, 1.0, 0.0, animation[0], TRUE);
	}
	else
	{
		if (camera_pos.x == 6400)
		{
			DrawRotaGraph(diff_x, diff_y, 1.0, 0.0, animation[0], TRUE);
		}
		else
		{
			if (diff_x > D_WIN_MAX_X / 2)
			{
				DrawRotaGraph(D_WIN_MAX_X / 2, diff_y, 1.0, 0.0, animation[0], TRUE);
			}
			else
			{
				DrawRotaGraph(diff_x, diff_y, 1.0, 0.0, animation[0], TRUE);
			}
		}
	}
}

///<summary>
///���݂̃X�e�[�g�����擾����
///</summary>
ePlayerState Fire::GetState() const
{
	return ePlayerState::FIRE;
}

