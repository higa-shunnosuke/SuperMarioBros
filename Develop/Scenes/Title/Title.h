#pragma once

#include "..//SceneBase.h"

// タイトルシーン
class Title : public SceneBase
{
private:
	int back_ground_image;		// 背景画像
	int top;					// トップ
	std::vector<int> num;		// 数字
	std::vector<int> player;	// プレイヤー画像

public:
	Title();
	virtual ~Title();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;
};

