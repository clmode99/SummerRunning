//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SpriteStudioPlayer.cpp
//!
//! @brief  SpriteStudio��2D�A�j���[�V�����f�[�^�Đ��֘A�̃\�[�X�t�@�C��
//!
//! @date   2016/6/15
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "SpriteStudioPlayer.h"

#include <memory>
#include <string>
#include <unordered_map>

#include <DxLibHelper\FrameTimer.h>




// ���C�u�����̃����N ======================================================
#if defined(_DEBUG)
	#pragma comment( lib, "ssbpLib\\ssbpLib_d.lib")
#else
	#pragma comment( lib, "ssbpLib\\ssbpLib.lib")
#endif




// �N���X��` ==============================================================
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//! @brief �A�j���[�V�����X�v���C�g�N���X
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class AnimationSprite
{
	// �����o�ϐ��̐錾 --------------------------------------------
	private:
		std::unique_ptr<ss::Player> m_ssplayer;    //!< �A�j���[�V�������Đ�����v���[���[
		float                       m_deltaTime;   //!< �A�j���[�V������i�߂�t���[������[s]



	// �����o�֐��̐錾����ђ�` ----------------------------------
	public:
		//------------------------------------------------------
		//! @brief �R���X�g���N�^
		//!
		//! @param[in] animationPackName : �A�j���[�V�����p�b�N��
		//------------------------------------------------------
		AnimationSprite(const std::string& animationPackName)
			: m_ssplayer(ss::Player::create())
		{
			m_ssplayer->setData(animationPackName);
		}


		//------------------------------------------------------
		//! @brief �f�X�g���N�^
		//------------------------------------------------------
		~AnimationSprite() = default;



		//------------------------------------------------------
		//! @brief �A�j���[�V�����̍Đ�
		//!
		//! @param[in] animationName : �Đ�����A�j���[�V������
		//! @param[in] loop          : �Đ����[�v��
		//! @param[in] startFrameNo  : �Đ����J�n����t���[��No
		//!
		//! @return �Ȃ�
		//------------------------------------------------------
		void PlayAnimation(const std::string& animationName, int loop = 0, int startFrameNo = 0)
		{
			m_ssplayer->play(animationName, loop, startFrameNo);
		}


		//------------------------------------------------------
		//! @brief �A�j���[�V�����̒�~
		//!
		//! @param[in] �Ȃ�
		//!
		//! @return �Ȃ�
		//------------------------------------------------------
		void StopAnimation()
		{
			m_ssplayer->stop();
		}


		//------------------------------------------------------
		//! @brief �A�j���[�V�����̒��f
		//!
		//! @param[in] �Ȃ�
		//!
		//! @return �Ȃ�
		//------------------------------------------------------
		void PauseAnimation()
		{
			m_ssplayer->animePause();
		}


		//------------------------------------------------------
		//! @brief �A�j���[�V�����̍ĊJ
		//!
		//! @param[in] �Ȃ�
		//!
		//! @return �Ȃ�
		//------------------------------------------------------
		void ResumeAnimation()
		{
			m_ssplayer->animeResume();
		}


		//------------------------------------------------------
		//! @brief �X�V
		//!
		//! @param[in] dt : �i�߂�t���[������[s]
		//!
		//! @return �Ȃ�
		//------------------------------------------------------
		void Update(float dt)
		{
			m_deltaTime = dt;
		}


		//------------------------------------------------------
		//! @brief �`��
		//!
		//! @param[in] x      : �`�悷��̈�̍��W
		//! @param[in] y      : �`�悷��̈�̍��W
		//! @param[in] scale  : �g�嗦(1.0�œ��{)
		//! @param[in] angle  : �`��p�x(���W�A���w��)
		//!
		//! @return �Ȃ�
		//------------------------------------------------------
		void Draw(int x, int y, double scaleX, double scaleY, double angle)
		{
			int screen_height;
			GetGraphSize(GetDrawScreen(), NULL, &screen_height);

			m_ssplayer->setPosition(static_cast<float>(x), static_cast<float>(screen_height - y));
			m_ssplayer->setScale(static_cast<float>(scaleX), static_cast<float>(scaleY));
			m_ssplayer->setRotation(0.0f, 0.0f, SSRadianToDegree(angle));

			m_ssplayer->update(m_deltaTime);
			m_deltaTime = 0.0f;

			m_ssplayer->draw();
		}


		//------------------------------------------------------
		//! @brief �A�j���[�V�����̏�Ԃ̎擾
		//!
		//! @param[in] �Ȃ�
		//!
		//! @retval 0: ��~��
		//! @retval 1: �Đ���
		//! @retval 2: ���f��
		//------------------------------------------------------
		int GetAnimationState()
		{
			return m_ssplayer->getState();
		}
};




// �^�̕ʖ��錾 ============================================================
using ASpritePtr = std::unique_ptr<AnimationSprite>;




