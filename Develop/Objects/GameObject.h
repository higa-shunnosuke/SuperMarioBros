#pragma once

#include "DxLib.h"
#include "../Utility/Collision.h"
#include "../Utility/ProjectConfig.h"

// �Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D			location;		// �ʒu���W
	Collision			collision;		// �����蔻����
	int					image;			// �摜���
	int					z_layer;		// ���C���[���
	bool				is_mobility;	// ����

public:
	GameObject();
	virtual ~GameObject();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">1�t���[��������̎���</param>
	virtual void Update(float delta_second);
	/// <summary>
	/// �`�揈��
	/// </summary>
	virtual void Draw(const Vector2D camera_pos) const;
	/// <summary>
	/// �I��������
	/// </summary>
	virtual void Finalize();

public:
	/// <summary>
	/// �����蔻��ʒm����
	/// </summary>
	/// <param name="hit_object">���������Q�[���I�u�W�F�N�g�̃|�C���^</param>
	virtual void OnHitCollision(GameObject* hit_object);

public:
	/// <summary>
	/// �ʒu���W�擾����
	/// </summary>
	/// <returns>�ʒu���W���</returns>
	const Vector2D& GetLocation() const;

	/// <summary>
	/// �ʒu���ύX����
	/// </summary>
	/// <param name="location">�ύX�������ʒu���</param>
	void SetLocation(const Vector2D& location);

	/// <summary>
	/// �����蔻��擾����
	/// </summary>
	/// <returns>�����蔻����</returns>
	const Collision& GetCollision() const;

	/// <summary>
	/// �y���C���[���擾����
	/// </summary>
	/// <returns>�y���C���[���</returns>
	const unsigned char GetZLayer() const;

	/// <summary>
	/// �������̎擾����
	/// </summary>
	/// <returns>�������</returns>
	const bool GetMobility() const;
};