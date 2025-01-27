#include "Camera.h"
#include "../ProjectConfig.h"

Camera::Camera():
	player(nullptr),
	location()
{

}

Camera::~Camera()
{

}

void Camera::Initialize()
{
	this->location.x = D_WIN_MAX_X / 2;
	this->location.y = D_WIN_MAX_Y / 2;
}

void Camera::Update()
{
	// �v���C���[��ǂ�����
	if (player->GetLocation().x >= this->location.x)
	{
		this->location.x = player->GetLocation().x;
	}
	else
	{
#ifdef DEBUG
		location.x = player->GetLocation().x;
#endif
	}

	float right;
	right = 6400;
	 //�X�e�[�W�O�ɂ����Ȃ��悤�ɂ��鏈��
	if (location.x > right)
	{
		location.x = right;
	}
}

Vector2D Camera::GetCameraPos()
{
	return this->location;
}

void Camera::SetPlayer(Player* player)
{
	this->player = player;
}