// �t�@�C���X�R�[�v�ϐ��̒�` ==============================================
static std::unordered_map<int, std::string> f_animationPackNameList;    //!< �A�j���[�V�����p�b�N���̃��X�g
static std::unordered_map<int, ASpritePtr>  f_animationSpriteList;      //!< �A�j���[�V�����X�v���C�g�̃��X�g




// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief SpriteStudio�v���[���[�̍X�V
//!
//! @param[in] �Ȃ�
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int UpdateSpriteStudioPlayers()
{
	float dt = GetFrameDeltaTime();

	for (auto& e : f_animationSpriteList)
	{
		e.second->Update(dt);
	}

	return 0;
}



//----------------------------------------------------------------------
//! @brief SpriteStudio�v���[���[�I������
//!
//! @param[in] �Ȃ�
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int FinalizeSpriteStudioPlayers()
{
	f_animationSpriteList.clear();


	auto resourceManager = ss::ResourceManager::getInstance();
	for (auto& e : f_animationPackNameList)
	{
		resourceManager->removeData(e.second);
	}


	f_animationPackNameList.clear();


	return 0;
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����p�b�N�t�@�C���̃������ւ̓ǂ݂���
//!
//! @param[in] FileName : ���[�h����A�j���[�V�����p�b�N�t�@�C���̃t�@�C���p�X������ւ̃|�C���^
//!
//! @retval -1    �F�G���[����
//! @retval -1�ȊO�F�A�j���[�V�����p�b�N�̃n���h��
//----------------------------------------------------------------------
HAPACK LoadAPack(const char* FileName)
{
	auto resourceManager   = ss::ResourceManager::getInstance();
	auto animationPackName = resourceManager->addData(FileName);

	if (!animationPackName.empty())
	{
		int handle = std::hash<std::string>()(animationPackName)& 0x7FFFFFFF;
		f_animationPackNameList.insert(std::make_pair(handle, animationPackName));

		return handle;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �w��̃A�j���[�V�����p�b�N���������ォ��폜����
//!
//! @param[in] APackHandle : �������ォ��폜�������A�j���[�V�����p�b�N�̃n���h��
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int DeleteAPack(HAPACK APackHandle)
{
	auto it = f_animationPackNameList.find(APackHandle);

	if (it != f_animationPackNameList.end())
	{
		auto resourceManager = ss::ResourceManager::getInstance();
		resourceManager->removeData(it->second);

		f_animationPackNameList.erase(it);

		return 0;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g���쐬����
//!
//! @param[in] APackHandle : �쐬����A�j���[�V�����p�b�N�̎��ʔԍ�(�A�j���[�V�����p�b�N�n���h��)
//!
//! @retval -1    �F�G���[����
//! @retval -1�ȊO�F�A�j���[�V�����X�v���C�g�̃n���h��
//----------------------------------------------------------------------
HASPRITE CreateASprite(HAPACK APackHandle)
{
	auto it = f_animationPackNameList.find(APackHandle);

	if (it != f_animationPackNameList.end())
	{
		ASpritePtr animationSprite(new AnimationSprite(it->second));

		int handle = std::hash<ASpritePtr>()(animationSprite) & 0x7FFFFFFF;
		f_animationSpriteList.insert(std::make_pair(handle, std::move(animationSprite)));

		return handle;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g���������ォ��폜����
//!
//! @param[in] APackHandle : �������ォ��폜�������A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int DeleteASprite(HASPRITE ASpriteHandle)
{
	auto a = f_animationSpriteList.erase(ASpriteHandle);

	return 0;
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g�̃A�j���[�V�������Đ�����
//!
//! @param[in] AnimationName : �Đ�����A�j���[�V�������ւ̃|�C���^
//! @param[in] Loop          : �Đ����[�v��
//! @param[in] StartFrameNo  : �Đ����J�n����t���[��No
//! @param[in] ASpriteHandle : �Đ�����A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int PlayASprite(const char* AnimationName, int Loop, int StartFrameNo, HASPRITE ASpriteHandle)
{
	auto it = f_animationSpriteList.find(ASpriteHandle);

	if (it != f_animationSpriteList.end())
	{
		it->second->PlayAnimation(AnimationName, Loop, StartFrameNo);
		return 0;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g�̃A�j���[�V�����𒆒f����
//!
//! @param[in] ASpriteHandle : ���f����A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int PauseASprite(HASPRITE ASpriteHandle)
{
	auto it = f_animationSpriteList.find(ASpriteHandle);

	if (it != f_animationSpriteList.end())
	{
		it->second->PauseAnimation();
		return 0;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g�̃A�j���[�V�������ĊJ����
//!
//! @param[in] ASpriteHandle : �ĊJ����A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int ResumeASprite(HASPRITE ASpriteHandle)
{
	auto it = f_animationSpriteList.find(ASpriteHandle);

	if (it != f_animationSpriteList.end())
	{
		it->second->ResumeAnimation();
		return 0;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g�̃A�j���[�V�������~����
//!
//! @param[in] ASpriteHandle : ��~����A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int StopASprite(HASPRITE ASpriteHandle)
{
	auto it = f_animationSpriteList.find(ASpriteHandle);

	if (it != f_animationSpriteList.end())
	{
		it->second->StopAnimation();
		return 0;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g�̃A�j���[�V�������Đ��������ׂ�
//!
//! @param[in] ASpriteHandle : �Đ���Ԃ𒲂ׂ�A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//!
//! @retval  0�F��~��
//! @retval  1�F�Đ���
//! @retval  2�F���f��
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int CheckASprite(HASPRITE ASpriteHandle)
{
	auto it = f_animationSpriteList.find(ASpriteHandle);

	if (it != f_animationSpriteList.end())
	{
		return it->second->GetAnimationState();
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g�̕`��
//!
//! @param[in] x             : �A�j���[�V�����X�v���C�g��`�悷��̈�̍��W
//! @param[in] y             : �A�j���[�V�����X�v���C�g��`�悷��̈�̍��W
//! @param[in] ASpriteHandle : �`�悷��A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//! @param[in] TransFlag     : �摜�̓����x��L���ɂ��邩�ǂ���(���g�p)
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int DrawASprite(int x, int y, HASPRITE ASpriteHandle, int TransFlag)
{
	auto it = f_animationSpriteList.find(ASpriteHandle);

	if (it != f_animationSpriteList.end())
	{
		it->second->Draw(x, y, 1.0, 1.0, 0.0);
		return 0;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g��LR���]�`��
//!
//! @param[in] x             : �A�j���[�V�����X�v���C�g��`�悷��̈�̍��W
//! @param[in] y             : �A�j���[�V�����X�v���C�g��`�悷��̈�̍��W
//! @param[in] ASpriteHandle : �`�悷��A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//! @param[in] TransFlag     : �摜�̓����x��L���ɂ��邩�ǂ���(���g�p)
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int DrawTurnASprite(int x, int y, HASPRITE ASpriteHandle, int TransFlag)
{
	auto it = f_animationSpriteList.find(ASpriteHandle);

	if (it != f_animationSpriteList.end())
	{
		it->second->Draw(x, y, -1.0, 1.0, 0.0);
		return 0;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g�̊g��k���`��
//!
//! @param[in] x             : �A�j���[�V�����X�v���C�g��`�悷��̈�̍��W
//! @param[in] y             : �A�j���[�V�����X�v���C�g��`�悷��̈�̍��W
//! @param[in] ExtRate       : �g�嗦(1.0�œ��{)
//! @param[in] ASpriteHandle : �`�悷��A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//! @param[in] TransFlag     : �摜�̓����x��L���ɂ��邩�ǂ���(���g�p)
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int DrawExtendASprite(int x, int y, double ExtRate, HASPRITE ASpriteHandle, int TransFlag)
{
	auto it = f_animationSpriteList.find(ASpriteHandle);

	if (it != f_animationSpriteList.end())
	{
		it->second->Draw(x, y, ExtRate, ExtRate, 0.0);
		return 0;
	}
	else
	{
		return -1;
	}
}



//----------------------------------------------------------------------
//! @brief �A�j���[�V�����X�v���C�g�̉�]�`��
//!
//! @param[in] x             : �A�j���[�V�����X�v���C�g��`�悷��̈�̍��W
//! @param[in] y             : �A�j���[�V�����X�v���C�g��`�悷��̈�̍��W
//! @param[in] ExtRate       : �g�嗦(1.0�œ��{)
//! @param[in] Angle         : �`��p�x(���W�A���w��)
//! @param[in] ASpriteHandle : �`�悷��A�j���[�V�����X�v���C�g�̎��ʔԍ�(�A�j���[�V�����X�v���C�g�n���h��)
//! @param[in] TransFlag     : �摜�̓����x��L���ɂ��邩�ǂ���(���g�p)
//! @param[in] TurnFlag      : �摜�̍��E���]���s�����A�̃t���O(FALSE�ŕ��ʂɕ`�� TRUE�Ŕ��])
//!
//! @retval  0�F����
//! @retval -1�F�G���[����
//----------------------------------------------------------------------
int DrawRotaASprite(int x, int y, double ExtRate, double Angle, HASPRITE ASpriteHandle, int TransFlag, int TurnFlag)
{
	auto it = f_animationSpriteList.find(ASpriteHandle);

	if (it != f_animationSpriteList.end())
	{
		double ExtRateX = TurnFlag ? -ExtRate : ExtRate;
		it->second->Draw(x, y, ExtRateX, ExtRate, Angle);
		return 0;
	}
	else
	{
		return -1;
	}
}
