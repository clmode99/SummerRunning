//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Common.h
//!
//! @brief  ���ʂ��Ďg������
//!
//! @date   2016.08.19
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �C���N���[�h�t�@�C�� */
#include "Object.h"


/* �}�N���̒�` */
// �Q�[�����
#define SCREEN_WIDTH  (640)		// ��ʂ̕�
#define SCREEN_HEIGHT (480)		// ��ʂ̍���

#define CHIP_SIZE     (16)		// �}�b�v�`�b�v�̑傫��

#define MAX_STAGE_FILESIZE (500)		// �X�e�[�W�t�@�C���ő�l(�������ɒu���͕̂s�K�؂ȋC�����邵�A���I�m�ۂ������E�E�E)


/* �񋓌^�̒�` */
enum SCENE
{
	LOGO,
	TITLE,
	CREDIT,
	PLAY,
};


/* �֐��̃v���g�^�C�v�錾 */
void InitCommon(void);						// ������
void UpdateCommon(void);					// �X�V

// ���C�u����(�H)�֐�
//	�L�[�����n
bool PressKeyTrigger(const int direction);					// �L�[����(�g���K�[)

//	����
int GetPassageTime(void);									// ���������Ă���̌o�ߎ���(�~���b)���擾����

//	�����蔻��
bool CollisionObject(const Object *object1, const Object *object2);		// Object�^���m�̓����蔻��

//	�t�@�C������
void LoadFile(const char *file_name, char *data);			// �t�@�C����ǂݍ��݁A�w�肵��������ɑ������

//	�����񏈗�
void CopyString(char copy_1[], const char copy_2[]);		// ��������R�s�[����
int GetStringLength(const char string[]);					// ������̒������擾����
int ConvertNumCharToInt(const char c);						// ���������l�ɕϊ�����

// ���l�ϊ�����
float CutDecimalPoint(const float data, const int place);	// ����̏����_�扽�ʖ�����؂�̂Ă�

//	�G���[
void Error(void);			// �G���[���o