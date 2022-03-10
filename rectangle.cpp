//**************************************************
// 
// FPG制作 ( rectangle.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "rectangle.h"
#include "color.h"

#include <assert.h>

//==================================================
// マクロ定義
//==================================================
#define MAX_RECTANGLE		(1024)		// 矩形の最大数
#define NUM_VERTEX			(4)			// 頂点の数
#define NUM_POLYGON			(2)			// ポリゴンの数

//==================================================
// 構造体
//==================================================
typedef struct
{
	LPDIRECT3DTEXTURE9			pTexture;		// テクスチャ
	LPDIRECT3DVERTEXBUFFER9		pVtxBuff;		// 頂点バッファ
	bool						bUse;			// 使用しているかどうか
}MyRectangle;

//==================================================
// スタティック変数
//==================================================
MyRectangle		s_aRectangle[MAX_RECTANGLE];		// 矩形の情報

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitRectangle(void)
{
	// メモリのクリア
	memset(s_aRectangle, 0, sizeof(s_aRectangle));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitRectangle(void)
{
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawRectangle(void)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int i = 0; i < MAX_RECTANGLE; i++)
	{
		MyRectangle *pRectangle = &s_aRectangle[i];

		if (!pRectangle->bUse)
		{// 使用していない
			continue;
		}

		/*↓ 使用している ↓*/

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, pRectangle->pVtxBuff, 0, sizeof(VERTEX_2D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// テクスチャの設定
		pDevice->SetTexture(0, pRectangle->pTexture);

		// ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,		// プリミティブの種類
			0,							// 描画する最初の頂点インデックス
			NUM_POLYGON);				// プリミティブ(ポリゴン)数

		// テクスチャの解除
		pDevice->SetTexture(0, NULL);
	}
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
int SetRectangle(LPDIRECT3DTEXTURE9 pTexture)
{
	for (int i = 0; i < MAX_RECTANGLE; i++)
	{
		MyRectangle *pRectangle = &s_aRectangle[i];

		if (pRectangle->bUse)
		{// 使用している
			continue;
		}

		/*↓ 使用していない ↓*/

		pRectangle->pTexture = pTexture;
		pRectangle->bUse = true;

		// 頂点バッファの生成
		GetDevice()->CreateVertexBuffer(
			sizeof(VERTEX_2D) * NUM_VERTEX,
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,
			D3DPOOL_MANAGED,
			&pRectangle->pVtxBuff,
			NULL);

		VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

		// 頂点情報をロックし、頂点情報へのポインタを取得
		pRectangle->pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点バッファをアンロックする
		pRectangle->pVtxBuff->Unlock();

		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// 位置の設定
		SetPosRectangle(i, pos, size);

		//色の設定
		SetColorRectangle(i, GetColor(COLOR_WHITE));

		D3DXVECTOR2 texU = D3DXVECTOR2(0.0f, 1.0f);
		D3DXVECTOR2 texV = D3DXVECTOR2(0.0f, 1.0f);

		// テクスチャ座標の設定
		SetTexRectangle(i, texU, texV);

		return i;
	}

	assert(false);
	return -1;
}

//--------------------------------------------------
// 使用をやめる
//--------------------------------------------------
void StopUseRectangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	pRectangle->bUse = false;

	if (pRectangle->pVtxBuff != NULL)
	{// 頂点バッファの解放
		pRectangle->pVtxBuff->Release();
		pRectangle->pVtxBuff = NULL;
	}
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void SetPosRectangle(int nIdx, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle(nIdx);

	// 頂点情報をロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidth = size.x * 0.5f;
	float fHeight = size.y * 0.5f;

	// 頂点座標の設定
	pVtx[0].pos = pos + D3DXVECTOR3(-fWidth, -fHeight, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(fWidth, -fHeight, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(-fWidth, fHeight, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(fWidth, fHeight, 0.0f);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// 回転する位置の設定
//--------------------------------------------------
void SetRotationPosRectangle(int nIdx, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &rot, float fAngle, float fLength)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle(nIdx);

	// 頂点情報をロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos.x = pos.x + (sinf(rot.z + (-D3DX_PI + fAngle)) * fLength);
	pVtx[0].pos.y = pos.y + (cosf(rot.z + (-D3DX_PI + fAngle)) * fLength);
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = pos.x + (sinf(rot.z + (D3DX_PI + (fAngle * -1.0f))) * fLength);
	pVtx[1].pos.y = pos.y + (cosf(rot.z + (D3DX_PI + (fAngle * -1.0f))) * fLength);
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = pos.x + (sinf(rot.z + (fAngle * -1.0f)) * fLength);
	pVtx[2].pos.y = pos.y + (cosf(rot.z + (fAngle * -1.0f)) * fLength);
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = pos.x + (sinf(rot.z + fAngle) * fLength);
	pVtx[3].pos.y = pos.y + (cosf(rot.z + fAngle) * fLength);
	pVtx[3].pos.z = 0.0f;

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// 色の設定
//--------------------------------------------------
void SetColorRectangle(int nIdx, const D3DXCOLOR &color)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle(nIdx);

	// 頂点情報をロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// テクスチャ座標の設定
//--------------------------------------------------
void SetTexRectangle(int nIdx, const D3DXVECTOR2 &texU, const D3DXVECTOR2 &texV)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// 使用していない
		return;
	}

	/*↓ 使用している ↓*/

	VERTEX_2D *pVtx = NULL;		// 頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuffRectangle(nIdx);

	// 頂点情報をロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(texU.x, texV.x);
	pVtx[1].tex = D3DXVECTOR2(texU.y, texV.x);
	pVtx[2].tex = D3DXVECTOR2(texU.x, texV.y);
	pVtx[3].tex = D3DXVECTOR2(texU.y, texV.y);

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//--------------------------------------------------
// 頂点バッファを取得
//--------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 GetVtxBuffRectangle(int nIdx)
{
	assert(nIdx >= 0 && nIdx < MAX_RECTANGLE);

	MyRectangle *pRectangle = &s_aRectangle[nIdx];

	if (!pRectangle->bUse)
	{// 使用していない
		return NULL;
	}

	/*↓ 使用している ↓*/

	return s_aRectangle[nIdx].pVtxBuff;
}
