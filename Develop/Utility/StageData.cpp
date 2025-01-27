#include "StageData.h"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

/// <summary>
/// �X�e�[�W�f�[�^��ǂݍ���
/// </summary>
void StageData::Load()
{
	FILE* fp = NULL;	// �t�@�C���̏��
	int mc = 0;			// �}�b�v�`�b�v
	int i = 0;
	int j = 0;

	//�Ǎ��t�@�C�����J��
	fopen_s(&fp, "Resource/Map/Stage.csv", "r");

	//�G���[�`�F�b�N
	if (fp == NULL)
	{
		throw("�t�@�C�����ǂݍ��߂܂���\n");
	}
	else
	{
		//�t�@�C���̍Ō�܂Ń��[�v����
		while (mc != EOF)
		{
			// id�̏����l
			ePanelID id = ePanelID::FLOOR;

			//�t�@�C�������P���ǂݍ���
			mc = fgetc(fp);
			j++;

			//�J���}�͖�������
			if (mc == ',')
			{
				j--;
				continue;
			}
			//���s����
			else if (mc == '\n')
			{
				i++;
				j = 0;
				continue;
			}
			else
			{
				switch (mc)
				{
				case '0':
					break;
				case 'F':
					break;
				case 'H':
					break;
				case 'B':
					break;
				case 'S':
					break;
				case 'W':
					break;
				default:
					break;
				}
			}
		}
		//�t�@�C�������
		fclose(fp);
	}
}

/// <summary>
/// �S�Ẵp�l�������擾����
/// </summary>
/// <returns>�S�Ẵp�l�����</returns>
const std::vector<std::vector<ePanelID>> StageData::GetAll()
{
	StageData* stage = StageData::GetInstance();

	if (stage == nullptr)
	{
		// �I�u�W�F�N�g�̍쐬
		stage = new StageData();
		stage->Load();
	}

	return stage->data;
}

/// <summary>
/// ���ݍ��W�̃p�l�������擾����
/// </summary>
/// <param name="location">���ݍ��W</param>
/// <returns>�p�l�����</returns>
const ePanelID StageData::GetPanelData(const Vector2D& location)
{
	StageData* stage = StageData::GetInstance();

	if (stage == nullptr)
	{
		// �I�u�W�F�N�g�̍쐬
		stage = new StageData();
		stage->Load();
	}

	// ���W��Y���ɕϊ�
	int i = 0, j = 0;
	ConvertToIndex(location, i, j);

	// i��j�͈̔̓`�F�b�N
	if ((i < 0) || (j < 0) || (stage->data.size() <= i) || (stage->data[0].size() <= j))
	{
		return ePanelID::NONE;
	}

	return stage->data[i][j];
}

/// <summary>
/// ���W����Y���ɕϊ�����
/// </summary>
/// <param name="location">���W���</param>
/// <param name="i">�ϊ���̓Y��</param>
/// <param name="j">�ϊ���̓Y��</param>
void StageData::ConvertToIndex(const Vector2D& location, int& i, int& j)
{
	j = static_cast<int>(location.x / BLOCK_SIZE);
	i = static_cast<int>(location.y / BLOCK_SIZE);
}