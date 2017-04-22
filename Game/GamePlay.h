//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  �Q�[���v���C�֘A�̃w�b�_�t�@�C��
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �C���N���[�h�t�@�C�� */
#include "Common.h"


/* �}�N���̒�` */
// �}�b�v�֌W
#define PLAYER_X (CHIP_SIZE * 15)		// �v���C���[�̂w���W�̏����l
#define PLAYER_Y (CHIP_SIZE * 26)		// �v���C���[�̂x���W�̏����l
#define LIFE_X (2 * (CHIP_SIZE * 2))	// ���C�t�̂w���W
#define LIFE_Y (1 * (CHIP_SIZE * 2))	// ���C�t�̂x���W
#define FACE_X (CHIP_SIZE)				// ��O���̂w���W
#define FACE_Y (CHIP_SIZE)				// ��O���̂x���W
#define BALLOON_X (CHIP_SIZE - 8.0f)		// �����o���̂w���W
#define BALLOON_Y (CHIP_SIZE * 5)		// �����o���̂x���W
#define ITEM0_X (CHIP_SIZE * 7)			// ���[���O�̂w���W
#define ITEM1_X (CHIP_SIZE * 15)		// ���[���P�̂w���W
#define ITEM2_X (CHIP_SIZE * 23)		// ���[���Q�̂w���W
#define ITEM3_X (CHIP_SIZE * 31)		// ���[���R�̂w���W
#define ITEM_X (0.0f)					// �A�C�e���̂w���W�̏����l
#define ITEM_Y (0.0f)					// �A�C�e���̂x���W�̏����l

// �v���C���[���
#define MAX_LIFE (10)		//���C�t�̍ő�l

// �A�C�e�����
#define MAX_ITEM (4)		// �A�C�e���̍ő吔

// �I�����
#define ARROW_LEFT  (103)	// ���̂w���W
#define ARROW_RIGHT (203)	// �E�̂w���W

// ���̑�
#define MAX_TIME_LIMIT (30)			// ��������


/* �񋓌^�̒�` */
enum PLAY_SCENE
{
	PLAY_EXPLAN1,		// �����P
	PLAY_EXPLAN2,		// �����Q
	PLAY_PLAY,			// �v���C(���C��)�B���O���������E�E�E
	PLAY_CLEAR,			// �Q�[���N���A
	PLAY_OVER			// �Q�[���I�[�o�[
};


/* �֐��̃v���g�^�C�v�錾 */
void InitializePlay(void);			// �Q�[���v���C�̏���������
void UpdatePlay(void);				// �Q�[���v���C�̍X�V����
void RenderPlay(void);				// �Q�[���v���C�̕`�揈��
void FinalizePlay(void);			// �Q�[���v���C�̏I������

bool IsFinished(void);				// �Q�[���̏I������
void InitGameData(void);			// �f�[�^���܂Ƃ߂ď�����
void ResetAllFlag(void);			// �t���O��S�����Z�b�g����