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

//=============================================================================
// ��`
//=============================================================================
namespace
{
const int	MAX_TIME = 600;	// �^�C���̍ő�l
}// namespace�͂����܂�

//=============================================================================
// �X�^�e�B�b�N�ϐ�
//=============================================================================
namespace
{
int	s_nIdxMoon;				// �w�i�̋�`�̃C���f�b�N�X
int	s_nIdxUI[2];			// UI�̋�`�̃C���f�b�N�X
int	s_nGaugeIdxGray;		// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int	s_nGaugeIdxYellow;		// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int	s_nTime;				// �^�C��
float s_fGaugeAlphaGray;	// ���݂̃Q�[�W�̃A���t�@�l
float s_fGaugeAlphaYellow;	// ���݂̃Q�[�W�̃A���t�@�l
}// namespace�͂����܂�

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

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
		s_nIdxUI[0] = SetRectangle(TEXTURE_YourScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(750.0f, 100.0f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxUI[0], pos, size);
	}

	{// �x�X�g�X�R�A
		// ��`�̐ݒ�
		s_nIdxUI[1] = SetRectangle(TEXTURE_BestScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(750.0f, 100.0f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxUI[1], pos, size);
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

	// �Q�[�W�̏I��
	UninitGauge();

	// �����L���O�̏I��
	UninitRanking();

	// �G�t�F�N�g�̏I��
	UninitEffect();

	// �X�R�A�̏I��
	InitScore();
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

	s_nTime++;

	if (s_nTime >= MAX_TIME)
	{
		// ���[�h�̕ύX
		ChangeMode(MODE_TITLE);
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//����L�[(ENTER�L�[)�������ꂽ���ǂ���
		// ���[�h�̕ύX
		ChangeMode(MODE_TITLE);

		// �T�E���h�̍Đ�
		PlaySound(SOUND_LABEL_SE_ENTER);
	}

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