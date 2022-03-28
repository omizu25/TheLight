//=========================================
// 
// パーティクルの処理
// Author YudaKaito
// 
//=========================================

//-----------------------------------------
// include
//-----------------------------------------
#include "main.h"
#include "effect.h"
#include "rectangle.h"
#include "color.h"
#include "utility.h"
#include <assert.h>

//-----------------------------------------
// マクロ定義
//-----------------------------------------
#define MAX_EFFECT	(512)	// パーティクルの最大数
#define MAX_TEX		(MAX_EFFECT)		// テクスチャの種類
#define JUMP_TEX	"data/TEXTURE/jump.png"

//-----------------------------------------
// パーティクル構造体
//-----------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	// 位置
	D3DXVECTOR3 move;	// 移動量
	D3DXVECTOR3 rot;	// 角度
	D3DXCOLOR col;		// 色
	float fRaduus;		// 半径
	int nMaxLife;		// 最大寿命
	int nLife;			// 寿命
	int nIdx;			// RectAngel
	EFFECT_TYPE type;	// パーティクルの種類
	bool bUse;			// 使用しているかどうかe
}Effect;

//-----------------------------------------
// 静的変数
//-----------------------------------------
static LPDIRECT3DTEXTURE9 s_pTexture[MAX_EFFECT] = {};		// テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;	// 頂点バッファへのポインタ
static Effect s_aEffect[MAX_EFFECT];
static float s_fAngle;

//=========================================
// パーティクルの初期化処理
//=========================================
void InitEffect(void)
{
	ZeroMemory(s_aEffect, sizeof(s_aEffect));

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		Effect *pEffect = &s_aEffect[i];

		// 矩形の設定
		pEffect->nIdx = SetRectangle(TEXTURE_NONE);

		// 矩形を描画するかどうか
		SetDrawRectangle(pEffect->nIdx, false);
	}
}

//=========================================
// パーティクルの終了処理
//=========================================
void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		Effect *pEffect = &s_aEffect[i];

		if (!pEffect->bUse)
		{// 使用していない
			continue;
		}

		/*↓ 使用している ↓*/

		// 使うのを止める
		StopUseRectangle(pEffect->nIdx);
	}
}

//=========================================
// パーティクルの更新処理
//=========================================
void UpdateEffect(void)
{
	Effect *pEffect;

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		pEffect = s_aEffect + i;

		if (!pEffect->bUse)
		{	// パーティクルが使用されていない
			continue;
		}

		// パーティクルが使用されている
		// 位置の更新
		pEffect->pos += pEffect->move;

		switch (pEffect->type)
		{
		case EFFECT_TYPE_PLAYER_JUMP:	// プレイヤーのジャンプパーティクル	// 列挙型に変更する。
			pEffect->nLife--;			// 体力の更新
			pEffect->col.a -= (float)1.0f / pEffect->nMaxLife;			// 透明度の更新
			pEffect->fRaduus += 1.5f;	// 半径の拡大
			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}
			break;
		case  EFFECT_TYPE_PLAYER_WALK:		// プレイヤーの移動
			pEffect->nLife -= 1;
			if (pEffect->nLife <= 0)
			{
				pEffect->bUse = false;
			}
			break;
		//case EFFECT_TYPE_PLAYER_AIR:			// プレイヤーの空中軌道
		//	pEffect->nLife--;
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	if (pEffect->nLife <= 0)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_PLAYER_DEATH:
		//	break;
		//case EFFECT_TYPE_SPLITBALL_ATTACK:
		//	pEffect->fRaduus -= 2.0f;
		//	if (pEffect->fRaduus <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_BALL_HOMING00_ATTACK:	// 甘い追従をする円の攻撃 
		//									// 体力の更新
		//	pEffect->nLife--;
		//	if (pEffect->nLife <= 0)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	// 透明度の更新
		//	pEffect->col.g -= (float)1 / pEffect->nMaxLife;
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	break;
		//case EFFECT_TYPE_BALL_HOMING01_ATTACK:	// 追従をする円の攻撃 
		//									// 体力の更新
		//	pEffect->nLife--;
		//	if (pEffect->nLife <= 0)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	// 透明度の更新
		//	pEffect->col.g -= (float)1 / pEffect->nMaxLife;
		//	pEffect->col.r -= (float)1 / pEffect->nMaxLife;
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	break;
		//case EFFECT_TYPE_GOSTRAIGHT_DIE:	// 直進する長方形死亡時
		//	pEffect->fRaduus -= 0.15f;
		//	if (pEffect->fRaduus <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_BALL_HOMING00_DIE:		// 甘い追従をする円の死亡時
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	pEffect->fRaduus -= 0.05f;
		//	if (pEffect->fRaduus <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_BALL_HOMING01_DIE:		// 追従をする円の死亡時
		//	pEffect->col.a -= (float)0.5f / pEffect->nMaxLife;
		//	pEffect->fRaduus -= 0.05f;
		//	if (pEffect->fRaduus <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		//case EFFECT_TYPE_SERECT_DECISION:		// 決定時発生するパーティクル
		//	pEffect->col.a -= (float)1.0f / pEffect->nMaxLife;			// 透明度の更新
		//	if (pEffect->col.a <= 0.0f)
		//	{
		//		pEffect->bUse = false;
		//	}
		//	break;
		default:
			break;
		}

		if (!pEffect->bUse)
		{	// パーティクルが使用されていない
			// 矩形を描画するかどうか
			SetDrawRectangle(pEffect->nIdx, false);
		}

		// 矩形の位置の設定
		SetPosRectangle(pEffect->nIdx, pEffect->pos, D3DXVECTOR3(pEffect->fRaduus, pEffect->fRaduus, 0.0f));
	}
}

