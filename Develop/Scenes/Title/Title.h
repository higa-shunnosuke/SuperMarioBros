#pragma once

#include "..//SceneBase.h"

// �^�C�g���V�[��
class Title : public SceneBase
{
private:
	int back_ground_image;		// �w�i�摜
	int top;					// �g�b�v
	std::vector<int> num;		// ����
	std::vector<int> player;	// �v���C���[�摜

public:
	Title();
	virtual ~Title();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;
};

