//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Life.cpp
//!
//! @brief  Life�N���X�̒�`
//!
//! @date   2016.08.19
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "GamePlay.h"
#include "Life.h"


/* �N���X�̒�` */
/* ----------------------------------------
�֐����FLife::Life
�T�v�@�FLife�N���X�̃R���X�g���N�^
�����@�F��(int)�A����(int)�A���W�w(float)�A���W�x(float)
		���x�w(float)�A���W�x(float)
�߂�l�F�Ȃ�
---------------------------------------- */
Life::Life(int w, int h, float px, float py, float sx, float sy)
	:Object(w, h, px, py, sx, sy),
	grp_damage_handle(0)
{}

/* ----------------------------------------
�֐����FLife::LoadGraphic
�T�v�@�F�摜���������ɓǂݍ���
�����@�F�t�@�C����(const char*, const char*)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Life::LoadGraphic(const char *file_name1, const char *file_name2)
{
	grp_handle = LoadGraph(file_name1);			// ���C�t
	grp_damage_handle = LoadGraph(file_name2);	// �_���[�W
}

/* ----------------------------------------
�֐����FLife::Draw
�T�v�@�F�`�悷��
�����@�F�v���C���[�̃��C�t(const int)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Life::Draw(const int player_life)
{
	/* ���[�J���ϐ��̏����� */
	int grp_handle_temp = 0;			// �O���t�B�b�N�n���h���B�ꎞ�ϐ�

	for (int i = 1; i <= MAX_LIFE; i++)
	{
		if (i <= player_life)
		{
			grp_handle_temp = grp_handle;
		}
		else
		{
			grp_handle_temp = grp_damage_handle;
		}

		DrawGraph(static_cast<int>(pos_x + (CHIP_SIZE * 2 * i)), static_cast<int>(pos_y), grp_handle_temp, TRUE);
	}
	
}