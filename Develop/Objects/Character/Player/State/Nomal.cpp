#include "Nomal.h"
#include "../Player.h"

///<summary>
///�R���X�g���N�^
///</summary>
///<param name="p">�v���C���[���</param>
Nomal::Nomal(class Player* p)
	:PlayerStateBase(p)
{

}

///<summary>
///�f�X�g���N�^
///</summary>
Nomal::~Nomal()
{

}

///<summary>
///����������
///</summary>
void Nomal::Initialize()
{
	// �摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);

	// �����蔻�菉����                                                                               
	box_size = (32.0f, 32.0f);
}

///<summary>
///�I��������
///</summary>
void Nomal::Finalize()
{

}

///<summary>
///�X�V����
///</summary>
void Nomal::Update()
{
	InputManager* input = InputManager::GetInstance();

	//�ړ���ԂɑJ��
	if (input->GetKeyState(KEY_INPUT_Z) == eInputState::Pressed)
	{
		player->SetNextState(ePlayerState::SUPER);
	}
}

///<summary>
///�`�揈��
///</summary>
void Nomal::Draw(const Vector2D camera_pos) const
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
ePlayerState Nomal::GetState() const
{
	return ePlayerState::NOMAL;
}

