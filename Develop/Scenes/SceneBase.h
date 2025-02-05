#pragma once

#include <vector>
#include <string>
#include "DxLib.h"

#include "../Utility/ProjectConfig.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/Input/InputManager.h"
#include "../Utility/Input/InputEventManager.h"
#include "../Objects/GameObjectManager.h"
#include "../Utility/Camera/Camera.h"


/// <summary>
/// シーンタイプ
/// </summary>
enum class eSceneType
{
	title,		// タイトル
	in_game,	// インゲーム
	re_start,	// リスタート
	result,		// リザルト
	exit,		// 終了
};

/// <summary>
/// シーン基底クラス
/// </summary>
class SceneBase
{
protected:
	// 各シーンが所有する情報
	int back_ground_sound;				// BGM
	int name_mario;						// プレイヤーネーム
	int world;							// ステージ
	int time;							// タイム
	int coin_image;						// コイン
	std::vector<int> string;			// 文字
	std::vector<int> coin_animation_1;	// コイン（地上）
	std::vector<int> coin_animation_2;	// コイン（地下）
	float animation_time;				// アニメーション時間
	int animation_count;				// アニメーション添字
	GameObjectManager* object;			// オブジェクトマネージャーのポインタ
	InputEventManager* input_event;		// インプットイベントのポインタ
	Camera* camera;						// カメラのポインタ


public:
	// コンストラクタ
	SceneBase() :
		back_ground_sound(NULL),
		name_mario(NULL),
		world(NULL),
		time(NULL),
		coin_image(NULL),
		string(NULL),
		coin_animation_1(NULL),
		coin_animation_2(NULL),
		animation_time(0.0f),
		animation_count(0),
		object(nullptr),
		input_event(nullptr),
		camera(nullptr)
	{
		
	}
	// デストラクタ
	virtual ~SceneBase()
	{
		// 解放忘れ防止
		Finalize();
	}

public:
	/// <summary>
	/// 初期化処理
	/// </summary>
	virtual void Initialize()
	{
		// カメラの情報を取得
		camera = Camera::GetInstance();

		// オブジェクトマネージャーの情報を取得
		object = GameObjectManager::GetInstance();

		// 画像の読み込み
		ResourceManager* rm = ResourceManager::GetInstance();
		name_mario = rm->GetImages("Resource/Images/UI/name_mario.png")[0];
		world = rm->GetImages("Resource/Images/UI/world.png")[0];
		time = rm->GetImages("Resource/Images/UI/time.png")[0];
		string = rm->GetImages("Resource/Images/UI/string.png", 26, 26, 1, 16, 16);
		coin_animation_1 = rm->GetImages("Resource/Images/UI/uicoin.png", 4, 4, 1, 16, 16);
		coin_animation_2 = rm->GetImages("Resource/Images/UI/uicoin_1.png", 4, 4, 1, 16, 16);

		// シーンがリザルトのとき読み込む画像を変更
		if (GetNowSceneType() != eSceneType::result)
		{
			coin_image = coin_animation_1[0];
		}
		else
		{
			coin_image = coin_animation_2[0];
		}

		//入力イベントのインスタンスを取得
		input_event = InputEventManager::GetInstance();
	}

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns>次のシーンタイプ情報</returns>
	virtual eSceneType Update(const float& delta_second)
	{
		//登録されている入力イベントの呼び出し
		input_event->InputActionEvent();

		// 生成するオブジェクトがあれば、オブジェクトリスト内に挿入する
		object->CheckCreateObject();

		// リスト内のオブジェクトを更新する
		for (GameObject* obj : object->GetObjectsList())
		{
			obj->Update(delta_second);
		}

		// デストロイリストの更新
		object->CheckDestroyObject();

		// 現在のシーン情報を返却する
		return GetNowSceneType();
	}

	/// <summary>
	/// 描画処理
	/// </summary>
	virtual void Draw() const
	{
		// オブジェクトリスト内のオブジェクトを描画する
		for (GameObject* obj : object->GetObjectsList())
		{
			obj->Draw(camera->GetCameraPos());
		}

		/*****************　UIの描画　************************/

		// 操作キャラ名の描画
		DrawRotaGraph(125, 35, 1.1, 0.0, name_mario, TRUE);
		
		// コインの描画
		DrawRotaGraph(235, 55, 1.1, 0.0, coin_image, TRUE);
		
		// ステージ名の描画
		DrawRotaGraph(400, 35, 1.1, 0.0, world, TRUE);
		
		// タイムの描画
		DrawRotaGraph(523, 35, 1.1, 0.0, time, TRUE);
	}

	/// <summary>
	/// 終了時処理
	/// </summary>
	virtual void Finalize()
	{
		// 入力イベントの削除
		input_event->AllUnbind();

		// オブジェクトリスト内のオブジェクトを破棄
		object->DestroyAllObject();
	}

	/// <summary>
	/// 現在のシーンタイプ取得処理
	/// </summary>
	/// <returns>現在のシーンタイプ情報</returns>
	virtual const eSceneType GetNowSceneType() const = 0;

protected:
	/// <summary>
	/// uiコインのアニメーション制御
	/// </summary>
	/// <param name="delta_second">1フレームあたりの時間</param>
	void AnimationControl(float delta_second,bool hierarchy)
	{
		animation_time += delta_second;
		if (animation_time >= (1.0f / 5.0f))
		{
			animation_time = 0.0f;
			animation_count++;
			if (animation_count >= 4)
			{
				animation_count = 0;
			}
			// 画像の設定
			if (hierarchy = true)
			{
				coin_image = coin_animation_1[animation_count];
			}
			else
			{
				coin_image = coin_animation_2[animation_count];
			}

		}
	}
};

