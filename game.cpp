//**************************************************
//
// FPD制作 ( game.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "sound.h"
#include "rectangle.h"
#include "fanangle.h"
#include "pause.h"
#include "menu.h"
#include "number.h"
#include "bg.h"
#include "cursor.h"
#include "gauge.h"
#include "effect.h"
#include "color.h"
#include "time.h"
#include "score.h"
#include "ranking.h"

#include <assert.h>

//==================================================
// スタティック変数
//==================================================
namespace
{
GAMESTATE	s_gameState = GAMESTATE_NONE;	// ゲームの状態
int			s_nCounterState;				// 状態管理カウンター
bool		s_bPause = false;				// ポーズ中かどうか [してる  : true してない  : false]
int			s_nIdx;
}// namesapceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitGame(void)
{
	// 背景の初期化
	InitBG();

	// ゲージの初期化
	InitGauge();

	// 数の初期化
	InitNumber();

	// メニューの初期化
	InitTime();

	// カーソル初期化
	InitScore();

	// ポーズの初期化
	InitRanking();

	// エフェクトの初期化
	InitEffect();

	//サウンド開始
	InitMenu();

	//PlaySound(SOUND_LABEL_BGM);
	InitCursor();

	// ポーズの初期化
	InitPause();

	//サウンド開始
	//PlaySound(SOUND_LABEL_BGM);

	s_gameState = GAMESTATE_START;	// 何もしていない状態に設定

	s_nCounterState = 0;	// カウンターの初期化

	s_bPause = false;	// ポーズ解除

	s_nIdx = SetFanangle(TEXTURE_NONE);

	// 矩形の位置の設定
	SetRotationPosFanangle(s_nIdx, D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f),1.5f, 30.0f);

	// 矩形の色の設定
	SetColorFanangle(s_nIdx, GetColor(COLOR_RED));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitGame(void)
{
	// サウンドの停止
	StopSound();

	// 背景の終了
	UninitBG();

	// ゲージの終了
	UninitGauge();

	// 数の終了
	UninitNumber();

	// ポーズの終了
	UninitTime();

	// スコアの終了
	UninitScore();

	// ランキングの終了
	UninitRanking();

	// ポーズの終了
	UninitPause();

	// メニューの終了
	UninitMenu();

	// カーソルの終了
	UninitCursor();

	// エフェクトの終了
	UninitEffect();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START,0))
	{// Pキーが押された
		if (s_gameState == GAMESTATE_NORMAL)
		{// 通常状態の時
			s_bPause = !s_bPause;

			if (s_bPause)
			{// ポーズしてる
				// ポーズの設定
				SetPause();
			}
			else
			{// ポーズしてない
				// ポーズのリセット
				ResetPause();
			}
		}
	}

	if (s_bPause)
	{// ポーズしている
		// ポーズの更新
		UpdatePause();

		// メニューの更新
		UpdateMenu();

		// カーソルの更新
		UpdateCursor();

		return;
	}

	switch (s_gameState)
	{
	case GAMESTATE_START:	// 開始状態
		s_gameState = GAMESTATE_NORMAL;	// 通常状態に設定
		break;

	case GAMESTATE_NORMAL:	// 通常状態
		break;

	case GAMESTATE_END:		// 終了状態
		break;

	case GAMESTATE_RESULT:	// リザルト状態
		break;

	case GAMESTATE_NONE:	// 何もしていない状態
	default:
		assert(false);
		break;
	}

	// ゲージの更新
	UpdateGauge();

	// エフェクトの更新
	UpdateEffect();
	SetEffect(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), EFFECT_TYPE_001);

	// タイムの更新
	UpdateTime();

	// スコアの更新
	UpdateScore();

	// ランキングの更新
	UpdateRanking();

	if (GetKeyboardPress(DIK_RETURN))
	{
		AddDrawFanangle(s_nIdx, -1);
	}
	if (GetKeyboardPress(DIK_BACKSPACE))
	{
		AddDrawFanangle(s_nIdx, 1);
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawGame(void)
{
	// 矩形の描画
	DrawRectangle();

	// 円形の描画
	DrawFanangle();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetGameState(GAMESTATE state)
{
	assert(state >= 0 && state < GAMESTATE_MAX);

	s_gameState = state;
	s_nCounterState = 0;
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
GAMESTATE GetGameState(void)
{
	return s_gameState;
}

//--------------------------------------------------
// ポーズの有効無効設定
//--------------------------------------------------
void SetEnablePause(bool bPause)
{
	s_bPause = bPause;
}
