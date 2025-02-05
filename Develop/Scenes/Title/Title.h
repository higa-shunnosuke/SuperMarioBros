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
	// �R���X�g���N�^
	Title();
	// �f�X�g���N�^
	virtual ~Title();

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
};

