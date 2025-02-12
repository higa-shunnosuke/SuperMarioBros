#include "Stairs.h"

Stairs::Stairs()
{

}

Stairs::~Stairs()
{

}

void Stairs::Initialize()
{
	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/kai_block.png")[0];

	is_mobility = false;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eGoomba);
	collision.hit_object_type.push_back(eObjectType::eKoopa);
	collision.box_size = Vector2D(32.0f, 32.0f);

}

void Stairs::Update(float delta_second)
{

}

void Stairs::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// ŠK’i‚Ì•`‰æ
	DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// “–‚½‚è”»’è•\Ž¦
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Stairs::Finalize()
{

}