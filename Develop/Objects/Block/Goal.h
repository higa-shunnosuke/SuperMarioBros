#pragma once

#include "BlockBase.h"

enum class eGoalType {
	Flag = 0,	//ä¯
	Bool,		//ã 
	Pool		//É|Å[Éã
};

class Goal :public BlockBase
{
public:
	eGoalType type;
	float frag_location;
public:
	Goal();
	~Goal();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	void SetType(eGoalType type);

};
