#pragma once
//#include <iostream>
//#include <thread>
//#include <chrono>

#include "../Character.h"


// カメラクラスへの参照
class Camera;

enum class ePlayerState {
	NOMAL = 0,	//ノーマルマリオ
	SUPER,		//スーパーマリオ
	FIRE,		//ファイヤマリオ
	TIBI,		//マメマリオ
	NONE		//
};


class Player : public Character
{
private:
	bool is_run;					//走っているか？
	bool is_star;					//スター状態か？
	bool is_death;					//死んでいるか？
	class PlayerStateBase* state;	//現在の状態
	ePlayerState next_state;		//次の状態
	float friction;					//摩擦
	Camera* camera;					//カメラ情報
	bool is_ug;						//地下にいるか
	std::vector<int> animation;		//移動のアニメーション画像

public:
	Player();	//初期位置 0, 速度 1
	~Player();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;

	//試し用
	//int x;		//マリオのx座標	
	//int speed;	//走る速度
	//Player():x(0),speed(1){}	//初期位置 0, 速度 1
	//void run() {
	//	while (x < 50) {	//50 の位置まで走る
	//		x += speed;
	//		/*display();*/
	//		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//	}
	//}
	/*void display() {
		system("clear");
		for (int i = 0; i < x; i++) std::cout << " ";
		std::cout << "P" << std::endl;
	}*/


	/// <summary>
	/// 当たり判定通知処理
	/// </summary>
	/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

	///<summary>
	///次のStateを設定
	/// </summary>
	/// <param name="init_location>次のState</param>
	void SetNextState(ePlayerState next_state);

private:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void Movement(float delta_second);

	/// <summary>
	/// ジャンプ処理
	/// </summary>
	void Jump();

	/// <summary>
	/// しゃがみ処理
	/// </summary>
	void Squt();

	/// <summary>
	/// アニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second);

	/// <summary>
	/// 走る処理
	/// </summary>
	void Run();

public:
	/// <summary>
	/// プレイヤーがスター状態か確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	bool GetIsStar();

	/// <summary>
	/// プレイヤーが死んでいるか確認する
	/// </summary>
	/// <returns>プレイヤーの状態</returns>
	bool GetIsDeath();

	/// <summary>
	/// カメラの情報を取得
	/// </summary>
	void SetCamera(Camera* camera);

	/// <summary>
	/// 地下フラグ取得処理
	/// </summary>
	/// <returns>地下フラグ</returns>
	bool GetIsUg();

	
	void Warp(Vector2D location);

	ePlayerState GetState();
};
