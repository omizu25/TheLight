//=============================================================================
//
// ���U���g���� [result.cpp]
// Author :�@koduna hirohito
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "result.h"
#include "gauge.h"
#include "rectangle.h"
#include "texture.h"
#include "color.h"
#include "sound.h"
#include "light.h"
#include "mode.h"
#include "utility.h"
#include "number.h"
#include "score.h"
#include "ranking.h"
#include "input.h"
#include "bg.h"
#include "effect.h"
#include "menu.h"
#include "fade.h"
#include "cursor.h"

#include <assert.h>

//=============================================================================
// ��`
//=============================================================================
namespace
{
const int	MAX_TIME = 900;			// �^�C���̍ő�l
const float	MENU_WIDTH = 280.0f;	// ���j���[�̕�
const float	MENU_HEIGHT = 80.0f;	// ���j���[�̍���
const float	CURSOR_SIZE = 50.0f;	// �J�[�\���̃T�C�Y

typedef enum
{
	MENU_GAME = 0,	// �Q�[��
	MENU_TITLE,		// �^�C�g��
	MENU_MAX
}MENU;
}// namespace�͂����܂�

//=============================================================================
// �X�^�e�B�b�N�ϐ�
//=============================================================================
namespace
{
int	s_nIdxMoon;				// �w�i�̋�`�̃C���f�b�N�X
int	s_nIdxScore;			// �X�R�A�̋�`�̃C���f�b�N�X
int	s_nIdxBestScore;		// �x�X�g�X�R�A�̋�`�̃C���f�b�N�X
int	s_nIdxMenu;				// ���j���[�̔z��̃C���f�b�N�X
int	s_nSelectMenu;			// �I�΂�Ă��郁�j���[
int	s_nIdxCursor;			// �J�[�\���̔z��̃C���f�b�N�X
int	s_nGaugeIdxGray;		// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int	s_nGaugeIdxYellow;		// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int	s_nTime;				// �^�C��
float s_fGaugeAlphaGray;	// ���݂̃Q�[�W�̃A���t�@�l
float s_fGaugeAlphaYellow;	// ���݂̃Q�[�W�̃A���t�@�l
}// namespace�͂����܂�

 //=============================================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//=============================================================================
namespace
{
void Input(void);
}// namespace�͂����܂�

