//**************************************************
//
// Hackathon ( time.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "time.h"
#include "rectangle.h"
#include "texture.h"
#include "number.h"
#include "color.h"
#include "mode.h"
#include "answer.h"
#include "game.h"

//==================================================
// 定義
//==================================================
namespace
{
const int	ONE_SECOND = 60;		// 1秒
const float	TIME_WIDTH = 100.0f;	// タイムの幅
const float	TIME_HEIGHT = 200.0f;	// タイムの高さ
}// namespaceはここまで

//==================================================
// スタティック変数
//==================================================
namespace
{
int	s_nIdxTime;	// 数の配列のインデックス
int	s_nTime;	// タイム
int	s_nSecond;	// 1秒を計測
}// namespaceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitTime(void)
{
	s_nTime = 0;
	s_nSecond = 0;
	s_nIdxTime = 0;

	D3DXVECTOR3 size = D3DXVECTOR3(TIME_WIDTH, TIME_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, TIME_HEIGHT * 0.5f, 0.0f);

	pos.x += DigitNumber(s_nTime) * (TIME_WIDTH * 0.5f);

	// 数の設定
	s_nIdxTime = SetNumber(pos, size, GetColor(COLOR_WHITE), s_nTime, DigitNumber(s_nTime), false);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTime(void)
{
	// 使うのを止める
	StopUseRectangle(s_nIdxTime);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateTime(void)
{
	if (GetGameState() != GAMESTATE_PLAYER)
	{
		// 数を描画するかどうか
		SetDrawNumber(s_nIdxTime, false);

		return;
	}

	// 数を描画するかどうか
	SetDrawNumber(s_nIdxTime, true);

	if (GetAnswer())
	{// 最大値
		return;
	}

	s_nSecond++;

	if ((s_nSecond % ONE_SECOND) == 0)
	{// 1秒毎に
		// 加算
		AddTime(-1);

		if (s_nTime <= 0)
		{// 制限時間が来た
			// モードの変更
			ChangeMode(MODE_RESULT);
		}
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawTime(void)
{
	/* 矩形で描画してます */
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetTime(int nTime)
{
	s_nTime = nTime;
	s_nSecond = 0;

	// 数の変更
	s_nIdxTime = ChangeNumber(s_nIdxTime, s_nTime);

	D3DXVECTOR3 size = D3DXVECTOR3(TIME_WIDTH, TIME_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, TIME_HEIGHT * 0.5f, 0.0f);

	pos.x += DigitNumber(s_nTime) * (TIME_WIDTH * 0.5f);

	// 位置の設定
	SetPosNumber(s_nIdxTime, pos, size);
}

//--------------------------------------------------
// 加算
// 引数  : int nValue / 加算する値
//--------------------------------------------------
void AddTime(int nValue)
{
	s_nTime += nValue;

	// 数の変更
	s_nIdxTime = ChangeNumber(s_nIdxTime, s_nTime);

	D3DXVECTOR3 size = D3DXVECTOR3(TIME_WIDTH, TIME_HEIGHT, 0.0f);
	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, TIME_HEIGHT * 0.5f, 0.0f);

	pos.x += DigitNumber(s_nTime) * (TIME_WIDTH * 0.5f);

	// 位置の設定
	SetPosNumber(s_nIdxTime, pos, size);
}
