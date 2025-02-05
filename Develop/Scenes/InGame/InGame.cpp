#include "InGame.h"
#include "DxLib.h"
#include <fstream>

#include "../../Objects/Block/Floor.h"
#include "../../Objects/Block/Block.h"
#include "../../Objects/Block/Hatena.h"
#include "../../Objects/Block/Stairs.h"
#include "../../Objects/Block/WaterPipes.h"
#include "../../Objects/Block/WarpBox.h"
#include "../../Objects/Block/Goal.h"
#include "../../Objects/Block/UnderBlock.h"
#include "../../Objects/Block/UnderFloor.h"
#include "../../Objects/Character/Enemy/Koopa.h"
#include "../../Objects/Character/Enemy/Goomba.h"
#include "../../Utility/StageData.h"

#define PLAYER_INITIAL_LOCATION 50 // �v���C���[�����ʒu(���u���b�N�ځj

// �R���X�g���N�^
InGame::InGame() :
	score(0),
	num(NULL),
	player(nullptr),
	camera(nullptr),
	sky_image(),
	leaf_image(),
	mountain_image(),
	cloud_image()
{
	
}

// �f�X�g���N�^
InGame::~InGame()
{
	// ����Y��h�~
	Finalize();
}

// ����������
void InGame::Initialize()
{
	// �e�N���X�̏������������Ăяo��
	__super::Initialize();

	// �摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);
	sky_image = rm->GetImages("Resource/Images/sora.png")[0];
	leaf_image[0] = rm->GetImages("Resource/Images/ha0.png")[0];
	leaf_image[1] = rm->GetImages("Resource/Images/ha1.png")[0];
	leaf_image[2] = rm->GetImages("Resource/Images/ha2.png")[0];
	mountain_image[0] = rm->GetImages("Resource/Images/mountain_left.png")[0];
	mountain_image[1] = rm->GetImages("Resource/Images/mountain_right.png")[0];
	mountain_image[2] = rm->GetImages("Resource/Images/mountain_surface2.png")[0];
	mountain_image[3] = rm->GetImages("Resource/Images/mountain_surface.png")[0];
	mountain_image[4] = rm->GetImages("Resource/Images/mountain_surface1.png")[0];
	mountain_image[5] = rm->GetImages("Resource/Images/mountain_up.png")[0];
	cloud_image[0] = rm->GetImages("Resource/Images/cloud1.png")[0];
	cloud_image[1] = rm->GetImages("Resource/Images/cloud2.png")[0];
	cloud_image[2] = rm->GetImages("Resource/Images/cloud3.png")[0];
	cloud_image[3] = rm->GetImages("Resource/Images/cloud4.png")[0];
	cloud_image[4] = rm->GetImages("Resource/Images/cloud5.png")[0];
	cloud_image[5] = rm->GetImages("Resource/Images/cloud6.png")[0];

	// �J�����̏����擾
	camera = Camera::GetInstance();

	// �}�b�v�f�[�^�ǂݍ��ݐ�������
	LoadStage();

	// �v���C���[�̐���
	GameObjectManager* object = GameObjectManager::GetInstance();
	player = object->CreateObject<Player>(Vector2D(32 * PLAYER_INITIAL_LOCATION, 400));

	// �v���C���[�����J�����ɓn��
	camera->SetPlayer(player);
	player->SetCamera(camera);

	// �J�����̏�����
	camera->Initialize();
}

// �X�V����
eSceneType InGame::Update(const float& delta_second)
{
	// ���͏����擾
	InputManager* input = InputManager::GetInstance();

	// ���U���g�V�[���ɑJ�ڂ���
	if (input->GetKeyState(KEY_INPUT_RETURN) == eInputState::Pressed)
	{
		return eSceneType::result;
	}
	if (input->GetButtonState(XINPUT_BUTTON_START) == eInputState::Pressed)
	{
		return eSceneType::result;
	}
	if (player->GetIsDeath() == true)
	{
		return eSceneType::result;
	}

	// �e�N���X�̃A�j���[�V����������Ăяo��
	__super::AnimationControl(delta_second, true);

	// �J�����̍X�V
	camera->Update();

	// �e�N���X�̍X�V�������Ăяo��
	return __super::Update(delta_second);
}

