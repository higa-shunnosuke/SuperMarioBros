#pragma once

#include "InputManager.h"
#include "vector"
#include "../Singleton.h"

//�C�x���g���N���X
__interface BaseEvent
{
public:
	virtual void Invoke(float param = 0.0f) = 0;
};

//float�^�̈��������֐��C�x���g�N���X
template <class T>
class FEvent :public BaseEvent
{
private:
	T* object;
	void (T::* function)(float);

public:
	FEvent(T* object, void (T::* function)(float))
	{
		this->object = object;
		this->function = function;
	}

	void Invoke(float param = 0.0f) override
	{
		(object->*function)(param);
	}
};

//�����������Ȃ��֐��C�x���g�N���X
template <class T>
class VEvent :public BaseEvent
{
private:
	T* object;
	void (T::* function)(void);

public:
	VEvent(T* object, void (T::* function)(void))
	{
		this->object = object;
		this->function = function;
	}

	void Invoke(float param) override
	{
		(object->*function)();
	}
};

//�֐��C�x���g�ďo�N���X
class EventSender
{
public:
	BaseEvent* call_base_func = nullptr;
	int input_id = 0;
	eInputState event_state = eInputState::None;
	float value = 0.0f;
};

//���̓C�x���g�Ǘ��N���X
class InputEventManager : public Singleton<InputEventManager>
{
private:
	std::vector<EventSender> keycode_event;

public:
	//�o�C���h���ꂽ���̓C�x���g�̌Ăяo��
	void InputActionEvent();

public:
	//�o�C���h�֐�
	template <class T>
	void ActionKeyBind(int keycode, eInputState state, T* object, void (T::* func)(void))
	{
		EventSender sender = {};
		sender.call_base_func = new VEvent<T>(object, func);
		sender.event_state = state;
		sender.input_id = keycode;
		keycode_event.push_back(sender);
	}

	template <class T>
	void ActionKeyBind(int keycode, float value, T* object, void (T::* func)(float))
	{
		EventSender sender = {};
		sender.call_base_func = new FEvent<T>(object, func);
		sender.value = value;
		sender.input_id = keycode;
		keycode_event.push_back(sender);
	}

	template <class T>
	void ActionKeyBind(int keycode, eInputState state, float value, T* object, void (T::* func)(float))
	{
		EventSender sender = {};
		sender.call_base_func = new FEvent<T>(object, func);
		sender.event_state = state;
		sender.value = value;
		sender.input_id = keycode;
		keycode_event.push_back(sender);
	}

	//�o�C���h�����֐�
	void AllUnbind();
};