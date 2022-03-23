//**************************************************
//
// FPG制作 ( result.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _RESULT_H_	// このマクロ定義がされてなかったら
#define _RESULT_H_	// ２重インクルード防止のマクロ定義

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitResult(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitResult(void);

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateResult(void);

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawResult(void);

//--------------------------------------------------
// 勝敗の設定
// 引数1  : int nPlayerNo / プレイヤーの番号
// 引数2  : bool bResult / 勝敗 [ true : 勝ち / false : 負け ]
//--------------------------------------------------
void SetResult(int nPlayerNo, bool bResult);

//--------------------------------------------------
// 描画するかどうか
// 引数  : bool bDraw / 描画するかどうか
//--------------------------------------------------
void SetDrawResult(bool bDraw);

#endif // !_RESULT_H_
