#pragma once

#include <string>

/**********************************************************
* �}�N����`
***********************************************************/
#define	D_SUCCESS		(0)		// ����
#define	D_FAILURE		(-1)	// ���s

#define D_WIN_MAX_X		(640)	// �X�N���[���T�C�Y�i���j
#define D_WIN_MAX_Y		(480)	// �X�N���[���T�C�Y�i�����j
#define D_COLOR_BIT		(32)	// �J���[�r�b�g
#define BOX_SIZE		(32)	// �J���[�r�b�g

//#define DEBUG

/**********************************************************
* �v���g�^�C�v�錾
***********************************************************/
// �G���[���e���o�͂���
int ErrorThrow(std::string error_log);
