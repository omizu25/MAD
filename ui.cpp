//========================================================
//
//UI
//Author:ûüì]
//
//========================================================
#include "ui.h"
#include "game.h"
//====================================
//}Nè`
//====================================
#define MAX_UI		128				//UIÌÅå
#define NUM_UI		10				//UIÌíÞ
#define MAX_TIME	60				//oÄ¢éÔ
//====================================
//O[oÏ
//====================================
LPDIRECT3DTEXTURE9 g_pTextureUi[NUM_UI] = {};	//eNX`ÖÌ|C^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;	//¸_obt@ÖÌ|C^
Ui g_aUi[MAX_UI];		//UIÌîñ
bool g_bUse;			//UIðg¤©Ç¤©
bool bStop;				//êñ¾¯o·
//====================================
//CÖ
//====================================

//====================================
//UIÌú»
//====================================
void InitUi(void)
{
	//foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UI\\UI000.png",
		&g_pTextureUi[0]);
	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UI\\UI001.png",
		&g_pTextureUi[1]);
	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UI\\FivePoints.png",
		&g_pTextureUi[2]);
	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UI\\ThreePoints.png",
		&g_pTextureUi[3]);
	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UI\\Set1.png",
		&g_pTextureUi[4]);
	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UI\\Set2.png",
		&g_pTextureUi[5]);
	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UI\\Set3.png",
		&g_pTextureUi[6]);
	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UI\\Set4.png",
		&g_pTextureUi[7]);
	//eNX`ÌÇÝÝ
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\UI\\Set5.png",
		&g_pTextureUi[8]);
	//UIÌîñÌú»
	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		g_aUi[nCntUi].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCntUi].scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aUi[nCntUi].nCntTime = 0.0f;
		g_aUi[nCntUi].fHeight = 0.0f;
		g_aUi[nCntUi].fWidth = 0.0f;
		g_aUi[nCntUi].nType = 0;
		g_aUi[nCntUi].bUse = false;		//gpµÄ¢È¢óÔÉ·é
		g_aUi[nCntUi].bSwitch = false;	//Á¦Ä¢­óÔÉ·é
	}
	g_bUse = true;
	bStop = false;
	//¸_obt@Ì¶¬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffUi,
		NULL);

	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^
	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		//¸_ÀWÌÝè
		pVtx[0].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth / 2, g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2, 0.0f);
		//rhwÌÝè
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//¸_J[ÌÝè
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//eNX`ÀWÌÝè
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//¸_f[^Ì|C^ð4Âªißé
	}
	//¸_obt@ðAbN·é
	g_pVtxBuffUi->Unlock();
}
//====================================
//UIÌI¹
//====================================
void UninitUi(void)
{
	//eNX`Ìjü
	for (int i = 0; i < NUM_UI; i++)
	{
		if (g_pTextureUi[i] != NULL)
		{
			g_pTextureUi[i]->Release();
			g_pTextureUi[i] = NULL;
		}
	}

	//¸_obt@Ìjü
	if (g_pVtxBuffUi != NULL)
	{
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}
}
//====================================
//UIÌXV
//====================================
void UpdateUi(void)
{
	if (!g_bUse)
	{//UIðgíÈ¢
		return;
	}

	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^
	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		//íÞ²ÆÌ®«(¶©çoé)
		if (g_aUi[nCntUi].nType == 2 && g_aUi[nCntUi].bSwitch == false)
		{//oÄ­é
			g_aUi[nCntUi].scale.x += 0.01f;
			//gå¦Ì²®
			if (g_aUi[nCntUi].scale.x > 1.0f)
			{
				g_aUi[nCntUi].scale.x = 1.0f;
				g_aUi[nCntUi].nCntTime++;
				if (g_aUi[nCntUi].nCntTime == MAX_TIME)
				{
					g_aUi[nCntUi].bSwitch = true;
				}
			}
		}
		else if (g_aUi[nCntUi].nType == 2 && g_aUi[nCntUi].bSwitch)
		{//Á¦é
			g_aUi[nCntUi].scale.x -= 0.01f;
		}

		//íÞ²ÆÌ®«(E©çoé)
		if (g_aUi[nCntUi].nType == 3 && g_aUi[nCntUi].bSwitch == false)
		{//oÄ­é
			g_aUi[nCntUi].scale.x -= 0.01f;
			//gå¦Ì²®
			if (g_aUi[nCntUi].scale.x < -1.0f)
			{
				g_aUi[nCntUi].scale.x = -1.0f;
				g_aUi[nCntUi].nCntTime++;
				if (g_aUi[nCntUi].nCntTime == MAX_TIME)
				{
					g_aUi[nCntUi].bSwitch = true;
				}
			}
		}
		else if (g_aUi[nCntUi].nType == 3 && g_aUi[nCntUi].bSwitch)
		{//Á¦é
			g_aUi[nCntUi].scale.x += 0.01f;
		}

		//íÞ²ÆÌ®«(ãºÉLÑé)
		if (g_aUi[nCntUi].nType == 4 && g_aUi[nCntUi].bSwitch == false)
		{//oÄ­é
			g_aUi[nCntUi].scale.y += 0.01f;
			//gå¦Ì²®
			if (g_aUi[nCntUi].scale.y > 1.0f)
			{
				g_aUi[nCntUi].scale.y = 1.0f;
				g_aUi[nCntUi].nCntTime++;
				if (g_aUi[nCntUi].nCntTime == MAX_TIME)
				{
					g_aUi[nCntUi].bSwitch = true;
				}
			}
		}
		else if (g_aUi[nCntUi].nType == 4 && g_aUi[nCntUi].bSwitch)
		{//Á¦é
			g_aUi[nCntUi].scale.y -= 0.01f;

			if (g_aUi[nCntUi].scale.y <= 0.0f)
			{
				g_bUse = false;
				bStop = true;
				g_aUi[nCntUi].bUse = false;
				// Q[ÌóÔÌÝè
				SetGameState(GAMESTATE_START);
			}
		}

		//gå¦Ì²®
		if (g_aUi[nCntUi].scale.x > 1.0f)
		{
			g_aUi[nCntUi].scale.x = 1.0f;
			g_aUi[nCntUi].bSwitch = true;
		}
		else if(g_aUi[nCntUi].scale.y > 1.0f)
		{
			g_aUi[nCntUi].scale.y = 1.0f;
			g_aUi[nCntUi].bSwitch = true;
		}
		if (g_aUi[nCntUi].scale.x < -1.0f)
		{
			g_aUi[nCntUi].scale.x = -1.0f;
		}
		else if (g_aUi[nCntUi].scale.y < -1.0f)
		{
			g_aUi[nCntUi].scale.y = -1.0f;
		}

		if (g_aUi[nCntUi].nType == 2)
		{
			//¸_ÀWÌÝè
			pVtx[0].pos = D3DXVECTOR3((g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2), (g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + (g_aUi[nCntUi].fWidth / 2 * g_aUi[nCntUi].scale.x), (g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2), (g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + (g_aUi[nCntUi].fWidth / 2 * g_aUi[nCntUi].scale.x), (g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
		}
		else if (g_aUi[nCntUi].nType == 3)
		{
			//¸_ÀWÌÝè
			pVtx[0].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x - (g_aUi[nCntUi].fWidth / 2 * -g_aUi[nCntUi].scale.x), (g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth  / 2, (g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x - (g_aUi[nCntUi].fWidth / 2 * -g_aUi[nCntUi].scale.x), (g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth  / 2 , (g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
		}
		else if (g_aUi[nCntUi].nType == 4)
		{
			//¸_ÀWÌÝè
			pVtx[0].pos = D3DXVECTOR3((g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2),							g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2 * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + (g_aUi[nCntUi].fWidth / 2 * g_aUi[nCntUi].scale.x), g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2 * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2),							g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2 * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aUi[nCntUi].pos.x + (g_aUi[nCntUi].fWidth / 2 * g_aUi[nCntUi].scale.x), g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2 * g_aUi[nCntUi].scale.y, 0.0f);
		}
		if (g_aUi[nCntUi].nType == 3)
		{
			//¸_J[ÌÝè
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * -g_aUi[nCntUi].scale.x);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * -g_aUi[nCntUi].scale.x);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * -g_aUi[nCntUi].scale.x);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * -g_aUi[nCntUi].scale.x);
		}
		else
		{
			//¸_J[ÌÝè
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * g_aUi[nCntUi].scale.x);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * g_aUi[nCntUi].scale.x);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * g_aUi[nCntUi].scale.x);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f * g_aUi[nCntUi].scale.x);
		}

		pVtx += 4;
	}
	//¸_obt@ðAbN·é
	g_pVtxBuffUi->Unlock();
}
//====================================
//UIÌ`æ
//====================================
void DrawUi(void)
{
	if (!g_bUse)
	{//UIðgíÈ¢
		return;
	}

	//foCXÌæ¾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	//¸_obt@ðf[^Xg[ÉÝè
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));
	//¸_tH[}bgÌÝè
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		if (g_aUi[nCntUi].nType == 1 && bStop)
		{
			continue;
		}
		if (g_aUi[nCntUi].bUse)
		{//UIªgp³êÄ¢é
		 //eNX`ÌÝè
			pDevice->SetTexture(0, g_pTextureUi[g_aUi[nCntUi].nTexture]);
			//|SÌ`æ
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntUi * 4, 2);	//v~eBu(|S)
		}
	}
}
//====================================
//UIÌÝè
//====================================
void SetUi(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType, D3DXVECTOR3 scale,int nTexture)
{
	VERTEX_2D * pVtx;		//¸_îñÖÌ|C^
	//¸_obt@ðbNµA¸_îñÖÌ|C^ðæ¾
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntUi = 0; nCntUi < MAX_UI; nCntUi++)
	{
		if (g_aUi[nCntUi].bUse == false)
		{//UIªgp³êÄ¢È¢
			g_aUi[nCntUi].pos = pos;
			g_aUi[nCntUi].fWidth = fWidth;
			g_aUi[nCntUi].fHeight = fHeight;
			g_aUi[nCntUi].nType = nType;
			g_aUi[nCntUi].scale = scale;
			g_aUi[nCntUi].nTexture = nTexture;
			g_aUi[nCntUi].nCntTime = 0;
			//¸_ÀWÌÝè
			pVtx[0].pos = D3DXVECTOR3((g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2) *  g_aUi[nCntUi].scale.x, (g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth / 2) *  g_aUi[nCntUi].scale.x, (g_aUi[nCntUi].pos.y - g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((g_aUi[nCntUi].pos.x - g_aUi[nCntUi].fWidth / 2) *  g_aUi[nCntUi].scale.x, (g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((g_aUi[nCntUi].pos.x + g_aUi[nCntUi].fWidth / 2) *  g_aUi[nCntUi].scale.x, (g_aUi[nCntUi].pos.y + g_aUi[nCntUi].fHeight / 2) * g_aUi[nCntUi].scale.y, 0.0f);

			g_aUi[nCntUi].bSwitch = false;
			g_bUse = true;
			g_aUi[nCntUi].bUse = true;		//gpµÄ¢éóÔ
			break;
		}
		pVtx += 4;
	}
	//¸_obt@ðAbN·é
	g_pVtxBuffUi->Unlock();
}
//====================================
//UIîñÌæ¾
//====================================
Ui * GetUi(void)
{
	return &g_aUi[0];
}