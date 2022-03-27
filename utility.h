//**************************************************
//
// Hackathon ( utility.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _UTILITY_H_	// このマクロ定義がされてなかったら
#define _UTILITY_H_	// ２重インクルード防止のマクロ定義

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 角度の正規化
// 引数  : pAngle / 角度
//--------------------------------------------------
void NormalizeAngle(float *pAngle);

//--------------------------------------------------
// ホーミング
// 引数1  : D3DXVECTOR3 *pPosOut / 位置
// 引数2  : D3DXVECTOR3 &posNow / 現在の位置
// 引数3  : D3DXVECTOR3 &posDest / 目的の位置
// 引数4  : float fSpeed / 速さ
// 返値  : bool / 目的の位置に着いたかどうか
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed);

//--------------------------------------------------
// 小数点のランダム
// 引数1  : float fMax / 最大値
// 引数2  : float fMin / 最小値
// 返値  : float / ランダム値
//--------------------------------------------------
float FloatRandam(float fMax, float fMin);

//--------------------------------------------------
// 整数のランダム
// 引数1  : int nMax / 最大値
// 引数2  : int nMin / 最小値
// 返値  : int / ランダム値
//--------------------------------------------------
int IntRandam(int nMax, int nMin);

#endif // !_UTILITY_H_
