//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SpriteStudioPlayer.h
//!
//! @brief  SpriteStudio��2D�A�j���[�V�����f�[�^�Đ��֘A�̃w�b�_�t�@�C��
//!
//! @date   2016/6/15
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <ssbpLib\SS5Player.h>




// �^�̒�` ================================================================
typedef int HAPACK;       //!< �A�j���[�V�����p�b�N�n���h��
typedef int HASPRITE;     //!< �A�j���[�V�����X�v���C�g�n���h��




// �֐��̐錾 ==============================================================

// SpriteStudio�v���[���[�֘A --------------------------------------------

// SpriteStudio�v���[���[�̍X�V
int UpdateSpriteStudioPlayers();

// SpriteStudio�v���[���[�̏I������
int FinalizeSpriteStudioPlayers();



// �A�j���[�V�����f�[�^�֘A --------------------------------------------

// �A�j���[�V�����p�b�N�t�@�C���̓ǂݍ���
HAPACK LoadAPack(const char* FileName);

// �A�j���[�V�����p�b�N���������ォ��폜����
int DeleteAPack(HAPACK APackHandle);

// �A�j���[�V�����X�v���C�g���쐬
HASPRITE CreateASprite(HAPACK APackHandle);

// �A�j���[�V�����X�v���C�g���������ォ��폜����
int DeleteASprite(HASPRITE ASpriteHandle);



// �A�j���[�V�����̐���֘A ---------------------------------------------

// �A�j���[�V�����X�v���C�g�̃A�j���[�V�������Đ�����
int PlayASprite(const char* AnimationName, int Loop, int StartFrameNo, HASPRITE ASpriteHandle);

// �A�j���[�V�����X�v���C�g�̃A�j���[�V�����𒆒f����
int PauseASprite(HASPRITE ASpriteHandle);

//�A�j���[�V�����X�v���C�g�̃A�j���[�V�������ĊJ����
int ResumeASprite(HASPRITE ASpriteHandle);

// �A�j���[�V�����X�v���C�g�̃A�j���[�V�������~����
int StopASprite(HASPRITE ASpriteHandle);

// �A�j���[�V�����X�v���C�g�̃A�j���[�V�������Đ��������ׂ�
int CheckASprite(HASPRITE ASpriteHandle);



// �A�j���[�V�����X�v���C�g�̕`��֘A -----------------------------------

// �A�j���[�V�����X�v���C�g�̕`��
int DrawASprite(int x, int y, HASPRITE ASpriteHandle, int TransFlag);

// �A�j���[�V�����X�v���C�g��LR���]�`��
int DrawTurnASprite(int x, int y, HASPRITE ASpriteHandle, int TransFlag);

// �A�j���[�V�����X�v���C�g�̊g��k���`��
int DrawExtendASprite(int x, int y, double ExtRate, HASPRITE ASpriteHandle, int TransFlag);

// �A�j���[�V�����X�v���C�g�̉�]�`��
int DrawRotaASprite(int x, int y, double ExtRate, double Angle, HASPRITE ASpriteHandle, int TransFlag, int TurnFlag);
