#include "Goal.h"

Goal::Goal():
	type()
{

}

Goal::~Goal()
{

}

void Goal::Initialize()
{
	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/block.png")[0];

	is_mobility = false;

	collision.is_blocking = false;
	collision.object_type = eObjectType::eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);

}

void Goal::Update(float delta_second)
{

}

void Goal::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// ƒS[ƒ‹‚Ì•`‰æ
	DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// “–‚½‚è”»’è•\Ž¦
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Goal::Finalize()
{

}

void Goal::SetType(eGoalType type)
{
	this->type = type;

	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	ResourceManager* rm = ResourceManager::GetInstance();
	switch (type)
	{
	case eGoalType::Flag:
		image = rm->GetImages("Resource/Images/flag.png")[0];
		collision.box_size = Vector2D(32.0f, 32.0f);
		z_layer = 3;
		location.x += 15;
		break;
	case eGoalType::Bool:
		image = rm->GetImages("Resource/Images/pole.png")[0];
		collision.box_size = Vector2D(0.0f, 0.0f);
		break;
	case eGoalType::Pool:
		image = rm->GetImages("Resource/Images/pole_down.png")[0];
		collision.box_size = Vector2D(10.0f, 32.0f);
		break;
	}
}