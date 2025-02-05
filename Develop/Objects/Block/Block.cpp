#include "Block.h"

Block::Block()
{

}

Block::~Block()
{

}

void Block::Initialize()
{
	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
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
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// ƒŒƒ“ƒK‚Ì•`‰æ
	DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// “–‚½‚è”»’è•\Ž¦
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Block::Finalize()
{

}