#include "Hatena.h"

Hatena::Hatena()
{

}

Hatena::~Hatena()
{

}

void Hatena::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/hatena.png",4,4,1,32,32)[0];

	is_mobility = false;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.box_size = Vector2D(32.0f, 32.0f);

}

void Hatena::Update(float delta_second)
{

}

void Hatena::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;

	// ハテナブロックの描画
	DrawRotaGraph(position.x, location.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// 当たり判定表示
	DrawBox(position.x - collision.box_size.x / 2, location.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, location.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Hatena::Finalize()
{

}