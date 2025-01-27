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

	// �v���C���[�̕`��
	if (camera_pos.x == 6400)
	{
		float diff = location.x - camera_pos.x;
		DrawRotaGraph(D_WIN_MAX_X / 2 + diff, location.y, 1.0, 0.0, animation[0], TRUE);

	}
	else
	{
		if (camera_pos.x <= location.x)
		{
			DrawRotaGraph(D_WIN_MAX_X / 2, location.y, 1.0, 0.0, animation[0], TRUE);
		}
		else
		{
			float diff = camera_pos.x - location.x;
			DrawRotaGraph((D_WIN_MAX_X / 2) - diff, location.y, 1.0, 0.0, animation[0], TRUE);
		}
	}
}

///<summary>
///���݂̃X�e�[�g�����擾����
///</summary>
ePlayerState Nomal::GetState() const
{
	return ePlayerState::FIRE;
}

