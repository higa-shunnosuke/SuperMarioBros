#pragma once

#include "../Utility/Singleton.h"
#include "../Utility/Vector2D.h"
#include "../Utility/Camera/Camera.h"
#include "GameObject.h"

#include "string"
#include "vector"

// �Q�[���I�u�W�F�N�g�N���X
class GameObjectManager : public Singleton<GameObjectManager>
{
private:
	std::vector<GameObject*>	create_objects;		// �������s���I�u�W�F�N�g���X�g
	std::vector<GameObject*>	game_objects_list;	// �X�V�ƕ`����s���I�u�W�F�N�g���X�g
	std::vector<GameObject*>	destroy_objects;	// �j�����s���I�u�W�F�N�g���X�g

public:
	/// <summary>
	/// �I�u�W�F�N�g���X�g�̍X�V
	/// </summary>
	void CheckCreateObject()
	{
		// ��������I�u�W�F�N�g������΁A�I�u�W�F�N�g���X�g���ɑ}������
		if (!create_objects.empty())
		{
			for (GameObject* obj : create_objects)
			{
				// ���C���[������ɏ��Ԃ����ւ���
				int z_layer = obj->GetZLayer();
				std::vector<GameObject*>::iterator itr = game_objects_list.begin();	// �I�u�W�F�N�g���X�g�̐擪
				// ���X�g�̖����ɂȂ�܂ő�������
				for (; itr != game_objects_list.end(); itr++)
				{
					// Z���C���[���傫���ꏊ�ɗv�f��ǉ�����
					// �� itr->ZLayer{1, 1, 2, 3}�Az_layer = 2 �̎�
					//    itr->ZLayer{1, 1, 2, z_layer, 3}�Ƃ���
					if (z_layer < (*itr)->GetZLayer())
					{
						break;
					}
				}
				// ���X�g�̓r���ɑ}������
				game_objects_list.insert(itr, obj);
			}
			// �������X�g���������
			create_objects.clear();
		}
	}

	/// <summary>
	/// �f�X�g���C���X�g�̍X�V
	/// </summary>
	void CheckDestroyObject()
	{
		// �j�����X�g������łȂ��ꍇ�A���X�g���̃I�u�W�F�N�g��j������
		if (!destroy_objects.empty())
		{
			for (GameObject* obj : destroy_objects)
			{
				std::vector<GameObject*>::iterator itr = game_objects_list.begin();	// �I�u�W�F�N�g���X�g�̐擪
				// ���X�g�̖����ɂȂ�܂ő�������
				for (; itr != game_objects_list.end(); itr++)
				{
					// ���X�g���ɂ���΁A�폜����
					if ((*itr) == obj)
					{
						game_objects_list.erase(itr);
						obj->Finalize();
						delete obj;
						break;
					}
				}
			}
			// ���I�z��̊J��
			destroy_objects.clear();
		}
	}

	/// <summary>
	///  �I�u�W�F�N�g���X�擾����
	/// </summary>
	/// <returns></returns>
	const std::vector<GameObject*>& GetObjectsList() const
	{
		return game_objects_list;
	}

	/// <summary>
	/// �Q�[���I�u�W�F�N�g��������
	/// </summary>
	/// <typeparam name="OBJECT">��������Q�[���I�u�W�F�N�g�N���X</type_param>
	/// <param name="generate_location">�����ʒu</param>
	/// <returns>���������Q�[���I�u�W�F�N�g�̃|�C���^</returns>
	template <class T>
	T* CreateObject(const Vector2D& generate_location)
	{
		// ��������Q�[���I�u�W�F�N�g�N���X�𓮓I�m��
		T* new_instance = new T();
		// GameObjectBase���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);
		// �G���[�`�F�b�N
		if (new_object == nullptr)
		{
			// ���I�m�ۂ����������̊J��
			delete new_instance;
			// ��O�e�L�X�g��ʒm
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
			return nullptr;
		}
	
		// �I�u�W�F�N�g�̏�����
		new_object->Initialize();
		// �ʒu���̐ݒ�
		new_object->SetLocation(generate_location);
		// �����I�u�W�F�N�g���X�g�̖����Ɋi�[����
		create_objects.push_back(new_object);
		// ���������Q�[���I�u�W�F�N�g�̃|�C���^��Ԃ�
		return new_instance;
	}

	/// <summary>
	/// �I�u�W�F�N�g�j������
	/// </summary>
	/// <param name="target">�j�����s���Q�[���I�u�W�F�N�g�̃|�C���^</param>
	void DestroyObject(GameObject* target)
	{
		// �k���|�`�F�b�N
		if (target == nullptr)
		{
			return;
		}

		// �j���I�u�W�F�N�g���X�g���ɂ���΁A�ǉ����Ȃ�
		for (GameObject* obj : destroy_objects)
		{
			if (obj == target)
			{
				return;
			}
		}

		// �j�����s���I�u�W�F�N�g���X�g�ɒǉ�����
		destroy_objects.push_back(target);
	}

	/// <summary>
	/// �V�[�����I�u�W�F�N�g�j������
	/// </summary>
	void DestroyAllObject()
	{
		// �I�u�W�F�N�g���X�g����Ȃ珈�����I������
		if (game_objects_list.empty())
		{
			return;
		}
		// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���폜����
		for (GameObject* obj : game_objects_list)
		{
			obj->Finalize();
			delete obj;
		}
		// ���I�z��̉��
		game_objects_list.clear();
	}
};