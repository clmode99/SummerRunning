//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ItemMgr.h
//!
//! @brief  ItemMgr�N���X�̐錾
//!
//! @date   2016.09.15
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �C���N���[�h�t�@�C�� */
#include "Item.h"
#include "Common.h"
#include "GamePlay.h"


/* �N���X�̐錾 */
class ItemMgr
{
public:
	ItemMgr(void);						// �R���X�g���N�^

	void Init(void);														// ������
	void LoadGraphic(const char *file_name1, const char *file_name2);		// �������ɉ摜��ǂݍ���
	void Update(const int time_limit);										// �X�V
	void Draw(void);														// �`��

	void AllDelete(void);				// �S�ď���
	void AllResetSpeed(void);			// �S�Ă̑��x�����Z�b�g

	Item m_item[MAX_ITEM] = {
		{ 33, 48, ITEM_X, ITEM_Y, 0.0f, 7.0f },
		{ 33, 48, ITEM_X, ITEM_Y, 0.0f, 7.0f },
		{ 33, 48, ITEM_X, ITEM_Y, 0.0f, 7.0f },
		{ 33, 48, ITEM_X, ITEM_Y, 0.0f, 7.0f } };		// �A�C�e��(����C�ɏ������������E�E�E)

private:
	char stage[MAX_STAGE_FILESIZE];				// �X�e�[�W�f�[�^(�����I�m�ۂ������E�E�E)
	int pos_start = 0;							// �X�^�[�g�n�_

	int grp_colditem_handle;					// �O���t�B�b�N�n���h��(�₽��)
	int grp_hotitem_handle;						// �O���t�B�b�N�n���h��(������)
};