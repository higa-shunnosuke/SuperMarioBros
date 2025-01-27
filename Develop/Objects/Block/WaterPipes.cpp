#include "WaterPipes.h"

WaterPipes::WaterPipes() :
	type()
{

}

WaterPipes::~WaterPipes()
{

}

void WaterPipes::Initialize()
{
	is_mobility = false;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.box_size = Vector2D(32.0f, 32.0f);

}

void WaterPipes::Update(float delta_second)
{

}

void WaterPipes::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;

	// ƒŒƒ“ƒK‚Ì•`‰æ
	DrawRotaGraph(position.x, location.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// “–‚½‚è”»’è•\Ž¦
	DrawBox(position.x - collision.box_size.x / 2, location.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, location.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void WaterPipes::Finalize()
{

}

void WaterPipes::SetType(ePipeType type)
{
	this->type = type;

	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	ResourceManager* rm = ResourceManager::GetInstance();
	switch (type)
	{
	case ePipeType::LEFT_DOWN:
		image = rm->GetImages("Resource/Images/dokan_left_down.png")[0];
		break;
	case ePipeType::LEFT_UP:
		image = rm->GetImages("Resource/Images/dokan_left_up.png")[0];
		break;
	case ePipeType::RIGHT_DOWN:
		image = rm->GetImages("Resource/Images/dokan_right_down.png")[0];
		break;
	case ePipeType::RIGHT_UP:
		image = rm->GetImages("Resource/Images/dokan_right_up.png")[0];
		break;
	}
}
