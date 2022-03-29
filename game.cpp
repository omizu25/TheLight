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
#include "answer.h"
#include "tutorial.h"
#include "utility.h"

#include <assert.h>

//==================================================
// スタティック変数
//==================================================
namespace
{
GAMESTATE	s_gameState = GAMESTATE_NONE;	// ゲームの状態
int			s_nCounterState;				// 状態管理カウンター
bool		s_bPause = false;				// ポーズ中かどうか [してる  : true してない  : false]
int			s_nIdxMoon;						// 背景の矩形のインデックス
int			s_nGaugeIdxGray;				// ゲージのインデックスの保管
int			s_nGaugeIdxYellow;				// ゲージのインデックスの保管
int			s_nTime;						// タイム
float		s_fGaugeAlphaGray;				// 現在のゲージのアルファ値
float		s_fGaugeAlphaYellow;			// 現在のゲージのアルファ値
float		s_fGaugeWidth;					// ゲージの幅（黄色）
}// namesapceはここまで

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitGame(void)
{
	s_nTime = 0;
	s_fGaugeAlphaGray = 0.3f;
	s_fGaugeAlphaYellow = 0.3f;

	// ゲージの初期化
	InitGauge();

	// ゲージの設定
	s_nGaugeIdxGray = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);

	// ゲージの設定(黄色)
	s_nGaugeIdxYellow = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_YELLOW), 0.0f, SCREEN_HEIGHT, GAUGE_LEFT);

	// ゲージの色の設定(灰色)
	SetColorGauge(s_nGaugeIdxGray, D3DXCOLOR(GetColor(COLOR_GRAY).r, GetColor(COLOR_GRAY).g, GetColor(COLOR_GRAY).b, s_fGaugeAlphaGray));

	// ゲージの色の設定(黄色)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlphaYellow));

	// 背景の初期化
	InitBG();

	D3DXCOLOR col = GetColor(COLOR_GRAY);
	col.a = 0.75f;

	s_fGaugeWidth = 0.0f;

	// ゲージの設定
	SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.35f, 0.0f), col, SCREEN_WIDTH, 100.0f, GAUGE_LEFT);
	// ゲージの設定
	SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), col, SCREEN_WIDTH, 100.0f, GAUGE_LEFT);

	// 数の初期化
	InitNumber();

	// タイムの初期化
	InitTime();

	// セレクトの初期化
	InitSelect();

	// ライトの初期化
	InitLight();

	// プレイヤーの初期化
	InitPlayer();

	// アンサーの初期化
	InitAnswer();

	// エフェクトの初期化
	InitEffect();

	// メニューの初期化
	InitMenu();

	// カーソルの初期化
	InitCursor();

	// ポーズの初期化
	InitPause();

	// チュートリアルの初期化
	InitTutorial();

	{// 月
	 // 矩形の設定
		s_nIdxMoon = SetRectangle(TEXTURE_BG_MOON);

		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdxMoon, pos, size);
	}

	//サウンド開始
	PlaySound(SOUND_LABEL_BGM_GAME);

	s_gameState = GAMESTATE_START;	// 何もしていない状態に設定

	s_nCounterState = 0;	// カウンターの初期化

	s_bPause = false;	// ポーズ解除

	{
		int nIdx = SetRectangle(TEXTURE_Method);

		D3DXVECTOR3 pos(SCREEN_WIDTH - 100.0f, 95.0f, 0.0f);
		D3DXVECTOR3 size(155.0f, 155.0f, 0.0f);

		SetPosRectangle(nIdx, pos, size);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitGame(void)
{
	// サウンドの停止
	StopSound();

	// チュートリアルの終了
	UninitTutorial();

	// 背景の終了
	UninitBG();

	// ゲージの終了
	UninitGauge();

	// 数の終了
	UninitNumber();

	// ポーズの終了
	UninitTime();

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

	// アンサーの終了
	UninitAnswer();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateGame(void)
{
	if (GetKeyboardTrigger(DIK_P) || GetJoypadTrigger(JOYKEY_START,0))
	{// Pキーが押された
		if (s_gameState == GAMESTATE_PLAYER)
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

	// 背景の更新
	UpdateBG();

	// ライトの更新
	UpdateLight();

	// プレイヤーの更新
	UpdatePlayer();

	// アンサーの更新
	UpdateAnswer();

	// ゲージの更新
	UpdateGauge();

	// セレクトの更新
	UpdateSelect();

	// メニューの更新
	UpdateMenu();

	// エフェクトの更新
	UpdateEffect();

	// タイムの更新
	UpdateTime();

	// チュートリアルの更新
	UpdateTutorial();

	s_nTime++;

	float fCurve = CosCurve(s_nTime, 0.01f);
	s_fGaugeAlphaGray = Curve(fCurve, 0.3f, 0.6f);

	fCurve = CosCurve(s_nTime, 0.01f);

	s_fGaugeAlphaYellow = Curve(fCurve, 0.3f, 1.0f);

	// ゲージの色の設定(灰色)
	SetColorGauge(s_nGaugeIdxGray, D3DXCOLOR(GetColor(COLOR_GRAY).r, GetColor(COLOR_GRAY).g, GetColor(COLOR_GRAY).b, s_fGaugeAlphaGray));

	// ゲージの色の設定(黄色)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlphaYellow));

	{// 月エフェクト
		D3DXVECTOR3 pos(140.5f, 90.5f, 0.0f);
		D3DXCOLOR col = GetColor(COLOR_WHITE);

		col.b = 0.1f;

		if (s_nTime % 45 == 0)
		{
			SetEffect(pos, EFFECT_TYPE_003, col);
		}
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

//--------------------------------------------------
// ポーズの有効無効取得
//--------------------------------------------------
bool GetEnablePause(void)
{
	return s_bPause;
}

//--------------------------------------------------
// ゲーム画面の背景ゲージ(黄色)の増加
//--------------------------------------------------
void IncreaseGaugeGame(void)
{
	s_fGaugeWidth += SCREEN_WIDTH / 16.0f;
	SetSizeGauge(s_nGaugeIdxYellow, s_fGaugeWidth, SCREEN_HEIGHT);
}
