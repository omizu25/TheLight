//**************************************************
//
// Hackathon ( answer.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "answer.h"
#include "rectangle.h"
#include "texture.h"
#include "color.h"
#include "mode.h"
#include "light.h"
#include "player.h"
#include "game.h"
#include "bg.h"

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_TIME = 60;	// �^�C���̍ő�l
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
bool	s_bMax;		// �ő�ɂȂ������ǂ���
bool	s_bAnswer;	// �����Ă邩�ǂ���
int		s_nTime;	// �^�C��
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitAnswer(void)
{
	s_nTime = 0;
	s_bMax = false;
	s_bAnswer = false;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitAnswer(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateAnswer(void)
{
	if (s_bMax)
	{
		s_nTime++;

		if (s_nTime >= MAX_TIME)
		{
			if (s_bAnswer)
			{
				s_bMax = false;
				s_nTime = 0;
				s_bAnswer = true;

				// �Q�[����ʂ̔w�i�Q�[�W(���F)�̑���
				IncreaseGaugeGame();

				// �Q�[����Ԃ̐ݒ�
				SetGameState(GAMESTATE_RESET);

				// ��`�̐F�̐ݒ�
				SetColorRectangle(GetBG(), GetColor(COLOR_WHITE));
			}
			else
			{
				s_bMax = true;
				s_nTime = 0;
				s_bAnswer = false;

				// ���[�h�̕ύX
				ChangeMode(MODE_RESULT);
			}
		}
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawAnswer(void)
{
	/* ��`�ŕ`�悵�Ă܂� */
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetAnswer(int nNowLight)
{
	if (GetColorLight(nNowLight) == GetColorPlayer(nNowLight))
	{
		if ((GetPlayer() + 1) >= GetLight())
		{// �ő�ɂȂ���
			s_bMax = true;
			s_nTime = 0;
			s_bAnswer = true;
		}
	}
	else
	{
		s_nTime = 0;
		s_bMax = true;
		s_bAnswer = false;
	}
}

//--------------------------------------------------
// �擾
// �Ԓl  : bool / �ő�l�ɂȂ������ǂ���
//--------------------------------------------------
bool GetAnswer(void)
{
	return s_bMax;
}