#include "Camera.h"
#include "../ProjectConfig.h"

// コンストラクタ
Camera::Camera():
	player(nullptr),
	location()
{

}

// デストラクタ
Camera::~Camera()
{

}

// 初期化処理
void Camera::Initialize()
{
	// カメラの初期座標を設定
	this->location.x = D_WIN_MAX_X / 2;
	this->location.y = D_WIN_MAX_Y / 2;
}

// 更新処理
void Camera::Update()
{
	// プレイヤーを追う処理
	if (player->GetLocation().x >= this->location.x)
	{
		this->location.x = player->GetLocation().x;
	}
	else
	{
		// DEBUGフラグ = TRUE   : プレイヤーが戻るとカメラも追従する
		// DEBUGフラグ = FARUSE : プレイヤーが戻るとカメラは追従しない
#ifdef DEBUG
		location.x = player->GetLocation().x;
#endif
	}

	//ステージ外にいかないようにする処理
	float right;
	right = STAGE_SIZE_X * BOX_SIZE - D_WIN_MAX_X / 2;
	if (location.x > right)
	{
		location.x = right;
	}
}

// カメラ情報取得処理
Vector2D Camera::GetCameraPos()
{
	return this->location;
}

// プレイヤー情報設定処理
void Camera::SetPlayer(Player* player)
{
	this->player = player;
}