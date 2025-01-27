#pragma once
#include <vector>
#include <map>

#include "Vector2D.h"
#include "Singleton.h"

#define BLOCK_SIZE 32
#define STAGE_WIDTH 20
#define STAGE_HEIGHT 16

/// <summary>
/// �p�l�����
/// </summary>
enum ePanelID : unsigned char
{
	SORA,
	FLOOR,
	NONE
};

/// <summary>
/// �X�e�[�W�̃p�l�����
/// </summary>
class StageData :public Singleton<StageData>
{
private:
	std::vector<std::vector<ePanelID>> data;

public:
	/// <summary>
	/// �S�Ẵp�l�������擾����
	/// </summary>
	/// <returns>�S�Ẵp�l�����</returns>
	static const std::vector<std::vector<ePanelID>> GetAll();

	/// <summary>
	/// ���ݍ��W�̃p�l�������擾����
	/// </summary>
	/// <param name="location">���ݍ��W</param>
	/// <returns>�p�l�����</returns>
	static const ePanelID GetPanelData(const Vector2D& location);

	/// <summary>
	/// ���W����Y���ɕϊ�����
	/// </summary>
	/// <param name="location">���W���</param>
	/// <param name="i">�ϊ���̓Y��</param>
	/// <param name="j">�ϊ���̓Y��</param>
	static void ConvertToIndex(const Vector2D& location, int& i, int& j);

private:
	/// <summary>
	/// �X�e�[�W�f�[�^��ǂݍ���
	/// </summary>
	void Load();
};