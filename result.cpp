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

#include "input.h"

//=============================================================================
// スタティック変数
//=============================================================================
namespace
{
	int	s_nIdxBG;	// 背景の矩形のインデックス
}// namespaceはここまで

static int s_nGaugeIdx;			//ゲージのインデックスの保管
static float s_fGaugeWidth;		//ゲージの幅（黄色）

//=============================================================================
// プロトタイプ宣言
//=============================================================================

//=============================================================================
// リザルト初期化処理
//=============================================================================
void InitResult(void)
{
	PlaySound(SOUND_LABEL_BGM_RESULT);

	s_fGaugeWidth = 0.0f;
	// ゲージの初期化
	InitGauge();

	// ゲージの設定(灰色)
	SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_GRAY), SCREEN_WIDTH, SCREEN_HEIGHT, GAUGE_LEFT);
	// ゲージの設定(黄色)
	s_nGaugeIdx = SetGauge(D3DXVECTOR3(0.0f, SCREEN_HEIGHT * 0.5f, 0.0f), GetColor(COLOR_YELLOW), 0.0f, SCREEN_HEIGHT, GAUGE_LEFT);

	// 矩形の設定
	s_nIdxBG = SetRectangle(TEXTURE_BG);

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	D3DXVECTOR3 size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// 矩形の位置の設定
	SetPosRectangle(s_nIdxBG, pos, size);

	// 矩形の色の設定
	SetColorRectangle(s_nIdxBG, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================================================
// リザルト終了処理
//=============================================================================
void UninitResult(void)
{
	StopSound();

	// 使うのを止める
	StopUseRectangle(s_nIdxBG);
}

//=============================================================================
// リザルト更新処理
//=============================================================================
void UpdateResult(void)
{
	if (GetKeyboardTrigger(DIK_8))
	{
		s_fGaugeWidth += SCREEN_WIDTH / 16.0f;
		ChangeGauge(s_nGaugeIdx, s_fGaugeWidth, SCREEN_HEIGHT);
	}
	UpdateGauge();
}

//=============================================================================
// リザルト描画処理
//=============================================================================
void DrawResult(void)
{
	// 矩形の描画
	DrawRectangle();
}