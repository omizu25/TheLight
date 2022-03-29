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
int	s_nIdxBG;			// 背景の矩形のインデックス
int	s_nIdxUI[2];			// UIの矩形のインデックス
int	s_nGaugeIdxGray;	// ゲージのインデックスの保管
int	s_nGaugeIdxYellow;	// ゲージのインデックスの保管
int	s_nTime;			// タイム
float s_fGaugeAlpha;	// 現在のゲージのアルファ値
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

	s_fGaugeAlpha = 0.3f;	// 現在のゲージのアルファ値

	// ゲージの初期化
	InitGauge();

	// ゲージの設定(灰色)
	s_nGaugeIdxGray =  SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);
	
	// ゲージの設定(黄色)
	s_nGaugeIdxYellow = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_YELLOW), (GetLight() - 1) * (SCREEN_WIDTH / 16.0f), SCREEN_HEIGHT, GAUGE_LEFT);

	// ゲージの色の設定(黄色)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlpha));
	
	{// 背景
		// 矩形の設定
		s_nIdxBG = SetRectangle(TEXTURE_BG);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdxBG, pos, size);

		// 矩形の色の設定
		SetColorRectangle(s_nIdxBG, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	{// 今回のスコア
	 // 矩形の設定
		s_nIdxUI[0] = SetRectangle(TEXTURE_YourScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.25f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(600.0f, 100.0f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdxUI[0], pos, size);

		// 矩形の色の設定
		SetColorRectangle(s_nIdxUI[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		pos = D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.25f, 0.0f);
		size = D3DXVECTOR3(70.0f, 90.0f, 0.0f);
		SetNumber(pos,size,GetColor(COLOR_WHITE),GetLight() - 1,1,false);
	}

	{// ベストスコア
	 // 矩形の設定
		s_nIdxUI[1] = SetRectangle(TEXTURE_BestScore);

		D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(600.0f, 100.0f, 0.0f);

		// 矩形の位置の設定
		SetPosRectangle(s_nIdxUI[1], pos, size);

		// 矩形の色の設定
		SetColorRectangle(s_nIdxUI[1], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		pos = D3DXVECTOR3(SCREEN_WIDTH * 0.65f, SCREEN_HEIGHT * 0.5f, 0.0f);
		size = D3DXVECTOR3(70.0f, 90.0f, 0.0f);
		SetNumber(pos, size, GetColor(COLOR_WHITE), GetRanking(), 1, false);
	}

}

//=============================================================================
// リザルト終了処理
//=============================================================================
void UninitResult(void)
{
	StopSound();

	// 使うのを止める
	StopUseRectangle(s_nIdxBG);

	// ゲージの終了
	UninitGauge();
}

//=============================================================================
// リザルト更新処理
//=============================================================================
void UpdateResult(void)
{
	// ゲージの更新
	UpdateGauge();

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
	s_fGaugeAlpha = Curve(fCurve, 0.3f, 1.0f);

	// ゲージの色の設定(黄色)
	SetColorGauge(s_nGaugeIdxYellow, D3DXCOLOR(GetColor(COLOR_YELLOW).r, GetColor(COLOR_YELLOW).g, GetColor(COLOR_YELLOW).b, s_fGaugeAlpha));
}

//=============================================================================
// リザルト描画処理
//=============================================================================
void DrawResult(void)
{
	// 矩形の描画
	DrawRectangle();
}