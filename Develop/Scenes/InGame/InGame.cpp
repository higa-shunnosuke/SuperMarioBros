#include "InGame.h"
#include "DxLib.h"
#include <fstream>

#include "../../Objects/Block/Floor.h"
#include "../../Objects/Block/Block.h"
#include "../../Objects/Block/Hatena.h"
#include "../../Objects/Block/Stairs.h"
#include "../../Objects/Block/WaterPipes.h"
#include "../../Objects/Block/Goal.h"
#include "../../Objects/Character/Enemy/Koopa.h"
#include "../../Objects/Character/Enemy/Goomba.h"
#include "../../Utility/StageData.h"

#define PLAYER_INITIAL_LOCATION 3 // プレイヤー初期位置(何ブロック目）

// コンストラクタ
InGame::InGame() :
	score(0),
	num(NULL),
	player(nullptr),
	camera(nullptr),
	sky_image(),
	leaf_image(),
	mountain_image(),
	cloud_image()
{
	
}

// デストラクタ
InGame::~InGame()
{
	// 解放忘れ防止
	Finalize();
}

void InGame::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);
	sky_image = rm->GetImages("Resource/Images/sora.png")[0];
	leaf_image[0] = rm->GetImages("Resource/Images/ha0.png")[0];
	leaf_image[1] = rm->GetImages("Resource/Images/ha1.png")[0];
	leaf_image[2] = rm->GetImages("Resource/Images/ha2.png")[0];
	mountain_image[0] = rm->GetImages("Resource/Images/mountain_left.png")[0];
	mountain_image[1] = rm->GetImages("Resource/Images/mountain_right.png")[0];
	mountain_image[2] = rm->GetImages("Resource/Images/mountain_surface2.png")[0];
	mountain_image[3] = rm->GetImages("Resource/Images/mountain_surface.png")[0];
	mountain_image[4] = rm->GetImages("Resource/Images/mountain_surface1.png")[0];
	mountain_image[5] = rm->GetImages("Resource/Images/mountain_up.png")[0];
	cloud_image[0] = rm->GetImages("Resource/Images/cloud1.png")[0];
	cloud_image[1] = rm->GetImages("Resource/Images/cloud2.png")[0];
	cloud_image[2] = rm->GetImages("Resource/Images/cloud3.png")[0];
	cloud_image[3] = rm->GetImages("Resource/Images/cloud4.png")[0];
	cloud_image[4] = rm->GetImages("Resource/Images/cloud5.png")[0];
	cloud_image[5] = rm->GetImages("Resource/Images/cloud6.png")[0];

	// カメラの生成
	camera = Camera::GetInstance();

	// マップデータ読み込み生成処理
	LoadStage();

	// プレイヤーの生成
	GameObjectManager* object = GameObjectManager::GetInstance();
	player = object->CreateObject<Player>(Vector2D(32 * PLAYER_INITIAL_LOCATION, 400));

	// プレイヤー情報をカメラに渡す
	camera->SetPlayer(player);
	player->SetCamera(camera);
	// カメラの初期化
	camera->Initialize();
	// カメラの情報を親クラスに渡す
	__super::SetCamera(camera);

}

eSceneType InGame::Update(const float& delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	// リザルトシーンに遷移する
	if (input->GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return eSceneType::result;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START) == eInputState::Pressed)
	{
		return eSceneType::result;
	}
	if (player->GetIsDeath() == true)
	{
		return eSceneType::result;
	}

	// 親クラスのアニメーション制御を呼び出す
	__super::AnimationControl(delta_second, true);

	// カメラの更新
	camera->Update();

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

