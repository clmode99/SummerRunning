//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Life.h
//!
//! @brief  Life�N���X�̐錾
//!
//! @date   2016.08.19
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �C���N���[�h�t�@�C�� */
#include "Object.h"


/* �N���X�̐錾 */
class Life :public Object
{
public:
	Life(int w, int h, float px, float py, float sx, float sy);				// �R���X�g���N�^
	
	void LoadGraphic(const char *file_name1, const char *file_name2);		// �������ɉ摜��ǂݍ���
	void Draw(const int player_life);										// �`��

private:
	int grp_damage_handle;			// �O���t�B�b�N�n���h��(�_���[�W��)
};