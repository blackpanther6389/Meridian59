// Meridian 59, Copyright 1994-2024 Andrew Kirmse and Chris Kirmse.
// All rights reserved.
//
// This software is distributed under a license that is described in
// the LICENSE file that accompanies it.
//
// Meridian is a registered trademark.
#include "client.h"

// Variables

static particle_system gParticleSystem;

extern custom_xyz playerDeltaPos;
extern LPDIRECT3DVERTEXDECLARATION9 decl0dc;
extern LPDIRECT3DVERTEXDECLARATION9 decl1dc;

extern d3d_render_pool_new gParticlePool;
extern d3d_render_cache_system gParticleCacheSystem;
extern d3d_render_cache_system	gObjectCacheSystem;
extern d3d_render_pool_new gObjectPool;
extern unsigned int gFrame;
extern LPDIRECT3DTEXTURE9 gpBackBufferTex[16];
extern LPDIRECT3DTEXTURE9 gpBackBufferTexFull;
extern int gFullTextureSize;
extern int gSmallTextureSize;
extern d3d_render_cache_system gEffectCacheSystem;
extern d3d_render_pool_new gEffectPool;
extern D3DMATRIX mat;

// Interfaces

static void SandstormInit(void);

// Implementations

/**
* Initializes the particle effects, specifically the sandstorm particle emitters.
*/
void D3DFxInit()
{
	SandstormInit();
}

/**
* Updates and renders all active particle emitters, including the sandstorm effect, 
* in the current frame.
*/
void D3DRenderParticles()
{
	list_type	list;
	emitter		*pEmitter;

	for (list = gParticleSystem.emitterList; list != NULL; list = list->next)
	{
		pEmitter = (emitter *)list->data;

		if (pEmitter)
			D3DParticleEmitterUpdate(pEmitter, playerDeltaPos.x, playerDeltaPos.y, playerDeltaPos.z);
	}

	if (effects.sand)
	{
		IDirect3DDevice9_SetVertexShader(gpD3DDevice, NULL);
		IDirect3DDevice9_SetVertexDeclaration(gpD3DDevice, decl0dc);

		D3DParticleSystemUpdate(&gParticleSystem, &gParticlePool, &gParticleCacheSystem);
	}
}

