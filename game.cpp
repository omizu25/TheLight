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
#include "light.h"
#include "select.h"
#include "player.h"

#include <assert.h>

//==================================================
// スタティック変数
//==================================================
namespace
{
GAMESTATE	s_gameState = GAMESTATE_NONE;	// ゲームの状態
int			s_nCounterState;				// 状態管理カウンター
bool		s_bPause = false;				// ポーズ中かどうか [してる  : true してない  : false]
}// namesapceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitGame(void)
{
	// ゲージの初期化
	InitGauge();

	// ゲージの設定
	SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);

	// 背景の初期化
	InitBG();

	D3DXCOLOR col = GetColor(COLOR_GRAY);
	col.a = 0.75f;

	// ゲージの設定
	SetGauge(D3DXVECTOR3(0.0f,SCREEN_HEIGHT * 0.5f,0.0f), col,SCREEN_WIDTH,125.0f, GAUGE_LEFT);



	// 数の初期化
	InitNumber();

	// タイムの初期化
	InitTime();

	// スコア初期化
	//InitScore();

	// ランキングの初期化
	//InitRanking();

	// セレクトの初期化
	InitSelect();

	// ライトの初期化
	InitLight();

	// エフェクトの初期化
	InitEffect();

	// メニューの初期化
	InitMenu();

	// カーソルの初期化
	InitCursor();

	// ポーズの初期化
	//InitPause();

	//サウンド開始
	// プレイヤーの初期化
	//PlaySound(SOUND_LABEL_BGM);
	InitPlayer();

	//サウンド開始
	//PlaySound(SOUND_LABEL_BGM);

	s_gameState = GAMESTATE_START;	// 何もしていない状態に設定

	s_nCounterState = 0;	// カウンターの初期化

	s_bPause = false;	// ポーズ解除
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

	// セレクトの終了
	UninitSelect();

	// メニューの終了
	UninitMenu();

	// カーソルの終了
	UninitCursor();

	// エフェクトの終了
	UninitEffect();

	// ライトの終了
	UninitLight();

	// プレイヤーの終了
	UninitPlayer();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START,0))
	{// Pキーが押された
		if (s_gameState == GAMESTATE_SAMPLE ||
			s_gameState == GAMESTATE_PLAYER)
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

	// ライトの更新
	UpdateLight();

	// ゲージの更新
	UpdatePlayer();

	// ゲージの更新
	UpdateGauge();

	// セレクトの更新
	UpdateSelect();

	// メニューの更新
	UpdateMenu();

	// エフェクトの更新
	UpdateEffect();

	// タイムの更新
	//UpdateTime();

	// スコアの更新
	//UpdateScore();

	// ランキングの更新
	//UpdateRanking();

	switch (s_gameState)
	{
	case GAMESTATE_START:	// 開始状態
		s_gameState = GAMESTATE_SAMPLE;	// 見本状態に設定
		break;

	case GAMESTATE_SAMPLE:	// 見本状態
		break;

	case GAMESTATE_PLAYER:	// プレイヤー状態
		break;

	case GAMESTATE_RESET:	// リセット状態
		break;

	case GAMESTATE_NONE:	// 何もしていない状態
	default:
		assert(false);
		break;
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
