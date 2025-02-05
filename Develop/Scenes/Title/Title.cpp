#include "Title.h"
#include "DxLib.h"

// コンストラクタ
Title::Title() :
	back_ground_image(NULL),
	top(NULL),
	num(NULL),
	player(NULL)
{

}

// デストラクタ
Title::~Title()
{

}

// 初期化処理
void Title::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];
	top = rm->GetImages("Resource/Images/UI/top.png")[0];
	num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);
	player = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
}

// 更新処理
eSceneType Title::Update(const float& delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	// インゲームシーンに遷移する
	if (input->GetKeyState(KEY_INPUT_RETURN)==eInputState::Pressed)
	{
		return eSceneType::in_game;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START)== eInputState::Pressed)
	{
		return eSceneType::in_game;
	}

	// 親クラスのアニメーション制御を呼び出す
	__super::AnimationControl(delta_second,true);

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

// 描画処理
void Title::Draw() const
{
	// 背景画像の描画
	DrawRotaGraph(D_WIN_MAX_X/2, D_WIN_MAX_Y/2, 1.0, 0.0, back_ground_image, TRUE);

	/*************************　UIの描画　***************************/

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
	// トップの描画
	DrawRotaGraph(285, 380, 1.1, 0.0, top, TRUE);
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraph(350 + (i * 19), 380, 1.1, 0.0, num[0], TRUE);
	}
	// プレイヤーの描画
	DrawRotaGraph(32 * 3, 480 - 32 * 2 - 16, 1.0, 0.0, player[0], TRUE);

	
	DrawFormatString(100, 300, 0xffffff, "Enterを押してください");

	// 親クラスの描画処理を呼び出す
	__super::Draw();

}

// 終了処理
void Title::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

// 現在のシーンタイプ取得処理
const eSceneType Title::GetNowSceneType() const
{
	return eSceneType::title;
}
