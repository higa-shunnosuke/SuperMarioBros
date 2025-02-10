#pragma once

#include "BlockBase.h"

class Hatena :public BlockBase
{
public:

public:
	Hatena();
	~Hatena();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
<<<<<<< Updated upstream
=======
	virtual void OnHitCollision(GameObject* hit_object) override;

	//void SetItem();

private:
	void AnimationControl(float delta_second);
>>>>>>> Stashed changes
};

