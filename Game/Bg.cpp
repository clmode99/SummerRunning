//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Bg.cpp
//!
//! @brief  Bg�N���X�̒�`
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "Bg.h"


/* �N���X�̒�` */
/* ----------------------------------------
�֐����FBg::Bg
�T�v�@�FBg�N���X�̃R���X�g���N�^
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�
---------------------------------------- */
Bg::Bg(BG_TYPE type)
	: Object(640, 480, 0.0f, 0.0f, 0.0f, 0.0f), type(type)
{
	if (type == SCROLL)
	{
		ResetPosition();
	}
}

/* ----------------------------------------
�֐����FBg::Update
�T�v�@�F�X�V����
�����@�F��������(const int)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Bg::Update(const int time_limit)
{
	/* �X�N���[������ */
	if (type == SCROLL)
	{
		if (is_draw1 == true)
		{
			grp_y -= spd_y;
			if ((grp_y < 0) && (is_draw2 == false))
			{
				grp_y2 = 960;
				is_draw2 = true;
			}
			if (grp_y < -480)
			{
				is_draw1 = false;
			}
		}

		if (is_draw2 == true)
		{
			grp_y2 -= spd_y;
			if ((grp_y2 < 0) && (is_draw1 == false))
			{
				grp_y = 958;			// -2���Ă�͔̂�����
				is_draw1 = true;
			}

			if (grp_y2 < -480)
			{
				is_draw2 = false;
			}
		}
	}

	/* �P�O�b�؂�����X�s�[�h�A�b�v */
	if (time_limit < 10)
	{
		UpSpeed();
	}
}

/* ----------------------------------------
�֐����FBg::Draw
�T�v�@�F�`�揈��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Bg::Draw(void)
{
	if (type == SCROLL)
	{
		if (is_draw1 == true)
		{
			DrawRectGraph(pos_x, pos_y, 0, grp_y, 640, 480, grp_handle, TRUE, FALSE);
		}
		if (is_draw2 == true)
		{
			DrawRectGraph(pos_x, pos_y, 0, grp_y2, 640, 480, grp_handle, TRUE, FALSE);
		}
	}
	else
	{
		DrawGraph(pos_x, pos_y, grp_handle, TRUE);
	}
}

/* ----------------------------------------
�֐����FBg::ResetPositon
�T�v�@�F���W�����Z�b�g����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Bg::ResetPosition(void)
{
	grp_height = 960;
	grp_y = 480;
	grp_y2 = 960;
	spd_y = 2;
	is_draw1 = true;
	is_draw2 = false;
}

/* ----------------------------------------
�֐����FBg::Upspeed
�T�v�@�F���x���グ��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Bg::UpSpeed(void)
{
	spd_y = 4;
}
