#include "Castle.h"

Castle::Castle():
	frag_image(),
	frag_location(),
	goal(false)
{

}

Castle::~Castle()
{

}

void Castle::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/siro1.png")[0];
	frag_image = rm->GetImages("Resource/Images/flag_siro.png")[0];
	is_mobility = false;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eCastle;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = Vector2D(160.0f, 160.0f);

	frag_location = -32.0f;
}

void Castle::Update(float delta_second)
{
	if (goal == true)
	{
		if (frag_location > -96.0f)
		{
			frag_location -= 30 * delta_second;
		}
		else
		{
			frag_location = -96;
		}
	}
}

void Castle::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// 城の描画
	DrawRotaGraph(position.x, position.y + frag_location, 1.0, 0.0, frag_image, TRUE);
	DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// 当たり判定表示
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Castle::Finalize()
{

}

void Castle::OnHitCollision(GameObject* hit_object)
{
	// 当たり判定情報を取得して、矩形がある位置を求める
	Collision hc = hit_object->GetCollision();

	// 当たった、オブジェクトがプレイヤーだったら
	if (hc.object_type == eObjectType::ePlayer)
	{
		if (location.x < hit_object->GetLocation().x)
		{
			goal = true;
		}
	}
}