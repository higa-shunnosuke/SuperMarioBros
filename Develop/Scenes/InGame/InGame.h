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
	int sky_image;					// 空の画像
	int leaf_image[3];				// 葉の画像
	int mountain_image[6];			// 山の画像
	int cloud_image[6];				// 雲の画像

public:
	// コンストラクタ
	InGame();
	// デストラクタ
	virtual ~InGame();

	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns>次のシーンタイプ情報</returns>
	virtual eSceneType Update(const float& delta_second) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() const override;

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize() override;

	/// <summary>
	/// 現在のシーンタイプ情報を取得する
	/// </summary>
	/// <returns>現在のシーンタイプ</returns>
	virtual const eSceneType GetNowSceneType() const override;

private:
	/// <summary>
	/// ステージの生成処理
	/// </summary>
	void LoadStage();
};

