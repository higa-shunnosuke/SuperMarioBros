#pragma once

#include "../Character.h"
#include "../../../Utility/Camera/Camera.h"

class Koopa : public Character
{
private:
	std::vector<int> animation1;		//移動のアニメーション画像
	std::vector<int> animation2;		//甲羅のアニメーション画像

	bool is_shell;  // 甲羅状態かどうか
	bool is_hit;    // 一度当たった状態かどうか

	Camera* camera;

public:
	Koopa();
	~Koopa();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;

	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

	/// <summary>
	/// カメラの情報を取得
	/// </summary>
	void SetCamera(Camera* camera);

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);

	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);

	
};
