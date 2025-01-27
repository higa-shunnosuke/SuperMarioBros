#pragma once

#include "../Vector2D.h"
#include "../Singleton.h"

// �}�N����`
#define	D_KEYCODE_MAX	(256)		// �L�[�{�[�h���͒l�ő吔
#define D_BUTTON_MAX	(16)		// �R���g���[���[�̓��̓{�^���ő吔

//�L�[���͏��
enum class eInputState :unsigned char
{
	None,
	Pressed,
	Released,
	Hold,
};

/// <summary>
/// ���͊Ǘ��N���X�iSingleton�j
/// </summary>
class InputManager : public Singleton<InputManager>
{
private:
	// �L�[���͏��
	char now_key[D_KEYCODE_MAX];		// ���݂̓��͒l
	char old_key[D_KEYCODE_MAX];		// �O��̓��͒l

	// �R���g���[���[���͏��
	bool now_button[D_BUTTON_MAX];		// ���݂̃{�^�����͒l
	bool old_button[D_BUTTON_MAX];		// �O��̃{�^�����͒l
	float trigger[2];					// �g���K�[���͒l�i0.0f�`1.0f�j
	Vector2D stick[2];					// �X�e�B�b�N���͒l�i-1.0f�`1.0f�j

public:
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

public:
	/// <summary>
	/// �L�[�{�[�h�̓��͏�Ԃ��m�F����
	/// </summary>
	/// <param name="button">���蓖�Ă�ꂽ�L�[</param>
	/// <returns>�������u�ԁFPressed�A�����Ă���ԁFHold�A�������u�ԁFReleased</returns>
	eInputState GetKeyState(int keycode) const;

	/// <summary>
	/// �R���g���[���[�̓��͏�Ԃ��m�F����
	/// </summary>
	/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
	/// <returns>�������u�ԁFPressed�A�����Ă���ԁFHold�A�������u�ԁFReleased</returns>
	eInputState GetButtonState(int buttoncode) const;

	///// <summary>
	///// �}�E�X�̓��͏�Ԃ��m�F����
	///// </summary>
	///// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
	///// <returns>�������u�ԁFPressed�A�����Ă���ԁFHold�A�������u�ԁFReleased</returns>
	//eInputState GetMouseButtonState(int mouse_button) const;

	/// <summary>
	/// ���g���K�[���͏�Ԏ擾
	/// </summary>
	/// <returns>���g���K�[���͏��(0.0f�`1.0f)</returns>
	float GetLeftTrigger() const;

	/// <summary>
	/// �E�g���K�[���͏�Ԏ擾
	/// </summary>
	/// <returns>�E�g���K�[���͏��(0.0f�`1.0f)</returns>
	float GetRightTrigger() const;

	/// <summary>
	/// ���X�e�B�b�N���͏�Ԏ擾
	/// </summary>
	/// <returns>���X�e�B�b�N���͏��(-1.0f�`1.0f)</returns>
	Vector2D GetLeftStick() const;

	/// <summary>
	/// �E�X�e�B�b�N���͏�Ԏ擾
	/// </summary>
	/// <returns>�E�X�e�B�b�N���͏��(-1.0f�`1.0f)</returns>
	Vector2D GetRightStick() const;

private:
	/// <summary>
	/// �g���K�[���͒l�̐��K��
	/// </summary>
	/// <param name="value">�g���K�[���͒l</param>
	/// <returns>���͒l�𐳋K�������l</returns>
	float TriggerNormalize(unsigned char value);

	/// <summary>
	/// �X�e�B�b�N���͒l�̐��K��
	/// </summary>
	/// <param name="value">�X�e�B�b�N���͒l</param>
	/// <returns>���͒l�𐳋K�������l</returns>
	float StickNormalize(short value);

	/// <summary>
	/// ���蓖�ăL�[�R�[�h�͈͓��`�F�b�N����
	/// </summary>
	/// <param name="key_code">���蓖�Ă�ꂽ�L�[�R�[�h</param>
	/// <returns>�͈͓��Ȃ�Atrue</returns>
	bool CheckKeyCodeRange(int key_code) const;

	/// <summary>
	/// ���蓖�ă{�^���͈͓��`�F�b�N����
	/// </summary>
	/// <param name="button">���蓖�Ă�ꂽ�{�^��</param>
	/// <returns>�͈͓��Ȃ�Atrue</returns>
	bool CheckButtonRange(int button) const;

};