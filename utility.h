//**************************************************
//
// Hackathon ( utility.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _UTILITY_H_	// ���̃}�N����`������ĂȂ�������
#define _UTILITY_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// �p�x�̐��K��
// ����  : pAngle / �p�x
//--------------------------------------------------
void NormalizeAngle(float *pAngle);

//--------------------------------------------------
// �z�[�~���O
// ����1  : D3DXVECTOR3 *pPosOut / �ʒu
// ����2  : D3DXVECTOR3 &posNow / ���݂̈ʒu
// ����3  : D3DXVECTOR3 &posDest / �ړI�̈ʒu
// ����4  : float fSpeed / ����
// �Ԓl  : bool / �ړI�̈ʒu�ɒ��������ǂ���
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed);

#endif // !_UTILITY_H_
