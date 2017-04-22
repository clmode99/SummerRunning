//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLogo.cpp
//!
//! @brief  �Q�[�����S�֘A�̃\�[�X�t�@�C��
//!
//! @date   2016.09.10
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "GameLogo.h"
#include "Common.h"
#include "Bg.h"


/* �O���[�o���ϐ��̒�` */
static Bg logo(BG_NORMAL);						// ���S
static bool is_init = false;		// ������
extern SCENE g_next_scene;			// �V�[���Ǘ�


/* �����O��̃V���[�e�B���O�̃��S�����ۂ��ƃR�s�y�Ȃ̂ŁA������������*/

/* �֐��̒�` */
/* ----------------------------------------
�֐����FUpdateLogo
�T�v�@�F�Q�[�����S�̍X�V����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void UpdateLogo(void)
{
	/* ���[�J���ϐ��̏����� */
	static int start_time_ms = 0, now_time_ms = 0;	// ���Ԋ֌W�B�~���b�P��
	static int brightness = 0;						// �`��P�x
	static int revised_brightness = 0;				// �`��P�x�̒����l
	static int cnt_frame = 0;						// 1�t���[�����ƂɃC���N�������g
	static int press_key_time_ms = 0;				// �L�[�������ꂽ�u�Ԃ̎���
	static int press_key_brightness = 0;			// �L�[�������ꂽ�u�Ԃ̕`��P�x
	static bool is_press_key = false;				// �L�[�������ꂽ��
	static bool is_normal_fadeout = false;			// �ʏ�t�F�[�h�A�E�g����


	/* ������ */
	if (is_init == false)
	{
		// �J��Ԃ��g�����[�J���ϐ�
		start_time_ms = GetNowCount();

		// �摜���������ɓǂݍ���
		logo.LoadGraphic("Resources\\Images\\my_logo.png");

		is_init = true;
	}

	// ���Ԏ擾
	now_time_ms = GetNowCount() - start_time_ms;

	// �ʏ�t�F�[�h�A�E�g
	if (is_press_key == false)
	{
		revised_brightness = (int)(MAX_BRIGHTNESS / 60);

		switch (now_time_ms / 1000)
		{
			// �t�F�[�h�C��
		case 0:
			brightness = cnt_frame * revised_brightness;
			break;

			// �ێ�
		case 1:
		case 2:
			brightness = MAX_BRIGHTNESS;
			break;

			// �t�F�[�h�A�E�g
		case 3:
		case 4:
			// �ŏ�����������
			if (is_normal_fadeout == false)
			{
				cnt_frame = 0;
				is_normal_fadeout = true;
			}
			brightness = MAX_BRIGHTNESS - (cnt_frame * revised_brightness);
			break;

		default:
			DrawString(0, 20, "�G���[", GetColor(255, 0, 0));
			break;
		}

		// �L�[����
		if (CheckHitKeyAll())
		{
			// �����t�F�[�h�A�E�g�̏�����
			press_key_time_ms = now_time_ms;
			press_key_brightness = brightness;
			cnt_frame = 0;
			is_press_key = true;
		}
	}
	// �����t�F�[�h�A�E�g
	else
	{
		revised_brightness = (int)press_key_brightness / 40;	// 40�������l�Ƃ��Ē��x�悩����

		// �L�[�������ꂽ�Ƃ�����1�b�ȓ��Ȃ�t�F�[�h�A�E�g
		if ((now_time_ms >= press_key_time_ms) && (now_time_ms <= (press_key_time_ms + 1000)))
		{
			brightness = press_key_brightness - (cnt_frame * revised_brightness);
		}
	}

	SetDrawBright(brightness, brightness, brightness);

	cnt_frame++;

	// �^�C�g����
	// �ʏ펞�F5�b�o�߁A�������F�t�F�[�h�A�E�g�������Ԃ���0.5�b�o��
	if ((now_time_ms >= (5 * 1000)) || ((is_press_key == true) && (now_time_ms >= (press_key_time_ms + 1500))))
	{
		g_next_scene = TITLE;
	}

}

/* ----------------------------------------
�֐����FRenderLogo
�T�v�@�F�Q�[�����S�̕`�揈��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void RenderLogo(void)
{
	if (g_next_scene == LOGO)
	{
		logo.Draw();
	}
	else
	{
		SetDrawBright(MAX_BRIGHTNESS, MAX_BRIGHTNESS, MAX_BRIGHTNESS);		// �߂��Ă���
	}
}
