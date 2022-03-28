//**************************************************
//
// Hackathon ( title.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "menu.h"
#include "mode.h"
#include "rectangle.h"
#include "title.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "cursor.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	TITLE_WIDTH = 600.0f;	// �^�C�g���̕�
const float	TITLE_HEIGHT = 600.0f;	// �^�C�g���̍���
const float	MENU_WIDTH = 300.0f;	// ���j���[�̕�
const float	MENU_HEIGHT = 80.0f;	// ���j���[�̍���
const float	CURSOR_SIZE = 50.0f;	// �J�[�\���̃T�C�Y

typedef enum
{
	MENU_GAME = 0,	// �Q�[��
	MENU_TUTORIAL,	// �`���[�g���A��
	MENU_TEST_1,
	MENU_TEST_2,
	MENU_TEST_3,
	MENU_TEST_4,
	MENU_TEST_5,
	MENU_TEST_6,
	MENU_TEST_7,
	MENU_TEST_8,
	MENU_MAX
}MENU;
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int		s_nIdxBG;		// �w�i�̋�`�̃C���f�b�N�X
int		s_nIdx;			// ��`�̃C���f�b�N�X
int		s_nSelectMenu;	// �I�΂�Ă��郁�j���[
int		s_nIdxUseMenu;	// �g���Ă��郁�j���[�̔ԍ�
int		s_nIdxCursor;	// �J�[�\���̔z��̃C���f�b�N�X
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void Input(void);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitTitle(void)
{
	// �T�E���h�̍Đ�
	//PlaySound(SOUND_LABEL_TITLE2);

	s_nSelectMenu = 0;

	{// �w�i
		// ��`�̐ݒ�
		s_nIdxBG = SetRectangle(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxBG, pos, size);
	}

	{// ���S
		// ��`�̐ݒ�
		s_nIdx = SetRectangle(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.25f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdx, pos, size);
	}

	{// ���j���[
		// ���j���[�̏�����
		InitMenu();

		MenuArgument menu;
		menu.nNumUse = MENU_MAX;
		menu.fLeft = SCREEN_WIDTH * 0.55f;
		menu.fRight = SCREEN_WIDTH * 0.95f;
		menu.fTop = 0.0f;
		menu.fBottom = SCREEN_HEIGHT;
		menu.fWidth = MENU_WIDTH;
		menu.fHeight = MENU_HEIGHT;
		menu.bSort = true;

		menu.texture[MENU_GAME] = TEXTURE_NONE;
		menu.texture[MENU_TUTORIAL] = TEXTURE_NONE;
		menu.texture[MENU_TEST_1] = TEXTURE_NONE;
		menu.texture[MENU_TEST_2] = TEXTURE_NONE;
		menu.texture[MENU_TEST_3] = TEXTURE_NONE;
		menu.texture[MENU_TEST_4] = TEXTURE_NONE;
		menu.texture[MENU_TEST_5] = TEXTURE_NONE;
		menu.texture[MENU_TEST_6] = TEXTURE_NONE;
		menu.texture[MENU_TEST_7] = TEXTURE_NONE;
		menu.texture[MENU_TEST_8] = TEXTURE_NONE;

		FrameArgument Frame;
		Frame.bUse = true;
		Frame.col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);
		Frame.texture = TEXTURE_NONE;

		// ���j���[�̐ݒ�
		s_nIdxUseMenu = SetMenu(menu, Frame);
	}

	{// �J�[�\��
		// �J�[�\��������
		InitCursor();

		CursorArgument cursor;
		cursor.nNumUse = MENU_MAX;
		cursor.fPosX = SCREEN_WIDTH * 0.595f;
		cursor.fTop = 0.0f;
		cursor.fBottom = SCREEN_HEIGHT;
		cursor.fWidth = CURSOR_SIZE;
		cursor.fHeight = CURSOR_SIZE;
		cursor.texture = TEXTURE_Cursor_Right;
		cursor.nSelect = s_nSelectMenu;
		cursor.bRotation = false;

		// �J�[�\���̐ݒ�
		s_nIdxCursor = SetCursor(cursor);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitTitle(void)
{
	//�T�E���h��~
	StopSound();

	// ���j���[�̏I��
	UninitMenu();

	// �J�[�\���̏I��
	UninitCursor();

	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxBG);
	StopUseRectangle(s_nIdx);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateTitle(void)
{
	// ����
	Input();

	// ���j���[�̍X�V
	UpdateMenu();

	// �J�[�\���̍X�V
	UpdateCursor();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawTitle(void)
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

	if (GetKeyboardTrigger(DIK_W) || GetJoypadTrigger(JOYKEY_UP,0) || 
		GetJoypadStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_CROSS_UP,0))
	{// W�L�[�������ꂽ���ǂ���
		// �I�����̐F�̏�����
		InitColorOption();

		s_nSelectMenu = ((s_nSelectMenu - 1) + MENU_MAX) % MENU_MAX;

		// �I�����̕ύX
		ChangeOption(s_nSelectMenu);

		// �J�[�\���̈ʒu�̕ύX
		ChangePosCursor(s_nIdxCursor, s_nSelectMenu);

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);
	}
	else if (GetKeyboardTrigger(DIK_S) || GetJoypadTrigger(JOYKEY_DOWN,0) || 
		GetJoypadStickTrigger(JOYKEY_LEFT_STICK, JOYKEY_CROSS_DOWN,0))
	{// S�L�[�������ꂽ���ǂ���
		// �I�����̐F�̏�����
		InitColorOption();

		s_nSelectMenu = ((s_nSelectMenu + 1) + MENU_MAX) % MENU_MAX;

		// �I�����̕ύX
		ChangeOption(s_nSelectMenu);

		// �J�[�\���̈ʒu�̕ύX
		ChangePosCursor(s_nIdxCursor, s_nSelectMenu);

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadTrigger(JOYKEY_START,0) ||
		GetJoypadTrigger(JOYKEY_A,0) || GetJoypadTrigger(JOYKEY_B,0))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		switch (s_nSelectMenu)
		{
		case MENU_GAME:	// �Q�[��
			ChangeMode(MODE_GAME);
			break;

		case MENU_TUTORIAL:	// �`���[�g���A��
			ChangeMode(MODE_TUTORIAL);
			break;

		case MENU_TEST_1:
		case MENU_TEST_2:
		case MENU_TEST_3:
		case MENU_TEST_4:
		case MENU_TEST_5:
		case MENU_TEST_6:
		case MENU_TEST_7:
		case MENU_TEST_8:
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
