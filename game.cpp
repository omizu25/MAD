//**************************************************
//
// FPD制作 ( game.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// インクルード
//==================================================
#include "main.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "sound.h"
#include "player.h"
#include "rectangle.h"
#include "disc.h"
#include "ui.h"
#include "pause.h"

#include <assert.h>
//==================================================
// スタティック変数
//==================================================
static GAMESTATE		s_gameState = GAMESTATE_NONE;		// ゲームの状態
static int				s_nCounterState;					// 状態管理カウンター
static bool				s_bPause = false;					// ポーズ中かどうか [してる  : true してない  : false]

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void InitGame(void)
{
	// 矩形の初期化
	InitRectangle();

	// ディスクの初期化
	InitDisc();

	//プレイヤーの初期化
	InitPlayer();

	//UIの初期化
	InitUi();

	// ポーズの初期化
	InitPause();

	//UIの配置
	SetUi(D3DXVECTOR3 (50.0f, 15.0f, 0.0f), 100.0f, 30.0f, 0);
	SetUi(D3DXVECTOR3 (SCREEN_WIDTH - 50.0f, 15.0f, 0.0f), 100.0f, 30.0f, 1);

	s_gameState = GAMESTATE_START;		// 開始状態に設定

	s_nCounterState = 0;				// カウンターの初期化

	s_bPause = false;					// ポーズ解除
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void UninitGame(void)
{
	// サウンドの停止
	StopSound();

	// 矩形の終了
	UninitRectangle();

	// ディスクの終了
	UninitDisc();

	// プレイヤーの終了
	UninitPlayer();

	//UIの終了
	UninitUi();

	// ポーズの終了
	UninitPause();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void UpdateGame(void)
{
	if (GetDirectJoypadTrigger(JOYKEY_DIRECT_7_BUTTON) || GetKeyboardTrigger(DIK_P))
	{
		s_bPause = !s_bPause;

		if (s_bPause)
		{// ポーズしている
			// メニューの設定
			SetPause();
		}
	}

	if (s_bPause)
	{// ポーズしている
		// ポーズの更新
		UpdatePause();
		return;
	}

	// ディスクの更新
	UpdateDisc();

	switch (s_gameState)
	{
	case GAMESTATE_START:		// 開始状態
		s_gameState = GAMESTATE_NORMAL;
		break;

	case GAMESTATE_NORMAL:		// 通常状態
		// プレイヤーの更新
		UpdatePlayer();
		
		//UIの更新(まだ何もしてない)
		UpdateUi();

		break;

	case GAMESTART_RESET:		// リセット状態

		break;

	case GAMESTATE_END:			// 終了状態

		break;

	case GAMESTATE_RESULT:		// リザルト状態

		break;

	case GAMESTATE_NONE:		// 何もしていない状態
	default:
		assert(false);
		break;
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void DrawGame(void)
{
	// プレイヤーの描画
	DrawPlayer();

	//UIの描画
	DrawUi();

	// 矩形の描画
	DrawRectangle();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void SetGameState(GAMESTATE state)
{
	s_gameState = state;
	s_nCounterState = 0;
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
GAMESTATE GetGameState(void)
{
	return s_gameState;
}

//--------------------------------------------------
// ポーズの有効無効設定
//--------------------------------------------------
void SetEnablePause(bool bPause)
{
	s_bPause = bPause;
}
