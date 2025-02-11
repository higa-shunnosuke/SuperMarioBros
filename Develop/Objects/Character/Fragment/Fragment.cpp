#include "Fragment.h"
#include "../../GameObjectManager.h"

Fragment::Fragment() :
	type()
{

}

Fragment::~Fragment()
{

}

void Fragment::Initialize()
{
	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Block/bloak_1.png")[0];

	is_mobility = false;

	collision.is_blocking = false;
	collision.object_type = eObjectType::eFragment;

	velocity.y = -100;
}

void Fragment::Update(float delta_second)
{
	location += velocity * 5 * delta_second;

	velocity.y += 3;

	if (type == 0)
	{
		if (velocity.x > -10)
		{
			velocity.x -= 1;
		}
	}
	else
	{
		if (velocity.x < 10)
		{
			velocity.x += 1;
		}
	}
	

	if (location.y > D_WIN_MAX_Y)
	{
		GameObjectManager* object = GameObjectManager::GetInstance();
		object->DestroyObject(this);
	}
}

void Fragment::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

	// Œ‡•Ð‚Ì•`‰æ
	DrawRotaGraph(position.x, position.y, 1.0, 0.0, image, TRUE);

#ifdef DEBUG
	// “–‚½‚è”»’è•\Ž¦
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void Fragment::Finalize()
{

}

void Fragment::SetType(int type)
{
	this->type = type;
}