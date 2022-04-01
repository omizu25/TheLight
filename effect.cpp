//=========================================
// 
// �p�[�e�B�N���̏���
// Author YudaKaito
// 
//=========================================

//-----------------------------------------
// include
//-----------------------------------------
#include "main.h"
#include "effect.h"
#include "rectangle.h"
#include "color.h"
#include "utility.h"
#include <assert.h>

//-----------------------------------------
// ��`
//-----------------------------------------
namespace
{
const int MAX_EFFECT = 512;	// �p�[�e�B�N���̍ő吔

//-----------------------------------------
// �p�[�e�B�N���\����
//-----------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ���
	D3DXVECTOR3 rot;	// �p�x
	D3DXCOLOR col;		// �F
	float fRaduus;		// ���a
	int nMaxLife;		// �ő����
	int nLife;			// ����
	int nIdx;			// RectAngel
	EFFECT_TYPE type;	// �p�[�e�B�N���̎��
	bool bUse;			// �g�p���Ă��邩�ǂ���
}Effect;

}

//-----------------------------------------
// �ÓI�ϐ�
//-----------------------------------------
namespace
{
Effect s_aEffect[MAX_EFFECT];
int nCnt;
int nData;
}

//=========================================
// �p�[�e�B�N���̏���������
//=========================================
void InitEffect(void)
{
	ZeroMemory(s_aEffect, sizeof(s_aEffect));

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		Effect *pEffect = &s_aEffect[i];

		// ��`�̐ݒ�
		pEffect->nIdx = SetRectangle(TEXTURE_NONE);

		// ��`��`�悷�邩�ǂ���
		SetDrawRectangle(pEffect->nIdx, false);
	}

	nCnt = 0;
}

//=========================================
// �p�[�e�B�N���̏I������
//=========================================
void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		Effect *pEffect = &s_aEffect[i];

		if (!pEffect->bUse)
		{// �g�p���Ă��Ȃ�
			continue;
		}

		/*�� �g�p���Ă��� ��*/

		// �g���̂��~�߂�
		StopUseRectangle(pEffect->nIdx);
	}
}

//=========================================
// �p�[�e�B�N���̍X�V����
//=========================================
void UpdateEffect(void)
{
	Effect *pEffect;

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		pEffect = s_aEffect + i;

		if (!pEffect->bUse)
		{	// �p�[�e�B�N�����g�p����Ă��Ȃ�
			continue;
		}

		// �p�[�e�B�N�����g�p����Ă���
		// �ʒu�̍X�V
		pEffect->pos += pEffect->move;

		switch (pEffect->type)
		{
		case EFFECT_TYPE_000:
			pEffect->nLife--;											// �̗͂̍X�V
			pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;			// �����x�̍X�V
			pEffect->fRaduus += 1.75f;	// ���a�̊g��
			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}
			break;
		case EFFECT_TYPE_001:		// �v���C���[�̈ړ�
			pEffect->nLife--;											// �̗͂̍X�V
			pEffect->col.a -= (float)1.0f / pEffect->nMaxLife;			// �����x�̍X�V
			pEffect->fRaduus += 1.75f;	// ���a�̊g��
			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}
			break;
		case EFFECT_TYPE_002:		// �v���C���[�̈ړ�
			//pEffect->nLife--;											// �̗͂̍X�V
			//pEffect->col.a -= (float)1.0f / pEffect->nMaxLife;			// �����x�̍X�V
			pEffect->move.x = SinCurve(nCnt, 1.0f) * 2.0f;	// �ړ�
			pEffect->fRaduus += SinCurve(nCnt, 1.0f) * 2.0f;	// ���a�̊g��
			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}
			break;
		case EFFECT_TYPE_003:		// �v���C���[�̈ړ�
			pEffect->nLife--;											// �̗͂̍X�V
			pEffect->col.a -= (float)1.0f / pEffect->nMaxLife;			// �����x�̍X�V
			pEffect->fRaduus += 0.85f;	// ���a�̊g��
			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}
			break;
		case EFFECT_TYPE_004_1:		// �v���C���[�̈ړ�
			pEffect->move.y -= pEffect->move.y * 0.2f;	// ���a�̊g��

			pEffect->move.x = sinf(nCnt * 0.8f) * 5.0f;	// �ړ�

			if (pEffect->move.y >= -0.5f)
			{
				pEffect->bUse = false;
				for (int j = 0; j < 145; j++)
				{
					SetEffect(pEffect->pos, EFFECT_TYPE_004_2, pEffect->col);
				}
			}
			break;
		case EFFECT_TYPE_004_2:		// �v���C���[�̈ړ�
			pEffect->nLife--;							// �̗͂̍X�V

			if (pEffect->nLife == 10)
			{
				pEffect->bUse = false;
				for (int j = 0; j < 10; j++)
				{
					//SetEffect(pEffect->pos, EFFECT_TYPE_004_3, pEffect->col);
				}
			}
			break;
		case EFFECT_TYPE_004_3:		// �v���C���[�̈ړ�
			pEffect->nLife--;							// �̗͂̍X�V
			pEffect->col.a -= (float)1.0f / pEffect->nMaxLife;			// �����x�̍X�V

			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}
			break;
		default:
			assert(false);
			break;
		}

		if (!pEffect->bUse)
		{	// �p�[�e�B�N�����g�p����Ă��Ȃ�
			// ��`��`�悷�邩�ǂ���
			SetDrawRectangle(pEffect->nIdx, false);
		}

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle(pEffect->nIdx, pEffect->pos, D3DXVECTOR3(pEffect->fRaduus, pEffect->fRaduus, 0.0f));

		// ��`�̐F�̐ݒ�
		SetColorRectangle(pEffect->nIdx, pEffect->col);
	}

	nCnt++;
	
	if (nCnt >= 100)
	{
		nCnt = 0;
	}
}

