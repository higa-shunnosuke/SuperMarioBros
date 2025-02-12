#pragma once

#include "../Character.h"
#include "../../../Utility/Camera/Camera.h"

class Goomba : public Character
{
private:
	std::vector<int> animation1;		//�ړ��̃A�j���[�V�����摜
	bool is_hit;   // ��x����������Ԃ��ǂ���

	int step_s;    // ���܂ꂽ�Ƃ��̉�

public:
	Goomba();
	~Goomba();
	Camera* camera;

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

	/// <summary>
	/// �J�����̏����擾
	/// </summary>
	void SetCamera(Camera* camera);

private:
	/// <summary>
	/// �ړ�����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void Movement(float delta_second);

	/// <summary>
	/// �A�j���[�V��������
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	void AnimationControl(float delta_second);


};

