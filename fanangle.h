#pragma once
//**************************************************
// 
// Hackathon ( rectangle.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _FANANGLE_H_	//このマクロ定義がされてなかったら
#define _FANANGLE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "texture.h"

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitFanangle(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitFanangle(void);

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawFanangle(void);

//--------------------------------------------------
// 設定
// 引数  : TEXTURE texture / 列挙型 種類
//--------------------------------------------------
int SetFanangle(TEXTURE texture);

//--------------------------------------------------
// 設定 [ テクスチャあり ]
// 引数  : LPDIRECT3DTEXTURE9 pTexture / テクスチャ
//--------------------------------------------------
int SetFanangleWithTex(LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// 使うのを止める
// 引数  : int nIdx / インデックス
//--------------------------------------------------
void StopUseFanangle(int nIdx);

//--------------------------------------------------
// 位置の設定
// 引数1  : int nIdx / インデックス
// 引数2  : D3DXVECTOR3 &pos / 中心の位置
// 引数3  : D3DXVECTOR3 &size / サイズ
//--------------------------------------------------
void SetPosFanangle(int nIdx, const D3DXVECTOR3 &pos, const float &fLength);

//--------------------------------------------------
// 回転する位置の設定
// 引数1  : int nIdx / インデックス
// 引数2  : D3DXVECTOR3 &pos / 中心の位置
// 引数3  : float fRot / 向き
// 引数4  : float fLength / 長さ
//--------------------------------------------------
void SetRotationPosFanangle(int nIdx, const D3DXVECTOR3 &pos, float fRot, float fLength);

//--------------------------------------------------
// 色の設定
// 引数1  : int nIdx / インデックス
// 引数2  : D3DXCOLOR &color / 色
//--------------------------------------------------
void SetColorFanangle(int nIdx, const D3DXCOLOR &color);

//--------------------------------------------------
// 中心色の設定
// 引数1  : int nIdx / インデックス
// 引数2  : D3DXCOLOR &color / 色
//--------------------------------------------------
void SetColorCenterFanangle(int nIdx, const D3DXCOLOR &color);

//--------------------------------------------------
// テクスチャ座標の設定
// 引数  : int nIdx / インデックス
//--------------------------------------------------
void SetTexFanangle(int nIdx);

//--------------------------------------------------
// 描画するかどうか
// 引数1  : int nIdx / インデックス
// 引数2  : bool bDraw / 描画するかどうか
//--------------------------------------------------
void SetDrawFanangle(int nIdx, bool bDraw);

//--------------------------------------------------
// 加算合成するかどうか
// 引数1  : int nIdx / インデックス
// 引数2  : bool bDraw / 加算合成するかどうか
//--------------------------------------------------
void SetAddFanangle(int nIdx, bool bAdd);

//--------------------------------------------------
// テクスチャの変更
// 引数1  : int nIdx / インデックス
// 引数2  : TEXTURE texture / 列挙型 種類
//--------------------------------------------------
void ChangeTextureRectangle(int nIdx, TEXTURE texture);

//--------------------------------------------------
// テクスチャの変更 [ テクスチャあり ]
// 引数1  : int nIdx / インデックス
// 引数2  : TEXTURE texture / 列挙型 種類
//--------------------------------------------------
void ChangeTextureFanangleWithTex(int nIdx, LPDIRECT3DTEXTURE9 pTexture);

//--------------------------------------------------
// 頂点バッファの取得
// 引数  : int nIdx / インデックス
// 返値  : LPDIRECT3DVERTEXBUFFER9 / 頂点バッファ
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffFanangle(int nIdx);

//--------------------------------------------------
// 頂点バッファの取得
// 引数  : int nIdx / インデックス
// 返値  : LPDIRECT3DVERTEXBUFFER9 / 頂点バッファ
//--------------------------------------------------
void AddDrawFanangle(int nIdx,int nVolume);

#endif // !_FANANGLE_H_
