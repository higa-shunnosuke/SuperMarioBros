#pragma once

#include "../Character.h"

// �J�����N���X�ւ̎Q��
class Camera;

enum class ePlayerState {
	NOMAL = 0,	//�m�[�}���}���I
	SUPER,		//�X�[�p�[�}���I
	FIRE,		//�t�@�C���}���I
	TIBI,		//�}���}���I
	NONE		//
};


class Player : public Character
{
private:
	bool is_run;					//�����Ă��邩�H
	bool is_star;					//�X�^�[��Ԃ��H
	bool is_death;					//����ł��邩�H
	class PlayerStateBase* state;	//���݂̏��
	ePlayerState next_state;		//���̏��
	float friction;					//���C
	Camera* camera;					//�J�������
	

public:
	Player();
	~Player();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;

	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObject* hit_object) override;

	///<summary>
	///����State��ݒ�
	/// </summary>
	/// <param name="init_location>����State</param>
	void SetNextState(ePlayerState next_state);

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);

	/// <summary>
	/// �W�����v����
	/// </summary>
	void Jump();

	/// <summary>
	/// ���Ⴊ�ݏ���
	/// </summary>
	void Squt();

	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);

	/// <summary>
	/// ���鏈��
	/// </summary>
	void Run();

public:
	/// <summary>
	/// �v���C���[���X�^�[��Ԃ��m�F����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	bool GetIsStar();

	/// <summary>
	/// �v���C���[������ł��邩�m�F����
	/// </summary>
	/// <returns>�v���C���[�̏��</returns>
	bool GetIsDeath();

	/// <summary>
	/// �J�����̏����擾
	/// </summary>
	void SetCamera(Camera* camera);
};