/**
* Initializes the sandstorm particle emitters with predefined positions, energy, and colors for the 
* particle system.
*/
void SandstormInit(void)
{
	static const int EMITTER_RADIUS = 12;
	static const int EMITTER_ENERGY = 40;
	static const int EMITTER_HEIGHT = 0;

	D3DParticleSystemReset(&gParticleSystem);
	// four corners, blowing around the perimeter
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -724.0f, EMITTER_RADIUS * -724.0f, EMITTER_HEIGHT,
		0, 500.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -724.0f, EMITTER_RADIUS * 724.0f, EMITTER_HEIGHT,
		500.0f, 0, 0,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 724.0f, EMITTER_RADIUS * 724.0f, EMITTER_HEIGHT,
		0, -500.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 724.0f, EMITTER_RADIUS * -724.0f, EMITTER_HEIGHT,
		-500.0f, 0, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);

	// four corners, blowing towards player
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -724.0f, EMITTER_RADIUS * -724.0f, EMITTER_HEIGHT,
		353.55f, 353.55f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -724.0f, EMITTER_RADIUS * 724.0f, EMITTER_HEIGHT,
		353.55f, -353.55f, 0,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 724.0f, EMITTER_RADIUS * 724.0f, EMITTER_HEIGHT,
		-353.55f, -353.55f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 724.0f, EMITTER_RADIUS * -724.0f, EMITTER_HEIGHT,
		-353.55f, 353.55f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);

	// forward, left, right, and back, blowing towards player
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -1024.0f, 0, EMITTER_HEIGHT,
		500.0f, 0.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 1024.0f, 0, EMITTER_HEIGHT,
		-500.0f, 0, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		0, EMITTER_RADIUS * 1024.0f, EMITTER_HEIGHT,
		0, -500.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		0, EMITTER_RADIUS * -1024.0f, EMITTER_HEIGHT,
		0, 500.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);

	// four corners, blowing around the perimeter
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -724.0f, EMITTER_RADIUS * -724.0f, EMITTER_HEIGHT,
		0, 500.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -724.0f, EMITTER_RADIUS * 724.0f, EMITTER_HEIGHT,
		500.0f, 0, 0,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 724.0f, EMITTER_RADIUS * 724.0f, EMITTER_HEIGHT,
		0, -500.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 724.0f, EMITTER_RADIUS * -724.0f, EMITTER_HEIGHT,
		-500.0f, 0, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);

	// four corners, blowing towards player
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -724.0f, EMITTER_RADIUS * -724.0f, EMITTER_HEIGHT,
		353.55f, 353.55f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -724.0f, EMITTER_RADIUS * 724.0f, EMITTER_HEIGHT,
		353.55f, -353.55f, 0,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 724.0f, EMITTER_RADIUS * 724.0f, EMITTER_HEIGHT,
		-353.55f, -353.55f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 724.0f, EMITTER_RADIUS * -724.0f, EMITTER_HEIGHT,
		-353.55f, 353.55f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);

	// forward, left, right, and back, blowing towards player
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * -1024.0f, 0, EMITTER_HEIGHT,
		500.0f, 0.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		EMITTER_RADIUS * 1024.0f, 0, EMITTER_HEIGHT,
		-500.0f, 0, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		0, EMITTER_RADIUS * 1024.0f, EMITTER_HEIGHT,
		0, -500.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
	D3DParticleEmitterInit(&gParticleSystem,
		0, EMITTER_RADIUS * -1024.0f, EMITTER_HEIGHT,
		0, 500.0f, 0.0f,
		SANDSTORM_B, SANDSTORM_G, SANDSTORM_R, SANDSTORM_A,
		EMITTER_ENERGY, 1,
		0, -PI / 500.0f, -PI / 500.0f,
		1, 1024, 2);
}