void InGame::Draw() const
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/Back.csv";
	// BackGround
	// back

	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;

	// ファイル内の文字を確認していく
	while (true)
	{
		//描画する座標を計算
		Vector2D location;
		location.x = (float)(x * BOX_SIZE) + D_WIN_MAX_X / 2 - camera->GetCameraPos().x + BOX_SIZE / 2;
		location.y = (float)(y * BOX_SIZE + BOX_SIZE/2);

		// ファイルから1文字抽出する
		int c = fgetc(fp);

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
		// 抽出した文字がBなら、描画しないで次の文字を見に行く
		else if (c == 'B')
		{
			x++;
		}
		// 抽出した文字がSなら、空を描画
		else if(c == 'S')
		{
			DrawRotaGraph(location.x, location.y, 1.0, 0.0, sky_image, TRUE);
			x++;
		}
		// 抽出した文字がLなら、葉を描画
		else if (c == 'L')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '0':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, leaf_image[0], TRUE);
				break;
			case '1':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, leaf_image[1], TRUE);
				break;
			case '2':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, leaf_image[2], TRUE);
				break;
			}
			x++;
		}
		// 抽出した文字がMなら、山を描画
		else if (c == 'M')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '0':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[0], TRUE);
				break;
			case '1':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[1], TRUE);
				break;
			case '2':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[2], TRUE);
				break;
			case '3':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[3], TRUE);
				break;
			case '4':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[4], TRUE);
				break;
			case '5':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[5], TRUE);
				break;
			}
			x++;
		}
		// 抽出した文字がCなら、雲を描画
		else if (c == 'C')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '0':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[0], TRUE);
				break;
			case '1':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[1], TRUE);
				break;
			case '2':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[2], TRUE);
				break;
			case '3':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[3], TRUE);
				break;
			case '4':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[4], TRUE);
				break;
			case '5':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[5], TRUE);
				break;
			}
			x++;
		}
	}
	// 開いたファイルを閉じる
	fclose(fp);

	// 親クラスの描画処理を呼び出す
	__super::Draw();

	// UIの描画
	// スコアの描画
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraph(90 + (i * 19), 55, 1.1, 0.0, num[0], TRUE);
	}
	//コイン枚数描画
	DrawRotaGraph(255, 55, 1.1, 0.0, num[11], TRUE);
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(275 + (i * 19), 55, 1.1, 0.0, num[0], TRUE);
	}
	// ステージ名の描画
	DrawRotaGraph(399, 55, 1.1, 0.0, num[10], TRUE);
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(380 + (i * 38), 55, 1.1, 0.0, num[1], TRUE);
	}
	// タイムの描画
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(514 + (i * 19), 55, 1.1, 0.0, num[0], TRUE);
	}

	SetFontSize(16);
	DrawFormatString(10, 80, 0xffffff, "A:左移動");
	DrawFormatString(100, 80, 0xffffff, "D:右移動");
	DrawFormatString(200, 80, 0xffffff, "W:ジャンプ");
	DrawFormatString(1, 1, 0xffffff, "InGame");
	SetFontSize(32);

}

void InGame::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();

	// プレイヤーの削除
	object->DestroyObject(player);


}

const eSceneType InGame::GetNowSceneType() const
{
	return eSceneType::in_game;
}

// ステージ生成処理
void InGame::LoadStage()
{
	GameObjectManager* object = GameObjectManager::GetInstance();
	
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/Stage.csv";
	// BackGround
	// back

	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;

	// ファイル内の文字を確認していく
	while (true)
	{
		 //座標計算
		Vector2D location;
		location.x = (float)(x * BOX_SIZE + BOX_SIZE / 2) + (camera->GetCameraPos().x);
		location.y = (float)(y * BOX_SIZE + BOX_SIZE / 2);

		// ファイルから1文字抽出する
		int c = fgetc(fp);

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		// 抽出した文字が空白文字なら、生成しないで次の文字を見に行く
		else if (c == ' ')
		{
			break;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
		else if (c == '0')
		{
			x++;
		}
		else if (c == 'F')
		{
			object->CreateObject<Floor>(Vector2D(location.x, location.y));
			x++;
		}
		else if (c == 'H')
		{
			object->CreateObject<Hatena>(Vector2D(location.x, location.y));
			x++;
		}
		else if (c == 'B')
		{
			object->CreateObject<Block>(Vector2D(location.x, location.y));
			x++;
		}
		else if (c == 'S')
		{
			object->CreateObject<Stairs>(Vector2D(location.x, location.y));
			x++;
		}
		else if (c == 'W')
		{
			WaterPipes* pipe;
			pipe = object->CreateObject<WaterPipes>(Vector2D(location.x, location.y));

			c = fgetc(fp);
			switch (c)
			{
			case '0':
				pipe->SetType(ePipeType::LEFT_DOWN);
				break;
			case '1':
				pipe->SetType(ePipeType::LEFT_UP);
				break;
			case '2':
				pipe->SetType(ePipeType::RIGHT_DOWN);
				break;
			case '3':
				pipe->SetType(ePipeType::RIGHT_UP);
				break;
			}
			x++;
		}
		else if (c == 'G')
		{
			Goal* goal;
			goal = object->CreateObject<Goal>(Vector2D(location.x, location.y));

			c = fgetc(fp);

			switch (c)
			{
			case '0':
				goal->SetType(eGoalType::Pool);
				break;
			case '1':
				goal->SetType(eGoalType::Bool);
				break;
			case '2':
				goal->SetType(eGoalType::Flag);
				break;
			}
			x++;
		}
		else if (c == 'E')
		{
			c = fgetc(fp);

			switch (c)
			{
			case '1':
				Goomba * goomba;
				goomba = object->CreateObject<Goomba>(Vector2D(location.x, location.y));
				goomba->SetCamera(camera);
				break;
			case '2':
				Koopa * koopa;
				koopa = object->CreateObject<Koopa>(Vector2D(location.x, location.y - 5.0f));
				koopa->SetCamera(camera);
				break;
			}
			x++;
		}
	}
	// 開いたファイルを閉じる
	fclose(fp);
}