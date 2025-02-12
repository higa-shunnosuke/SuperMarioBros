#include "Hatena.h"
#include "../Character/Player/Player.h"
#include "../GameObjectManager.h"

Hatena::Hatena() :
	anim_time(),
	anim_count(),
	move_count(),
	is_animation(true),
	empty_image(),
	type(eHatenaState::COIN)
{

}

Hatena::~Hatena()
{

}

void Hatena::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	anim_img = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	empty_image = rm->GetImages("Resource/Images/Block/kara_block.png")[0];

	is_mobility = false;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGoomba);
	collision.hit_object_type.push_back(eObjectType::eKoopa);;
	collision.box_size = Vector2D(32.0f, 32.0f);

}

void Hatena::Update(float delta_second)
{
	AnimationControl(delta_second);

}

void Hatena::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// ハテナブロックの描画
	DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// 当たり判定表示
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Hatena::Finalize()
{

}

void Hatena::OnHitCollision(GameObject* hit_object)
{
	// 当たり判定情報を取得して、矩形がある位置を求める
	Collision hc = hit_object->GetCollision();

	// 当たった、オブジェクトがプレイヤーだったら
	if (hc.object_type == eObjectType::ePlayer)
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
				// ブロックの右辺と下辺、プレイヤーの左辺と上辺のめり込みを計算
				diff = (this->location + collision.box_size / 2)
					- (hit_object->GetLocation() - hc.box_size / 2);

				// アニメーション
				if (diff.x >= diff.y)
				{
					is_animation = false;
					CreateItem(hit_object);
				}
			}
		}
		else
		{
			if (distance.y < 0)
			{
				// ブロックの左辺と下辺、プレイヤーの右辺と上辺のめり込みを計算
				diff = Vector2D((this->location.x - collision.box_size.x / 2),
					(this->location.y + collision.box_size.y / 2))
					- Vector2D((hit_object->GetLocation().x + hc.box_size.x / 2),
						(hit_object->GetLocation().y - hc.box_size.y / 2));

				// アニメーション
				if (-diff.x > diff.y)
				{
					is_animation = false;
					CreateItem(hit_object);
				}
			}
		}
	}
}

void Hatena::AnimationControl(float delta_second)
{
	anim_time += delta_second;

	if (is_animation == true)
	{
		if (type != eHatenaState::UP && type != eHatenaState::STAR)
		{
			if (anim_time >= 0.1f)
			{
				anim_time = 0.0f;
				anim_count++;
				if (anim_count >= 4)
				{
					anim_count = 0;
				}

				image = anim_img[anim_count];
			}
		}
	}
	else if(move_count < 18)
	{
		image = empty_image;

		if (anim_time >= 0.01f)
		{
			anim_time = 0;

			if (move_count < 7)
			{
				location.y -= 1;
				move_count++;
			}
			else if (move_count < 16)
			{
				location.y += 1;
				move_count++;
			}
			else if (move_count < 18)
			{
				location.y -= 1;
				move_count++;
			}
		}
	}
}

void Hatena::SetType(eHatenaState type)
{
	this->type = type;

	if (type == eHatenaState::STAR)
	{
		ResourceManager* rm = ResourceManager::GetInstance();
		image = rm->GetImages("Resource/Images/Block/block.png")[0];
	}
	else if (type == eHatenaState::UP)
	{
		ResourceManager* rm = ResourceManager::GetInstance();
		image = rm->GetImages("Resource/Images/sora.png")[0];
	}
}

void Hatena::CreateItem(GameObject* player)
{
	GameObjectManager* object = GameObjectManager::GetInstance();
	dynamic_cast<Player*>(player);

	switch (type)
	{
	case eHatenaState::COIN:

		break;
	case eHatenaState::ITEM:

		break;
	case eHatenaState::UP:

		break;
	case eHatenaState::STAR:

		break;
	}
}