#pragma once

#include "DxLib.h"

#include "Utility/Singleton.h"
#include "Utility/ProjectConfig.h"
#include "Utility/Input/InputManager.h"
#include "Scenes/SceneManager.h"

class Application : public Singleton<Application>
{
private:
	// �O���[�o���ϐ���`
	LONGLONG old_time;		// �O��v���l
	LONGLONG now_time;		// ���݌v���l
	float delta_second;		// �P�t���[��������̎���

public:
	bool WakeUp()
	{
		// �E�B���h�E���[�h�ŋN������
		ChangeWindowMode(TRUE);

		// �E�B���h�E�T�C�Y�̐ݒ�
		SetGraphMode(D_WIN_MAX_X, D_WIN_MAX_Y, D_COLOR_BIT);

		// �E�B���h�E�^�C�g���̐ݒ�
		SetWindowText("Game Development Pac-Man 2024");

		// �����������s��Ȃ�
		SetWaitVSyncFlag(FALSE);

		// Log.txt�t�@�C���̐�������iDebug���[�h�̂ݐ�������j
#if _DEBUG
		SetOutApplicationLogValidFlag(TRUE);
#else
		SetOutApplicationLogValidFlag(FALSE);
#endif // _DEBUG

		// Dx���C�u�����̏�����
		if (DxLib_Init() == D_FAILURE)
		{
			throw std::string("Dx���C�u�����̏������Ɏ��s���܂����I\n");
		}

		// �`����\��ʂɔ��f����
		SetDrawScreen(DX_SCREEN_BACK);

		// �V�[���}�l�[�W���[�𐶐�����
		SceneManager* manager = SceneManager::GetInstance();

		// ����������
		manager->Initialize();

		// ��A�N�e�B�u��Ԃł����삳����
		SetAlwaysRunFlag(TRUE);

		return true;
	}

	void Run()
	{
		// �V�[���}�l�[�W���[�𐶐�����
		SceneManager* manager = SceneManager::GetInstance();

		// ���͏����擾����
		InputManager* input = InputManager::GetInstance();

		// ���C�����[�v
		while (ProcessMessage() == D_SUCCESS)
		{			
			// ���͏��̍X�V
			input->Update();

			// �t���[�����[�g�̐���
			UpdateDeltaTime();

			// ���s����
			manager->Update(delta_second);
		
			// �Q�[�����I�����邩�m�F����
			if ((input->GetButtonState(XINPUT_BUTTON_BACK) == eInputState::Released) ||
				(input->GetKeyState(KEY_INPUT_ESCAPE) == eInputState::Released))
			{
				break;
			}
		}
	}

	void Shutdown()
	{
		// �V�[���}�l�[�W���[�𐶐�����
		SceneManager* manager = SceneManager::GetInstance();

		// �I��������
		manager->Finalize();

		// Dx���C�u�����̎g�p���I������
		DxLib_End();
	}

private:
	void UpdateDeltaTime()
	{
		// ���ݎ��Ԃ̎擾�i�ʕb�j
		now_time = GetNowHiPerformanceCount();

		// �J�n���Ԃ��猻�ݎ��Ԃ܂łɌo�߂������Ԃ��v�Z����i�ʕb�j
		// ����\���ʕb���b�ɕϊ�����
		delta_second = (float)(now_time - old_time) * 1.0e-6f;

		// �v���J�n���Ԃ��X�V����
		old_time = now_time;

		// �f�B�X�v���C�̃��t���b�V�����[�g���擾����
		float refresh_rate = (float)GetRefreshRate();

		// �P�t���[��������̎��Ԃ�1/���t���b�V�����[�g�b�𒴂�����A������
		if (delta_second > (1.0f / refresh_rate))
		{
			delta_second = (1.0f / refresh_rate);
		}
	}
};