#pragma once

#include "BlockBase.h"

enum class ePipeType {
	LEFT_DOWN = 0,	//����
	LEFT_UP,		//����
	RIGHT_DOWN,		//�E��
	RIGHT_UP,		//�E��
	LIE_LEFT_DOWN,	//����������
	LIE_MIDDLE_DOWN,//�������^�񒆉�
	LIE_RIGHT_DOWN,	//�������E��
	LIE_RIGHT_UP,	//�������E��
	LIE_MIDDLE_UP,	//�������^�񒆏�
	LIE_LEFT_UP		//����������
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

