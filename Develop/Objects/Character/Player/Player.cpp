#include "Player.h"
#include "Factory/PlayerStateFactory.h"
#include "../../../Utility/Input/InputEventManager.h"
#include "../../../Utility/Camera/Camera.h"
#include "../../Block/WarpBox.h"

#include <iostream>
#include <thread>
#include <chrono>

#define D_PLAYER_SPEED 400.0f

Player::Player() :
	is_run(false),
	is_star(false),
	state(nullptr),
	next_state(ePlayerState::NONE),
	friction(0.0f),
	camera(nullptr),
	is_ug(false)
{

}

Player::~Player()

{
	
}

//Initializeにする
//int main() {
//	Player player;
//	player.run();
//	return 0;
//}

//int main() {
//	// DxLibの初期化
//	ChangeWindowMode(TRUE);  // ウィンドウモードで起動
//	if (DxLib_Init() == -1) return -1;  // DxLibの初期化 (エラーなら終了)
//
//	// 画面サイズ設定
//	SetGraphMode(800, 600, 32);
//
//	// マリオの座標
//	int marioX = 100;
//	int marioY = 400;
//	int speed = 5;  // 走るスピード
//
//	// マリオの画像 (事前に "mario.png" を用意する)
//	int marioImg = LoadGraph("mario.png");


void Player::Initialize()		
{
	state = PlayerStateFactory::Get((*this), ePlayerState::NOMAL);
	next_state = ePlayerState::NONE;
	g_velocity = 0.0f;
	velocity = Vector2D(0.0f);
	on_ground = true;
	is_mobility = true;
	z_layer = 3;

	//入力イベントの登録
	InputEventManager* input_event = InputEventManager::GetInstance();
	input_event->ActionKeyBind(KEY_INPUT_W, eInputState::Pressed, this, &Player::Jump);
	/*input_event->ActionKeyBind(KEY_INPUT_LSHIFT, eInputState::Hold, this, &Player::Run);*/
	input_event->ActionKeyBind(KEY_INPUT_A, -1, this, &Player::Movement);
	input_event->ActionKeyBind(KEY_INPUT_D, 1, this, &Player::Movement);

	collision.is_blocking = true;
	collision.object_type = eObjectType::ePlayer;
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.hit_object_type.push_back(eObjectType::eItem);
	collision.hit_object_type.push_back(eObjectType::eWarp);
}

//Updateに追加
//while (ProcessMessage() == 0) {
//	// 画面クリア
//	ClearDrawScreen();
//
//	// 右キーで走る
//	if (CheckHitKey(KEY_INPUT_RIGHT)) {
//		marioX += speed;
//	}
//
//	// 左キーで戻る
//	if (CheckHitKey(KEY_INPUT_LEFT)) {
//		marioX -= speed;
//	}
//
//	// マリオの描画
//	DrawGraph(marioX, marioY, marioImg, TRUE);
//
//	// 画面更新
//	ScreenFlip();
//}


void Player::Update(float delta_second)
{

	//当たり判定の設定
	collision.box_size = state->GetPlayerSize();

	//stateの変更処理
	if (next_state != ePlayerState::NONE)
	{
		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}

	//状態別の更新処理を行う
	state->Update();

	if (on_ground == true)
	{
		if (velocity.y > 0)
		{
			g_velocity = 0.0f;
			velocity.y = 0.0f;
		}
	}
	else
	{
		//重力加速度の計算
		if (g_velocity)
		{
			g_velocity += D_GRAVITY / 100 * delta_second;				//(9807),
		}
		else
		{
			g_velocity += D_GRAVITY / 100 * delta_second;				//(9807),
		}
		g_velocity += D_GRAVITY / 10 * delta_second;				//(9807),
		velocity.y += g_velocity;
	}

	//移動の実行
	location += velocity * D_PLAYER_SPEED * delta_second;

	on_ground = false;
	velocity.x = 0.0f;

	// 画面外にいかないようにする
	float left;
	left = camera->GetCameraPos().x - D_WIN_MAX_X / 2 + collision.box_size.x / 2;
	if (left > location.x)
	{
		location.x = left;
	}

	if (is_ug == false)
	{
		//// 画面外に落ちると死ぬ
		//if (D_WIN_MAX_Y < location.y)
		//{
		//	is_death = true;
		//	location.y = D_WIN_MAX_Y;
		//	on_ground = true;
		//}
	}
}

void Player::Draw(const Vector2D camera_pos) const
{
	//状態別の描画処理を行う
	state->Draw(camera_pos);

#ifdef DEBUG
	// 座標表示
	DrawFormatString(10, 90, 0xffffff, "X:%f", location.x);
	DrawFormatString(10, 120, 0xffffff, "Y:%f", location.y);
	DrawFormatString(250, 90, 0xffffff, "VX:%f", velocity.x);
	DrawFormatString(250, 120, 0xffffff, "VY:%f", velocity.y);
	DrawFormatString(490, 90, 0xffffff, ":%d", on_ground);

	float diff_x = camera_pos.x - location.x;
	float diff_y = camera_pos.y + location.y - D_WIN_MAX_Y / 2;

	// 当たり判定表示
	if (is_ug == true)
	{
		DrawBox((D_WIN_MAX_X / 2) - diff_x - collision.box_size.x / 2, diff_y - collision.box_size.y / 2,
			(D_WIN_MAX_X / 2) - diff_x + collision.box_size.x / 2, diff_y + collision.box_size.y / 2, 0xff0000, FALSE);
	}
	else
	{
		if (camera_pos.x <= location.x)
		{
			DrawBox(D_WIN_MAX_X / 2 - collision.box_size.x / 2, diff_y - collision.box_size.y / 2,
				D_WIN_MAX_X / 2 + collision.box_size.x / 2, diff_y + collision.box_size.y / 2, 0xff0000, FALSE);
		}
		else
		{

			DrawBox((D_WIN_MAX_X / 2) - diff_x - collision.box_size.x / 2, diff_y - collision.box_size.y / 2,
				(D_WIN_MAX_X / 2) - diff_x + collision.box_size.x / 2, diff_y + collision.box_size.y / 2, 0xff0000, FALSE);
		}
	}
	
#endif

}

