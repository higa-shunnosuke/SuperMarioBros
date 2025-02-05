#pragma once

#include "BlockBase.h"

enum class ePipeType {
	LEFT_DOWN = 0,	//左下
	LEFT_UP,		//左上
	RIGHT_DOWN,		//右下
	RIGHT_UP,		//右上
	LIE_LEFT_DOWN,	//横向き左下
	LIE_MIDDLE_DOWN,//横向き真ん中下
	LIE_RIGHT_DOWN,	//横向き右下
	LIE_RIGHT_UP,	//横向き右上
	LIE_MIDDLE_UP,	//横向き真ん中上
	LIE_LEFT_UP		//横向き左上
};

class WaterPipes :public BlockBase
{
public:
	ePipeType type;

public:
	WaterPipes();
	~WaterPipes();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	void SetType(ePipeType type);
};

