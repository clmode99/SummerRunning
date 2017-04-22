//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   TimeLimit.h
//!
//! @brief  TimeLimit�N���X�̐錾
//!
//! @date   2016.09.02
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �N���X�̐錾 */
class TimeLimit
{
public:
	TimeLimit(void);		// �R���X�g���N�^
	
	void LoadFont(const char *font_name);	// �t�H���g��ǂݍ���

	void Update(void);		// �X�V
	void Draw(void);		// �`��

	int GetTimeLimit(void);		// �������Ԃ��擾����
	void ResetTimeLimit(void);	// �������Ԃ����Z�b�g����
	
private:
	int time_limit;		// ��������
	int font_handle;	// �t�H���g�n���h��
};