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
	int sky_image;					// ��̉摜
	int leaf_image[3];				// �t�̉摜
	int mountain_image[6];			// �R�̉摜
	int cloud_image[6];				// �_�̉摜

public:
	// �R���X�g���N�^
	InGame();
	// �f�X�g���N�^
	virtual ~InGame();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	/// <returns>���̃V�[���^�C�v���</returns>
	virtual eSceneType Update(const float& delta_second) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw() const override;

	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize() override;

	/// <summary>
	/// ���݂̃V�[���^�C�v�����擾����
	/// </summary>
	/// <returns>���݂̃V�[���^�C�v</returns>
	virtual const eSceneType GetNowSceneType() const override;

private:
	/// <summary>
	/// �X�e�[�W�̐�������
	/// </summary>
	void LoadStage();
};

