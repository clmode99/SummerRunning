//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Object.cpp
//!
//! @brief  Object�N���X�̒�`
//!
//! @date   2016.08.12
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "Object.h"


/* �N���X�̒�` */
/* ----------------------------------------
�֐����FObject::Object
�T�v�@�FObject�N���X�̃R���X�g���N�^(�����Ȃ�)
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�
---------------------------------------- */
Object::Object()
	:grp_width(0), grp_height(0), pos_x(0.0f), pos_y(0.0f), spd_x(0.0f), spd_y(0.0f), grp_handle(0)
{}

/* -------------------------------------------------------
�֐����FObject::Object
�T�v�@�FObject�N���X�̃R���X�g���N�^(��������)
�����@�F��(int)�A����(int)�A���W�w(float)�A���W�x(float)
		���x�w(float)�A���W�x(float)
�߂�l�F�Ȃ�
------------------------------------------------------- */
Object::Object(int w, int h, float px, float py, float sx, float sy)
	:grp_width(w), grp_height(h), pos_x(px), pos_y(py), spd_x(sx), spd_y(sy), grp_handle(0)
{}

/* ----------------------------------------
�֐����FObject::Update
�T�v�@�F�X�V����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Object::Update()
{}

/* ----------------------------------------
�֐����FObject::Draw
�T�v�@�F�`�悷��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Object::Draw()
{
	DrawGraph(static_cast<int>(pos_x), static_cast<int>(pos_y), grp_handle, TRUE);
}

/* ------------------------------------------------------------------------------
�֐����FObject::LoadGraph
�T�v�@�F�������Ɏw�肳�ꂽ�摜��ǂݍ��݁A�O���t�B�b�N�n���h�������o�ɑ������
�����@�F�t�@�C����(const char*)
�߂�l�F�Ȃ�(void)
------------------------------------------------------------------------------ */
void Object::LoadGraphic(const char *file_name)
{
	grp_handle = LoadGraph(file_name);
}

/* ------------------------------------------------------------------------------
�֐����FObject::GetLeftBorder
�T�v�@�F���[�̍��W���擾����
�����@�F�Ȃ�(void)
�߂�l�F���[�̍��W(float)
------------------------------------------------------------------------------ */
float Object::GetLeftBorder() const
{
	return pos_x;
}

/* ------------------------------------------------------------------------------
�֐����FObject::GetRightBorder
�T�v�@�F�E�[�̍��W���擾����
�����@�F�Ȃ�(void)
�߂�l�F�E�[�̍��W(float)
------------------------------------------------------------------------------ */
float Object::GetRightBorder() const
{
	return pos_x + (static_cast<float>(grp_width));
}

/* ------------------------------------------------------------------------------
�֐����FObject::GetUpBorder
�T�v�@�F��[�̍��W���擾����
�����@�F�Ȃ�(void)
�߂�l�F��[�̍��W(float)
------------------------------------------------------------------------------ */
float Object::GetUpBorder() const
{
	return pos_y;
}

/* ------------------------------------------------------------------------------
�֐����FObject::GetDownBorder
�T�v�@�F���[�̍��W���擾����
�����@�F�Ȃ�(void)
�߂�l�F���[�̍��W(float)
------------------------------------------------------------------------------ */
float Object::GetDownBorder() const
{
	return pos_y + (static_cast<float>(grp_height));
}