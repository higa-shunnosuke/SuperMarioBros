#include "OneUpMushrooms.h"
#include "../GameObjectManager.h"
#include "../Character/Player/Player.h"

OneUpMushrooms::OneUpMushrooms()
{

}

OneUpMushrooms::~OneUpMushrooms()
{

}

void OneUpMushrooms::Initialize()
{
	// ‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	ResourceManager* rm = ResourceManager::GetInstance();
	image = rm->GetImages("Resource/Images/Item/1up_mushroom.png")[0];

	is_mobility = true;

	collision.is_blocking = true;
	collision.object_type = eObjectType::e1UPMushrooms;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);
	collision.box_size = Vector2D(32.0f, 32.0f);
	z_layer = 1;
}

void OneUpMushrooms::Update(float delta_second)
{
	__super::Update(delta_second);
}

void OneUpMushrooms::Draw(const Vector2D camera_pos) const
{
	__super::Draw(camera_pos);
}

void OneUpMushrooms::Finalize()
{

}

void OneUpMushrooms::OnHitCollision(GameObject* hit_object)
{
	__super::OnHitCollision(hit_object);
}

void OneUpMushrooms::AnimationControl(float delta_second)
{
	__super::AnimationControl(delta_second);

}