void Player::Finalize()
{
	PlayerStateFactory::Finalize();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Player::OnHitCollision(GameObject* hit_object)
{
	// 当たり判定情報を取得して、矩形がある位置を求める
	Collision hc = hit_object->GetCollision();

	// 当たった、オブジェクトが壁だったら
	if (hc.object_type == eObjectType::eBlock)
	{
		Vector2D diff;	// めり込み

		// ２点間の距離を計算
		Vector2D distance;
		distance = this->location - hit_object->GetLocation();

		// 衝突面を求める
		if (distance.x <= 0)
		{
			if (distance.y <= 0)
			{
				// プレイヤーの右辺と下辺、ブロックの左辺と上辺のめり込みを計算
				diff = (this->location + collision.box_size / 2)
					- (hit_object->GetLocation() - hc.box_size / 2);

				// 押し戻し処理
				if (diff.x <= diff.y)
				{
					// 左に
					location.x -= diff.x;
				}
				else
				{
					// 上に
					location.y -= diff.y;
					on_ground = true;
				}
			}
			else
			{
				// プレイヤーの右辺と上辺、ブロックの左辺と下辺のめり込みを計算
				diff = Vector2D((this->location.x + collision.box_size.x / 2),
					(this->location.y - collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x - hc.box_size.x / 2),
						(hit_object->GetLocation().y + hc.box_size.y / 2));

				// 押し戻し処理
				if (diff.x < -diff.y)
				{
					// 左に
					location.x -= diff.x;
				}
				else
				{
					// 下に
					location.y -= diff.y;
					velocity.y = 0;
				}
			}
		}
		else
		{
			if (distance.y >= 0)
			{
				// プレイヤーの左辺と上辺、ブロックの右辺と下辺のめり込みを計算
				diff = (this->location - collision.box_size / 2)
					- (hit_object->GetLocation() + hc.box_size / 2);

				// 押し戻し処理
				if (-diff.x < -diff.y || distance.y == 0)
				{
					// 右に
					location.x -= diff.x;
				}
				else
				{
					// 下に
					location.y -= diff.y;
					velocity.y = 0;
				}
			}
			else
			{
				// プレイヤーの左辺と下辺、ブロックの右辺と上辺のめり込みを計算
				diff = Vector2D((this->location.x - collision.box_size.x / 2),
					(this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + hc.box_size.x / 2),
						(hit_object->GetLocation().y - hc.box_size.y / 2));

				// 押し戻し処理
				if (-diff.x < diff.y)
				{
					// 右に
					location.x -= diff.x;
				}
				else
				{
					// 上に
					location.y -= diff.y;
					on_ground = true;
				}
			}
		}
	}

	// 当たった、オブジェクトがワープブロックだったら
	if (hc.object_type == eObjectType::eWarp)
	{
		// 入力情報を取得
		InputManager* input = InputManager::GetInstance();

		if (dynamic_cast<WarpBox*>(hit_object)->GetPairNo() == 1)
		{
			// 地下フラグをTrueにする
			if (input->GetKeyState(KEY_INPUT_S) == eInputState::Pressed)
			{
				is_ug = true;
			}
		}
		else if(dynamic_cast<WarpBox*>(hit_object)->GetPairNo() == 2)
		{
			// 地下フラグをFalseにする
			if (input->GetKeyState(KEY_INPUT_D) == eInputState::Pressed)
			{
				is_ug = false;
			}
		}
	}
}

///<summary>
///次のStateを設定
/// </summary>
/// <param name="init_location>次のState</param>
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::Movement(float param)
{
	velocity.x += param;
}

/// <summary>
/// ジャンプ処理
/// </summary>
void Player::Jump()
{
	if (on_ground == true)
	{
		velocity.y = -6.5f;
	}

	on_ground = false;
}

/// <summary>
/// しゃがみ処理
/// </summary>
void Player::Squt()
{

}

 // <summary>
 // 走る処理
 // </summary>
void Player::Run()
{
//while (x < 50) {	//50 の位置まで走る
//	x += speed;
//	/*display();*/
//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
//	}
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Player::AnimationControl(float delta_second)
{

}

/// <summary>
/// プレイヤーがスター状態か確認する
/// </summary>
/// <returns>プレイヤーの状態</returns>
bool Player::GetIsStar()
{
	return is_star;
}

/// <summary>
/// プレイヤーが死んでいるか確認する
/// </summary>
/// <returns>プレイヤーの状態</returns>
bool Player::GetIsDeath()
{
	return is_death;
}

/// <summary>
/// カメラの情報を取得
/// </summary>
void Player::SetCamera(Camera* camera)
{
	this->camera = camera;
}

bool Player::GetIsUg()
{
	return is_ug;
}

//ワープ処理
void Player::Warp(Vector2D location)
{
	this->location = location;
}

//現在の状態取得処理
ePlayerState Player::GetState()
{
	return state->GetState();
}