// �`�揈��
void InGame::Draw() const
{
	// �w�icsv�t�@�C���Ǎ���
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/Back.csv";

	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	// �J�E���g�p�ϐ�
	int x = 0;			// ��
	int y = 0;			// �s

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{
		//�`�悷����W���v�Z
		Vector2D location;
		location.x = (float)(x * BOX_SIZE + D_WIN_MAX_X / 2) - camera->GetCameraPos().x + BOX_SIZE / 2;
		location.y = (float)(y * BOX_SIZE + BOX_SIZE/2) + camera->GetCameraPos().y - D_WIN_MAX_Y / 2;

		// �t�@�C������1�������o����
		int c = fgetc(fp);

		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
		// ���o����������B�Ȃ�A�`�悵�Ȃ��Ŏ��̕��������ɍs��
		else if (c == 'B')
		{
			x++;
		}
		// ���o����������S�Ȃ�A���`��
		else if(c == 'S')
		{
			DrawRotaGraph(location.x, location.y, 1.0, 0.0, sky_image, TRUE);
			x++;
		}
		// ���o����������L�Ȃ�A�t��`��
		else if (c == 'L')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '0':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, leaf_image[0], TRUE);
				break;
			case '1':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, leaf_image[1], TRUE);
				break;
			case '2':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, leaf_image[2], TRUE);
				break;
			}
			x++;
		}
		// ���o����������M�Ȃ�A�R��`��
		else if (c == 'M')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '0':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[0], TRUE);
				break;
			case '1':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[1], TRUE);
				break;
			case '2':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[2], TRUE);
				break;
			case '3':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[3], TRUE);
				break;
			case '4':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[4], TRUE);
				break;
			case '5':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, mountain_image[5], TRUE);
				break;
			}
			x++;
		}
		// ���o����������C�Ȃ�A�_��`��
		else if (c == 'C')
		{
			c = fgetc(fp);
			switch (c)
			{
			case '0':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[0], TRUE);
				break;
			case '1':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[1], TRUE);
				break;
			case '2':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[2], TRUE);
				break;
			case '3':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[3], TRUE);
				break;
			case '4':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[4], TRUE);
				break;
			case '5':
				DrawRotaGraph(location.x, location.y, 1.0, 0.0, cloud_image[5], TRUE);
				break;
			}
			x++;
		}
	}
	// �J�����t�@�C�������
	fclose(fp);

	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	/*************************�@UI�̕`��@***************************/

	// �X�R�A�̕`��
	for (int i = 0; i < 6; i++)
	{
		DrawRotaGraph(90 + (i * 19), 55, 1.1, 0.0, num[0], TRUE);
	}
	//�R�C�������`��
	DrawRotaGraph(255, 55, 1.1, 0.0, num[11], TRUE);
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(275 + (i * 19), 55, 1.1, 0.0, num[0], TRUE);
	}
	// �X�e�[�W���̕`��
	DrawRotaGraph(399, 55, 1.1, 0.0, num[10], TRUE);
	for (int i = 0; i < 2; i++)
	{
		DrawRotaGraph(380 + (i * 38), 55, 1.1, 0.0, num[1], TRUE);
	}
	// �^�C���̕`��
	for (int i = 0; i < 3; i++)
	{
		DrawRotaGraph(514 + (i * 19), 55, 1.1, 0.0, num[0], TRUE);
	}

	DrawFormatString(10, 150, 0xffffff, "x:%f",camera->GetCameraPos().x);
	DrawFormatString(250, 150, 0xffffff, "y:%f",camera->GetCameraPos().y);

	SetFontSize(16);
	DrawFormatString(10, 80, 0xffffff, "A:���ړ�");
	DrawFormatString(100, 80, 0xffffff, "D:�E�ړ�");
	DrawFormatString(200, 80, 0xffffff, "W:�W�����v");
	DrawFormatString(1, 1, 0xffffff, "InGame");
	SetFontSize(32);

}

// �I������
void InGame::Finalize()
{
	// �e�N���X�̏I�����������Ăяo��
	__super::Finalize();

	// �v���C���[�̍폜
	object->DestroyObject(player);
}

// ���݂̃V�[���^�C�v�����擾����
const eSceneType InGame::GetNowSceneType() const
{
	return eSceneType::in_game;
}

