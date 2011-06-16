/*
===========================================================================
ARX FATALIS GPL Source Code
Copyright (C) 1999-2010 Arkane Studios SA, a ZeniMax Media company.

This file is part of the Arx Fatalis GPL Source Code ('Arx Fatalis Source Code'). 

Arx Fatalis Source Code is free software: you can redistribute it and/or modify it under the terms of the GNU General Public 
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

Arx Fatalis Source Code is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Arx Fatalis Source Code.  If not, see 
<http://www.gnu.org/licenses/>.

In addition, the Arx Fatalis Source Code is also subject to certain additional terms. You should have received a copy of these 
additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Arx 
Fatalis Source Code. If not, please request a copy in writing from Arkane Studios at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing Arkane Studios, c/o 
ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.
===========================================================================
*/
//////////////////////////////////////////////////////////////////////////////////////
//   @@        @@@        @@@                @@                           @@@@@     //
//   @@@       @@@@@@     @@@     @@        @@@@                         @@@  @@@   //
//   @@@       @@@@@@@    @@@    @@@@       @@@@      @@                @@@@        //
//   @@@       @@  @@@@   @@@  @@@@@       @@@@@@     @@@               @@@         //
//  @@@@@      @@  @@@@   @@@ @@@@@        @@@@@@@    @@@            @  @@@         //
//  @@@@@      @@  @@@@  @@@@@@@@         @@@@ @@@    @@@@@         @@ @@@@@@@      //
//  @@ @@@     @@  @@@@  @@@@@@@          @@@  @@@    @@@@@@        @@ @@@@         //
// @@@ @@@    @@@ @@@@   @@@@@            @@@@@@@@@   @@@@@@@      @@@ @@@@         //
// @@@ @@@@   @@@@@@@    @@@@@@           @@@  @@@@   @@@ @@@      @@@ @@@@         //
// @@@@@@@@   @@@@@      @@@@@@@@@@      @@@    @@@   @@@  @@@    @@@  @@@@@        //
// @@@  @@@@  @@@@       @@@  @@@@@@@    @@@    @@@   @@@@  @@@  @@@@  @@@@@        //
//@@@   @@@@  @@@@@      @@@      @@@@@@ @@     @@@   @@@@   @@@@@@@    @@@@@ @@@@@ //
//@@@   @@@@@ @@@@@     @@@@        @@@  @@      @@   @@@@   @@@@@@@    @@@@@@@@@   //
//@@@    @@@@ @@@@@@@   @@@@             @@      @@   @@@@    @@@@@      @@@@@      //
//@@@    @@@@ @@@@@@@   @@@@             @@      @@   @@@@    @@@@@       @@        //
//@@@    @@@  @@@ @@@@@                          @@            @@@                  //
//            @@@ @@@                           @@             @@        STUDIOS    //
//////////////////////////////////////////////////////////////////////////////////////

#ifndef EERIEDRAW_H
#define EERIEDRAW_H

#define EERIE_NOCOUNT	0x4000	// do not incr EERIEDrawnPolys for EERIEDRAWPRIM

#include "graphics/d3dwrapper.h"
#include "graphics/data/Mesh.h"
#include "graphics/data/Texture.h"
#include "graphics/Math.h"
#include "core/Application.h"

extern long ARX_ALTERNATE_3D;
extern Vec3f SPRmins;
extern Vec3f SPRmaxs;

void MDL_AddMetalDrawLater(D3DTLVERTEX * tv);
void MDL_FlushAll();


void Delayed_EERIEDRAWPRIM(EERIEPOLY * ep);
void Delayed_FlushAll();

HRESULT EERIEDRAWPRIM(D3DPRIMITIVETYPE dptPrimitiveType,
                      DWORD  dwVertexTypeDesc,
                      LPVOID lpvVertices,
                      DWORD  dwVertexCount,
                      DWORD  dwFlags,					//d3d flag
                      long flags = 0					//eerie flag
                     );

void EERIEDrawCircle(float x0, float y0, float r, Color col, float z);
void EERIEDraw2DLine(float x0, float y0, float x1, float y1, float z, Color col);
void EERIEDrawBitmap(float x, float y, float sx, float sy, float z, TextureContainer * tex, Color color);
void EERIEDraw2DRect(float x0, float y0, float x1, float y1, float z, Color col);
void EERIEDrawFill2DRectDegrad(float x0, float y0, float x1, float y1, float z, Color cold, Color cole);

void EERIEDraw3DCylinder(const EERIE_CYLINDER & cyl, Color col);
void EERIEDraw3DCylinderBase(const EERIE_CYLINDER & cyl, Color col);
void EERIEDrawTrue3DLine(const Vec3f & orgn, const Vec3f & dest, Color col);
void EERIEDraw3DLine(const Vec3f & orgn, const Vec3f & dest, Color col);
void EERIEDrawBitmap2DecalY(float x, float y, float sx, float sy, float z, TextureContainer * tex,
                            Color col, float _fDeltaY);

void EERIEOBJECT_Quadify(EERIE_3DOBJ * obj);
void EERIE_DRAW_SetTextureZMAP(TextureContainer * Z_map);

void EERIEDrawSprite(D3DTLVERTEX * in, float siz, TextureContainer * tex, Color col, float Zpos);
void EERIEDrawRotatedSprite(D3DTLVERTEX * in, float siz, TextureContainer * tex, Color col, float Zpos, float rot);

void EERIEPOLY_DrawWired(EERIEPOLY * ep, Color col = Color::none);
void EERIEPOLY_DrawNormals(EERIEPOLY * ep);

extern TextureContainer * EERIE_DRAW_sphere_particle;
extern TextureContainer * EERIE_DRAW_square_particle;

void EERIEDrawBitmap2(float x, float y, float sx, float sy, float z, TextureContainer * tex, Color col);
void EERIEDrawBitmap_uv(float x, float y, float sx, float sy, float z, TextureContainer * tex, Color col,
                        float u0, float v0, float u1, float v1);
void EERIEDrawBitmapUVs(float x, float y, float sx, float sy, float z, TextureContainer * tex, Color col,
                        float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3);

bool ARX_DrawPrimitive_SoftClippZ(D3DTLVERTEX *, D3DTLVERTEX *, D3DTLVERTEX *, float _fAdd = 0.f);

#endif

