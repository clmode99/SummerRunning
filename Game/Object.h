//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Object.h
//!
//! @brief  Object�N���X�̐錾
//!
//! @date   2016.08.12
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �N���X�̐錾 */
class Object
{
public:
	Object();													// �R���X�g���N�^(�����Ȃ��B�S��0�ŏ������B���f�t�H���g����0�ɂ���΂��ꂢ��Ȃ����ȁE�E�E)
	Object(int w, int h, float px, float py, float sx, float sy);	// �R���X�g���N�^(��������)

	void LoadGraphic(const char *file_name);	// �������ɉ摜��ǂݍ���
	virtual void Update();				// �X�V
	virtual void Draw();					// �`��

	// ���W�擾�n
	float GetLeftBorder() const;		// ���[
	float GetRightBorder() const;		// �E�[
	float GetUpBorder() const;			// ��[
	float GetDownBorder() const;		// ���[

protected:
	int grp_handle;		// �O���t�B�b�N�n���h��
	int grp_width;		// �摜�̕�
	int grp_height;		// �摜�̍���
	float pos_x;		// ���W�w
	float pos_y;		// ���W�x
	float spd_x;		// ���x�w
	float spd_y;		// ���x�x
};