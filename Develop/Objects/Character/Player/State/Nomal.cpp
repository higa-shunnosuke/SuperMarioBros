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
	float diff_x = location.x - camera_pos.x + D_WIN_MAX_Y / 2 + 80;
	float diff_y = camera_pos.y + location.y - D_WIN_MAX_Y / 2;

	// プレイヤーの描画
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
///現在のステート情報を取得する
///</summary>
ePlayerState Nomal::GetState() const
{
	return ePlayerState::NOMAL;
}

