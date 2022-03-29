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
#include "answer.h"
#include "tutorial.h"
#include "utility.h"

#include <assert.h>

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
GAMESTATE	s_gameState = GAMESTATE_NONE;	// �Q�[���̏��
int			s_nCounterState;				// ��ԊǗ��J�E���^�[
bool		s_bPause = false;				// �|�[�Y�����ǂ��� [���Ă�  : true ���ĂȂ�  : false]
int			s_nIdxMoon;						// �w�i�̋�`�̃C���f�b�N�X
int			s_nGaugeIdxGray;				// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int			s_nGaugeIdxYellow;				// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int			s_nTime;						// �^�C��
float		s_fGaugeAlphaGray;				// ���݂̃Q�[�W�̃A���t�@�l
float		s_fGaugeAlphaYellow;			// ���݂̃Q�[�W�̃A���t�@�l
float		s_fGaugeWidth;					// �Q�[�W�̕��i���F�j
}// namesapce�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitGame(void)
{
	s_nTime = 0;
	s_fGaugeAlphaGray = 0.3f;
	s_fGaugeAlphaYellow = 0.3f;

	// �Q�[�W�̏�����
	InitGauge();

	// �Q�[�W�̐ݒ�
	s_nGaugeIdxGray = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);

	// �Q�[�W�̐ݒ�(���F)
	s_nGaugeIdxYellow = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_YELLOW), 0.0f, SCREEN_HEIGHT, GAUGE_LEFT);

	// �Q�[�W�̐F�̐ݒ�(�D�F)
	SetColorGauge(s_nGaugeIdxGray, D3DXCOLOR(GetColor(COLOR_GRAY).r, GetColor(COLOR_GRAY).g, GetColor(COLOR_GRAY).b, s_fGaugeAlphaGray));

	// �Q�[�W�̐F�̐ݒ�(���F)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlphaYellow));

	// �w�i�̏�����
	InitBG();

	D3DXCOLOR col = GetColor(COLOR_GRAY);
	col.a = 0.75f;

	s_fGaugeWidth = 0.0f;

	// �Q�[�W�̐ݒ�
	SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.35f, 0.0f), col, SCREEN_WIDTH, 100.0f, GAUGE_LEFT);
	// �Q�[�W�̐ݒ�
	SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), col, SCREEN_WIDTH, 100.0f, GAUGE_LEFT);

	// ���̏�����
	InitNumber();

	// �^�C���̏�����
	InitTime();

	// �Z���N�g�̏�����
	InitSelect();

	// ���C�g�̏�����
	InitLight();

	// �v���C���[�̏�����
	InitPlayer();

	// �A���T�[�̏�����
	InitAnswer();

	// �G�t�F�N�g�̏�����
	InitEffect();

	// ���j���[�̏�����
	InitMenu();

	// �J�[�\���̏�����
	InitCursor();

	// �|�[�Y�̏�����
	InitPause();

	// �`���[�g���A���̏�����
	InitTutorial();

	{// ��
	 // ��`�̐ݒ�
		s_nIdxMoon = SetRectangle(TEXTURE_BG_MOON);

		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxMoon, pos, size);
	}

	//�T�E���h�J�n
	PlaySound(SOUND_LABEL_BGM_GAME);

	s_gameState = GAMESTATE_START;	// �������Ă��Ȃ���Ԃɐݒ�

	s_nCounterState = 0;	// �J�E���^�[�̏�����

	s_bPause = false;	// �|�[�Y����

	{
		int nIdx = SetRectangle(TEXTURE_Method);

		D3DXVECTOR3 pos(SCREEN_WIDTH - 100.0f, 95.0f, 0.0f);
		D3DXVECTOR3 size(155.0f, 155.0f, 0.0f);

		SetPosRectangle(nIdx, pos, size);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitGame(void)
{
	// �T�E���h�̒�~
	StopSound();

	// �`���[�g���A���̏I��
	UninitTutorial();

	// �w�i�̏I��
	UninitBG();

	// �Q�[�W�̏I��
	UninitGauge();

	// ���̏I��
	UninitNumber();

	// �|�[�Y�̏I��
	UninitTime();

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

	// �A���T�[�̏I��
	UninitAnswer();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START,0))
	{// P�L�[�������ꂽ
		if (s_gameState == GAMESTATE_PLAYER)
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

	// �w�i�̍X�V
	UpdateBG();

	// ���C�g�̍X�V
	UpdateLight();

	// �v���C���[�̍X�V
	UpdatePlayer();

	// �A���T�[�̍X�V
	UpdateAnswer();

	// �Q�[�W�̍X�V
	UpdateGauge();

	// �Z���N�g�̍X�V
	UpdateSelect();

	// ���j���[�̍X�V
	UpdateMenu();

	// �G�t�F�N�g�̍X�V
	UpdateEffect();

	// �^�C���̍X�V
	UpdateTime();

	// �`���[�g���A���̍X�V
	UpdateTutorial();

	s_nTime++;

	float fCurve = CosCurve(s_nTime, 0.01f);
	s_fGaugeAlphaGray = Curve(fCurve, 0.3f, 0.6f);

	fCurve = CosCurve(s_nTime, 0.01f);

	s_fGaugeAlphaYellow = Curve(fCurve, 0.3f, 1.0f);

	// �Q�[�W�̐F�̐ݒ�(�D�F)
	SetColorGauge(s_nGaugeIdxGray, D3DXCOLOR(GetColor(COLOR_GRAY).r, GetColor(COLOR_GRAY).g, GetColor(COLOR_GRAY).b, s_fGaugeAlphaGray));

	// �Q�[�W�̐F�̐ݒ�(���F)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlphaYellow));

	{// ���G�t�F�N�g
		D3DXVECTOR3 pos(140.5f, 90.5f, 0.0f);
		D3DXCOLOR col = GetColor(COLOR_WHITE);

		col.b = 0.1f;

		if (s_nTime % 45 == 0)
		{
			SetEffect(pos, EFFECT_TYPE_003, col);
		}
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

//--------------------------------------------------
// �|�[�Y�̗L�������擾
//--------------------------------------------------
bool GetEnablePause(void)
{
	return s_bPause;
}

//--------------------------------------------------
// �Q�[����ʂ̔w�i�Q�[�W(���F)�̑���
//--------------------------------------------------
void IncreaseGaugeGame(void)
{
	s_fGaugeWidth += SCREEN_WIDTH / 16.0f;
	SetSizeGauge(s_nGaugeIdxYellow, s_fGaugeWidth, SCREEN_HEIGHT);
}
