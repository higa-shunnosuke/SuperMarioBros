#include "InputEventManager.h"

void InputEventManager::InputActionEvent()
{
	//���͊Ǘ��N���X�̃C���X�^���X���擾����
	InputManager* input = InputManager::GetInstance();

	//�L�[�{�[�h���̓C�x���g������΁A
	//�L�[�{�[�h���̓C�x���g�̎��s
	if (!keycode_event.empty())
	{
		for (EventSender sender : keycode_event)
		{
			/*if (input->GetKeyState(sender.input_id) == sender.event_state &&
				sender.value != 0.0f)
			{
				sender.call_base_func->Invoke();
			}
			else */if (input->GetKeyState(sender.input_id) == sender.event_state &&
				sender.event_state != eInputState::None)
			{
				sender.call_base_func->Invoke();
			}
			else if (input->GetKeyState(sender.input_id) == eInputState::Hold)
			{
				sender.call_base_func->Invoke(sender.value);
			}
		}
	}
}

void InputEventManager::AllUnbind()
{
	//�o�^����Ă���C�x���g���e���폜����
	if (!keycode_event.empty())
	{
		for (EventSender sender : keycode_event)
		{
			delete sender.call_base_func;
			sender.call_base_func = nullptr;
		}
		keycode_event.clear();
	}
}