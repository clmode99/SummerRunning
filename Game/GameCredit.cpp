//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameCredit.cpp
//!
//! @brief  �Q�[���N���W�b�g�֘A�̃\�[�X�t�@�C��
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "GameCredit.h"
#include "Common.h"
#include "Bg.h"
#include "Sound.h"


/* �O���[�o���ϐ��̒�` */
static Bg credit(BG_NORMAL);				// �N���W�b�g
static Sound page;				// �y�[�W�߂��鉹

// ���̑�
static bool is_init = false;		// ������
extern SCENE g_next_scene;			// �V�[�����


/* �֐��̒�` */
/* ----------------------------------------
�֐����FUpdateCredit
�T�v�@�F�Q�[���N���W�b�g�̍X�V����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void UpdateCredit(void)
{
	/* ������ */
	if (is_init == false)
	{
		// �摜���������ɓǂݍ���
		credit.LoadGraphic("Resources\\Images\\credit.png");

		// �T�E���h���������ɓǂݍ���
		page.LoadSound("Resources\\Sounds\\page.mp3");

		is_init = true;
	}

	// �^�C�g���֖߂�
	if (PressKeyTrigger(PAD_INPUT_10) == true)
	{
		g_next_scene = TITLE;
		page.Play(SE);
	}

}

/* ----------------------------------------
�֐����FRenderCredit
�T�v�@�F�Q�[���N���W�b�g�̕`�揈��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void RenderCredit(void)
{
	credit.Draw();
}
