#pragma once

#include "../SceneBase.h"

class Result : public SceneBase
{
private:
	std::vector<int> num;		// 数字

public:
	Result();
	virtual ~Result();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;
};

