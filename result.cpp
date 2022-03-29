//=============================================================================
//
// リザルト処理 [result.cpp]
// Author :　koduna hirohito
//
//=============================================================================

//=============================================================================
// インクルードファイル
//=============================================================================
#include "result.h"
#include "gauge.h"
#include "rectangle.h"
#include "texture.h"
#include "color.h"
#include "sound.h"
#include "light.h"
#include "mode.h"
#include "utility.h"
#include "number.h"
#include "score.h"
#include "ranking.h"
#include "input.h"
#include "bg.h"
#include "effect.h"

//=============================================================================
// 定義
//=============================================================================
namespace
{
const int	MAX_TIME = 600;	// タイムの最大値
}// namespaceはここまで

//=============================================================================
// スタティック変数
//=============================================================================
namespace
{
int	s_nIdxMoon;				// 背景の矩形のインデックス
int	s_nIdxUI[2];			// UIの矩形のインデックス
int	s_nGaugeIdxGray;		// ゲージのインデックスの保管
int	s_nGaugeIdxYellow;		// ゲージのインデックスの保管
int	s_nTime;				// タイム
float s_fGaugeAlphaGray;	// 現在のゲージのアルファ値
float s_fGaugeAlphaYellow;	// 現在のゲージのアルファ値
}// namespaceはここまで

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// リザルト初期化処理
//=============================================================================
void InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM_RESULT);

	s_nTime = 0;

	s_fGaugeAlphaGray = 0.3f;	// 現在のゲージのアルファ値
	s_fGaugeAlphaYellow = 0.3f;	// 現在のゲージのアルファ値

	// ゲージの初期化
	InitGauge();

	// ゲージの設定(灰色)
	s_nGaugeIdxGray =  SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);
	
	// ゲージの設定(黄色)
	s_nGaugeIdxYellow = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_YELLOW), (GetLight() - 1) * (SCREEN_WIDTH / 16.0f), SCREEN_HEIGHT, GAUGE_LEFT);

	// ゲージの色の設定(灰色)
	SetColorGauge(s_nGaugeIdxGray, D3DXCOLOR(GetColor(COLOR_GRAY).r, GetColor(COLOR_GRAY).g, GetColor(COLOR_GRAY).b, s_fGaugeAlphaGray));

	// ゲージの色の設定(黄色)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlphaYellow));
	
	// 背景の初期化
	InitBG();

	// エフェクトの初期化
	InitEffect();

	{// 月
		// 矩形の設定
		s_nIdxMoon = SetRectangle(TEXTURE_BG_MOON);

		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdxMoon, pos, size);
	}

	{// 今回のスコア
		s_nIdxUI[0] = SetRectangle(TEXTURE_YourScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(750.0f, 100.0f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdxUI[0], pos, size);
	}

	{// ベストスコア
		// 矩形の設定
		s_nIdxUI[1] = SetRectangle(TEXTURE_BestScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(750.0f, 100.0f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdxUI[1], pos, size);
	}

	// ランキングの初期化
	InitRanking();

	// スコアの初期化
	InitScore();

	// ランキングの設定
	SetRanking();
}

//=============================================================================
// リザルト終了処理
//=============================================================================
void UninitResult(void)
{
	StopSound();

	// 使うのを止める
	StopUseRectangle(s_nIdxMoon);

	// ゲージの終了
	UninitGauge();

	// ランキングの終了
	UninitRanking();

	// エフェクトの終了
	UninitEffect();

	// スコアの終了
	InitScore();
}

//=============================================================================
// リザルト更新処理
//=============================================================================
void UpdateResult(void)
{
	// ゲージの更新
	UpdateGauge();

	// エフェクトの更新
	UpdateEffect();

	// スコアの更新
	UpdateScore();

	// ランキングの更新
	UpdateRanking();

	s_nTime++;

	if (s_nTime >= MAX_TIME)
	{
		// モードの変更
		ChangeMode(MODE_TITLE);
	}

	if (GetFunctionKeyTrigger(FUNCTION_KEY_DESISION))
	{//決定キー(ENTERキー)が押されたかどうか
		// モードの変更
		ChangeMode(MODE_TITLE);

		// サウンドの再生
		PlaySound(SOUND_LABEL_SE_ENTER);
	}

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

//=============================================================================
// リザルト描画処理
//=============================================================================
void DrawResult(void)
{
	// 矩形の描画
	DrawRectangle();
}