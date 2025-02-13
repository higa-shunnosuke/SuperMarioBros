#include "Mushrooms.h"
#include "../GameObjectManager.h"

Mushrooms::Mushrooms() :
	anim_time(),
	spawn_anim(true),
	spawn_count(),
	velocity(),
	on_ground(true)
{

}

Mushrooms::~Mushrooms()
{

}

void Mushrooms::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Item/mushroom.png")[0];

	is_mobility = true;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eMushrooms;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(32.0f, 32.0f);
	z_layer = 1;
}

void Mushrooms::Update(float delta_second)
{
	if (spawn_anim == false)
	{
		if (on_ground == true)
		{
			velocity.y = 0.0f;
		}
		else
		{
			//重力加速度の計算
			velocity.y += D_GRAVITY / 1000;
		}

		//落下の実行
		location.y += velocity.y;

		on_ground = false;

		location.x += velocity.x * delta_second;
	}

	// 奈落に落ちたら死ぬ
	if (location.y >= 500.0f)
	{
		GameObjectManager* object = GameObjectManager::GetInstance();
		object->DestroyObject(this);
	}

	AnimationControl(delta_second);
}

void Mushrooms::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// スーパーキノコの描画
	if (spawn_count > 1)
	{
		DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);
	}

#ifdef DEBUG
	// 当たり判定表示
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Mushrooms::Finalize()
{

}

void Mushrooms::OnHitCollision(GameObject* hit_object)
{
	// 当たり判定情報を取得して、矩形がある位置を求める
	Collision hc = hit_object->GetCollision();

	// 当たった、オブジェクトがプレイヤーだったら
	if (hc.object_type == eObjectType::ePlayer)
	{
		GameObjectManager* object = GameObjectManager::GetInstance();
		object->DestroyObject(this);
	}

	if (spawn_anim == false)
	{
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
	}
	
}

void Mushrooms::AnimationControl(float delta_second)
{
	anim_time += delta_second;

	if (anim_time >= 0.1f)
	{
		anim_time = 0.0f;
		
		if (spawn_count < 8)
		{
			location.y -= 4;
			spawn_count++;
		}
		else
		{
			if (spawn_anim == true)
			{
				spawn_anim = false;
				velocity.x = 100;
			}
		}
	}
}