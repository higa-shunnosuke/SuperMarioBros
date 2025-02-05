#include "Title.h"
#include "DxLib.h"

// �R���X�g���N�^
Title::Title() :
	back_ground_image(NULL),
	top(NULL),
	num(NULL),
	player(NULL)
{

}

// �f�X�g���N�^
Title::~Title()
{

}

// ����������
void Title::Initialize()
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();

	// �摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	back_ground_image = rm->GetImages("Resource/Images/title.png")[0];
	top = rm->GetImages("Resource/Images/UI/top.png")[0];
	num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);
	player = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
}

// �X�V����
eSceneType Title::Update(const float& delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// �C���Q�[���V�[���ɑJ�ڂ���
	if (input->GetKeyState(KEY_INPUT_RETURN)==eInputState::Pressed)
	{
		return eSceneType::in_game;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START)== eInputState::Pressed)
	{
		return eSceneType::in_game;
	}

	// �e�N���X�̃A�j���[�V����������Ăяo��
	__super::AnimationControl(delta_second,true);

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

// �`�揈��
void Title::Draw() const
{
	// �w�i�摜�̕`��
	DrawRotaGraph(D_WIN_MAX_X/2, D_WIN_MAX_Y/2, 1.0, 0.0, back_ground_image, TRUE);

	/*************************�@UI�̕`��@***************************/

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
	// �g�b�v�̕`��
	DrawRotaGraph(285, 380, 1.1, 0.0, top, TRUE);
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraph(350 + (i * 19), 380, 1.1, 0.0, num[0], TRUE);
	}
	// �v���C���[�̕`��
	DrawRotaGraph(32 * 3, 480 - 32 * 2 - 16, 1.0, 0.0, player[0], TRUE);

	
	DrawFormatString(100, 300, 0xffffff, "Enter�������Ă�������");

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

}

// �I������
void Title::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();
}

// ���݂̃V�[���^�C�v�擾����
const eSceneType Title::GetNowSceneType() const
{
	return eSceneType::title;
}
