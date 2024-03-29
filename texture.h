//**************************************************
// 
// FPG制作 ( texture.h )
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// 列挙型
//==================================================
typedef enum
{
	/*↓ タイトル ↓*/
	TEXTURE_BG = 0,				// タイトル画面の背景(平原)
	TEXTURE_BG2,				// タイトル画面の背景(雪原)
	TEXTURE_BG3,				// タイトル画面の背景(海)
	TEXTURE_Title_Logo,			// タイトルロゴ
	TEXTURE_Light_Blue,			// 青い光
	TEXTURE_Light_Red,			// 赤い光
	TEXTURE_Game_Start,			// ゲームスタートの文字
	TEXTURE_Rule_Select,		// ルール選択の文字
	TEXTURE_Map_Select,			// マップ選択の文字
	TEXTURE_Char_Select,		// キャラ選択の文字
	TEXTURE_Tutorial_Start,		// チュートリアルの文字

	/*↓ セレクト ↓*/
	TEXTURE_Select_Left,		// 左ボタン
	TEXTURE_Select_Right,		// 右ボタン
	TEXTURE_Select_Time,		// 制限時間
	TEXTURE_Select_Point,		// ポイント数
	TEXTURE_Select_Set,			// セット数
	TEXTURE_Select_BG,			// セレクト画面の背景
	TEXTURE_Map_Title,			// マップ選択
	TEXTURE_Rule_Title,			// ルール設定
	TEXTURE_Char_Title,			// キャラ選択
	TEXTURE_Speed,				// 速度
	TEXTURE_Power,				// 力
	TEXTURE_Stage1,				// ステージ1
	TEXTURE_Stage2,				// ステージ2
	TEXTURE_Stage3,				// ステージ3
	TEXTURE_OK,					// OK

	/*↓ ゲーム ↓*/
	TEXTURE_Disc,				// ディスク
	TEXTURE_Number_Yellow,		// 数字(黄色)
	TEXTURE_Stage01,			// 1つ目のステージ
	TEXTURE_Stage02,			// 2つ目のステージ
	TEXTURE_Stage03,			// 3つ目のステージ
	TEXTURE_Stage01_BG,			// 1つ目のステージの背景
	TEXTURE_Stage02_BG,			// 2つ目のステージの背景
	TEXTURE_Stage03_BG,			// 3つ目のステージの背景

	/*↓ ゲーム中のUI ↓*/
	TEXTURE_GAME_SetFrame01,	// セットの枠(1pカラー)
	TEXTURE_GAME_SetFrame02,	// セットの枠(2pカラー)
	TEXTURE_GAME_PtsFrame01,	// ポイントの枠(1pカラー)
	TEXTURE_GAME_PtsFrame02,	// ポイントの枠(2pカラー)
	TEXTURE_UI000,				// UI-0
	TEXTURE_UI001,				// UI-1
	TEXTURE_Set1,				// セット1の表示
	TEXTURE_Set2,				// セット2の表示
	TEXTURE_Set3,				// セット3の表示
	TEXTURE_Set4,				// セット4の表示
	TEXTURE_Set5,				// セット5の表示
	TEXTURE_Three_Point,		// 3ポイント
	TEXTURE_Five_Point,			// 5ポイント

	/*↓ ポーズ ↓*/
	TEXTURE_Pose_Title,			// ポーズ画面のタイトル
	TEXTURE_Pose_Resume,		// 再開
	TEXTURE_Pose_Quit,			// 終了

	/*↓ リザルト ↓*/
	TEXTURE_Result_Win,			// 勝利
	TEXTURE_Result_Lose,		// 敗北
	TEXTURE_Result_Draw,		// 引き分け

	/*↓ プレイヤー ↓*/
	TEXTURE_enemy000,			// カピバラ
	TEXTURE_kitune,				// ゴン
	TEXTURE_player000,			// スライム
	TEXTURE_ghost,				// ゴースト
	TEXTURE_cat,				// 猫

	/*↓ エフェクト ↓*/
	TEXTURE_Effect_fire,		// 炎のエフェクト
	TEXTURE_Effect_spin,		// ディスクのエフェクト
	TEXTURE_Effect_tackle,		// タックルのエフェクト
	TEXTURE_Effect_goal,		// ゴールのエフェクト
	TEXTURE_Effect_spark,		// 壁のエフェクト

	/*↓ その他 ↓*/
	TEXTURE_Number_0To9,		// 数字
	TEXTURE_MAX,
	TEXTURE_NONE,
}TEXTURE;

//==================================================
// プロトタイプ宣言
//==================================================
//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void LoadTexture(void);

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitTexture(void);

//--------------------------------------------------
// 取得
// 引数  : TEXTURE texture / 列挙型 種類
// 返値  : LPDIRECT3DTEXTURE9 / テクスチャ
//--------------------------------------------------
LPDIRECT3DTEXTURE9 GetTexture(TEXTURE texture);

#endif // !_TEXTURE_H_
