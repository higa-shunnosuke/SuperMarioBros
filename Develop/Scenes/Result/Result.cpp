#include "Result.h"
#include "../../Objects/Character/Player/Player.h"

Result::Result() :
	num(NULL)
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();
}

Result::~Result()
{

}

void Result::Initialize()
{
	// 親クラスの初期化処理を呼び出す
	__super::Initialize();

	// 画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);
}

eSceneType Result::Update(const float& delta_second)
{
	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	// インゲームシーンに遷移する
	if (input->GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return eSceneType::title;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START) == eInputState::Pressed)
	{
		return eSceneType::title;
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);

}

void Result::Draw() const
{
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

	SetFontSize(60);
	DrawFormatString(120, 140, 0xffffff, "Result");
	SetFontSize(32);

	DrawFormatString(100, 300, 0xffffff, "Enterを押してください");

	// 親クラスの描画処理を呼び出す
 	__super::Draw();
}

void Result::Finalize()
{
	// 親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType Result::GetNowSceneType() const
{
	return eSceneType::result;
}
