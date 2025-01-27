#pragma once

#include "../SceneBase.h"
#include "../../Objects/Character/Player/Player.h"

#define SIZE_X 211
#define SIZE_Y 16

class InGame : public SceneBase
{
private:
	int	score;						//スコア
	std::vector<int> num;			// 数字
	Player* player;					// プレイヤー情報
	Camera* camera;					// カメラ情報
	int sky_image;
	int leaf_image[3];				// 葉の画像
	int mountain_image[6];			// 山の画像
	int cloud_image[6];				// 雲の画像

public:
	InGame();
	virtual ~InGame();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

private:
	// ステージ生成処理
	void LoadStage();
};

