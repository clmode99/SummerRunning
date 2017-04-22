//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Balloon.cpp
//!
//! @brief  Balloon�N���X�̒�`
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "Balloon.h"


/* �N���X�̒�` */
/* -------------------------------------------------------
�֐����FBalloon::Balloon
�T�v�@�FBalloon�N���X�̃R���X�g���N�^
�����@�F��(int)�A����(int)�A���W�w(float)�A���W�x(float)
		���x�w(float)�A���W�x(float)
�߂�l�F�Ȃ�
-------------------------------------------------------- */
Balloon::Balloon(int w, int h, float px, float py, float sx, float sy)
	:Object(w, h, px, py, sx, sy), 
	grp_caution_handle(0),grp_danger_handle(0)
{}

/* -------------------------------------------------------
�֐����FBalloon::LoadGraphic
�T�v�@�F�摜���������ɓǂݍ���
�����@�F�ǂݍ��މ摜�̃t�@�C����(const char*,const char*)
�߂�l�F�Ȃ�(void)
-------------------------------------------------------- */
void Balloon::LoadGraphic(const char *file_name1, const char *file_name2)
{
	grp_caution_handle = LoadGraph(file_name1);			// ����
	grp_danger_handle = LoadGraph(file_name2);			// �댯
}

/* -------------------------------------------------------
�֐����FBalloon::Update
�T�v�@�F�X�V����
�����@�F�v���C���[�̃��C�t(const int)
�߂�l�F�Ȃ�(void)
-------------------------------------------------------- */
void Balloon::Update(const int player_life)
{
	/* ���C�t�ɉ����ăO���t�B�b�N�n���h����ݒ肷�� */
	if (player_life >= 7)				// �m�[�}��(�V�`�P�O�j
	{
		grp_handle = -1;
	}
	else if (player_life >= 4)			// ����(�S�`�U�j
	{
		grp_handle = grp_caution_handle;
	}
	else								//�댯(�O�`�R�j
	{
		grp_handle = grp_danger_handle;
	}
}