#include "Super.h"
#include "../Player.h"

///<summary>
///コンストラクタ
///</summary>
///<param name="p">プレイヤー情報</param>
Super::Super(class Player* p)
	:PlayerStateBase(p)
{

}

///<summary>
///デストラクタ
///</summary>
Super::~Super()
{

}

///<summary>
///初期化処理
///</summary>
void Super::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	animation = rm->GetImages("Resource/Images/Mario/dekamario.png", 10, 10, 1, 32, 64);

	//// 座標の初期化
	//Vector2D location = player->GetLocation();
	//location.y -= 16.0f;

	//player->SetLocation(location);

	// 当たり判定初期化
	box_size = Vector2D(32.0f, 64.0f);
}

///<summary>
///終了時処理
///</summary>
void Super::Finalize()
{

}

///<summary>
///更新処理
///</summary>
void Super::Update()
{
	InputManager* input = InputManager::GetInstance();

	//移動状態に遷移
	if (input->GetKeyState(KEY_INPUT_Z) == eInputState::Pressed)
	{
		player->SetNextState(ePlayerState::FIRE);
	}
}

///<summary>
///描画処理
///</summary>
void Super::Draw(const Vector2D camera_pos) const
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
ePlayerState Super::GetState() const
{
	return ePlayerState::FIRE;
}