//=========================================
// パーティクルの描画処理
//=========================================
void DrawEffect(void)
{
}

//=========================================
// パーティクルの設定処理
//=========================================
void SetEffect(D3DXVECTOR3 pos, EFFECT_TYPE type)
{
	Effect *pEffect;
	int nCntParticle;

	for (nCntParticle = 0; nCntParticle < MAX_EFFECT; nCntParticle++)
	{
		pEffect = &(s_aEffect[nCntParticle]);

		if (pEffect->bUse)
		{// パーティクルが使用されてる
			continue;
		}

		// パーティクルが使用されていない
		pEffect->type = type;
//		pEffect->nIdx = SetRectangle(TEXTURE_NONE);

		switch (type)
		{
		case EFFECT_TYPE_PLAYER_JUMP:	// プレイヤーのジャンプパーティクル
			// 矩形のテクスチャの変更
			ChangeTextureRectangle(pEffect->nIdx, TEXTURE_NONE);
			pEffect->pos = pos;
			pEffect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pEffect->move.x = 0.0f;
			pEffect->move.y = 0.0f;
			pEffect->move.z = 0.0f;
			pEffect->col = D3DXCOLOR(0.4f, 0.71f, 0.63f, 1.0f);
			pEffect->fRaduus = 10.0f;
			pEffect->nMaxLife = 25;
			pEffect->nLife = pEffect->nMaxLife;
			break;
		case  EFFECT_TYPE_PLAYER_WALK:		// プレイヤーの移動
			pEffect->pos = pos;
			pEffect->col = D3DXCOLOR(0.5f, 0.35f, 0.25f, 1.0f);
			pEffect->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pEffect->move.x = cosf(FloatRandam(D3DX_PI, -D3DX_PI)) * FloatRandam(5.3f, 2.0f);
			pEffect->move.y = sinf(FloatRandam(D3DX_PI, -D3DX_PI)) * FloatRandam(5.3f, 2.0f);
			pEffect->fRaduus = 8.0f;
			pEffect->nMaxLife = 25;
			pEffect->nLife = pEffect->nMaxLife;
			break;
		default:
			assert(false);
			break;
		}

		pEffect->bUse = true;

		D3DXVECTOR3 size = D3DXVECTOR3(pEffect->fRaduus, pEffect->fRaduus, 0.0f);

		// 矩形を描画するかどうか
		SetDrawRectangle(pEffect->nIdx, true);

		// 矩形の位置の設定
		SetPosRectangle(pEffect->nIdx, pEffect->pos, size);

		// 矩形の色の設定
		SetColorRectangle(pEffect->nIdx, pEffect->col);

		break;
	}
}
