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
int	s_nIdxBG;			// �w�i�̋�`�̃C���f�b�N�X
int	s_nIdxUI[2];			// UI�̋�`�̃C���f�b�N�X
int	s_nGaugeIdxGray;	// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int	s_nGaugeIdxYellow;	// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int	s_nTime;			// �^�C��
float s_fGaugeAlpha;	// ���݂̃Q�[�W�̃A���t�@�l
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

	s_fGaugeAlpha = 0.3f;	// ���݂̃Q�[�W�̃A���t�@�l

	// �Q�[�W�̏�����
	InitGauge();

	// �Q�[�W�̐ݒ�(�D�F)
	s_nGaugeIdxGray =  SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);
	
	// �Q�[�W�̐ݒ�(���F)
	s_nGaugeIdxYellow = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_YELLOW), (GetLight() - 1) * (SCREEN_WIDTH / 16.0f), SCREEN_HEIGHT, GAUGE_LEFT);

	// �Q�[�W�̐F�̐ݒ�(���F)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlpha));
	
	{// �w�i
		// ��`�̐ݒ�
		s_nIdxBG = SetRectangle(TEXTURE_BG);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxBG, pos, size);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(s_nIdxBG, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	{// ����̃X�R�A
		// �X�R�A�̏�����
		InitScore();

		s_nIdxUI[0] = SetRectangle(TEXTURE_YourScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(600.0f, 100.0f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxUI[0], pos, size);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(s_nIdxUI[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	{// �x�X�g�X�R�A
		// �����L���O�̐ݒ�
		SetRanking();

		// �����L���O�̏�����
		InitRanking();

		// ��`�̐ݒ�
		s_nIdxUI[1] = SetRectangle(TEXTURE_BestScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(600.0f, 100.0f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(s_nIdxUI[1], pos, size);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(s_nIdxUI[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}

//=============================================================================
// ���U���g�I������
//=============================================================================
void UninitResult(void)
{
	StopSound();

	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxBG);

	// �Q�[�W�̏I��
	UninitGauge();
}

//=============================================================================
// ���U���g�X�V����
//=============================================================================
void UpdateResult(void)
{
	// �Q�[�W�̍X�V
	UpdateGauge();

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
	s_fGaugeAlpha = Curve(fCurve, 0.3f, 1.0f);

	// �Q�[�W�̐F�̐ݒ�(���F)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlpha));
}

//=============================================================================
// ���U���g�`�揈��
//=============================================================================
void DrawResult(void)
{
	// ��`�̕`��
	DrawRectangle();
}