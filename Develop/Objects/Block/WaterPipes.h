#pragma once

#include "BlockBase.h"

enum class ePipeType {
	LEFT_DOWN = 0,	//����
	LEFT_UP,		//����
	RIGHT_DOWN,		//�E��
	RIGHT_UP		//�E��
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

