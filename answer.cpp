//**************************************************
//
// Hackathon ( answer.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "answer.h"
#include "rectangle.h"
#include "texture.h"
#include "color.h"
#include "mode.h"
#include "light.h"
#include "player.h"
#include "game.h"
#include "bg.h"

//==================================================
// 定義
//==================================================
namespace
{
const int	MAX_TIME = 60;	// タイムの最大値
}// namespaceはここまで

 //==================================================
 // スタティック変数
 //==================================================
namespace
{
bool	s_bMax;		// 最大になったかどうか
bool	s_bAnswer;	// あってるかどうか
int		s_nTime;	// タイム
}// namespaceはここまで

 //--------------------------------------------------
 // 初期化
 //--------------------------------------------------
void InitAnswer(void)
{
	s_nTime = 0;
	s_bMax = false;
	s_bAnswer = false;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitAnswer(void)
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateAnswer(void)
{
	if (s_bMax)
	{
		s_nTime++;

		if (s_nTime >= MAX_TIME)
		{
			if (s_bAnswer)
			{
				s_bMax = false;
				s_nTime = 0;
				s_bAnswer = true;

				// ゲーム画面の背景ゲージ(黄色)の増加
				IncreaseGaugeGame();

				// ゲーム状態の設定
				SetGameState(GAMESTATE_RESET);

				// 矩形の色の設定
				SetColorRectangle(GetBG(), GetColor(COLOR_WHITE));
			}
			else
			{
				s_bMax = true;
				s_nTime = 0;
				s_bAnswer = false;

				// モードの変更
				ChangeMode(MODE_RESULT);
			}
		}
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawAnswer(void)
{
	/* 矩形で描画してます */
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetAnswer(int nNowLight)
{
	if (GetColorLight(nNowLight) == GetColorPlayer(nNowLight))
	{
		if ((GetPlayer() + 1) >= GetLight())
		{// 最大になった
			s_bMax = true;
			s_nTime = 0;
			s_bAnswer = true;
		}
	}
	else
	{
		s_nTime = 0;
		s_bMax = true;
		s_bAnswer = false;
	}
}

//--------------------------------------------------
// 取得
// 返値  : bool / 最大値になったかどうか
//--------------------------------------------------
bool GetAnswer(void)
{
	return s_bMax;
}