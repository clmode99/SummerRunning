//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Common.cpp
//!
//! @brief  ���ʂ��Ďg�����̂̒�`
//!
//! @date   2016.08.31
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "Common.h"
#include "Object.h"
#include <fstream>	// ifstream


/* �O���[�o���ϐ��̒�` */
// �L�[���
static int g_key_code;		// �L�[���
static int g_key_code_old;	// �P�t���[���O�̃L�[���

// ����
static int g_time_ms;			// �Q�[���J�n������o�߂�������(�~���b)
static int g_now_time_ms;		// ���̎���(�~���b)�B�ꎞ�ϐ�
static int g_start_time_ms;		// InitCommon()���̎���(�~���b)�B�ꎞ�ϐ�


/* �֐��̒�` */
/* ----------------------------------------
�֐����FInitCommon
�T�v�@�F����������
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void InitCommon(void)
{
	g_time_ms = 0;
	g_start_time_ms = GetNowCount();	// ���Ԃ��擾
}

/* ----------------------------------------
�֐����FUpdateCommon
�T�v�@�F�X�V����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void UpdateCommon(void)
{
	// �L�[���̍X�V
	g_key_code_old = g_key_code;
	g_key_code = GetJoypadInputState(DX_INPUT_KEY);

	// ���Ԃ̍X�V
	g_now_time_ms = GetNowCount();
	g_time_ms = g_now_time_ms - g_start_time_ms;
}

/* ----------------------------------------------------------------------
�֐����FPressKeyTrigger
�T�v�@�F�L�[����(�g���K�[)
�����@�F�g���K�[���肵�����L�[(GetJoypad�`�̃}�X�N)
�߂�l�F������Ă�(true)�A������ĂȂ� or �����L�[�������ςȂ�(false)
---------------------------------------------------------------------- */
bool PressKeyTrigger(const int direction)
{
	if ((g_key_code & direction) && (g_key_code != g_key_code_old))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* ----------------------------------------------------------------------
�֐����FGetPassageTime
�T�v�@�F���������Ă���̌o�ߎ���(�~���b)���擾����
�����@�Fvoid(�Ȃ�)
�߂�l�F�o�ߎ���(int)
---------------------------------------------------------------------- */
int GetPassageTime(void)
{
	return g_time_ms;
}

/* ----------------------------------------------------------------------
�֐����FCollisionObject
�T�v�@�FObject�^�̃I�u�W�F�N�g���m�̓����蔻��
�����@�F�����蔻�肵�����I�u�W�F�N�g(const Object*, const Object*)
�߂�l�F�������Ă�(true)�A�������ĂȂ�(false)
---------------------------------------------------------------------- */
bool CollisionObject(const Object *object1, const Object *object2)
{
	if ((object1->GetLeftBorder() <= object2->GetRightBorder()) &&
		(object1->GetRightBorder() >= object2->GetLeftBorder()) &&
		(object1->GetUpBorder() <= object2->GetDownBorder()) &&
		(object1->GetDownBorder() >= object2->GetUpBorder()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/* -------------------------------------------------------------------------------------
�֐����FLoadFile
�T�v�@�F�t�@�C����ǂݍ��݁A�w�肵��������ɑ������
�����@�F�ǂݍ��ރt�@�C����(const char*)�A�������ޕ�����(char*)
�߂�l�F�Ȃ�(void)
���Q�l���ЁF�u�Q�[���v���O���}�ɂȂ�O�Ɋo���Ă��������Z�p�vp.20�`p.21
------------------------------------------------------------------------------------- */
void LoadFile(const char *file_name, char *data)
{
	/* ���[�J���ϐ��A�I�u�W�F�N�g�̏����� */
	ifstream input_file(file_name, ifstream::binary);	// �t�@�C�������̂��߂̃I�u�W�F�N�g�H
	int file_size = 0;									// �t�@�C���T�C�Y


	// �t�@�C���T�C�Y�擾
	input_file.seekg(0, ifstream::end);
	file_size = static_cast<int>(input_file.tellg());	// �Ō�̈ʒu���t�@�C���T�C�Y
	
	// ���f�o�b�O����(�ŏI�I�ɂ͏�������)--------------------------------------
	// �ǂݍ��񂾃t�@�C���T�C�Y���t�@�C���ő�l�𒴂����Ƃ��̓G���[
	if (file_size > MAX_STAGE_FILESIZE)
	{
		Error();
	}
	// ------------------------------------------------------------------------


	// �t�@�C����ǂݍ���
	char *file_image = new char[file_size];		// �t�@�C���̒��g(���̈ʒu����Ȃ��Ɠ��I�m�ۂł��Ȃ�)
	input_file.seekg(0, ifstream::beg);
	input_file.read(file_image, file_size);

	CopyString(data, file_image);

	delete[] file_image;	// new������delete����
}

/* -------------------------------------------------------------------------------------
�֐����FCopyString
�T�v�@�F���镶����Ɏw�肵����������R�s�[����Bstrcpy�Ɠ����@�\
�����@�F�R�s�[��̕�����(char[])�A�R�s�[���̕�����(const char[])
�߂�l�F�Ȃ�(void)
------------------------------------------------------------------------------------- */
void CopyString(char copy_1[], const char copy_2[])
{
	for (int i = 0; copy_2[i] != '\0'; i++)
	{
		copy_1[i] = copy_2[i];
	}
}

/* -------------------------------------------------------------------------------------
�֐����FGetStringLength
�T�v�@�F������̒������擾����Bstrlen�Ɠ����@�\
�����@�F�������擾������������(const char[])
�߂�l�F����(int)
------------------------------------------------------------------------------------- */
int GetStringLength(const char string[])
{
	/* ���[�J���ϐ��̏����� */
	int  length = 0;			// ������̒���


	for (int i = 0; string[i] != '\0'; i++)		// i��length���قڈꏏ�����ǁA���₷���d����
	{
		length++;
	}

	return length;
}

/* -------------------------------------------------------------------------------------
�֐����FConvertNumCharToInt
�T�v�@�F���������l(����)�ɕϊ�����
�����@�F����(const char)
�߂�l�F���l(int)
------------------------------------------------------------------------------------- */
int ConvertNumCharToInt(const char c)
{
	return static_cast<int>(c - 48);	// '0' = 48������
}

/* -------------------------------------------------------------------------------------
�֐����FCutDecimalPoint
�T�v�@�F����̏����扽�ʖ�����؂�̂Ă�
�����@�F�ϊ����������l(const float)�A����̏����_�扽��(const int)
�߂�l�F���l(float)
------------------------------------------------------------------------------------- */
float CutDecimalPoint(const float data, const int place)
{
	/* ���[�J���ϐ��̏����� */
	int temp = 1;
	int temp_data = 0;

	// ����̑扽�ʂ̂Ƃ���܂ł𐮐��ɂ���
	for (int i = 1; i <= place; i++)
	{
		temp *= 10;
	}
	temp_data = static_cast<int>(data * temp);

	// �����������ɖ߂��B1.0f�����邱�ƂŎ����ɕϊ����Ă�
	return static_cast<float>(temp_data / (temp*1.0f));
}

/* ----------------------------------------------------------------------
�֐����FError
�T�v�@�F�G���[���͂����ɔ��ł���
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------------------------------------- */
void Error(void)
{
	WaitKey();
}