#pragma once

#include "PlayerStateBase.h"

///<summary>
///��~���
///</summary>
class Fire :public PlayerStateBase
{
private:
	

public:
	///<summary>
	///�R���X�g���N�^
	///</summary>
	///<param name="p">�v���C���[���</param>
	Fire(class Player* p);

	//�f�X�g���N�^
	virtual ~Fire();

public:
	//����������
	virtual void Initialize() override;

	//�I��������
	virtual void Finalize() override;

	//�X�V����
	virtual void Update() override;

	//�`�揈��
	virtual void Draw(const Vector2D camera_pos) const override;

	//���݂̃X�e�[�g�����擾����
	virtual ePlayerState GetState() const override;
};

