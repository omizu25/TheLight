//**************************************************
//
// FPD���� ( game.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "sound.h"
#include "rectangle.h"
#include "pause.h"
#include "menu.h"
#include "number.h"
#include "bg.h"
#include "cursor.h"
#include "gauge.h"
#include "effect.h"
#include "color.h"

#include <assert.h>

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
GAMESTATE	s_gameState = GAMESTATE_NONE;	// �Q�[���̏��
int			s_nCounterState;				// ��ԊǗ��J�E���^�[
bool		s_bPause = false;				// �|�[�Y�����ǂ��� [���Ă�  : true ���ĂȂ�  : false]
}// namesapce�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitGame(void)
{
	// �w�i�̏�����
	InitBG();

	// �Q�[�W�̏�����
	InitGauge();

	// ���̏�����
	InitNumber();

	// ���j���[�̏�����
	InitMenu();

	// �J�[�\��������
	InitCursor();

	// �|�[�Y�̏�����
	InitPause();

	// �G�t�F�N�g�̏�����
	InitEffect();

	//�T�E���h�J�n
	//PlaySound(SOUND_LABEL_BGM);

	s_gameState = GAMESTATE_START;	// �������Ă��Ȃ���Ԃɐݒ�

	s_nCounterState = 0;	// �J�E���^�[�̏�����

	s_bPause = false;	// �|�[�Y����
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitGame(void)
{
	// �T�E���h�̒�~
	StopSound();

	// �w�i�̏I��
	UninitBG();

	// �Q�[�W�̏I��
	UninitGauge();

	// ���̏I��
	UninitNumber();

	// �|�[�Y�̏I��
	UninitPause();

	// ���j���[�̏I��
	UninitMenu();

	// �J�[�\���̏I��
	UninitCursor();

	// �G�t�F�N�g�̏I��
	UninitEffect();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START,0))
	{// P�L�[�������ꂽ
		if (s_gameState == GAMESTATE_NORMAL)
		{// �ʏ��Ԃ̎�
			s_bPause = !s_bPause;

			if (s_bPause)
			{// �|�[�Y���Ă�
				// �|�[�Y�̐ݒ�
				SetPause();
			}
			else
			{// �|�[�Y���ĂȂ�
				// �|�[�Y�̃��Z�b�g
				ResetPause();
			}
		}
	}

	if (s_bPause)
	{// �|�[�Y���Ă���
		// �|�[�Y�̍X�V
		UpdatePause();

		// ���j���[�̍X�V
		UpdateMenu();

		// �J�[�\���̍X�V
		UpdateCursor();

		return;
	}

	switch (s_gameState)
	{
	case GAMESTATE_START:	// �J�n���
		s_gameState = GAMESTATE_NORMAL;	// �ʏ��Ԃɐݒ�
		break;

	case GAMESTATE_NORMAL:	// �ʏ���
		break;

	case GAMESTATE_END:		// �I�����
		break;

	case GAMESTATE_RESULT:	// ���U���g���
		break;

	case GAMESTATE_NONE:	// �������Ă��Ȃ����
	default:
		assert(false);
		break;
	}

	// �Q�[�W�̍X�V
	UpdateGauge();

	// �G�t�F�N�g�̍X�V
	UpdateEffect();
	SetEffect(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), EFFECT_TYPE_PLAYER_WALK);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawGame(void)
{
	// ��`�̕`��
	DrawRectangle();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetGameState(GAMESTATE state)
{
	assert(state >= 0 && state < GAMESTATE_MAX);

	s_gameState = state;
	s_nCounterState = 0;
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
GAMESTATE GetGameState(void)
{
	return s_gameState;
}

//--------------------------------------------------
// �|�[�Y�̗L�������ݒ�
//--------------------------------------------------
void SetEnablePause(bool bPause)
{
	s_bPause = bPause;
}
