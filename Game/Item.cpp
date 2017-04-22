//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Item.cpp
//!
//! @brief  Item�N���X�̒�`
//!
//! @date   2016.09.15
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "Item.h"
#include "Common.h"	// SCREEN_HEIGHT
#include "GamePlay.h"


/* �N���X�̒�` */
/* ----------------------------------------
�֐����FItem::Item
�T�v�@�FItem�N���X�̃R���X�g���N�^
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�
---------------------------------------- */
Item::Item(int w, int h, float px, float py, float sx, float sy)
	: Object(w, h, px, py, sx, sy), exist_state(false), kind(NONE), is_fadeout(false), opacity(MAX_OPACITY)
{}

/* ----------------------------------------
�֐����FItem::Update
�T�v�@�F�X�V����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Item::Update(void)
{
	// �ړ�����(���֐������)
	if (is_fadeout == false)
	{
		pos_y += spd_y;
	}

	// ��ʉ��܂ł��������
	if (pos_y >= SCREEN_HEIGHT)
	{
		Delete();
	}

	// ����������t�F�[�h�A�E�g����(���֐������)
	if (is_fadeout == true)
	{
		pos_y += 4.0f;			// �኱���W�����邱�ƂŁA������ۂ����o�ɂ��Ă݂�
		
		opacity -= 40;			// �S�O�����x�悩����
		if (opacity <= 0)
		{
			Delete();
		}
	}
}

/* ----------------------------------------
�֐����FItem::Draw
�T�v�@�F�`�揈��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Item::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, opacity);			// �s�����x�ݒ�

	DrawGraph((int)pos_x, (int)pos_y, grp_handle, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				// ���Ƃɖ߂��Ȃ��Ƃ��������Ȃ�
}

/* --------------------------------------------------------------
�֐����FItem::Create
�T�v�@�F�A�C�e�������
�����@�F�o�����[��(const int)�A�O���t�B�b�N�n���h��(const int)�A���(const KIND)
�߂�l�F�Ȃ�(void)
--------------------------------------------------------------- */
void Item::Create(const int lane, const int handle, const KIND kind_temp)
{
	// �A�C�e���̍��W�w�����߂�(���֐������)
	switch (lane)
	{
	case 0:
		pos_x = ITEM0_X;
		break;

	case 1:
		pos_x = ITEM1_X;
		break;

	case 2:
		pos_x = ITEM2_X;
		break;

	case 3:
		pos_x = ITEM3_X;
		break;

	default:
		Error();
		break;
	}

	// �O���t�B�b�N�n���h���ݒ� (LoadGraphic�I��)
	grp_handle = handle;

	// ��ސݒ�
	kind = kind_temp;

	exist_state = true;
}

/* ----------------------------------------
�֐����FItem::Delete
�T�v�@�F�A�C�e��������
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Item::Delete(void)
{
	exist_state = false;
	is_fadeout = false;
	opacity = MAX_OPACITY;
	kind = NONE;
	grp_handle = 0;

	// �ʒu��߂�
	pos_x = 0.0f;
	pos_y = 0.0f;
}

/* ----------------------------------------
�֐����FItem::UpSpeed
�T�v�@�F���x���グ��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Item::UpSpeed(void)
{
	spd_y = 9.0f;
}

/* ----------------------------------------
�֐����FItem::ResetSpeed
�T�v�@�F���x�����Z�b�g����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Item::ResetSpeed(void)
{
	spd_y = 7.0f;
}

/* ----------------------------------------
�֐����FItem::IsExistState
�T�v�@�F�A�C�e�������݂��邩
�����@�F�Ȃ�(void)
�߂�l�F���݂���(true)�A���݂��Ȃ�(false)
---------------------------------------- */
bool Item::IsExistState(void)
{
	return exist_state;
}

/* ----------------------------------------
�֐����FItem::GetKind
�T�v�@�F��ނ��擾����
�����@�F�Ȃ�(void)
�߂�l�F���(KIND)
---------------------------------------- */
KIND Item::GetKind(void)
{
	return kind;
}

/* ----------------------------------------------------
�֐����FItem::IsFadeOut
�T�v�@�F�t�F�[�h�A�E�g���Ă邩
�����@�F�Ȃ�(void)
�߂�l�F�t�F�[�h�A�E�g���Ă�(true)�A���ĂȂ�(false)
---------------------------------------------------- */
bool Item::IsFadeOut(void)
{
	return is_fadeout;
}

/* ----------------------------------------
�֐����FItem::StartFadeout
�T�v�@�F�t�F�[�h�A�E�g�J�n
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Item::StartFadeout(void)
{
	is_fadeout = true;
}