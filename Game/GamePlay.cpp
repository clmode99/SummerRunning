//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.cpp
//!
//! @brief  �Q�[���v���C�֘A�̃\�[�X�t�@�C��
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "GamePlay.h"
#include "Common.h"
#include "Sound.h"
#include "Balloon.h"
#include "ItemMgr.h"
#include "Face.h"
#include "Life.h"
#include "Object.h"
#include "Bg.h"
#include "Player.h"
#include "TimeLimit.h"


/* �O���[�o���I�u�W�F�N�g�A�O���[�o���ϐ��̒�` */
// �I�u�W�F�N�g
static Player player(28, 36, PLAYER_X, SCREEN_HEIGHT, 0.0f, 0.0f, MAX_LIFE);	// �v���C���[
static ItemMgr food;															// �H�ו�

// �����n
static Bg bg(SCROLL);														// �w�i
static Face face(64, 64, FACE_X, FACE_Y, 0.0f, 0.0f);				// ��O��
static Balloon balloon(80, 48, BALLOON_X, BALLOON_Y, 0.0f, 0.0f);	// �����o��
static Life life(32, 32, LIFE_X, LIFE_Y, 0.0f, 0.0f);				// ���C�t
static TimeLimit timelimit;											// ��������
static Bg explan1(BG_NORMAL);													// �����P
static Bg explan2(BG_NORMAL);													// �����Q
static Bg clear(BG_NORMAL);													// �Q�[���N���A
static Bg over(BG_NORMAL);														// �Q�[���I�[�o�[
static Object ice_resault(13, 20, 210, 335, 0.0f, 0.0f);			// �N���A���̃A�C�X�A�C�R��
static Object oden_resault(13, 20, 310, 335, 0.0f, 0.0f);			// �N���A���̂��ł�A�C�R��

// �T�E���h
static Sound play_bgm;			// ���C���a�f�l
static Sound sub_bgm;			// �T�u�a�f�l
static Sound decision;			// ���艹
static Sound cursor_move;		// �J�[�\���ړ�
static Sound ice_se;			// �A�C�X��H�ׂ鉹
static Sound oden_se;			// ���ł��H�ׂ鉹
static Sound clear_se;			// �Q�[���N���A
static Sound page;				// �y�[�W�߂��鉹
static bool is_play_clear;		// �Đ��������t���O

// �t�H���g�n���h��
static int font_normal_handle = 0;					// �m�[�}��
static int font_arrow_handle = 0;					// �I�����̖��
static int font_start_handle = 0;					// �u�r�o�`�b�d�L�[�ŃX�^�[�g�I�v�̕���

// �t���O
static bool is_init = false;			// ������
static bool is_explan = false;			// ����������
static bool is_startline = false;		// �X�^�[�g���C���ɗ�������
static bool is_fadeout = false;			// �t�F�[�h�A�E�g���Ă�������

// �A�C�e���J�E���^
static int ice_cnt = 0;		// �A�C�X�H�ׂ���
static int oden_cnt = 0;	// ���ł�H�ׂ���

// ���̑�
static int arrow_x = ARROW_LEFT;					// �I�����̖��w���W
static PLAY_SCENE play_scene = PLAY_EXPLAN1;		// GamePlay���̃V�[���Ǘ�
static int fadein_opacity = 0;						// �s�����x
static bool is_fadeout_bgm = false;					// �a�f�l���t�F�[�h�A�E�g���Ă邩
extern SCENE g_next_scene;							// �V�[�����


