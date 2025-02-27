#include "Goal.h"

Goal::Goal():
	type(),
	frag_location()
{

}

Goal::~Goal()
{

}

void Goal::Initialize()
{
	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/block.png")[0];

	is_mobility = false;

	collision.is_blocking = false;
	collision.object_type = eObjectType::eGole;
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

	// ゴールの描画
	DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// 当たり判定表示
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

	// 画像の読み込み
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
		collision.box_size = Vector2D(20.0f, 32.0f);
		break;
	case eGoalType::Pool:
		image = rm->GetImages("Resource/Images/pole_down.png")[0];
		collision.box_size = Vector2D(10.0f, 32.0f);
		break;
	}
}