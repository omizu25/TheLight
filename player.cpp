//**************************************************
//
// Hackathon ( player.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h" 
#include "fade.h"
#include "input.h"
#include "select.h"
#include "mode.h"
#include "rectangle.h"
#include "light.h"
#include "color.h"
#include "sound.h"
#include "texture.h"
#include "utility.h"
#include "game.h"
#include "effect.h"
#include "player.h"
#include "answer.h"
#include "time.h"
#include "bg.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const int	MAX_TIME = 5;		// �^�C���̍ő�l
const int	MAX_LIGHT = 16;		// ���C�g�̍ő吔
const float	LIGHT_SIZE = 50.0f;	// ���C�g�̃T�C�Y

typedef enum
{
	LIGHT_COLOR_RED = 0,	// ��
	LIGHT_COLOR_GREEN,		// ��
	LIGHT_COLOR_BLUE,		// ��
	LIGHT_COLOR_YELLOW,		// ���F
	LIGHT_COLOR_MAX,
}LIGHT_COLOR;
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
COLOR	s_aColor[LIGHT_COLOR_MAX];	// ���C�g�̐F
int		s_nPlayer;					// ���C�g�̌��݂̐�
int		s_nIdxSelect;				// ���j���[�̔z��̃C���f�b�N�X
int		s_nIdxColor[MAX_LIGHT];		// �F�̔ԍ�
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�֐��v���g�^�C�v�錾
 //==================================================
namespace
{
void ResetDrawPlayer(void);
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitPlayer(void)
{
	s_aColor[LIGHT_COLOR_RED] = COLOR_RED;
	s_aColor[LIGHT_COLOR_GREEN] = COLOR_GREEN;
	s_aColor[LIGHT_COLOR_BLUE] = COLOR_BLUE;
	s_aColor[LIGHT_COLOR_YELLOW] = COLOR_YELLOW;

	s_nPlayer = 0;

	{// ���j���[
		SelectArgument select;
		select.nNumUse = MAX_LIGHT;
		select.fLeft = 0.0f;
		select.fRight = SCREEN_WIDTH;
		select.fTop = SCREEN_HEIGHT * 0.5f;
		select.fBottom = SCREEN_HEIGHT * 0.5f;
		select.fWidth = LIGHT_SIZE;
		select.fHeight = LIGHT_SIZE;
		select.bSort = false;

		for (int i = 0; i < MAX_LIGHT; i++)
		{
			select.texture[i] = TEXTURE_effect_000;
		}

		// �Z���N�g�̐ݒ�
		s_nIdxSelect = SetSelect(select);
	}

	// �`��̃��Z�b�g
	ResetDrawPlayer();

	// �^�C���̐ݒ�
	SetTime(MAX_TIME);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitPlayer(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdatePlayer(void)
{
	if (GetFade() != FADE_NONE)
	{
		return;
	}

	switch (GetGameState())
	{
	case GAMESTATE_RESET:	// ���Z�b�g���
		// �`��̃��Z�b�g
		ResetDrawPlayer();

		// �Q�[����Ԃ̐ݒ�
		SetGameState(GAMESTATE_SAMPLE);
		break;

	case GAMESTATE_PLAYER:	// �v���C���[���

		if (GetAnswer())
		{// �ő�l
			return;
		}

		if (GetLightKeyTrigger(LIGHT_KEY_RED))
		{// ��
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_RED;

			// �Z���N�g�̐F�̐ݒ�
			SetColorSelect(s_nIdxSelect, s_nPlayer, s_aColor[s_nIdxColor[s_nPlayer]]);

			// �Z���N�g�̕`�悷�邩�ǂ���
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ���C�g�̕`��ݒ�
			SetDrawLight(s_nPlayer);

			// �������킹
			SetAnswer(s_nPlayer);

			// �^�C���̐ݒ�
			SetTime(MAX_TIME);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(GetBG(), GetColor(COLOR_RED));

			s_nPlayer++;

			// �G�t�F�N�g�̐ݒ�
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, s_nPlayer - 1));
		}
		else if (GetLightKeyTrigger(LIGHT_KEY_GREEN))
		{// ��
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_GREEN;

			// �Z���N�g�̐F�̐ݒ�
			SetColorSelect(s_nIdxSelect, s_nPlayer, s_aColor[s_nIdxColor[s_nPlayer]]);

			// �Z���N�g�̕`�悷�邩�ǂ���
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ���C�g�̕`��ݒ�
			SetDrawLight(s_nPlayer);

			// �������킹
			SetAnswer(s_nPlayer);

			// �^�C���̐ݒ�
			SetTime(MAX_TIME);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(GetBG(), GetColor(COLOR_GREEN));

			s_nPlayer++;

			// �G�t�F�N�g�̐ݒ�
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, s_nPlayer - 1));
		}
		else if (GetLightKeyTrigger(LIGHT_KEY_BLUE))
		{// ��
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_BLUE;

			// �Z���N�g�̐F�̐ݒ�
			SetColorSelect(s_nIdxSelect, s_nPlayer, s_aColor[s_nIdxColor[s_nPlayer]]);

			// �Z���N�g�̕`�悷�邩�ǂ���
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ���C�g�̕`��ݒ�
			SetDrawLight(s_nPlayer);

			// �������킹
			SetAnswer(s_nPlayer);

			// �^�C���̐ݒ�
			SetTime(MAX_TIME);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(GetBG(), GetColor(COLOR_BLUE));

			s_nPlayer++;

			// �G�t�F�N�g�̐ݒ�
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, s_nPlayer - 1));
		}
		else if (GetLightKeyTrigger(LIGHT_KEY_YELLOW))
		{// ���F
			s_nIdxColor[s_nPlayer] = LIGHT_COLOR_YELLOW;

			// �Z���N�g�̐F�̐ݒ�
			SetColorSelect(s_nIdxSelect, s_nPlayer, s_aColor[s_nIdxColor[s_nPlayer]]);

			// �Z���N�g�̕`�悷�邩�ǂ���
			SetDrawSelect(s_nIdxSelect, s_nPlayer, true);

			// ���C�g�̕`��ݒ�
			SetDrawLight(s_nPlayer);
		
			// �������킹
			SetAnswer(s_nPlayer);

			// �^�C���̐ݒ�
			SetTime(MAX_TIME);

			// ��`�̐F�̐ݒ�
			SetColorRectangle(GetBG(), GetColor(COLOR_YELLOW));

			s_nPlayer++;

			// �G�t�F�N�g�̐ݒ�
			SetEffect(GetPosSelect(s_nIdxSelect, s_nPlayer - 1), EFFECT_TYPE_000, GetColSelect(s_nIdxSelect, s_nPlayer - 1));
		}
		break;

	case GAMESTATE_SAMPLE:	// ���{���
	case GAMESTATE_NONE:	// �������Ă��Ȃ����
	case GAMESTATE_START:	// �J�n���
		break;

	default:
		assert(false);
		break;
	}


}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawPlayer(void)
{
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int GetPlayer(void)
{
	return s_nPlayer;
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
int GetColorPlayer(int nNowLight)
{
	assert(nNowLight >= 0 && nNowLight < MAX_LIGHT);

	return s_nIdxColor[nNowLight];
}

namespace
{
//--------------------------------------------------
// �`��̃��Z�b�g
//--------------------------------------------------
void ResetDrawPlayer(void)
{
	for (int i = 0; i < MAX_LIGHT; i++)
	{
		// �Z���N�g�̕`�悷�邩�ǂ���
		SetDrawSelect(s_nIdxSelect, i, false);
	}

	s_nPlayer = 0;
}
}// namespace�͂����܂