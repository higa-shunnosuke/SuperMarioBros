#pragma once

#include "../SceneBase.h"
#include "../../Objects/Character/Player/Player.h"

#define SIZE_X 211
#define SIZE_Y 16

class InGame : public SceneBase
{
private:
	int	score;						//�X�R�A
	std::vector<int> num;			// ����
	Player* player;					// �v���C���[���
	Camera* camera;					// �J�������
	int sky_image;
	int leaf_image[3];				// �t�̉摜
	int mountain_image[6];			// �R�̉摜
	int cloud_image[6];				// �_�̉摜

public:
	InGame();
	virtual ~InGame();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// ���݂̃V�[���^�C�v�����擾����
	virtual const eSceneType GetNowSceneType() const override;

private:
	// �X�e�[�W��������
	void LoadStage();
};

