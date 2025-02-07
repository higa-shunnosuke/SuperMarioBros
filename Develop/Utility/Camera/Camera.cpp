#include "Camera.h"
#include "../ProjectConfig.h"

// �R���X�g���N�^
Camera::Camera():
	player(nullptr),
	location()
{

}

// �f�X�g���N�^
Camera::~Camera()
{

}

// ����������
void Camera::Initialize()
{
	// �J�����̏������W��ݒ�
	this->location.x = D_WIN_MAX_X / 2;
	this->location.y = D_WIN_MAX_Y / 2;
}

// �X�V����
void Camera::Update()
{
	if (player->GetIsUg() == true)
	{
		location.x = 1776.0f;
		location.y = -272.0f;
	}
	else
	{
		this->location.y = D_WIN_MAX_Y / 2;

		// �v���C���[��ǂ�����
		// DEBUG�t���O = TRUE   : �v���C���[���߂�ƃJ�������Ǐ]����
			// DEBUG�t���O = FARUSE : �v���C���[���߂�ƃJ�����͒Ǐ]���Ȃ�
#ifdef DEBUG
		location.x = player->GetLocation().x;
		location.y = -player->GetLocation().y + D_WIN_MAX_Y;
#else
		if (player->GetLocation().x >= this->location.x)
		{
			this->location.x = player->GetLocation().x;
		}
#endif
	}

	//�X�e�[�W�O�ɂ����Ȃ��悤�ɂ��鏈��
	float right;
	right = STAGE_SIZE_X * BOX_SIZE - D_WIN_MAX_X / 2;
	if (location.x > right)
	{
		location.x = right;
	}
}

// �J�������擾����
Vector2D Camera::GetCameraPos()
{
	return this->location;
}

// �v���C���[���ݒ菈��
void Camera::SetPlayer(Player* player)
{
	this->player = player;
}