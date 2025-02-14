#pragma once

#include "BlockBase.h"

class Castle :public BlockBase
{

public:
	int frag_image;
	float frag_location;
	bool goal;

public:
	Castle();
	~Castle();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;

};

