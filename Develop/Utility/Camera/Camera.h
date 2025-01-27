#pragma once

#include "../../Objects/Character/Player/Player.h"
#include "../Singleton.h"

class Camera : public Singleton<Camera>
{
private:
	Player* player;		// �v���C���[���
	Vector2D location;	// �J�������W

public:
	// �R���X�g���N�^
	Camera();
	// �f�X�g���N�^
	~Camera();

public:
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	///  ���s����
	/// </summary>
	void Update();

	/// <summary>
	/// �J�������W�擾����
	/// </summary>
	/// <returns>�J�������W</returns>
	Vector2D GetCameraPos();

	/// <summary>
	/// �v���C���[���ݒ菈��
	/// </summary>
	/// <param name="player">�v���C���[���</param>
	void SetPlayer(Player* player);
};

