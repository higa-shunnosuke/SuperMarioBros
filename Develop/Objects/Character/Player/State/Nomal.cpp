#include "Nomal.h"
#include "../Player.h"

///<summary>
///コンストラクタ
///</summary>
///<param name="p">プレイヤー情報</param>
Nomal::Nomal(class Player* p)
	:PlayerStateBase(p)
{

}

///<summary>
///デストラクタ
///</summary>
Nomal::~Nomal()
{

}

///<summary>
///初期化処理
///</summary>
void Nomal::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);

	// 当たり判定初期化
	box_size = (32.0f, 32.0f);
}

///<summary>
///終了時処理
///</summary>
void Nomal::Finalize()
{

}

///<summary>
///更新処理
///</summary>
void Nomal::Update()
{
	InputManager* input = InputManager::GetInstance();

	//移動状態に遷移
	if (input->GetKeyState(KEY_INPUT_Z) == eInputState::Pressed)
	{
		player->SetNextState(ePlayerState::SUPER);
	}
}

///<summary>
///描画処理
///</summary>
void Nomal::Draw(const Vector2D camera_pos) const
{
	// プレイヤーの座標を取得
	Vector2D location = player->GetLocation();

	// プレイヤーの描画
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
///現在のステート情報を取得する
///</summary>
ePlayerState Nomal::GetState() const
{
	return ePlayerState::FIRE;
}

