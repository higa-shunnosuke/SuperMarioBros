#include "FireFlower.h"
#include "../GameObjectManager.h"

FireFlower::FireFlower() :
	anim_time(),
	anim_count(),
	spawn_count()
{

}

FireFlower::~FireFlower()
{

}

void FireFlower::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	anim_img = rm->GetImages("Resource/Images/Item/flower.png", 4, 4, 1, 32, 32);

	is_mobility = false;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eFireFlower;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = Vector2D(32.0f, 32.0f);

	z_layer = 1;
}

void FireFlower::Update(float delta_second)
{
	AnimationControl(delta_second);

}

void FireFlower::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// レンガの描画
	DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// 当たり判定表示
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void FireFlower::Finalize()
{

}

void FireFlower::OnHitCollision(GameObject* hit_object)
{
	// 当たり判定情報を取得して、矩形がある位置を求める
	Collision hc = hit_object->GetCollision();

	// 当たった、オブジェクトがプレイヤーだったら
	if (hc.object_type == eObjectType::ePlayer)
	{
		GameObjectManager* object = GameObjectManager::GetInstance();
		object->DestroyObject(this);
	}
}

void FireFlower::AnimationControl(float delta_second)
{
	anim_time += delta_second;

	if (anim_time >= 0.1f)
	{
		anim_time = 0.0f;
		anim_count++;
		if (anim_count >= 4)
		{
			anim_count = 0;
		}

		image = anim_img[anim_count];

		if (spawn_count < 8)
		{
			location.y -= 4;
			spawn_count++;
		}
	}
}
