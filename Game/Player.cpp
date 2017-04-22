//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  Player�N���X�̒�`
//!
//! @date   2016.08.12
//!
//! @author Miyu Hara
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

/* �C���N���[�h�t�@�C�� */
#include "Player.h"
#include "GamePlay.h"
#include "Common.h"


/* �N���X�̒�` */
/* ----------------------------------------
�֐����FPlayer::Player
�T�v�@�FPlayer�N���X�̃R���X�g���N�^
�����@�FObject�N���X�̃����o�A���C�t(int)
�߂�l�F�Ȃ�
---------------------------------------- */
Player::Player(int w, int h, float px, float py, float sx, float sy, int l)
	: Object(w, h, px, py, sx, sy), life(l)
{}

/* ------------------------------------------------------------------------------
�֐����FPlayer::LoadGraph
�T�v�@�F�������Ɏw�肳�ꂽ�摜��ǂݍ��݁A�O���t�B�b�N�n���h�������o�ɑ������
�����@�F�t�@�C����(char*)
�߂�l�F�Ȃ�(void)
------------------------------------------------------------------------------ */
void Player::LoadGraphic(const char *file_name1, const char *file_name2, const char *file_name3)
{
	grp_normal_handle = LoadGraph(file_name1);		// ����
	grp_left_handle = LoadGraph(file_name2);		// ��
	grp_right_handle = LoadGraph(file_name3);		// �E
}

/* ----------------------------------------
�֐����FPlayer::Update
�T�v�@�F�X�V����
�����@�F��������(const int)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::Update(const int time_limit)
{
	// ���������͂��ꂼ��֐������Ă��������ȁ�

	/* �ړ����� */
	if (PressKeyTrigger(PAD_INPUT_LEFT) == true)
	{
		if (pos_x > (7 * CHIP_SIZE))		// ���{�[�_�[���C��(���萔)
		{
			pos_x -= (float)8 * CHIP_SIZE;
		}
	}
	if (PressKeyTrigger(PAD_INPUT_RIGHT) == true)
	{
		if (pos_x < (31 * CHIP_SIZE))		// �E�{�[�_�[���C��(���萔)
		{
			pos_x += (float)8 * CHIP_SIZE;
		}
	}

	/* ���C�t���� */
	now_time = GetPassageTime() / 1000;
	if (now_time != old_time)
	{
		life--;
		old_time = now_time;
	}

	/* �A�j���[�V�������� */
	if (time_limit < 10)			// 10�b�؂����瑬���Ȃ�
	{
		Animation(FAST);
	}
	else							// �ӂ[
	{
		Animation(NORMAL);
	}
}

/* ----------------------------------------
�֐����FPlayer::Draw
�T�v�@�F�`�悷��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::Draw(void)
{
	if (is_damage == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ADD, 127);		// �����ۂ��\��
		is_damage = false;
	}

	DrawGraph(static_cast<int>(pos_x), static_cast<int>(pos_y), grp_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);		// ���ɖ߂�
}

/* ----------------------------------------
�֐����FPlayer::GetLife
�T�v�@�F���C�t���擾����
�����@�F�Ȃ�(void)
�߂�l�F���C�t(int)
---------------------------------------- */
int Player::GetLife(void)
{
	return life;
}

/* ----------------------------------------
�֐����FPlayer::Heal
�T�v�@�F���C�t���񕜂���
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::Heal(void)
{
	life += 2;	// ��

	// �ő�l�ȏ�͉񕜂��Ȃ�����
	if (life > MAX_LIFE)
	{
		life = MAX_LIFE;
	}
}

/* ----------------------------------------
�֐����FPlayer::Damage
�T�v�@�F���C�t�Ƀ_���[�W��^����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::Damage(void)
{
	is_damage = true;

	life -= 1;					// �_���[�W

	// �O�������炱��ȏ�͉�����Ȃ�
	if (life < 0)
	{
		life = 0;
	}
}

/* ----------------------------------------
�֐����FPlayer::ResetLife
�T�v�@�F���C�t�����Z�b�g����
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::ResetLife(void)
{
	life = MAX_LIFE + 1;	// �{�P�͒���
}


/* ----------------------------------------
�֐����FPlayer::Advance
�T�v�@�F�O�ɐi��
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::Advance(void)
{
	pos_y -= 5.0f;
	Animation(FAST);
}

/* ----------------------------------------
�֐����FPlayer::Animation
�T�v�@�F����������
�����@�F�A�j���[�V�����̎��(ANIMATION_SPEED)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::Animation(ANIMATION_SPEED speed)
{
	/* ���[�J���ϐ��̏����� */
	int animation_time = 0;		// �ǂꂭ�炢�̃^�C�~���O�œ�����


	/* ��ނɂ���ē����^�C�~���O���ς�鏈�� */
	switch (speed)
	{
	case NORMAL:
		animation_time = (GetPassageTime() / 125) % 4;		// 125�~���b���ƂɃA�j���[�V����
		break;

	case FAST:
		animation_time = (GetPassageTime() / 100) % 4;		// 100�~���b���ƂɃA�j���[�V����
		break;

	default:												// �����ɂ���̂͂�������
		Error();
		break;
	}

	/* �A�j���[�V�������� */
	switch (animation_time)
	{
	case NORMAL0: case NORMAL1:				//����
		grp_handle = grp_normal_handle;
		break;

	case LEFT:								// ��
		grp_handle = grp_left_handle;
		break;

	case RIGHT:								// �E
		grp_handle = grp_right_handle;
		break;

	default:								// �����ɂ���̂͂�������
		Error();
		break;
	}
}

/* ----------------------------------------
�֐����FPlayer::ResetPositionX
�T�v�@�F�w���W��������Ԃɖ߂�
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::ResetPositionX(void)
{
	pos_x = PLAYER_X;
}

/* ----------------------------------------
�֐����FPlayer::ResetPositionY
�T�v�@�F�x���W��������Ԃɖ߂�
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::ResetPositionY(void)
{
	pos_y = SCREEN_HEIGHT;
}

/* ----------------------------------------
�֐����FPlayer::ResetPositionAll
�T�v�@�F�w�x���W��������Ԃɖ߂�
�����@�F�Ȃ�(void)
�߂�l�F�Ȃ�(void)
---------------------------------------- */
void Player::ResetPositionAll(void)
{
	ResetPositionX();
	ResetPositionY();
}
