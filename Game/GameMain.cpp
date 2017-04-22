//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���S�̊֘A�̃\�[�X�t�@�C��
//!
//! @date   2016.08.07
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "GameMain.h"
#include "GameLogo.h"
#include "GameTitle.h"
#include "GameCredit.h"
#include "GamePlay.h"
#include "Common.h"


/* �O���[�o���ϐ��̒�` */
static SCENE g_scene=PLAY;				// �V�[�����
SCENE g_next_scene = g_scene;		// ���̃V�[�����


/* �֐��̒�` */
/* ----------------------------------------
�֐����FInitializeGame
�T�v�@�F����������
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void InitializeGame(void)
{
	InitCommon();
	SetMouseDispFlag(FALSE);
}

/* ----------------------------------------
�֐����FUpdateGame
�T�v�@�F�X�V����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void UpdateGame(void)
{
	/* ���[�J���ϐ��̏����� */
	// �V�[���Ǘ�
	void(*p_update_scene[])(void) = { UpdateLogo,UpdateTitle,UpdateCredit,UpdatePlay };		// �X�V�̃V�[���Ǘ�
	

	/* ���� */
	UpdateCommon();

	if (g_scene != g_next_scene)	// �V�[���؂�ւ�����
	{
		g_scene = g_next_scene;
	}

	p_update_scene[g_scene]();		// �V�[���Ǘ�


}

/* ----------------------------------------
�֐����FRenderGame
�T�v�@�F�`�揈��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void RenderGame(void)
{
	/* ���[�J���ϐ��̏����� */
	void(*p_render_scene[])(void) = { RenderLogo,RenderTitle,RenderCredit,RenderPlay };		// �`��̃V�[���Ǘ�
	

	/* ���� */
	p_render_scene[g_scene]();		// �V�[���Ǘ�
}

/* ----------------------------------------
�֐����FFinalizeGame
�T�v�@�F�I������
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void FinalizeGame(void)
{
	;
}
