//**************************************************
//
// FPD制作 ( number.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _NUMBER_H_	//このマクロ定義がされてなかったら
#define _NUMBER_H_	//２重インクルード防止のマクロ定義

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitNumber(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitNumber(void);

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateNumber(void);

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawNumber(void);

//--------------------------------------------------
// 設定
// 引数1  : D3DXVECTOR3 &pos / 中心の位置
// 引数2  : D3DXVECTOR3 &size / サイズ
// 引数3  : D3DXCOLOR &col / 色
// 引数4  : int nNumber / 数
// 返値  : int / 配列のインデックス
//--------------------------------------------------
int SetNumber(const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size, const D3DXCOLOR &col, int nNumber);

//--------------------------------------------------
// 位置の設定
// 引数1  : int nIdx / 配列のインデックス
// 引数2  : D3DXVECTOR3 &pos / 中心の位置
// 引数3  : D3DXVECTOR3 &size / サイズ
//--------------------------------------------------
void SetPosNumber(int nIdx, const D3DXVECTOR3 &pos, const D3DXVECTOR3 &size);

//--------------------------------------------------
// 変更
// 引数1  : int nIdx / 配列のインデックス
// 引数2  : int nNumber / 数
// 返値  : int / 新しい配列のインデックス
//--------------------------------------------------
int ChangeNumber(int nIdx, int nNumber);

//--------------------------------------------------
// 使うのを止める
// 引数  : int nIdx / インデックス
//--------------------------------------------------
void StopUseNumber(int nIdx);

//--------------------------------------------------
// 桁数
// 引数  : int nNumber / 数
// 返値  : int / 桁数
//--------------------------------------------------
int DigitNumber(int nNumber);

//--------------------------------------------------
// 描画するかどうか
// 引数1  : int nIdx / インデックス
// 引数2  : bool bDraw / 描画するかどうか
//--------------------------------------------------
void SetDrawNumber(int nIdx, bool bDraw);

#endif // !_NUMBER_H_
