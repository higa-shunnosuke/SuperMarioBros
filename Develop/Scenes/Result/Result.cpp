#include "Result.h"
#include "../../Objects/Character/Player/Player.h"

Result::Result() :
	num(NULL)
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();
}

Result::~Result()
{

}

void Result::Initialize()
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();

	// �摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);
}

eSceneType Result::Update(const float& delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// �C���Q�[���V�[���ɑJ�ڂ���
	if (input->GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return eSceneType::title;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START) == eInputState::Pressed)
	{
		return eSceneType::title;
	}

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);

}

void Result::Draw() const
{
	// UI�̕`��
	// �X�R�A�̕`��
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraph(90 + (i * 19), 55, 1.1, 0.0, num[0], TRUE);
	}
	//�R�C�������`��
	DrawRotaGraph(255, 55, 1.1, 0.0, num[11], TRUE);
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(275 + (i * 19), 55, 1.1, 0.0, num[0], TRUE);
	}
	// �X�e�[�W���̕`��
	DrawRotaGraph(399, 55, 1.1, 0.0, num[10], TRUE);
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(380 + (i * 38), 55, 1.1, 0.0, num[1], TRUE);
	}
	// �^�C���̕`��
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(514 + (i * 19), 55, 1.1, 0.0, num[0], TRUE);
	}

	SetFontSize(60);
	DrawFormatString(120, 140, 0xffffff, "Result");
	SetFontSize(32);

	DrawFormatString(100, 300, 0xffffff, "Enter�������Ă�������");

	// �e�N���X�̕`�揈�����Ăяo��
 	__super::Draw();
}

void Result::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

const eSceneType Result::GetNowSceneType() const
{
	return eSceneType::result;
}
