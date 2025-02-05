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
	// コンストラクタ
	Title();
	// デストラクタ
	virtual ~Title();

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
};

