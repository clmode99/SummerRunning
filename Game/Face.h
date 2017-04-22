//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Face.h
//!
//! @brief  Face�N���X�̐錾
//!
//! @date   2016.09.05
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �C���N���[�h�t�@�C�� */
#include "Object.h"


/* �N���X�̐錾 */
class Face :public Object
{
public:
	Face(int w, int h, float px, float py, float sx, float sy);			// �R���X�g���N�^
	
	void LoadGraphic(const char *file_name1, const char *file_name2, const char *fine_name3);		// �������ɉ摜��ǂݍ���
	void Update(const int player_life);										// �X�V

private:
	int grp_fine_handle;		// �O���t�B�b�N�n���h���i�m�[�}���j
	int grp_caution_handle;		// �O���t�B�b�N�n���h���i���Ӂj
	int grp_danger_handle;		// �O���t�B�b�N�n���h���i�댯�j
};