/**
* Applies post-render overlay effects such as alpha blending, screen flashes, and pain effects, 
* and resets the rendering cache.
*/
void D3DPostOverlayEffects(d3d_render_pool_new *pPool)
{
	D3DRENDER_SET_ALPHATEST_STATE(gpD3DDevice, TRUE, 1, D3DCMP_GREATEREQUAL);
	D3DRENDER_SET_ALPHABLEND_STATE(gpD3DDevice, TRUE, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA);
	IDirect3DDevice9_SetRenderState(gpD3DDevice, D3DRS_ZENABLE, FALSE);

	D3DCacheSystemReset(&gObjectCacheSystem);
	D3DRenderPoolReset(&gObjectPool, &D3DMaterialObjectPool);

	static DWORD			timeLastFrame = 0;
	DWORD					timeCurrent, timeDelta;
	int						i;
	d3d_render_chunk_new	*pChunk;
	d3d_render_packet_new	*pPacket;

	timeCurrent = timeGetTime();
	timeDelta = timeCurrent - timeLastFrame;
	timeLastFrame = timeCurrent;

	// Flash of XLAT.  Could be color, blindness, whatever.
	if (effects.flashxlat != XLAT_IDENTITY)
	{
		custom_bgra	bgra;

		effects.duration -= (int)timeDelta;
		switch (effects.flashxlat)
		{
			case XLAT_BLEND10RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 25;
			break;

			case XLAT_BLEND20RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 50;
			break;

			case XLAT_BLEND25RED:
			case XLAT_BLEND30RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 75;
			break;

			case XLAT_BLEND40RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 100;
			break;

			case XLAT_BLEND50RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 125;
			break;

			case XLAT_BLEND60RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 150;
			break;

			case XLAT_BLEND70RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 175;
			break;

			case XLAT_BLEND75RED:
			case XLAT_BLEND80RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 200;
			break;

			case XLAT_BLEND90RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 225;
			break;

			case XLAT_BLEND100RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 255;
			break;

			case XLAT_BLEND10WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 25;
			break;

			case XLAT_BLEND20WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 50;
			break;

			case XLAT_BLEND30WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 75;
			break;

			case XLAT_BLEND40WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 100;
			break;

			case XLAT_BLEND50WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 125;
			break;

			case XLAT_BLEND60WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 150;
			break;

			case XLAT_BLEND70WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 175;
			break;

			case XLAT_BLEND80WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 200;
			break;

			case XLAT_BLEND90WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 225;
			break;

			case XLAT_BLEND100WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 255;
			break;

			case XLAT_BLEND25YELLOW:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 255;
			break;

			case XLAT_BLEND25GREEN:
				bgra.b = 0; bgra.g = COLOR_MAX; bgra.r = 0; bgra.a = 64;
			break;
			case XLAT_BLEND50GREEN:
				bgra.b = 0; bgra.g = COLOR_MAX; bgra.r = 0; bgra.a = 128;
			break;
			case XLAT_BLEND75GREEN:
				bgra.b = 0; bgra.g = COLOR_MAX; bgra.r = 0; bgra.a = 192;
			break;
			case XLAT_BLEND25BLUE:
				bgra.b = COLOR_MAX; bgra.g = 0; bgra.r = 0; bgra.a = 64;
			break;
			case XLAT_BLEND50BLUE:
				bgra.b = COLOR_MAX; bgra.g = 0; bgra.r = 0; bgra.a = 128;
			break;
			case XLAT_BLEND75BLUE:
				bgra.b = COLOR_MAX; bgra.g = 0; bgra.r = 0; bgra.a = 192;
			break;

			default:
				bgra.b = 0; bgra.g = 0; bgra.r = 0; bgra.a = 255;
			break;
		}

		if (effects.duration <= 0)
		{
			effects.flashxlat = XLAT_IDENTITY;
			effects.duration = 0;
		}

		pPacket = D3DRenderPacketFindMatch(pPool, NULL, NULL, 0, 0, 0);
		if (NULL == pPacket)
			return;
		pChunk = D3DRenderChunkNew(pPacket);
		assert(pChunk);
		pChunk->numIndices = 4;
		pChunk->numVertices = 4;
		pChunk->numPrimitives = pChunk->numVertices - 2;
		pPacket->pMaterialFctn = &D3DMaterialEffectPacket;
		pChunk->pMaterialFctn = &D3DMaterialEffectChunk;
		MatrixIdentity(&pChunk->xForm);

		for (i = 0; i < 4; i++)
		{
			CHUNK_BGRA_SET(pChunk, i, bgra.b, bgra.g, bgra.r, bgra.a);
		}

		CHUNK_XYZ_SET(pChunk, 0, D3DRENDER_SCREEN_TO_CLIP_X(0, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(0, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 1, D3DRENDER_SCREEN_TO_CLIP_X(0, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 2, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 3, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(0, gScreenHeight));

		pChunk->indices[0] = 1;
		pChunk->indices[1] = 2;
		pChunk->indices[2] = 0;
		pChunk->indices[3] = 3;
	}

	if (effects.xlatOverride > 0)
	{
		custom_bgra	bgra;

		switch (effects.xlatOverride)
		{
			case XLAT_BLEND10RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 25;
			break;

			case XLAT_BLEND20RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 50;
			break;

			case XLAT_BLEND25RED:
			case XLAT_BLEND30RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 75;
			break;

			case XLAT_BLEND40RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 100;
			break;

			case XLAT_BLEND50RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 125;
			break;

			case XLAT_BLEND60RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 150;
			break;

			case XLAT_BLEND70RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 175;
			break;

			case XLAT_BLEND75RED:
			case XLAT_BLEND80RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 200;
			break;

			case XLAT_BLEND90RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 225;
			break;

			case XLAT_BLEND100RED:
				bgra.b = 0; bgra.g = 0; bgra.r = COLOR_MAX; bgra.a = 255;
			break;

			case XLAT_BLEND10WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 25;
			break;

			case XLAT_BLEND20WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 50;
			break;

			case XLAT_BLEND30WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 75;
			break;

			case XLAT_BLEND40WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 100;
			break;

			case XLAT_BLEND50WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 125;
			break;

			case XLAT_BLEND60WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 150;
			break;

			case XLAT_BLEND70WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 175;
			break;

			case XLAT_BLEND80WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 200;
			break;

			case XLAT_BLEND90WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 225;
			break;

			case XLAT_BLEND100WHITE:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 255;
			break;

			case XLAT_BLEND25YELLOW:
				bgra.b = COLOR_MAX; bgra.g = COLOR_MAX; bgra.r = COLOR_MAX; bgra.a = 255;
			break;

			case XLAT_BLEND25GREEN:
				bgra.b = 0; bgra.g = COLOR_MAX; bgra.r = 0; bgra.a = 64;
			break;
			case XLAT_BLEND50GREEN:
				bgra.b = 0; bgra.g = COLOR_MAX; bgra.r = 0; bgra.a = 128;
			break;
			case XLAT_BLEND75GREEN:
				bgra.b = 0; bgra.g = COLOR_MAX; bgra.r = 0; bgra.a = 192;
			break;
			case XLAT_BLEND25BLUE:
				bgra.b = COLOR_MAX; bgra.g = 0; bgra.r = 0; bgra.a = 64;
			break;
			case XLAT_BLEND50BLUE:
				bgra.b = COLOR_MAX; bgra.g = 0; bgra.r = 0; bgra.a = 128;
			break;
			case XLAT_BLEND75BLUE:
				bgra.b = COLOR_MAX; bgra.g = 0; bgra.r = 0; bgra.a = 192;
			break;

			default:
				bgra.b = 0; bgra.g = 0; bgra.r = 0; bgra.a = 255;
			break;
		}

		pPacket = D3DRenderPacketFindMatch(pPool, NULL, NULL, 0, 0, 0);
		if (NULL == pPacket)
			return;
		pChunk = D3DRenderChunkNew(pPacket);
		assert(pChunk);
		pChunk->numIndices = 4;
		pChunk->numVertices = 4;
		pChunk->numPrimitives = pChunk->numVertices - 2;
		pPacket->pMaterialFctn = &D3DMaterialEffectPacket;
		pChunk->pMaterialFctn = &D3DMaterialEffectChunk;
		MatrixIdentity(&pChunk->xForm);

		for (i = 0; i < 4; i++)
		{
			CHUNK_BGRA_SET(pChunk, i, bgra.b, bgra.g, bgra.r, bgra.a);
		}

		CHUNK_XYZ_SET(pChunk, 0, D3DRENDER_SCREEN_TO_CLIP_X(0, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(0, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 1, D3DRENDER_SCREEN_TO_CLIP_X(0, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 2, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 3, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(0, gScreenHeight));

		pChunk->indices[0] = 1;
		pChunk->indices[1] = 2;
		pChunk->indices[2] = 0;
		pChunk->indices[3] = 3;
	}

	// May be drawn over room or map.

	// whiteout
	if (effects.whiteout)
	{
		int	whiteout = min(effects.whiteout, 500);

		whiteout = whiteout * COLOR_MAX / 500;
		whiteout = max(whiteout, 200);

		pPacket = D3DRenderPacketFindMatch(pPool, NULL, NULL, 0, 0, 0);
		if (NULL == pPacket)
			return;
		pChunk = D3DRenderChunkNew(pPacket);
		assert(pChunk);
		pChunk->numIndices = 4;
		pChunk->numVertices = 4;
		pChunk->numPrimitives = pChunk->numVertices - 2;
		pPacket->pMaterialFctn = &D3DMaterialEffectPacket;
		pChunk->pMaterialFctn = &D3DMaterialEffectChunk;
		MatrixIdentity(&pChunk->xForm);

		for (i = 0; i < 4; i++)
		{
			CHUNK_BGRA_SET(pChunk, i, COLOR_MAX, COLOR_MAX, COLOR_MAX, whiteout);
		}

		CHUNK_XYZ_SET(pChunk, 0, D3DRENDER_SCREEN_TO_CLIP_X(0, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(0, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 1, D3DRENDER_SCREEN_TO_CLIP_X(0, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 2, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 3, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth, gScreenWidth), 0,
			D3DRENDER_SCREEN_TO_CLIP_Y(0, gScreenHeight));

		pChunk->indices[0] = 1;
		pChunk->indices[1] = 2;
		pChunk->indices[2] = 0;
		pChunk->indices[3] = 3;
	}

	// Pain (always drawn last).
	if (config.pain)
	{
		if (effects.pain)
		{
			int	pain = min(effects.pain, 2000);

			pain = pain * 204 / 2000;

			pPacket = D3DRenderPacketFindMatch(pPool, NULL, NULL, 0, 0, 0);
			if (NULL == pPacket)
				return;
			pChunk = D3DRenderChunkNew(pPacket);
			assert(pChunk);
			pChunk->numIndices = 4;
			pChunk->numVertices = 4;
			pChunk->numPrimitives = pChunk->numVertices - 2;
			pPacket->pMaterialFctn = &D3DMaterialEffectPacket;
			pChunk->pMaterialFctn = &D3DMaterialEffectChunk;
			MatrixIdentity(&pChunk->xForm);

			for (i = 0; i < 4; i++)
			{
				CHUNK_BGRA_SET(pChunk, i, 0, 0, COLOR_MAX, pain);
			}

			CHUNK_XYZ_SET(pChunk, 0, D3DRENDER_SCREEN_TO_CLIP_X(0, gScreenWidth), 0,
				D3DRENDER_SCREEN_TO_CLIP_Y(0, gScreenHeight));
			CHUNK_XYZ_SET(pChunk, 1, D3DRENDER_SCREEN_TO_CLIP_X(0, gScreenWidth), 0,
				D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight, gScreenHeight));
			CHUNK_XYZ_SET(pChunk, 2, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth, gScreenWidth), 0,
				D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight, gScreenHeight));
			CHUNK_XYZ_SET(pChunk, 3, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth, gScreenWidth), 0,
				D3DRENDER_SCREEN_TO_CLIP_Y(0, gScreenHeight));

			pChunk->indices[0] = 1;
			pChunk->indices[1] = 2;
			pChunk->indices[2] = 0;
			pChunk->indices[3] = 3;
		}
	}

	D3DCacheFill(&gObjectCacheSystem, &gObjectPool, 1);
	D3DCacheFlush(&gObjectCacheSystem, &gObjectPool, 1, D3DPT_TRIANGLESTRIP);
	IDirect3DDevice9_SetRenderState(gpD3DDevice, D3DRS_ZENABLE, TRUE);
}

/**
* Creates a blur and wave distortion effect using frame buffers, applying it to the current screen 
* using a series of textures.
*/
void D3DFxBlurWaver()
{
	d3d_render_packet_new	*pPacket;
	d3d_render_chunk_new	*pChunk;
	int						i, t;
	static int				offset = 0;
	static int				offsetDir = 1;

	t = gFrame & 7;

	if (gFrame & 63)
	{
		offset += offsetDir;

		if ((offset > 31) || (offset < 0))
		{
			offsetDir = -offsetDir;
			offset += offsetDir;
		}
	}

	D3DRENDER_SET_ALPHATEST_STATE(gpD3DDevice, FALSE, 1, D3DCMP_GREATEREQUAL);
	D3DRENDER_SET_ALPHABLEND_STATE(gpD3DDevice, FALSE, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA);

	IDirect3DDevice9_SetVertexShader(gpD3DDevice, NULL);
	IDirect3DDevice9_SetVertexDeclaration(gpD3DDevice, decl1dc);

	D3DRenderFramebufferTextureCreate(gpBackBufferTexFull, gpBackBufferTex[t],
		gSmallTextureSize, gSmallTextureSize);

	D3DCacheSystemReset(&gEffectCacheSystem);
	D3DRenderPoolReset(&gEffectPool, &D3DMaterialBlurPool);

	for (i = 0; i <= 7; i++)
	{
		pPacket = D3DRenderPacketNew(&gEffectPool);
		if (NULL == pPacket)
			return;
		pChunk = D3DRenderChunkNew(pPacket);
		pPacket->pMaterialFctn = D3DMaterialBlurPacket;
		pChunk->pMaterialFctn = D3DMaterialBlurChunk;
		pPacket->pTexture = gpBackBufferTex[i];
		pChunk->numIndices = pChunk->numVertices = 4;
		pChunk->numPrimitives = pChunk->numVertices - 2;
		MatrixIdentity(&pChunk->xForm);

		CHUNK_XYZ_SET(pChunk, 0, D3DRENDER_SCREEN_TO_CLIP_X(-offset, gScreenWidth),
			0, D3DRENDER_SCREEN_TO_CLIP_Y(-offset, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 1, D3DRENDER_SCREEN_TO_CLIP_X(-offset, gScreenWidth),
			0, D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight + offset, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 2, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth + offset, gScreenWidth),
			0, D3DRENDER_SCREEN_TO_CLIP_Y(gScreenHeight + offset, gScreenHeight));
		CHUNK_XYZ_SET(pChunk, 3, D3DRENDER_SCREEN_TO_CLIP_X(gScreenWidth + offset, gScreenWidth),
			0, D3DRENDER_SCREEN_TO_CLIP_Y(-offset, gScreenHeight));

		CHUNK_ST0_SET(pChunk, 0, 0.0f, 0.0f);
		CHUNK_ST0_SET(pChunk, 1, 0.0f, 1.0f);
		CHUNK_ST0_SET(pChunk, 2, 1.0f, 1.0f);
		CHUNK_ST0_SET(pChunk, 3, 1.0f, 0.0f);

		CHUNK_BGRA_SET(pChunk, 0, COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX / 4);
		CHUNK_BGRA_SET(pChunk, 1, COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX / 4);
		CHUNK_BGRA_SET(pChunk, 2, COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX / 4);
		CHUNK_BGRA_SET(pChunk, 3, COLOR_MAX, COLOR_MAX, COLOR_MAX, COLOR_MAX / 4);

		CHUNK_INDEX_SET(pChunk, 0, 1);
		CHUNK_INDEX_SET(pChunk, 1, 2);
		CHUNK_INDEX_SET(pChunk, 2, 0);
		CHUNK_INDEX_SET(pChunk, 3, 3);
	}

	MatrixIdentity(&mat);
	IDirect3DDevice9_SetTransform(gpD3DDevice, D3DTS_WORLD, &mat);
	IDirect3DDevice9_SetTransform(gpD3DDevice, D3DTS_VIEW, &mat);
	IDirect3DDevice9_SetTransform(gpD3DDevice, D3DTS_PROJECTION, &mat);
	IDirect3DDevice9_SetRenderState(gpD3DDevice, D3DRS_ZENABLE, FALSE);

	D3DRENDER_SET_ALPHATEST_STATE(gpD3DDevice, FALSE, 1, D3DCMP_GREATEREQUAL);
	D3DRENDER_SET_ALPHABLEND_STATE(gpD3DDevice, TRUE, D3DBLEND_SRCALPHA, D3DBLEND_INVSRCALPHA);

	D3DCacheFill(&gEffectCacheSystem, &gEffectPool, 1);
	D3DCacheFlush(&gEffectCacheSystem, &gEffectPool, 1, D3DPT_TRIANGLESTRIP);

	IDirect3DDevice9_SetRenderState(gpD3DDevice, D3DRS_ZENABLE, TRUE);
}