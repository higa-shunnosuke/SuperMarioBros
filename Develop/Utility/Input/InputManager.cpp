#include "InputManager.h"
#include "DxLib.h"

/// <summary>
/// �X�V����
/// </summary>
void InputManager::Update()
{
	// �L�[���͒l�̍X�V
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));
	GetHitKeyStateAll(now_key);

	// �R���g���[���[���͒l�̍X�V
	XINPUT_STATE input = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	for (int i = 0; i < D_BUTTON_MAX; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = static_cast<bool>(input.Buttons[i]);
	}
	trigger[0] = TriggerNormalize(input.LeftTrigger);
	trigger[1] = TriggerNormalize(input.RightTrigger);
	stick[0].x = StickNormalize(input.ThumbLX);
	stick[0].y = StickNormalize(input.ThumbLY);
	stick[1].x = StickNormalize(input.ThumbRX);
	stick[1].y = StickNormalize(input.ThumbRY);

	//�}�E�X�̓��͒l�X�V

}

/// <summary>
	/// �L�[�{�[�h�̓��͏�Ԃ��m�F����
	/// </summary>
	/// <param name="button">���蓖�Ă�ꂽ�L�[</param>
	/// <returns>�������u�ԁFPressed�A�����Ă���ԁFHold�A�������u�ԁFReleased</returns>
eInputState InputManager::GetKeyState(int keycode) const
{
	if (CheckKeyCodeRange(keycode))
	{
		if (old_key[keycode] == TRUE)
		{
			if (now_key[keycode] == TRUE)
			{
				return eInputState::Hold;
			}
			else
			{
				return eInputState::Released;
			}
		}
		else
		{
			if (now_key[keycode] == TRUE)
			{
				return eInputState::Pressed;
			}
			else
			{
				return eInputState::None;
			}
		}
	}
	return eInputState::None;
}

/// <summary>
/// �R���g���[���[�̓��͏�Ԃ��m�F����
/// </summary>
/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
/// <returns>�������u�ԁFPressed�A�����Ă���ԁFHold�A�������u�ԁFReleased</returns>
eInputState InputManager::GetButtonState(int button) const
{
	if (CheckButtonRange(button))
	{
		if (old_button[button] == TRUE)
		{
			if (now_button[button] == TRUE)
			{
				return eInputState::Hold;
			}
			else
			{
				return eInputState::Released;
			}
		}
		else
		{
			if (now_button[button] == TRUE)
			{
				return eInputState::Pressed;
			}
			else
			{
				return eInputState::None;
			}
		}
	}
	return eInputState::None;
}

///// <summary>
///// �}�E�X�̓��͏�Ԃ��m�F����
///// </summary>
///// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
///// <returns>�������u�ԁFPressed�A�����Ă���ԁFHold�A�������u�ԁFReleased</returns>
//eInputState InputManager::GetMouseButtonState(int mousemouse_buttonbutton) const
//{
//
//}

/// <summary>
/// ���g���K�[���͏�Ԏ擾
/// </summary>
/// <returns>���g���K�[���͏��(0.0f�`1.0f)</returns>
float InputManager::GetLeftTrigger() const
{
	return trigger[0];
}

/// <summary>
/// �E�g���K�[���͏�Ԏ擾
/// </summary>
/// <returns>�E�g���K�[���͏��(0.0f�`1.0f)</returns>
float InputManager::GetRightTrigger() const
{
	return trigger[1];
}

/// <summary>
/// ���X�e�B�b�N���͏�Ԏ擾
/// </summary>
/// <returns>���X�e�B�b�N���͏��(-1.0f�`1.0f)</returns>
Vector2D InputManager::GetLeftStick() const
{
	return stick[0];
}

/// <summary>
/// �E�X�e�B�b�N���͏�Ԏ擾
/// </summary>
/// <returns>�E�X�e�B�b�N���͏��(-1.0f�`1.0f)</returns>
Vector2D InputManager::GetRightStick() const
{
	return stick[1];
}

/// <summary>
/// �g���K�[���͒l�̐��K��
/// </summary>
/// <param name="value">�g���K�[���͒l</param>
/// <returns>���͒l�𐳋K�������l</returns>
float InputManager::TriggerNormalize(unsigned char value)
{
	float result = 0.0f;

	result = (float)value / (float)UCHAR_MAX;

	return result;
}

/// <summary>
/// �X�e�B�b�N���͒l�̐��K��
/// </summary>
/// <param name="value">�X�e�B�b�N���͒l</param>
/// <returns>���͒l�𐳋K�������l</returns>
float InputManager::StickNormalize(short value)
{
	float result = 0.0f;

	if (value >= 0)
	{
		result = (float)value / (float)SHRT_MAX;
	}
	else
	{
		result = -((float)value / (float)SHRT_MIN);
	}

	return result;
}

/// <summary>
/// ���蓖�ăL�[�R�[�h�͈͓��`�F�b�N����
/// </summary>
/// <param name="button">���蓖�Ă�ꂽ�L�[�R�[�h</param>
/// <returns>�͈͓��Ȃ�Atrue</returns>
bool InputManager::CheckKeyCodeRange(int key_code) const
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

/// <summary>
/// ���蓖�ă{�^���͈͓��`�F�b�N����
/// </summary>
/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
/// <returns>�͈͓��Ȃ�Atrue</returns>
bool InputManager::CheckButtonRange(int button) const

{
	return (0 <= button && button < D_BUTTON_MAX);
}
