//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  Player�N���X�̐錾
//!
//! @date   2016.08.12
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* ��d�C���N���[�h�̖h�~ */
#pragma once


/* �C���N���[�h�t�@�C�� */
#include "Object.h"


/*�@�񋓌^�̐錾*/
enum ANIMATION_SPEED
{
	NORMAL,		// �ӂ[
	FAST		// �͂₢
};

enum ANIMATION_KIND
{
	NORMAL0,	// �m�[�}���O�B���������ǒ��g�͈Ⴄ
	LEFT,		// ��
	NORMAL1,	// �m�[�}���P�B���������ǒ��g�͈Ⴄ
	RIGHT,		// �E
};

/* �N���X�̐錾 */
class Player:public Object
{
public:
	Player(int w, int h, float px, float py, float sx, float sy, int l);		// �R���X�g���N�^
	
	void LoadGraphic(const char *file_name1, const char *file_name2, const char *file_name3);	// �������ɉ摜��ǂݍ���
	void Update(const int time_limit);															// �X�V
	void Draw(void);																			// �`��

	int GetLife(void);		// ���C�t���擾����
	void Heal(void);		// ���C�t���񕜂���
	void Damage(void);		// ���C�t�Ƀ_���[�W��^����
	void ResetLife(void);	// ���C�t�����Z�b�g����

	void Advance(void);							// �O�ɐi��
	void Animation(ANIMATION_SPEED speed);		// ����������
	
	void ResetPositionX(void);		// �w���W��������Ԃɖ߂�
	void ResetPositionY(void);		// �x���W��������Ԃɖ߂�
	void ResetPositionAll(void);	// �w�x���W��������Ԃɖ߂�

private:
	
	int life;				// ���C�t

	int now_time;			// ���̎���(�b)�B�ꎞ�ϐ�
	int old_time;			// �P�b�O�̎���(�b�j�B�ꎞ�ϐ�

	int grp_normal_handle;	// �O���t�B�b�N�n���h���i���ʁj
	int grp_left_handle;	// �O���t�B�b�N�n���h���i���j
	int grp_right_handle;	// �O���t�B�b�N�n���h���i�E�j

	bool is_damage;			// �_���[�W���󂯂���
};