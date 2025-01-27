#include "Block.h"

Block::Block()
{

}

Block::~Block()
{

}

void Block::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/block.png")[0];

	is_mobility = false;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.box_size = Vector2D(32.0f, 32.0f);

}

void Block::Update(float delta_second)
{

}

void Block::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;

	// レンガの描画
	DrawRotaGraph(position.x, location.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// 当たり判定表示
	DrawBox(position.x - collision.box_size.x / 2, location.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, location.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Block::Finalize()
{

}