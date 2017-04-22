//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   TimeLimit.cpp
//!
//! @brief  TimeLimit�N���X�̒�`
//!
//! @date   2016.09.02
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "TimeLimit.h"
#include "Common.h"
#include "GamePlay.h"


/* �N���X�̒�` */
/* ----------------------------------------
�֐����FTimeLimit::TimeLimit
�T�v�@�FTimeLimit�N���X�̃R���X�g���N�^
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�
---------------------------------------- */
TimeLimit::TimeLimit(void)
	:time_limit(MAX_TIME_LIMIT), font_handle(0)
{}

/* ----------------------------------------
�֐����FTimeLimit::LoadFont
�T�v�@�F�t�H���g�f�[�^���������ɓǂݍ���
�����@�F�t�H���g��(const char*)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void TimeLimit::LoadFont(const char *font_name)
{
	font_handle = CreateFontToHandle(font_name, 23, 5, DX_FONTTYPE_ANTIALIASING);
}

/* ----------------------------------------
�֐����FTimeLimit::Update
�T�v�@�F�X�V����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void TimeLimit::Update(void)
{
	time_limit = MAX_TIME_LIMIT - (GetPassageTime() / 1000);
}

/* ----------------------------------------
�֐����FTimeLimit::Draw
�T�v�@�F�`�揈��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void TimeLimit::Draw(void)
{
	if (time_limit <= 5)
	{
		DrawFormatStringToHandle(595, 10, GetColor(255, 0, 0), font_handle, "%02d", time_limit);
	}
	else
	{
		DrawFormatStringToHandle(595, 10, GetColor(0, 0, 0), font_handle, "%02d", time_limit);
	}
}

/* ----------------------------------------
�֐����FTimeLimit::GetTimeLimit
�T�v�@�F�������Ԃ��擾����
�����@�F�Ȃ�(void)
�߂�l�F��������(int)
---------------------------------------- */
int TimeLimit::GetTimeLimit(void)
{
	return time_limit;
}

/* ----------------------------------------
�֐����FTimeLimit::ResetTimeLimit
�T�v�@�F�������Ԃ����Z�b�g����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void TimeLimit::ResetTimeLimit(void)
{
	time_limit = MAX_TIME_LIMIT;
}
