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
int	s_nGaugeIdxGray;	// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int	s_nGaugeIdxYellow;	// �Q�[�W�̃C���f�b�N�X�̕ۊ�
int	s_nTime;			// �^�C��
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

	// �Q�[�W�̏�����
	InitGauge();

	// �Q�[�W�̐ݒ�(�D�F)
	s_nGaugeIdxGray =  SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);
	
	// �Q�[�W�̐ݒ�(���F)
	s_nGaugeIdxYellow = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_YELLOW), (GetLight() - 1) * (SCREEN_WIDTH / 16.0f), SCREEN_HEIGHT, GAUGE_LEFT);

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
}

//=============================================================================
// ���U���g�`�揈��
//=============================================================================
void DrawResult(void)
{
	// ��`�̕`��
	DrawRectangle();
}