// �X�e�[�W��������
void InGame::LoadStage()
{
	// �I�u�W�F�N�g�}�l�[�W���[�̃|�C���^
	GameObjectManager* object = GameObjectManager::GetInstance();
	
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/Stage.csv";

	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	// �J�E���g�p�ϐ�
	int x = 0;			// ��
	int y = 0;			// �s
	WarpBox* warp1e = nullptr;
	WarpBox* warp1s = nullptr;
	WarpBox* warp2e = nullptr;
	WarpBox* warp2s = nullptr;

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{
		 //���W�v�Z
		Vector2D location;
		location.x = (float)(x * BOX_SIZE + BOX_SIZE / 2) + (camera->GetCameraPos().x);
		location.y = (float)(y * BOX_SIZE + BOX_SIZE / 2);

		// �t�@�C������1�������o����
		int c = fgetc(fp);

		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		// ���o�����������󔒕����Ȃ�A�������Ȃ��Ŏ��̕��������ɍs��
		else if (c == ' ')
		{
			x++;
			break;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
		// ���o����������0�Ȃ�A�������Ȃ��Ŏ��̕��������ɍs��
		else if (c == '0')
		{
			x++;
		}
		// ���o����������F�Ȃ�A���u���b�N�𐶐�����
		else if (c == 'F')
		{
			c = fgetc(fp);
			switch (c)
			{
			case 'g':
				object->CreateObject<Floor>(Vector2D(location.x, location.y));
				break;

			case 'u':
				object->CreateObject<UnderFloor>(Vector2D(location.x, location.y));
				break;
			}
			x++;
		}
		// ���o����������H�Ȃ�A�͂Ăȃu���b�N�𐶐�����
		else if (c == 'H')
		{
			object->CreateObject<Hatena>(Vector2D(location.x, location.y));
			x++;
		}
		// ���o����������B�Ȃ�A�����K�u���b�N�𐶐�����
		else if (c == 'B')
		{
			c = fgetc(fp);
			switch (c)
			{
			case 'g':
				object->CreateObject<Block>(Vector2D(location.x, location.y));
					break;

			case 'u':
				object->CreateObject<UnderBlock>(Vector2D(location.x, location.y));
				break;
			}
			x++;
		}
		// ���o����������S�Ȃ�A�K�i�u���b�N�𐶐�����
		else if (c == 'S')
		{
			object->CreateObject<Stairs>(Vector2D(location.x, location.y));
			x++;
		}
		// ���o����������W�Ȃ�A�y�ǂ𐶐�����
		else if (c == 'W')
		{
			WaterPipes* pipe;
			pipe = object->CreateObject<WaterPipes>(Vector2D(location.x, location.y));

			c = fgetc(fp);
			switch (c)
			{
			case '0':
				pipe->SetType(ePipeType::LEFT_DOWN);
				break;
			case '1':
				pipe->SetType(ePipeType::LEFT_UP);
				break;
			case '2':
				pipe->SetType(ePipeType::RIGHT_DOWN);
				break;
			case '3':
				pipe->SetType(ePipeType::RIGHT_UP);
				break;
			case '4':
				pipe->SetType(ePipeType::LIE_LEFT_UP);
				break;
			case '5':
				pipe->SetType(ePipeType::LIE_MIDDLE_UP);
				break;
			case '6':
				pipe->SetType(ePipeType::LIE_RIGHT_UP);
				break;
			case '7':
				pipe->SetType(ePipeType::LIE_LEFT_DOWN);
				break;
			case '8':
				pipe->SetType(ePipeType::LIE_MIDDLE_DOWN);
				break;
			case '9':
				pipe->SetType(ePipeType::LIE_RIGHT_DOWN);
				break;
			}
			x++;
		}
		else if (c == 'T')
		{
			c = fgetc(fp);
			if (c == '1')
			{
				c = fgetc(fp);

				if (c == 'e')
				{
					warp1e = object->CreateObject<WarpBox>(Vector2D(location.x, location.y));
					warp1e->SetPaier(1);
					warp1e->SetType(eWarpType::ENTRANCE);
				}
				else if(c == 's')
				{
					warp1s = object->CreateObject<WarpBox>(Vector2D(location.x, location.y));
					warp1s->SetPaier(1);
					warp1s->SetType(eWarpType::EXit);
				}
			}
			else if (c == '2')
			{
				c = fgetc(fp);

				if (c == 'e')
				{
					warp2e = object->CreateObject<WarpBox>(Vector2D(location.x, location.y));
					warp2e->SetPaier(2);
					warp2e->SetType(eWarpType::ENTRANCE);
				}
				else if (c == 's')
				{
					warp2s = object->CreateObject<WarpBox>(Vector2D(location.x, location.y));
					warp2s->SetPaier(2);
					warp2s->SetType(eWarpType::EXit);
				}
			}

			if (warp1s != nullptr && warp1e != nullptr)
			{
				warp1e->SetExit(warp1s->GetLocation());
			}

			if (warp2s != nullptr && warp2e != nullptr)
			{
				warp2e->SetExit(warp2s->GetLocation());
			}

			x++;
		}
		// ���o����������G�Ȃ�A�S�[���𐶐�����
		else if (c == 'G')
		{
			Goal* goal;
			goal = object->CreateObject<Goal>(Vector2D(location.x, location.y));

			c = fgetc(fp);

			switch (c)
			{
			case '0':
				goal->SetType(eGoalType::Pool);
				break;
			case '1':
				goal->SetType(eGoalType::Bool);
				break;
			case '2':
				goal->SetType(eGoalType::Flag);
				break;
			}
			x++;
		}
		// ���o����������E�Ȃ�A�G�l�~�[�𐶐�����
		else if (c == 'E')
		{
			c = fgetc(fp);

			switch (c)
			{
			case '1':
				Goomba * goomba;
				goomba = object->CreateObject<Goomba>(Vector2D(location.x, location.y));
				goomba->SetCamera(camera);
				break;
			case '2':
				Koopa * koopa;
				koopa = object->CreateObject<Koopa>(Vector2D(location.x, location.y - 5.0f));
				koopa->SetCamera(camera);
				break;
			}
			x++;
		}
		else if (c == 'C')
		{
			x++;
		}
	}
	// �J�����t�@�C�������
	fclose(fp);
}