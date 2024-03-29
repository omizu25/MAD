//**************************************************
//
// FPG制作 ( disc.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _DISC_H_	// このマクロ定義がされてなかったら
#define _DISC_H_	// ２重インクルード防止のマクロ定義

//==================================================
// 構造体
//==================================================
typedef struct
{
	D3DXVECTOR3	pos;		// 位置
	D3DXVECTOR3	posOld;		// 前回の位置
	D3DXVECTOR3	rot;		// 向き
	D3DXVECTOR3	move;		// 移動量
	int			nIdx;		// 矩形のインデックス
	int			nThrow;		// 何番目のプレイヤーが投げたか
	int			nEffect;	// エフェクトの出すタイミングを調整
	bool		bHave;		// プレイヤーが持っているかどうか
}Disc;

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitDisc(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitDisc(void);

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateDisc(void);

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawDisc(void);

//--------------------------------------------------
// 取得
// 返値  : Disc / 構造体
//--------------------------------------------------
Disc *GetDisc(void);

//--------------------------------------------------
// リセット
//--------------------------------------------------
void ResetDisc(void);

//--------------------------------------------------
// 次に始めるプレイヤーの設定
// 引数  : int nIdx / プレイヤーの番号
//--------------------------------------------------
void SetPossDisc(int nIdx);

#endif // !_DISC_H_
