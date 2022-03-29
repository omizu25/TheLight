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
#include "fanangle.h"
#include "pause.h"
#include "menu.h"
#include "number.h"
#include "bg.h"
#include "cursor.h"
#include "gauge.h"
#include "effect.h"
#include "color.h"
#include "time.h"
#include "score.h"
#include "ranking.h"
#include "light.h"
#include "select.h"
#include "player.h"

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
	// �Q�[�W�̏�����
	InitGauge();

	// �Q�[�W�̐ݒ�
	SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);

	// �w�i�̏�����
	InitBG();

	D3DXCOLOR col = GetColor(COLOR_GRAY);
	col.a = 0.75f;

	// �Q�[�W�̐ݒ�
	SetGauge(D3DXVECTOR3(0.0f,SCREEN_HEIGHT * 0.5f,0.0f), col,SCREEN_WIDTH,125.0f, GAUGE_LEFT);



	// ���̏�����
	InitNumber();

	// �^�C���̏�����
	InitTime();

	// �X�R�A������
	//InitScore();

	// �����L���O�̏�����
	//InitRanking();

	// �Z���N�g�̏�����
	InitSelect();

	// ���C�g�̏�����
	InitLight();

	// �G�t�F�N�g�̏�����
	InitEffect();

	// ���j���[�̏�����
	InitMenu();

	// �J�[�\���̏�����
	InitCursor();

	// �|�[�Y�̏�����
	//InitPause();

	//�T�E���h�J�n
	// �v���C���[�̏�����
	//PlaySound(SOUND_LABEL_BGM);
	InitPlayer();

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
	UninitTime();

	// �X�R�A�̏I��
	UninitScore();

	// �����L���O�̏I��
	UninitRanking();

	// �|�[�Y�̏I��
	UninitPause();

	// �Z���N�g�̏I��
	UninitSelect();

	// ���j���[�̏I��
	UninitMenu();

	// �J�[�\���̏I��
	UninitCursor();

	// �G�t�F�N�g�̏I��
	UninitEffect();

	// ���C�g�̏I��
	UninitLight();

	// �v���C���[�̏I��
	UninitPlayer();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START,0))
	{// P�L�[�������ꂽ
		if (s_gameState == GAMESTATE_SAMPLE ||
			s_gameState == GAMESTATE_PLAYER)
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

	// ���C�g�̍X�V
	UpdateLight();

	// �Q�[�W�̍X�V
	UpdatePlayer();

	// �Q�[�W�̍X�V
	UpdateGauge();

	// �Z���N�g�̍X�V
	UpdateSelect();

	// ���j���[�̍X�V
	UpdateMenu();

	// �G�t�F�N�g�̍X�V
	UpdateEffect();

	// �^�C���̍X�V
	//UpdateTime();

	// �X�R�A�̍X�V
	//UpdateScore();

	// �����L���O�̍X�V
	//UpdateRanking();

	switch (s_gameState)
	{
	case GAMESTATE_START:	// �J�n���
		s_gameState = GAMESTATE_SAMPLE;	// ���{��Ԃɐݒ�
		break;

	case GAMESTATE_SAMPLE:	// ���{���
		break;

	case GAMESTATE_PLAYER:	// �v���C���[���
		break;

	case GAMESTATE_RESET:	// ���Z�b�g���
		break;

	case GAMESTATE_NONE:	// �������Ă��Ȃ����
	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawGame(void)
{
	// ��`�̕`��
	DrawRectangle();

	// �~�`�̕`��
	DrawFanangle();
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