/* �֐��̒�` */
/* ----------------------------------------
�֐����FInitializePlay
�T�v�@�F�Q�[���v���C�̏���������
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void InitializePlay(void)
{
	// �摜���������ɓǂݍ��� (���O���[�o�����ƃR���X�g���N�^�œǂݍ������Ƃ����玸�s��������)
	player.LoadGraphic("Resources\\Images\\player_normal.png", "Resources\\Images\\player_left.png", "Resources\\Images\\player_right.png");
	food.LoadGraphic("Resources\\Images\\ice.png", "Resources\\Images\\oden.png");
	bg.LoadGraphic("Resources\\Images\\bg.png");
	face.LoadGraphic("Resources\\Images\\face_fine.png", "Resources\\Images\\face_caution.png", "Resources\\Images\\face_danger.png");
	balloon.LoadGraphic("Resources\\Images\\balloon_caution.png", "Resources\\Images\\balloon_danger.png");
	life.LoadGraphic("Resources\\Images\\life.png", "Resources\\Images\\life_damage.png");
	explan1.LoadGraphic("Resources\\Images\\explan1.png");
	explan2.LoadGraphic("Resources\\Images\\explan2.png");
	clear.LoadGraphic("Resources\\Images\\clear.png");
	over.LoadGraphic("Resources\\Images\\over.png");
	ice_resault.LoadGraphic("Resources\\Images\\ice_resault.png");
	oden_resault.LoadGraphic("Resources\\Images\\oden_resault.png");

	// �t�H���g�f�[�^���������ɓǂݍ���
	timelimit.LoadFont("���C���I");
	font_normal_handle = CreateFontToHandle("���C���I", 20, 5, DX_FONTTYPE_ANTIALIASING);
	font_arrow_handle = CreateFontToHandle("���C���I", 20, 9, DX_FONTTYPE_ANTIALIASING);
	font_start_handle = CreateFontToHandle("���C���I", 26, 7, DX_FONTTYPE_ANTIALIASING);

	// �T�E���h���������ɓǂݍ���
	play_bgm.LoadSound("Resources\\Sounds\\play_bgm.mp3");
	sub_bgm.LoadSound("Resources\\Sounds\\summer_bgm.mp3");
	decision.LoadSound("Resources\\Sounds\\decision.mp3");
	cursor_move.LoadSound("Resources\\Sounds\\cursor.mp3");
	ice_se.LoadSound("Resources\\Sounds\\ice.mp3");
	oden_se.LoadSound("Resources\\Sounds\\oden.mp3");
	clear_se.LoadSound("Resources\\Sounds\\clear.mp3");
	page.LoadSound("Resources\\Sounds\\page.mp3");

	sub_bgm.ChangeVolume(65);		// �T�u�a�f�l�͉��ʂЂ�����
}

/* ----------------------------------------
�֐����FUpdatePlay
�T�v�@�F�Q�[���v���C�̍X�V����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void UpdatePlay(void)
{
	/* ������ */
	if (is_init == false)
	{
		InitializePlay();
		food.Init();			// �X�e�[�W�t�@�C���ǂݍ��ނ��܂�

		is_init = true;
	}
	
	/* ���� */
	switch (play_scene)
	{
	case PLAY_EXPLAN1:
		is_explan = true;
		play_bgm.Play(BGM);
		sub_bgm.Play(BGM);

		if (player.GetUpBorder() > PLAYER_Y)				// �v���C���[��������o�Ă���(�ŏ�����)
		{
			player.Advance();
		}
		else if (PressKeyTrigger(PAD_INPUT_RIGHT) == true)	// ���̐�����
		{
			play_scene = PLAY_EXPLAN2;
			page.Play(SE);
		}
		else												// ��������P
		{
			is_startline = true;
			player.Animation(NORMAL);
		}
		break;

	case PLAY_EXPLAN2:
		if (PressKeyTrigger(PAD_INPUT_LEFT) == true)		// �O�̐����ɖ߂�
		{
			play_scene = PLAY_EXPLAN1;
			page.Play(SE);
		}
		else if (PressKeyTrigger(PAD_INPUT_10) == true)		// �Q�[���X�^�[�g�I
		{
			is_explan = false;
			play_scene = PLAY_PLAY;
			decision.Play(SE);
			InitGameData();
		}
		else												// ��������Q
		{
			player.Animation(NORMAL);
		}
		break;

	case PLAY_PLAY:
		if (IsFinished() == false)
		{
			/* �X�V */
			timelimit.Update();
			bg.Update(timelimit.GetTimeLimit());
			food.Update(timelimit.GetTimeLimit());
			player.Update(timelimit.GetTimeLimit());
			face.Update(player.GetLife());
			balloon.Update(player.GetLife());

			/* �����蔻��(���֐������) */
			for (int i = 0; i < MAX_ITEM; i++)
			{
				if ((food.m_item[i].IsExistState() == true) && (food.m_item[i].IsFadeOut() == false))
				{
					if (CollisionObject(&player, &food.m_item[i]) == true)
					{
						// �񕜂��邩�_���[�W���󂯂邩(���֐������)
						switch (food.m_item[i].GetKind())
						{
						case COLD:
							player.Heal();
							ice_se.Play(SE);
							ice_cnt++;
							break;

						case HOT:
							player.Damage();
							oden_se.Play(SE);
							oden_cnt++;
							break;

						default:
							Error();
							break;
						}

						food.m_item[i].StartFadeout();
					}
				}
			}
		}
		else
		{
			if (timelimit.GetTimeLimit() <= 0)
			{
				play_scene = PLAY_CLEAR;
			}
			else
			{
				play_scene = PLAY_OVER;
			}
		}
		break;

	case PLAY_CLEAR:
		if (is_play_clear == false)		// ���ʉ��Ȃ̂ɒ����̂Ńt���O���ĂȂ��Ƃ��߁E�E�E
		{
			play_bgm.Stop();
			sub_bgm.Stop();

			clear_se.Play(SE);
			is_play_clear = true;
		}

		// ���莞����
		if (PressKeyTrigger(PAD_INPUT_10) == true)
		{
			InitGameData();
			ResetAllFlag();
			player.ResetPositionAll();
			decision.Play(SE);
			clear_se.Stop();
			WaitTimer(500);
			play_scene = PLAY_EXPLAN1;
			g_next_scene = TITLE;
		}

		// �N���A���o(���֐������)
		if (player.GetDownBorder() > 0.0f)
		{
			player.Advance();
		}
		break;

	case PLAY_OVER:
		// �u���g���C���܂����H�v
		if (PressKeyTrigger(PAD_INPUT_LEFT) == true)	// �u�͂��v
		{
			arrow_x = ARROW_LEFT;
			cursor_move.Play(SE);
		}
		if (PressKeyTrigger(PAD_INPUT_RIGHT) == true)	// �u�������v
		{
			arrow_x = ARROW_RIGHT;
			cursor_move.Play(SE);
		}

		// ���莞����
		if (PressKeyTrigger(PAD_INPUT_10) == true)
		{
			if (arrow_x == ARROW_LEFT)				// ���g���C����
			{
				decision.Play(SE);
				InitGameData();
				play_scene = PLAY_PLAY;
			}
			else									// �^�C�g����
			{
				decision.Play(SE);
				is_fadeout_bgm = true;
			}
		}
		break;

	default:
		Error();
		break;
	}

	// ���ʃt�F�[�h�A�E�g���ă^�C�g����
	if (is_fadeout_bgm == true)
	{
		static int bgm_volume = 100;		// BGM�̉���
		
		bgm_volume -= 3;
		play_bgm.ChangeVolume(bgm_volume);

		if (bgm_volume <= 0)
		{
			is_fadeout_bgm = false;
			InitGameData();
			ResetAllFlag();
			player.ResetPositionAll();
			play_bgm.Stop();
			sub_bgm.Stop();
			arrow_x = ARROW_LEFT;			// �J�[�\�������ɖ߂��Ă���
			bgm_volume = 100;
			play_bgm.ChangeVolume(100);
			WaitTimer(100);
			play_scene = PLAY_EXPLAN1;
			g_next_scene = TITLE;
		}
	}
}

