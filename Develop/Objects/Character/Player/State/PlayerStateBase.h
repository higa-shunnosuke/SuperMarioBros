#pragma once
#include "../Player.h"
#include "../../../../Utility/Input/InputManager.h"
#include "../../../../Utility/ResourceManager.h"


///<summary>
///プレイヤー状態管理用のベースクラス
///</summary>
class PlayerStateBase
{
protected:
	class Player* player;			//プレイヤー情報
	std::vector<int> animation;		//移動のアニメーション画像
	Vector2D box_size;				//プレイヤーの当たり判定

public:
	///<summary>
	///コンストラクタ
	///</summary>
	///<param name="p">プレイヤー情報</param>
	PlayerStateBase(class Player* p) :
		player(p)
	{

	}

	//デストラクタ
	virtual ~PlayerStateBase() = default;

public:
	//初期化処理関数
	virtual void Initialize() = 0;

	//終了時処理関数
	virtual void Finalize() = 0;

	//更新処理
	virtual void Update() = 0;

	//描画処理
	virtual void Draw(const Vector2D camera_pos) const = 0;

	//状態の取得
	virtual ePlayerState GetState() const = 0;

	//当たり判定取得処理
	Vector2D GetPlayerSize()
	{
		return box_size;
	}
};