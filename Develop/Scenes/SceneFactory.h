#pragma once

#include "SceneBase.h"
#include "Title/Title.h"
#include "InGame/InGame.h"
#include "Result/Result.h"

class SceneFactory
{
public:

	/// <summary>
	/// �V�[����������
	/// </summary>
	/// <param name="next_type">���̃V�[���^�C�v</param>
	/// <returns>���������V�[�����̃|�C���^</returns>
	static SceneBase* CreateScene(eSceneType next_type)
	{
		// �V�[���^�C�v�ɂ���āA��������V�[����؂�ւ���
		switch (next_type)
		{
		case eSceneType::title:
			return dynamic_cast<SceneBase*>(new Title());
		case eSceneType::in_game:
		case eSceneType::re_start:
			return dynamic_cast<SceneBase*>(new InGame());
		case eSceneType::result:
			return dynamic_cast<SceneBase*>(new Result());
		default:
			return nullptr;
		}
	}

};