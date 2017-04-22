//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   WinMain.cpp
//!
//! @brief  �v���O�����̃G���g���[�|�C���g�̃\�[�X�t�@�C��
//!
//! @date   2015/5/01
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Libralies\GameLib.h"
#include "Game\GameMain.h"
#include "Resources\Icon\resource.h"
#include "Game\Common.h"



// �֐���` ================================================================

//----------------------------------------------------------------------
//! @brief �v���O�����̃G���g���[�|�C���g
//!
//! @param[in] hInstance     ���݂̃C���X�^���X�̃n���h��
//! @param[in] hPrevInstance �ȑO�̃C���X�^���X�̃n���h��(���NULL)
//! @param[in] lpCmdLine     �R�}���h���C��
//! @param[in] nCmdShow      �E�B���h�E�̕\�����
//!
//! @retval  0 ����I��
//! @retval -1 �ُ�I��
//----------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ���g�p�����̌x���΍�
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(nCmdShow);


#if defined(_DEBUG)
	// �������[���[�N���o�@�\�̃Z�b�g�A�b�v
	SetUpMemoryLeakDetector();
#endif


	// �f�o�b�O���p���O�t�@�C���̏o�̗͂}��
	SetOutApplicationLogValidFlag(FALSE);


	// �N�����[�h�̐ݒ�
#if defined(_DEBUG)
	ChangeWindowMode(TRUE);	          // �E�C���h�E���[�h�Ŏ��s
	SetMainWindowText(GAME_TITLE);    // �E�C���h�E�^�C�g���̐ݒ�
	SetWindowIconID(IDI_ICON1);       // �E�C���h�E�A�C�R���̐ݒ�
#else
	ChangeWindowMode(FALSE);	      // �t���X�N���[���Ŏ��s
#endif


	// DX���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return -1;    // �G���[���N�����璼���ɏI��
	}


	// ��ʃ��[�h�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);


	// �`���𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	
	// �Q�[���̏���
	InitializeGame();                    // �Q�[���̏���������
	
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{ 
		UpdateFrameTimer();                  // �t���[���^�C�}�[�̍X�V 
		
		UpdateGame();                        // �Q�[���̍X�V����
		UpdateSpriteStudioPlayers();         // SpriteStudio�v���[���[�̍X�V

		RenderGame();                        // �Q�[���̕`�揈��

		ScreenFlip();                        // ����ʂ̓��e��\��ʂɔ��f
		ClearDrawScreen();                   // ����ʂ̏���
	}

	FinalizeGame();                      // �Q�[���̏I������
	FinalizeSpriteStudioPlayers();       // SpriteStudio�v���[���[�̏I������


	// DX���C�u�����̏I������
	DxLib_End();


	return 0;    // ����I��
}
