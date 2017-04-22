//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ItemMgr.cpp
//!
//! @brief  ItemMgr�N���X�̒�`
//!
//! @date   2016.09.15
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "ItemMgr.h"
#include "Common.h"


/* �N���X�̒�` */
/* ------------------------------------------------------------------------------
�֐����FItemMgr::ItemMgr
�T�v�@�FItemMgr�N���X�̃R���X�g���N�^
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�
------------------------------------------------------------------------------ */
ItemMgr::ItemMgr(void)
{
	LoadFile("stage.txt", stage);	// �X�e�[�W�f�[�^��ǂݍ���
}

/* ------------------------------------------------------------------------------
�֐����FItemMgr::ItemMgr
�T�v�@�F����������
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
------------------------------------------------------------------------------ */
void ItemMgr::Init(void)
{
	pos_start = 0;	

	// �f�[�^�̃X�^�[�g�n�_�����߂�
	int new_line = 0;					// ���s�J�E���^�B�ꎞ�ϐ�

	for (int i = 0; new_line < 4; i++)	//�S����s�����Ƃ��낪�����X�^�[�g�n�_
	{
		pos_start++;
		if (stage[i] == '\n')
		{
			new_line++;
		}
	}

	AllDelete();
	AllResetSpeed();
}

/* ------------------------------------------------------------------------------
�֐����FItemMgr::LoadGraphic
�T�v�@�F�������Ɏw�肳�ꂽ�摜��ǂݍ��݁A�O���t�B�b�N�n���h�������o�ɑ������
�����@�F�t�@�C����(const char*, const char*)
�߂�l�F�Ȃ�(void)
------------------------------------------------------------------------------ */
void ItemMgr::LoadGraphic(const char *file_name1, const char *file_name2)
{
	grp_colditem_handle = LoadGraph(file_name1);
	grp_hotitem_handle = LoadGraph(file_name2);
	/*for (int i = 0; i < MAX_ITEM; i++)
	{
		m_item[i].LoadGraphic(file_name);
	}*/
}

/* ------------------------------------------------------------------------------
�֐����FItemMgr::Update
�T�v�@�F�X�V����
�����@�F��������(const int)
�߂�l�F�Ȃ�(void)
------------------------------------------------------------------------------ */
void ItemMgr::Update(const int time_limit)
{
	/* ���[�J���ϐ��̏����� */
	int appearance_time = 0;		// �o������(�b)
	int appearance_lane = 0;		// �o�����[��(�O�`�R�j
	char item_type = '\0';			// �A�C�e���̎�ށB�t�@�C������ǂݍ��񂾂�����Ă����B�ꎞ�ϐ�
	KIND item_kind = NONE;			// �A�C�e���̎�ށB�֐��ɓn���p�B�ꎞ�ϐ�
	int grp_item_handle = 0;		// �A�C�e���̃O���t�B�b�N�n���h���B�ꎞ�ϐ�
	const int STAGE_WIDTH = 8;		// �X�e�[�W�f�[�^�̕�


	/* �w�肵�����ԂɂȂ�����A���ݕ������ */
	for (int i = 0; stage[pos_start + (STAGE_WIDTH * i)] != '\0'; i++)			// �s
	{
		for (int j = 0; stage[pos_start + (STAGE_WIDTH * i + j)] != '\n'; j++)	// ��
		{
			// �o������
			if (j == 0)			// �P�O�̈�
			{
				appearance_time = (ConvertNumCharToInt(stage[pos_start + (j + STAGE_WIDTH * i)])) * 10;
			}
			if (j == 1)			// �P�̈�
			{
				appearance_time += ConvertNumCharToInt(stage[pos_start + (j + STAGE_WIDTH * i)]);
			}

			// �o�����[��
			if (j == 3)
			{
				appearance_lane = ConvertNumCharToInt(stage[pos_start + (j + STAGE_WIDTH * i)]);
			}

			// �A�C�e���̎��
			if (j == 5)
			{
				item_type = stage[pos_start + (j + STAGE_WIDTH * i)];		// ���̂ق����킩��₷���E�E�E�H
				
				if (item_type == 'C')
				{
					item_kind = COLD;
					grp_item_handle = grp_colditem_handle;
				}
				if (item_type == 'H')
				{
					item_kind = HOT;
					grp_item_handle = grp_hotitem_handle;
				}
			}
		}

		if (time_limit == appearance_time)
		{
			if (m_item[appearance_lane].IsExistState() == false)
			{
				m_item[appearance_lane].Create(appearance_lane, grp_item_handle, item_kind);
				pos_start += STAGE_WIDTH;		// �X�^�[�g�n�_���X�V����
			}
		}
	}


	/* ���݂��Ă���ݕ��̍X�V */
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_item[i].IsExistState() == true)
		{
			if (time_limit < 10)
			{
				m_item[i].UpSpeed();
			}

			m_item[i].Update();
		}
	}
}

/* ------------------------------------------------------------------------------
�֐����FItemMgr::Draw
�T�v�@�F�`�揈��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
------------------------------------------------------------------------------ */
void ItemMgr::Draw(void)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_item[i].IsExistState() == true)
		{
			m_item[i].Draw();
		}
	}
}

/* ------------------------------------------------------------------------------
�֐����FItemMgr::AllDelete
�T�v�@�F�`�悵�Ă���̂�S�ď���
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
------------------------------------------------------------------------------ */
void ItemMgr::AllDelete(void)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		if (m_item[i].IsExistState() == true)
		{
			m_item[i].Delete();
		}
	}
}

/* ------------------------------------------------------------------------------
�֐����FItemMgr::AllResetSpeed
�T�v�@�F���x��S�ă��Z�b�g����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
------------------------------------------------------------------------------ */
void ItemMgr::AllResetSpeed(void)
{
	for (int i = 0; i < MAX_ITEM; i++)
	{
		m_item[i].ResetSpeed();
	}
}