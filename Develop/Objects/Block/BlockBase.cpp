#include "BlockBase.h"


BlockBase::BlockBase():
	image(NULL),
	is_collapse(false)
{

}

BlockBase::~BlockBase()
{

}

void BlockBase::Initialize()
{
	
}

void BlockBase::Update(float delta_second)
{

}

void BlockBase::Finalize()
{

}

void BlockBase::OnHitCollision(GameObject* hit_object)
{

}

bool BlockBase::GetIsCollapse()
{
	return is_collapse;
}

void BlockBase::SetBlockData()
{

}