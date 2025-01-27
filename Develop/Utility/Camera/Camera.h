#pragma once

#include "../../Objects/Character/Player/Player.h"
#include "../Singleton.h"

class Camera : public Singleton<Camera>
{
private:
	Player* player;		// プレイヤー情報
	Vector2D location;	// カメラ座標

public:
	// コンストラクタ
	Camera();
	// デストラクタ
	~Camera();

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	///  実行処理
	/// </summary>
	void Update();

	/// <summary>
	/// カメラ座標取得処理
	/// </summary>
	/// <returns>カメラ座標</returns>
	Vector2D GetCameraPos();

	/// <summary>
	/// プレイヤー情報設定処理
	/// </summary>
	/// <param name="player">プレイヤー情報</param>
	void SetPlayer(Player* player);
};

