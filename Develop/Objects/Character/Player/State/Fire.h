#pragma once

#include "PlayerStateBase.h"

///<summary>
///停止状態
///</summary>
class Fire :public PlayerStateBase
{
private:
	

public:
	///<summary>
	///コンストラクタ
	///</summary>
	///<param name="p">プレイヤー情報</param>
	Fire(class Player* p);

	//デストラクタ
	virtual ~Fire();

public:
	//初期化処理
	virtual void Initialize() override;

	//終了時処理
	virtual void Finalize() override;

	//更新処理
	virtual void Update() override;

	//描画処理
	virtual void Draw(const Vector2D camera_pos) const override;

	//現在のステート情報を取得する
	virtual ePlayerState GetState() const override;
};