//=============================================================================
// ���U���g����������
//=============================================================================
void InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM_RESULT);

	s_nTime = 0;

	s_fGaugeAlphaGray = 0.3f;	// ���݂̃Q�[�W�̃A���t�@�l
	s_fGaugeAlphaYellow = 0.3f;	// ���݂̃Q�[�W�̃A���t�@�l

	// �Q�[�W�̏�����
	InitGauge();

	// �Q�[�W�̐ݒ�(�D�F)
	s_nGaugeIdxGray =  SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);
	
	// �Q�[�W�̐ݒ�(���F)
	s_nGaugeIdxYellow = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_YELLOW), (GetLight() - 1) * (SCREEN_WIDTH / 16.0f), SCREEN_HEIGHT, GAUGE_LEFT);

	// �Q�[�W�̐F�̐ݒ�(�D�F)
	SetColorGauge(s_nGaugeIdxGray, D3DXCOLOR(GetColor(COLOR_GRAY).r, GetColor(COLOR_GRAY).g, GetColor(COLOR_GRAY).b, s_fGaugeAlphaGray));

	// �Q�[�W�̐F�̐ݒ�(���F)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlphaYellow));
	
	// �w�i�̏�����
	InitBG();

	// �G�t�F�N�g�̏�����
	InitEffect();

	{// ��
		// ��`�̐ݒ�
		s_nIdxMoon = SetRectangle(TEXTURE_BG_MOON);

		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxMoon, pos, size);
	}

	{// ����̃X�R�A
		s_nIdxScore = SetRectangle(TEXTURE_YourScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(750.0f, 100.0f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxScore, pos, size);
	}

	{// �x�X�g�X�R�A
		// ��`�̐ݒ�
		s_nIdxBestScore = SetRectangle(TEXTURE_BestScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(750.0f, 100.0f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxBestScore, pos, size);
	}

	{// ���j���[
		// ���j���[�̏�����
		InitMenu();

		MenuArgument menu;
		menu.nNumUse = MENU_MAX;
		menu.fLeft =  0.0f;
		menu.fRight = SCREEN_WIDTH;
		menu.fTop = SCREEN_HEIGHT * 0.7f;
		menu.fBottom = SCREEN_HEIGHT * 0.7f;
		menu.fWidth = MENU_WIDTH;
		menu.fHeight = MENU_HEIGHT;
		menu.bSort = false;

		menu.texture[MENU_GAME] = TEXTURE_play;
		menu.texture[MENU_TITLE] = TEXTURE_end;

		FrameArgument Frame;
		Frame.bUse = false;
		Frame.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		Frame.texture = TEXTURE_NONE;

		// ���j���[�̐ݒ�
		s_nIdxMenu = SetMenu(menu, Frame);

		// �I�����̐F�̐ݒ�
		SetColorOption(s_nIdxMenu, GetColor(COLOR_WHITE), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

		// �I�΂�Ă��Ȃ��I�����̐F�̐ݒ�
		SetColorDefaultOption(s_nIdxMenu, GetColor(COLOR_WHITE));

		s_nSelectMenu = 0;
	}

	{// �J�[�\��
		// �J�[�\��������
		InitCursor();

		CursorArgument cursor;
		cursor.nNumUse = MENU_MAX;
		cursor.fPosX = SCREEN_WIDTH * 0.65f;
		cursor.fTop = SCREEN_HEIGHT * 0.5f;
		cursor.fBottom = SCREEN_HEIGHT;
		cursor.fWidth = CURSOR_SIZE;
		cursor.fHeight = CURSOR_SIZE;
		cursor.texture = TEXTURE_Cursor_Right;
		cursor.nSelect = s_nSelectMenu;
		cursor.bRotation = false;

		// �J�[�\���̐ݒ�
		//s_nIdxCursor = SetCursor(cursor);
	}

	// �����L���O�̏�����
	InitRanking();

	// �X�R�A�̏�����
	InitScore();

	// �����L���O�̐ݒ�
	SetRanking();
}

//=============================================================================
// ���U���g�I������
//=============================================================================
void UninitResult(void)
{
	StopSound();

	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxMoon);
	StopUseRectangle(s_nIdxScore);
	StopUseRectangle(s_nIdxBestScore);

	// �Q�[�W�̏I��
	UninitGauge();

	// �����L���O�̏I��
	UninitRanking();

	// �G�t�F�N�g�̏I��
	UninitEffect();

	// �X�R�A�̏I��
	UninitScore();

	// ���j���[�̏I��
	UninitMenu();

	// �J�[�\���̏I��
	UninitCursor();
}

//=============================================================================
// ���U���g�X�V����
//=============================================================================
void UpdateResult(void)
{
	// �Q�[�W�̍X�V
	UpdateGauge();

	// �G�t�F�N�g�̍X�V
	UpdateEffect();

	// �X�R�A�̍X�V
	UpdateScore();

	// �����L���O�̍X�V
	UpdateRanking();

	// ���j���[�̍X�V�X�V
	UpdateMenu();

	// �J�[�\���̍X�V
	UpdateCursor();

	s_nTime++;

	if (s_nTime >= MAX_TIME)
	{
		// ���[�h�̕ύX
		ChangeMode(MODE_TITLE);
	}

	// ����
	Input();

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

//=============================================================================
// ���U���g�`�揈��
//=============================================================================
void DrawResult(void)
{
	// ��`�̕`��
	DrawRectangle();
}

namespace
{
//--------------------------------------------------
// ����
//--------------------------------------------------
void Input(void)
{
	if (GetFade() != FADE_NONE)
	{// �t�F�[�h���Ă���
		return;
	}

	if (GetKeyboardTrigger(DIK_W) || GetKeyboardTrigger(DIK_UP) ||
		GetJoypadTrigger(JOYKEY_CROSS_UP, 0) || GetJoypadStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_STICK_UP, 0))
	{// W�L�[�������ꂽ���ǂ���
		// �I�����̐F�̏�����
		InitColorOption();

		s_nSelectMenu = ((s_nSelectMenu - 1) + MENU_MAX) % MENU_MAX;

		// �I�����̕ύX
		ChangeOption(s_nSelectMenu);

		// �J�[�\���̈ʒu�̕ύX
		//ChangePosCursor(s_nIdxCursor, s_nSelectMenu);

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	else if (GetKeyboardTrigger(DIK_S) || GetKeyboardTrigger(DIK_DOWN) ||
		GetJoypadTrigger(JOYKEY_CROSS_DOWN, 0) || GetJoypadStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_STICK_DOWN, 0))
	{// S�L�[�������ꂽ���ǂ���
		// �I�����̐F�̏�����
		InitColorOption();

		s_nSelectMenu = ((s_nSelectMenu + 1) + MENU_MAX) % MENU_MAX;

		// �I�����̕ύX
		ChangeOption(s_nSelectMenu);

		// �J�[�\���̈ʒu�̕ύX
		//ChangePosCursor(s_nIdxCursor, s_nSelectMenu);

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		switch (s_nSelectMenu)
		{
		case MENU_GAME:		// �Q�[��
			ChangeMode(MODE_GAME);
			break;

		case MENU_TITLE:	// �^�C�g��
			ChangeMode(MODE_TITLE);
			break;

		default:
			assert(false);
			break;
		}

		// �I�����̌���
		DecisionOption();

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ENTER);
	}
}
}// namespace�͂����܂�
