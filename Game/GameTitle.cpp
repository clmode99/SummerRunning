//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameTitle.cpp
//!
//! @brief  �Q�[���^�C�g���֘A�̃\�[�X�t�@�C��
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "GameTitle.h"
#include "Common.h"
#include "Sound.h"
#include "Bg.h"
#include "Cloud.h"


/* �O���[�o���ϐ��A�I�u�W�F�N�g�̒�` */
static Bg bg(BG_NORMAL);																		// �w�i
static Object title_logo(448, 64, CHIP_SIZE * 11, CHIP_SIZE * 2, 0.0f, 0.0f);		// �^�C�g�����S
static Cloud cloud[MAX_CLOUD] = {
	{160,96,CHIP_SIZE * 16,CHIP_SIZE * 4,1.0f,0.0f},
	{160,96,640,CHIP_SIZE * 4,1.0f,0.0f} };				// �_(���]�͂����Mgr)

// �T�E���h
static Sound title_bgm;				// �^�C�g���a�f�l
static Sound decision;				// ���艹
static Sound cursor_move;			// �J�[�\���ړ�
static Sound page;					// �y�[�W�߂��鉹

// �t�H���g�n���h��
static int font_normal_handle = 0;			// �m�[�}��
static int font_arrow_handle = 0;			// ���

// ���̑�
static int arrow_y = START_Y;		// ���̂x���W
static bool is_init = false;		// ������
static int brightness = 0;			// �P�x(�O�`�Q�T�T)
static bool is_fadeout = false;		// �t�F�[�h�A�E�g���邩
extern SCENE g_next_scene;			// �V�[�����


/* �֐��̒�` */
/* ----------------------------------------
�֐����FUpdateTitle
�T�v�@�F�Q�[���^�C�g���̍X�V����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void UpdateTitle(void)
{
	/* ������ */
	if (is_init == false)
	{
		// �摜���������ɓǂݍ���
		bg.LoadGraphic("Resources\\Images\\title.png");
		title_logo.LoadGraphic("Resources\\Images\\title_logo.png");
		for (int i = 0; i < MAX_CLOUD; i++)
		{
			cloud[i].LoadGraphic("Resources\\Images\\cloud.png");
		}

		// �t�H���g�f�[�^���������ɓǂݍ���
		font_normal_handle = CreateFontToHandle("���C���I", 20, 5, DX_FONTTYPE_ANTIALIASING);
		font_arrow_handle = CreateFontToHandle("���C���I", 20, 9, DX_FONTTYPE_ANTIALIASING);

		// �T�E���h���������ɓǂݍ���
		title_bgm.LoadSound("Resources\\Sounds\\title.mp3");
		decision.LoadSound("Resources\\Sounds\\decision.mp3");
		cursor_move.LoadSound("Resources\\Sounds\\cursor.mp3");
		page.LoadSound("Resources\\Sounds\\page.mp3");

		is_init = true;
	}

	/* �X�V���� */
	else
	{
		// �_
		for (int i = 0; i < MAX_CLOUD; i++)
		{
			cloud[i].Update();
		}

		// �I��
		if (PressKeyTrigger(PAD_INPUT_UP) == true)
		{
			if (arrow_y != 305)
			{
				arrow_y -= 30;
				cursor_move.Play(SE);
			}
		}
		if (PressKeyTrigger(PAD_INPUT_DOWN) == true)
		{
			if (arrow_y != 365)
			{
				arrow_y += 30;
				cursor_move.Play(SE);
			}
		}
		// ����
		if (PressKeyTrigger(PAD_INPUT_10) == true)
		{
			switch (arrow_y)
			{
			case START_Y:
				is_fadeout = true;
				decision.Play(SE);
				break;

			case CREDIT_Y:
				g_next_scene = CREDIT;
				page.Play(SE);
				break;

			case EXIT_Y:
				DxLib_End();
				exit(1);
				break;

			default:
				Error();
			}
		}

		if (is_fadeout == true)		// ��ʂ������t�F�[�h�A�E�g���ۂ����Ă݂�
		{
			static int bgm_volume = 100;			// �a�f�l�̉���(�O�`�P�O�O)
			
			// �a�f�l���Ԃ����Ɛ؂��̂��C�ɂ���Ȃ��̂ŁA���ʕω��Ńt�F�[�h�A�E�g
			bgm_volume -= 2;
			title_bgm.ChangeVolume(bgm_volume);

			brightness -= 10;		// ����͉�ʂ̃t�F�[�h�A�E�g

			if (bgm_volume <= 0)
			{
				is_fadeout = false;
				WaitTimer(100);
				title_bgm.Stop();
				title_bgm.ChangeVolume(100);
				bgm_volume = 100;
				g_next_scene = PLAY;
			}
		}
		else
		{
			brightness += 20;		// �t�F�[�h�C���ۂ����Ă݂�
			if (brightness > 255)
			{
				brightness = 255;
			}
		}
	}

	if (g_next_scene != PLAY)		// �Q�[���v���C�̂ق��Ɉڂ�����Đ����Ȃ��悤�ɂ���
	{
		title_bgm.Play(BGM);
	}
}

/* ----------------------------------------
�֐����FRenderTitle
�T�v�@�F�Q�[���^�C�g���̕`�揈��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void RenderTitle(void)
{
	SetDrawBright(brightness, brightness, brightness);

	/* ��끨�O�֕`�悷�� */
	bg.Draw();

	// ���֐������
	switch (arrow_y)
	{
	case START_Y:
		DrawFormatStringToHandle(242, START_Y, GetColor(0, 0, 0), font_normal_handle, "�@ �r�s�`�q�s");
		DrawFormatStringToHandle(232, CREDIT_Y, GetColor(100, 100, 100), font_normal_handle, "�@ �b�q�d�c�h�s");
		DrawFormatStringToHandle(252, EXIT_Y, GetColor(100, 100, 100), font_normal_handle, "�@ �d�w�h�s");
		break;

	case CREDIT_Y:
		DrawFormatStringToHandle(242, START_Y, GetColor(100, 100, 100), font_normal_handle, "�@ �r�s�`�q�s");
		DrawFormatStringToHandle(232, CREDIT_Y, GetColor(0, 0, 0), font_normal_handle, "�@ �b�q�d�c�h�s");
		DrawFormatStringToHandle(252, EXIT_Y, GetColor(100, 100, 100), font_normal_handle, "�@ �d�w�h�s");
		break;

	case EXIT_Y:
		DrawFormatStringToHandle(242, START_Y, GetColor(100, 100, 100), font_normal_handle, "�@ �r�s�`�q�s");
		DrawFormatStringToHandle(232, CREDIT_Y, GetColor(100, 100, 100), font_normal_handle, "�@ �b�q�d�c�h�s");
		DrawFormatStringToHandle(252, EXIT_Y, GetColor(0, 0, 0), font_normal_handle, "�@ �d�w�h�s");
		break;

	default:
		Error();
		break;
	}
	//DrawFormatStringToHandle(242, arrow_y, GetColor(0, 0, 0), font_arrow_handle, "��");

	for (int i = 0; i < MAX_CLOUD; i++)
	{
		cloud[i].Draw();
	}
	title_logo.Draw();
}
