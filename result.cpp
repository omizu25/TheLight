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

#include "input.h"

//=============================================================================
// �X�^�e�B�b�N�ϐ�
//=============================================================================
namespace
{
	int	s_nIdxBG;	// �w�i�̋�`�̃C���f�b�N�X
}// namespace�͂����܂�

static int s_nGaugeIdx;			//�Q�[�W�̃C���f�b�N�X�̕ۊ�
static float s_fGaugeWidth;		//�Q�[�W�̕��i���F�j

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================

//=============================================================================
// ���U���g����������
//=============================================================================
void InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM_RESULT);

	s_fGaugeWidth = 0.0f;
	// �Q�[�W�̏�����
	InitGauge();

	// �Q�[�W�̐ݒ�(�D�F)
	SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);
	// �Q�[�W�̐ݒ�(���F)
	s_nGaugeIdx = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_YELLOW), 0.0f, SCREEN_HEIGHT, GAUGE_LEFT);

	// ��`�̐ݒ�
	s_nIdxBG = SetRectangle(TEXTURE_BG);

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle(s_nIdxBG, pos, size);

	// ��`�̐F�̐ݒ�
	SetColorRectangle(s_nIdxBG, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================================================
// ���U���g�I������
//=============================================================================
void UninitResult(void)
{
	StopSound();

	// �g���̂��~�߂�
	StopUseRectangle(s_nIdxBG);
}

//=============================================================================
// ���U���g�X�V����
//=============================================================================
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_8))
	{
		s_fGaugeWidth += SCREEN_WIDTH / 16.0f;
		ChangeGauge(s_nGaugeIdx, s_fGaugeWidth, SCREEN_HEIGHT);
	}
	UpdateGauge();
}

//=============================================================================
// ���U���g�`�揈��
//=============================================================================
void DrawResult(void)
{
	// ��`�̕`��
	DrawRectangle();
}