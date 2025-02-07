#include "SceneManager.h"
#include "SceneFactory.h"
#include "DxLib.h"

#include "../Utility/Input/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "../Objects/GameObjectManager.h"
#include "../Objects/GameObject.h"


// �R���X�g���N�^
SceneManager::SceneManager() :
	current_scene(nullptr)
{

}

// �f�X�g���N
SceneManager::~SceneManager()
{
	// ����Y��h�~
	Finalize();
}

// ����������
void SceneManager::Initialize()
{
	// �ŏ��̃V�[�����^�C�g����ʂɂ���
	ChangeScene(eSceneType::in_game);

}

//  �X�V����
void SceneManager::Update(float delta_second)
{
	// �V�[���̍X�V
	eSceneType next_scene_type = current_scene->Update(delta_second);

	GameObjectManager* object;			// �I�u�W�F�N�g�}�l�[�W���[�̃|�C���^
	object = GameObjectManager::GetInstance();

	// �I�u�W�F�N�g���X�g���擾
	std::vector<GameObject*> objects_list = object->GetObjectsList();

	// �����蔻��m�F����
	for (int i = 0; i < objects_list.size(); i++)
	{
		// �����Ȃ��I�u�W�F�N�g�̏ꍇ�����蔻��m�F���������Ȃ�
		if (objects_list[i]->GetMobility() == false)
		{
			continue;
		}
		else
		{
			for (int j = 0; j < objects_list.size(); j++)
			{
				if (i == j)
				{
					continue;
				}

				// �����蔻��m�F����
				CheckCollision(objects_list[i], objects_list[j]);
			}
		}
	}

	// �t�H���g�T�C�Y�ύX
	SetFontSize(32);

	// �`�揈��
	Draw();

	// ���݂̃V�[���^�C�v�����̃V�[���^�C�v�ƈ���Ă��邩�H
	if (current_scene->GetNowSceneType() != next_scene_type)
	{
		// �V�[���؂�ւ�����
		ChangeScene(next_scene_type);
	}
}

// �I��������
void SceneManager::Finalize()
{
	// �V�[����񂪐�������Ă���΁A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
		current_scene = nullptr;
	}
}

// �`�揈��
void SceneManager::Draw() const
{
	// ��ʂ̏�����
	ClearDrawScreen();

	// �V�[���̕`�揈��
	current_scene->Draw();

	// ����ʂ̓��e��\��ʂɔ��f����
	ScreenFlip();
}

// �V�[���؂�ւ�����
void SceneManager::ChangeScene(eSceneType next_type)
{
	// ���̃V�[���𐶐�����
	SceneBase* next_scene = SceneFactory::CreateScene(next_type);

	// �G���[�`�F�b�N
	if (next_scene == nullptr)
	{
		throw ("�V�[���������ł��܂���ł���\n");
	}

	// �V�[����񂪊i�[����Ă�����A�폜����
	if (current_scene != nullptr)
	{
		current_scene->Finalize();
		delete current_scene;
	}

	// ���̃V�[���̏�����
	next_scene->Initialize();

	// ���݃V�[���̏㏑��
	current_scene = next_scene;
}

/// �����蔻��m�F����
void SceneManager::CheckCollision(GameObject* target, GameObject* partner)
{
	// �k���|�`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// �����蔻������擾
	Collision tc = target->GetCollision();
	Collision pc = partner->GetCollision();

	if (tc.is_blocking == false || pc.is_blocking == false)
	{
		return;
	}

	// �����蔻�肪�L�����m�F����
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		//�Q�̃I�u�W�F�N�g�̋������擾
		Vector2D diff = target->GetLocation() - partner->GetLocation();

		//�Q�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
		Vector2D box_size = (tc.box_size + pc.box_size) / 2.0f;
		
		// ��`���m�̓����蔻��
		if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
		{
			// �������Ă��邱�Ƃ�ʒm����
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}
	}
}