#pragma once

#include "BlockBase.h"
#include "../Character/Player/Player.h"
#include <string>
#include <vector>

enum class eWarpType {
	ENTRANCE,	// ����
	EXit		// �o��
};

class WarpBox :public BlockBase
{
public:
	int pair_no;				// �y�A�ԍ�
	eWarpType type;				// �^�C�v
	WarpBox* exit;				// �o���̃|�C���^
	Vector2D exit_location;		// �o���̍��W

public:
	WarpBox();
	~WarpBox();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;

	/// <summary>
	/// �y�A�ݒ菈��
	/// </summary>
	/// <param name="nomber">�y�A�ԍ�</param>
	void SetPair(int nomber);

	/// <summary>
	/// �y�A�ԍ��擾����
	/// </summary>
	/// <retrun>�y�A�ԍ�</return>
	int GetPairNo();

	/// <summary>
	/// �^�C�v�ݒ菈��
	/// </summary>
	/// <param name="type">�^�C�v</param>
	void SetType(eWarpType type);

	/// <summary>
	/// �^�C�v�擾����
	/// </summary>
	/// <retrun>�^�C�v</return>
	eWarpType GetType();

	/// <summary>
	/// �o�����ݒ菈��
	/// </summary>
	/// <param name="location">�o�����</param>
	void SetExit(Vector2D location);


};