//=========================================
// �p�[�e�B�N���̕`�揈��
//=========================================
void DrawEffect(void)
{
}

//=========================================
// �p�[�e�B�N���̐ݒ菈��
//=========================================
void SetEffect(D3DXVECTOR3 pos, EFFECT_TYPE type, D3DXCOLOR col)
{
	Effect *pEffect;

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		pEffect = &(s_aEffect[i]);

		if (pEffect->bUse)
		{// �p�[�e�B�N�����g�p����Ă�
			continue;
		}

		int nIdx = pEffect->nIdx;
		ZeroMemory(&s_aEffect[i], sizeof(s_aEffect[0]));
		pEffect->nIdx = nIdx;

		pEffect->bUse = true;
		pEffect->type = type;
		pEffect->col = col;

		switch (type)
		{
		case EFFECT_TYPE_000:	// �v���C���[�̃W�����v�p�[�e�B�N��
			// ��`�̃e�N�X�`���̕ύX
			SetAddRectangle(pEffect->nIdx, true);
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_effect_002);
			pEffect->pos = pos;
			pEffect->col.a = 1.0f;
			pEffect->fRaduus = 50.0f;
			pEffect->nMaxLife = 30;
			pEffect->nLife = pEffect->nMaxLife;
			break;
		case  EFFECT_TYPE_001:		// �v���C���[�̈ړ�
			// ��`�̃e�N�X�`���̕ύX
			SetAddRectangle(pEffect->nIdx, true);
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_effect_001);
			pEffect->pos = pos;
			pEffect->col.a = 0.95f;
			pEffect->fRaduus = 30.0f;
			pEffect->nMaxLife = 30;
			pEffect->nLife = pEffect->nMaxLife;
			break;
		case  EFFECT_TYPE_002:		// �v���C���[�̈ړ�
			// ��`�̃e�N�X�`���̕ύX
			SetAddRectangle(pEffect->nIdx, true);
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_effect_000);
			pEffect->pos = pos;
			pEffect->col.g = 0.35f;
			pEffect->col.a = 0.25f;
			pEffect->fRaduus = 40.0f;
			pEffect->nMaxLife = 10;
			pEffect->nLife = pEffect->nMaxLife;
			break;
		case  EFFECT_TYPE_003:		// �v���C���[�̈ړ�
			// ��`�̃e�N�X�`���̕ύX
			SetAddRectangle(pEffect->nIdx, true);
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_effect_000);
			pEffect->pos = pos;
			pEffect->fRaduus = 40.0f;
			pEffect->nMaxLife = 170;
			pEffect->nLife = pEffect->nMaxLife;
			break;
		case  EFFECT_TYPE_004_1:		// �ԉ΂P
			// ���Z�����ɐ؂�ւ�
			SetAddRectangle(pEffect->nIdx, true);
			// ��`�̃e�N�X�`���̕ύX
			SetAddRectangle(pEffect->nIdx, true);
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_effect_000);
			pEffect->pos = pos;
			pEffect->move.y = -100.0f;
			pEffect->fRaduus = 30.0f;
			pEffect->nLife = pEffect->nMaxLife;
			break;
		case  EFFECT_TYPE_004_2:		// �ԉ΂Q
		{
			// ���Z�����ɐ؂�ւ�
			SetAddRectangle(pEffect->nIdx, true);
			// ��`�̃e�N�X�`���̕ύX
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_effect_000);
			pEffect->pos = pos;
			pEffect->move.x = FloatRandam(1.0f, -1.0f);
			pEffect->move.y = FloatRandam(1.0f, -1.0f);
			D3DXVec3Normalize(&pEffect->move, &pEffect->move);
			float fRandam = FloatRandam(0.8f, 0.1f);
			pEffect->move *= fRandam * 10.0f;
			pEffect->fRaduus = fRandam * 15.0f;
			pEffect->nMaxLife = 40;
			pEffect->nLife = pEffect->nMaxLife;
		}
			break;
		case  EFFECT_TYPE_004_3:		// �ԉ΂R
			// ��`�̃e�N�X�`���̕ύX
			SetAddRectangle(pEffect->nIdx, true);
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_effect_000);
			pEffect->pos = pos;
			pEffect->move.x = FloatRandam(10.0f, -10.0f);
			pEffect->move.y = FloatRandam(10.0f, -10.0f);
			pEffect->fRaduus = 10.0f;
			pEffect->nMaxLife = 20;
			pEffect->nLife = pEffect->nMaxLife;
			break;
		default:
			assert(false);
			break;
		}

		// ��`��`�悷�邩�ǂ���
		SetDrawRectangle(pEffect->nIdx, true);

		// ��`�̈ʒu�̐ݒ�
		D3DXVECTOR3 size = D3DXVECTOR3(pEffect->fRaduus, pEffect->fRaduus, 0.0f);
		SetPosRectangle(pEffect->nIdx, pEffect->pos, size);

		// ��`�̐F�̐ݒ�
		SetColorRectangle(pEffect->nIdx, pEffect->col);

		break;
	}
}
