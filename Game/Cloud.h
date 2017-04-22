//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Cloud.h
//!
//! @brief  Cloud�N���X�̐錾
//!
//! @date   2016.09.09
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �C���N���[�h�t�@�C�� */
#include "Object.h"


/* �N���X�̐錾 */
class Cloud :public Object
{
public:
	Cloud(int w, int h, float px, float py, float sx, float sy);		// �R���X�g���N�^
	
	void Update(void);			// �X�V
};