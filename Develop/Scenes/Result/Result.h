#pragma once

#include "../SceneBase.h"

class Result : public SceneBase
{
private:
	std::vector<int> num;		// ����

public:
	Result();
	virtual ~Result();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;
};

