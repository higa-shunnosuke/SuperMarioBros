#include "WarpBox.h"
#include "../GameObjectManager.h"

WarpBox::WarpBox():
	pair_no(),
	type(),
	exit(nullptr)
{

}

WarpBox::~WarpBox()
{

}

void WarpBox::Initialize()
{
	is_mobility = false;

	collision.is_blocking = true;
	collision.object_type = eObjectType::eWarp;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.box_size = Vector2D(32.0f, 32.0f);

}

void WarpBox::Update(float delta_second)
{
	
}

void WarpBox::Draw(const Vector2D camera_pos) const
{
	Vector2D position = this->GetLocation();
	position.x -= camera_pos.x - D_WIN_MAX_X / 2;
	position.y += camera_pos.y - D_WIN_MAX_Y / 2;

#ifdef DEBUG
	// “–‚½‚è”»’è•\Ž¦
	DrawBox(position.x - collision.box_size.x / 2, position.y - collision.box_size.y / 2,
		position.x + collision.box_size.x / 2, position.y + collision.box_size.y / 2, 0x00ff00, FALSE);
#endif
}

void WarpBox::Finalize()
{

}

void WarpBox::OnHitCollision(GameObject* hit_object)
{
	// “–‚½‚è”»’èî•ñ‚ðŽæ“¾
	Collision hc = hit_object->GetCollision();
	if (hc.object_type == eObjectType::ePlayer)
	{
		if (pair_no == 1)
		{
			if (dynamic_cast<Player*>(hit_object)->GetIsUg() == true)
			{
				if (exit_location.x != 0.0f)
				{
					dynamic_cast<Player*>(hit_object)->Warp(exit_location);
				}
			}
		}
		else if (pair_no == 2)
		{
			if (dynamic_cast<Player*>(hit_object)->GetIsUg() == false)
			{
				if (exit_location.x != 0.0f)
				{
					dynamic_cast<Player*>(hit_object)->Warp(exit_location);
				}
			}
		}
		
	}
}

void WarpBox::SetPaier(int nomber)
{
	this->pair_no = nomber;

	if (pair_no == 1)
	{
		location.x += 16.0f;
	}
	else
	{
		location += 16.0f;
	}
}

int WarpBox::GetPairNo()
{
	return pair_no;
}

void WarpBox::SetType(eWarpType type)
{
	this->type = type;
}

eWarpType WarpBox::GetType()
{
	return type;
}

void WarpBox::SetExit(Vector2D location)
{
	this->exit_location = location;
}
