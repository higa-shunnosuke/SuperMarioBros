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

	// �v���C���[�̕`��
	if (camera_pos.x == 6400)
	{
		float diff = location.x - camera_pos.x;
		DrawRotaGraph(D_WIN_MAX_X / 2 + diff, location.y, 1.0, 0.0, animation[0], TRUE);

	}
	else
	{
		if (camera_pos.x > D_WIN_MAX_X / 2)
		{
			DrawRotaGraph(D_WIN_MAX_X / 2, location.y, 1.0, 0.0, animation[0], TRUE);
		}
		else
		{
			DrawRotaGraph(location.x, location.y, 1.0, 0.0, animation[0], TRUE);
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

