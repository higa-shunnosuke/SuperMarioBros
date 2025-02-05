#pragma once

#include <vector>
#include <string>
#include "DxLib.h"

#include "../Utility/ProjectConfig.h"
#include "../Utility/ResourceManager.h"
#include "../Utility/Input/InputManager.h"
#include "../Utility/Input/InputEventManager.h"
#include "../Objects/GameObjectManager.h"
#include "../Utility/Camera/Camera.h"


/// <summary>
/// �V�[���^�C�v
/// </summary>
enum class eSceneType
{
	title,		// �^�C�g��
	in_game,	// �C���Q�[��
	re_start,	// ���X�^�[�g
	result,		// ���U���g
	exit,		// �I��
};

/// <summary>
/// �V�[�����N���X
/// </summary>
class SceneBase
{
protected:
	// �e�V�[�������L������
	int back_ground_sound;				// BGM
	int name_mario;						// �v���C���[�l�[��
	int world;							// �X�e�[�W
	int time;							// �^�C��
	int coin_image;						// �R�C��
	std::vector<int> string;			// ����
	std::vector<int> coin_animation_1;	// �R�C���i�n��j
	std::vector<int> coin_animation_2;	// �R�C���i�n���j
	float animation_time;				// �A�j���[�V��������
	int animation_count;				// �A�j���[�V�����Y��
	GameObjectManager* object;			// �I�u�W�F�N�g�}�l�[�W���[�̃|�C���^
	InputEventManager* input_event;		// �C���v�b�g�C�x���g�̃|�C���^
	Camera* camera;						// �J�����̃|�C���^


public:
	// �R���X�g���N�^
	SceneBase() :
		back_ground_sound(NULL),
		name_mario(NULL),
		world(NULL),
		time(NULL),
		coin_image(NULL),
		string(NULL),
		coin_animation_1(NULL),
		coin_animation_2(NULL),
		animation_time(0.0f),
		animation_count(0),
		object(nullptr),
		input_event(nullptr),
		camera(nullptr)
	{
		
	}
	// �f�X�g���N�^
	virtual ~SceneBase()
	{
		// ����Y��h�~
		Finalize();
	}

public:
	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize()
	{
		// �J�����̏����擾
		camera = Camera::GetInstance();

		// �I�u�W�F�N�g�}�l�[�W���[�̏����擾
		object = GameObjectManager::GetInstance();

		// �摜�̓ǂݍ���
		ResourceManager* rm = ResourceManager::GetInstance();
		name_mario = rm->GetImages("Resource/Images/UI/name_mario.png")[0];
		world = rm->GetImages("Resource/Images/UI/world.png")[0];
		time = rm->GetImages("Resource/Images/UI/time.png")[0];
		string = rm->GetImages("Resource/Images/UI/string.png", 26, 26, 1, 16, 16);
		coin_animation_1 = rm->GetImages("Resource/Images/UI/uicoin.png", 4, 4, 1, 16, 16);
		coin_animation_2 = rm->GetImages("Resource/Images/UI/uicoin_1.png", 4, 4, 1, 16, 16);

		// �V�[�������U���g�̂Ƃ��ǂݍ��މ摜��ύX
		if (GetNowSceneType() != eSceneType::result)
		{
			coin_image = coin_animation_1[0];
		}
		else
		{
			coin_image = coin_animation_2[0];
		}

		//���̓C�x���g�̃C���X�^���X���擾
		input_event = InputEventManager::GetInstance();
	}

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	/// <returns>���̃V�[���^�C�v���</returns>
	virtual eSceneType Update(const float& delta_second)
	{
		//�o�^����Ă�����̓C�x���g�̌Ăяo��
		input_event->InputActionEvent();

		// ��������I�u�W�F�N�g������΁A�I�u�W�F�N�g���X�g���ɑ}������
		object->CheckCreateObject();

		// ���X�g���̃I�u�W�F�N�g���X�V����
		for (GameObject* obj : object->GetObjectsList())
		{
			obj->Update(delta_second);
		}

		// �f�X�g���C���X�g�̍X�V
		object->CheckDestroyObject();

		// ���݂̃V�[������ԋp����
		return GetNowSceneType();
	}

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() const
	{
		// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��`�悷��
		for (GameObject* obj : object->GetObjectsList())
		{
			obj->Draw(camera->GetCameraPos());
		}

		/*****************�@UI�̕`��@************************/

		// ����L�������̕`��
		DrawRotaGraph(125, 35, 1.1, 0.0, name_mario, TRUE);
		
		// �R�C���̕`��
		DrawRotaGraph(235, 55, 1.1, 0.0, coin_image, TRUE);
		
		// �X�e�[�W���̕`��
		DrawRotaGraph(400, 35, 1.1, 0.0, world, TRUE);
		
		// �^�C���̕`��
		DrawRotaGraph(523, 35, 1.1, 0.0, time, TRUE);
	}

	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize()
	{
		// ���̓C�x���g�̍폜
		input_event->AllUnbind();

		// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��j��
		object->DestroyAllObject();
	}

	/// <summary>
	/// ���݂̃V�[���^�C�v�擾����
	/// </summary>
	/// <returns>���݂̃V�[���^�C�v���</returns>
	virtual const eSceneType GetNowSceneType() const = 0;

protected:
	/// <summary>
	/// ui�R�C���̃A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second,bool hierarchy)
	{
		animation_time += delta_second;
		if (animation_time >= (1.0f / 5.0f))
		{
			animation_time = 0.0f;
			animation_count++;
			if (animation_count >= 4)
			{
				animation_count = 0;
			}
			// �摜�̐ݒ�
			if (hierarchy = true)
			{
				coin_image = coin_animation_1[animation_count];
			}
			else
			{
				coin_image = coin_animation_2[animation_count];
			}

		}
	}
};

