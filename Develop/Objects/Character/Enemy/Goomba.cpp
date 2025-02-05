#include "Goomba.h"

Goomba::Goomba():
	camera()
{

}

Goomba::~Goomba()
{

}

void Goomba::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	animation1 = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);

	g_velocity = 0.0f;
	velocity = Vector2D(-200.0f, 0.0f);
	on_ground = true;
	is_mobility = true;
	z_layer = 2;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(25.0f, 25.0f);

	image = animation1[0];
	anim_count = 0.0f;
}

void Goomba::Update(float delta_second)
{

	if (on_ground == true)
	{
		g_velocity = 0.0f;
		velocity.y = 0.0f;
	}
	else
	{
		//重力加速度の計算
		g_velocity += D_GRAVITY / 9807;
		velocity.y += g_velocity;
	}

	//落下の実行
	location.y += velocity.y;

	on_ground = false;

	if (location.x < camera->GetCameraPos().x + D_WIN_MAX_X / 2)
	{
		Movement(delta_second);

		if (location.x < camera->GetCameraPos().x - D_WIN_MAX_X / 2)
		{
			is_death = true;
		}
	}

	AnimationControl(delta_second);
}

void Goomba::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// クリボーの描画(画像めり込み防止のためy座標のみ-3.0fの補正値追加)
	DrawRotaGraph(position.x, position.y-3, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// 当たり判定表示
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0xff0000, FALSE);
#endif
}

void Goomba::Finalize()
{

}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void Goomba::OnHitCollision(GameObject* hit_object)
{
	// 当たり判定情報を取得して、矩形がある位置を求める
	Collision hc = hit_object->GetCollision();

	// ２点間の距離を計算
	Vector2D distance;
	distance = this->location - hit_object->GetLocation();

	// 当たった、オブジェクトが壁だったら
	if (hc.object_type == eObjectType::eBlock)
	{
		Vector2D diff;	// めり込み

		// 衝突面を求める
		if (distance.x <= 0)
		{
			if (distance.y <= 0)
			{
				// プレイヤーの右辺と下辺、ブロックの左辺と上辺のめり込みを計算
				diff = (this->location + collision.box_size / 2)
					- (hit_object->GetLocation() - hc.box_size / 2);

				// 押し戻し処理
				if (diff.x < diff.y)
				{
					// 左に
					velocity.x *= -1;
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
					velocity.x *= -1;
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
					velocity.x *= -1;
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
					velocity.x *= -1;
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

	// プレイヤーに当たったときの処理
	if (hc.object_type==eObjectType::ePlayer)
	{
		// プレイヤーが上から当たったのなら
		if (distance.y >= collision.box_size.y/2.0f)
		{
			velocity = 0;
			image = animation1[2];
		}
	}
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Goomba::Movement(float delta_second)
{
	location.x += velocity.x * delta_second;
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void Goomba::AnimationControl(float delta_second)
{
	anim_count += delta_second;

	if (anim_count >= 0.1f)
	{
		if (image == animation1[0])
		{
			image = animation1[1];
		}
		else if (image == animation1[1])
		{
			image = animation1[0];
		}
		anim_count = 0;
	}
}

/// <summary>
/// カメラの情報を取得
/// </summary>
void Goomba::SetCamera(Camera* camera)
{
	this->camera = camera;
}