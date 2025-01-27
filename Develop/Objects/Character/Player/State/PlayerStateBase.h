#pragma once
#include "../Player.h"
#include "../../../../Utility/Input/InputManager.h"
#include "../../../../Utility/ResourceManager.h"


///<summary>
///�v���C���[��ԊǗ��p�̃x�[�X�N���X
///</summary>
class PlayerStateBase
{
protected:
	class Player* player;			//�v���C���[���
	std::vector<int> animation;		//�ړ��̃A�j���[�V�����摜
	Vector2D box_size;				//�v���C���[�̓����蔻��

public:
	///<summary>
	///�R���X�g���N�^
	///</summary>
	///<param name="p">�v���C���[���</param>
	PlayerStateBase(class Player* p) :
		player(p)
	{

	}

	//�f�X�g���N�^
	virtual ~PlayerStateBase() = default;

public:
	//�����������֐�
	virtual void Initialize() = 0;

	//�I���������֐�
	virtual void Finalize() = 0;

	//�X�V����
	virtual void Update() = 0;

	//�`�揈��
	virtual void Draw(const Vector2D camera_pos) const = 0;

	//��Ԃ̎擾
	virtual ePlayerState GetState() const = 0;

	//�����蔻��擾����
	Vector2D GetPlayerSize()
	{
		return box_size;
	}
};