/* ----------------------------------------
�֐����FRenderPlay
�T�v�@�F�Q�[���v���C�̕`�揈��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void RenderPlay(void)
{
	/* ��끨�O�ɕ`�悷�� */
	bg.Draw();
	face.Draw();
	if (is_explan == false)					// �������͕`�悵�Ȃ�
	{
		balloon.Draw();
		food.Draw();
	}
	player.Draw();
	life.Draw(player.GetLife());

	if (player.GetLife() <= 3)				// �댯��Ԃ̎��͏����Ԃ�����
	{
		SetDrawBright(255, 240, 240);		// �ق�̂�Ԃ�
	}
	else
	{
		SetDrawBright(255, 255, 255);		// ����
	}

	/* ����̏�ʂ̂ݕ`�悷�� */
	switch (play_scene)
	{
	case PLAY_EXPLAN1:
		if (is_startline == true)		// �v���C���[���X�^�[�g���C���ɗ��܂ł͕`�悵�Ȃ�
		{
			// �t�F�[�h�C������
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadein_opacity);		// �s�����x�ݒ�
			fadein_opacity += 5;
			if (fadein_opacity > 255)
			{
				fadein_opacity = 255;
			}

			explan1.Draw();
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);					// ���Ƃɖ߂��Ȃ��Ƃ��������Ȃ�
		}
		break;

	case PLAY_EXPLAN2:
		explan2.Draw();
		if ((GetPassageTime() / 500) % 2)			// �؂��؂��_�ł�����
		{
			DrawFormatStringToHandle(185, 372, GetColor(0, 0, 0), font_start_handle, "�r�o�`�b�d�L�[�ŃX�^�[�g�I");
		}
		break;

	case PLAY_PLAY:
		timelimit.Draw();
		break;

	case PLAY_CLEAR:
		SetDrawBright(255, 255, 255);			// ���ɖ߂�

		clear.Draw();
		ice_resault.Draw();
		oden_resault.Draw();
		DrawFormatStringToHandle(105, 335, GetColor(0, 0, 0), font_normal_handle, "�H�ׂ����@�@�F%2d�A�@�F%2d��", ice_cnt, oden_cnt);
		DrawFormatStringToHandle(105, 365, GetColor(0, 0, 0), font_normal_handle, "�r�o�`�b�d�L�[�Ń^�C�g����");
		break;

	case PLAY_OVER:
		over.Draw();

		// ���֐������
		DrawFormatStringToHandle(105, 335, GetColor(0, 0, 0), font_normal_handle, "���g���C���܂����H");
		DrawFormatStringToHandle(153, 365, GetColor(0, 0, 0), font_normal_handle, "�^");
		switch (arrow_x)
		{
		case ARROW_LEFT:
			DrawFormatStringToHandle(110, 365, GetColor(0, 0, 0), font_normal_handle, "�͂�");
			DrawFormatStringToHandle(177, 365, GetColor(100, 100, 100), font_normal_handle, "������");
			break;

		case ARROW_RIGHT:
			DrawFormatStringToHandle(110, 365, GetColor(100, 100, 100), font_normal_handle, "�͂�");
			DrawFormatStringToHandle(177, 365, GetColor(0, 0, 0), font_normal_handle, "������");
			break;

		default:
			Error();
			break;
		}
		//DrawFormatStringToHandle(arrow_x, 365, GetColor(0, 0, 0), font_arrow_handle, "��");
		break;
	}


	// ���f�o�b�O���͂�����
	//DrawFormatString(450, 25, GetColor(0, 0, 0), "�v���C���[�̃��C�t�F%d", player.GetLife());
}

/* ----------------------------------------
�֐����FIsFiniehed
�T�v�@�F�Q�[���̏I������
�����@�F�Ȃ�(void)
�߂�l�F�I��(true)�A���s(false)
---------------------------------------- */
bool IsFinished(void)
{
	if ((player.GetLife() > 0) && (timelimit.GetTimeLimit() > 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

/* ----------------------------------------
�֐����FInitGameData
�T�v�@�F�f�[�^���܂Ƃ߂ď�����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void InitGameData(void)
{
	InitCommon();
	bg.ResetPosition();
	food.Init();
	player.ResetPositionX();
	player.ResetLife();
	balloon.Update(player.GetLife());		// �v���C���Ă���^�C�g���߂��Ă܂��X�^�[�g����ƁA��u�����ӂ������o�����邽��
	timelimit.ResetTimeLimit();
	ice_cnt = 0;
	oden_cnt = 0;
	fadein_opacity = 0;
}

/* ----------------------------------------
�֐����FResetAllFlag
�T�v�@�F�t���O���܂Ƃ߂ă��Z�b�g����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void ResetAllFlag(void)
{
	is_init = false;
	is_explan = false;
	is_startline = false;
	is_play_clear = false;
}