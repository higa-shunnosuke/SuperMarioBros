#pragma once

#include "BlockBase.h"
#include "../Character/Player/Player.h"
#include <string>
#include <vector>

enum class eWarpType {
	ENTRANCE,	// 入口
	EXit		// 出口
};

class WarpBox :public BlockBase
{
public:
	int pair_no;				// ペア番号
	eWarpType type;				// タイプ
	WarpBox* exit;				// 出口のポインタ
	Vector2D exit_location;		// 出口の座標

public:
	WarpBox();
	~WarpBox();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;

	/// <summary>
	/// ペア設定処理
	/// </summary>
	/// <param name="nomber">ペア番号</param>
	void SetPair(int nomber);

	/// <summary>
	/// ペア番号取得処理
	/// </summary>
	/// <retrun>ペア番号</return>
	int GetPairNo();

	/// <summary>
	/// タイプ設定処理
	/// </summary>
	/// <param name="type">タイプ</param>
	void SetType(eWarpType type);

	/// <summary>
	/// タイプ取得処理
	/// </summary>
	/// <retrun>タイプ</return>
	eWarpType GetType();

	/// <summary>
	/// 出口情報設定処理
	/// </summary>
	/// <param name="location">出口情報</param>
	void SetExit(Vector2D location);


};

