//
// Copyright (C) 1993-1996 Id Software, Inc.
// Copyright (C) 2016-2017 Alexey Khokholov (Nuke.YKT)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// DESCRIPTION:
//	All the clipping: columns, horizontal spans, sky columns.
//

#include <stdlib.h>

#include "i_system.h"

#include "doomdef.h"
#include "doomstat.h"

#include "r_local.h"
#include "r_sky.h"
#include "r_data.h"
#include "w_wad.h"
#include "z_zone.h"

#include "std_func.h"

#include <conio.h>

#include "sizeopt.h"

#include "fastdiv.h"

#define SC_INDEX 0x3C4

// OPTIMIZE: closed two sided lines as single sided

// True if any of the segs textures might be visible.
int segtextured;

// False if the back side is the same plane.
byte markfloor;
byte markceiling;

int maskedtexture;
int toptexture;
int bottomtexture;
int midtexture;

angle_t rw_normalangle;
// angle to line origin
int rw_angle1;

//
// regular wall
//
int rw_x;
int rw_stopx;
angle_t rw_centerangle;
fixed_t rw_offset;
fixed_t rw_distance;
fixed_t rw_scale;
fixed_t rw_scalestep;
fixed_t rw_midtexturemid;
fixed_t rw_toptexturemid;
fixed_t rw_bottomtexturemid;

int worldtop;
int worldbottom;
int worldhigh;
int worldlow;

fixed_t pixhigh;
fixed_t pixlow;
fixed_t pixhighstep;
fixed_t pixlowstep;

fixed_t topfrac;
fixed_t topstep;

fixed_t bottomfrac;
fixed_t bottomstep;

lighttable_t **walllights;

short *maskedtexturecol;

//
// R_RenderMaskedSegRange
//
void R_RenderMaskedSegRange(drawseg_t *ds,
							int x1,
							int x2)
{
	unsigned index;
	column_t *col;
	int lightnum;
	int texnum;

	int lump;
	int ofs;
	int tex;
	int column;

	fixed_t basespryscale;

	// Calculate light table.
	// Use different light tables
	//   for horizontal / vertical / diagonal. Diagonal?
	// OPTIMIZE: get rid of LIGHTSEGSHIFT globally
	curline = ds->curline;
	frontsector = curline->frontsector;
	backsector = curline->backsector;
	texnum = texturetranslation[curline->sidedef->midtexture];

	lightnum = (frontsector->lightlevel >> LIGHTSEGSHIFT) + extralight;

	if (curline->v1->y == curline->v2->y)
		lightnum--;
	else lightnum += curline->v1->x == curline->v2->x;

	// Lightnum between 0 and 15
	if (lightnum < 0)
		walllights = scalelight[0];
	else if (lightnum > LIGHTLEVELS - 1)
		walllights = scalelight[LIGHTLEVELS - 1];
	else
		walllights = scalelight[lightnum];

	maskedtexturecol = ds->maskedtexturecol;

	rw_scalestep = ds->scalestep;
	spryscale = basespryscale = ds->scale1 + (x1 - ds->x1) * rw_scalestep;
	mfloorclip = ds->sprbottomclip;
	mceilingclip = ds->sprtopclip;

	// find positioning
	if (curline->linedef->flags & ML_DONTPEGBOTTOM)
	{
		dc_texturemid = frontsector->floorheight > backsector->floorheight
							? frontsector->floorheight
							: backsector->floorheight;
		dc_texturemid = dc_texturemid + textureheight[texnum] - viewz;
	}
	else
	{
		dc_texturemid = frontsector->ceilingheight < backsector->ceilingheight
							? frontsector->ceilingheight
							: backsector->ceilingheight;
		dc_texturemid = dc_texturemid - viewz;
	}
	dc_texturemid += curline->sidedef->rowoffset;

	if (fixedcolormap)
		dc_colormap = fixedcolormap;

	dc_x = x1;
	do
	{
		// calculate lighting
		if (maskedtexturecol[dc_x] != MAXSHORT)
		{
			int topscreen;
			int bottomscreen;
			fixed_t basetexturemid;

			int yl, yh;
			short mfc_x, mcc_x;

			if (!fixedcolormap)
			{
				index = spryscale >> LIGHTSCALESHIFT;

				if (index >= MAXLIGHTSCALE)
					index = MAXLIGHTSCALE - 1;

				dc_colormap = walllights[index];
			}

			sprtopscreen = centeryfrac - FixedMul(dc_texturemid, spryscale);

			// VITI95: OPTIMIZE
			dc_iscale = 0xffffffffu / (unsigned)spryscale;

			// draw the texture

			tex = texnum;
			column = maskedtexturecol[dc_x];
			column &= texturewidthmask[tex];
			lump = texturecolumnlump[tex][column];
			ofs = texturecolumnofs[tex][column] - 3;

			if (lump > 0)
			{
				col = (column_t *)((byte *)W_CacheLumpNum(lump, PU_CACHE) + ofs);
			}
			else
			{
				if (!texturecomposite[tex])
					R_GenerateComposite(tex);

				col = (column_t *)(texturecomposite[tex] + ofs);
			}

			basetexturemid = dc_texturemid;
			mfc_x = mfloorclip[dc_x];
			mcc_x = mceilingclip[dc_x];

			for (; col->topdelta != 0xff;)
			{
				// calculate unclipped screen coordinates
				//  for post
				topscreen = sprtopscreen + spryscale * col->topdelta;
				bottomscreen = topscreen + spryscale * col->length;

				yh = (bottomscreen - 1) >> FRACBITS;

				if (yh >= mfc_x)
					yh = mfc_x - 1;

				if (yh >= viewheight)
				{
					col = (column_t *)((byte *)col + col->length + 4);
					continue;
				}

				yl = (topscreen + FRACUNIT - 1) >> FRACBITS;

				if (yl <= mcc_x)
					yl = mcc_x + 1;

				if (yl > yh)
				{
					col = (column_t *)((byte *)col + col->length + 4);
					continue;
				}

				dc_source = (byte *)col + 3;
				dc_texturemid = basetexturemid - (col->topdelta << FRACBITS);

				dc_yh = yh;
				dc_yl = yl;

				#if defined(MODE_VGA16) || defined(MODE_CGA16) || defined(MODE_CVB) || defined(MODE_EGA16)
				if ((dc_x & 1) == 0){
					colfunc();
				}
				#elif defined(MODE_CGA136) || defined(MODE_VGA136) || defined(MODE_EGA136)
				if ((dc_x & 3) == 0){
					colfunc();
				}
				#else
					colfunc();
				#endif

				col = (column_t *)((byte *)col + col->length + 4);
			}

			dc_texturemid = basetexturemid;

			maskedtexturecol[dc_x] = MAXSHORT;
		}
		spryscale += rw_scalestep;
		dc_x++;
	} while (dc_x <= x2);
}

//
// R_RenderSegLoop
// Draws zero, one, or two textures (and possibly a masked
//  texture) for walls.
// Can draw or mark the starting pixel of floor and ceiling
//  textures.
// CALLED: CORE LOOPING ROUTINE.
//
#define HEIGHTBITS 12
#define HEIGHTUNIT (1 << HEIGHTBITS)

void R_RenderSegLoop(void)
{
	angle_t angle;
	unsigned index;
	int yl;
	int yh;
	int mid;
	fixed_t texturecolumn;
	int top;
	int bottom;

	int lump;
	int ofs;
	int tex;
	int col;

	int cc_rwx;
	int fc_rwx;

	//texturecolumn = 0;				// shut up compiler warning

	for (; rw_x < rw_stopx; rw_x++)
	{
		cc_rwx = ceilingclip[rw_x];
		fc_rwx = floorclip[rw_x];

		// mark floor / ceiling areas
		yl = (topfrac + HEIGHTUNIT - 1) >> HEIGHTBITS;

		// no space above wall?
		if (yl < cc_rwx + 1)
			yl = cc_rwx + 1;

		if (markceiling)
		{
			top = cc_rwx + 1;
			bottom = yl - 1;

			if (bottom >= fc_rwx)
				bottom = fc_rwx - 1;

			if (top <= bottom)
			{
				ceilingplane->top[rw_x] = top;
				ceilingplane->bottom[rw_x] = bottom;
				ceilingplane->modified = 1;
			}
		}

		yh = bottomfrac >> HEIGHTBITS;

		if (yh >= fc_rwx)
			yh = fc_rwx - 1;

		if (markfloor)
		{
			top = yh + 1;
			bottom = fc_rwx - 1;
			if (top <= cc_rwx)
				top = cc_rwx + 1;
			if (top <= bottom)
			{
				floorplane->top[rw_x] = top;
				floorplane->bottom[rw_x] = bottom;
				floorplane->modified = 1;
			}
		}

		// texturecolumn and lighting are independent of wall tiers
		if (segtextured)
		{
			// calculate texture offset
			angle = (rw_centerangle + xtoviewangle[rw_x]) >> ANGLETOFINESHIFT;
			texturecolumn = rw_offset - FixedMul(finetangent[angle], rw_distance);
			texturecolumn >>= FRACBITS;
			// calculate lighting
			index = rw_scale >> LIGHTSCALESHIFT;

			if (index >= MAXLIGHTSCALE)
				index = MAXLIGHTSCALE - 1;

			dc_colormap = walllights[index];
			dc_x = rw_x;

			// VITI95: OPTIMIZE
			dc_iscale = 0xffffffffu / (unsigned)rw_scale;
		}

		// draw the wall tiers
		if (midtexture)
		{
			if (yl > yh)
			{
				cc_rwx = viewheight;
				fc_rwx = -1;
			}
			else
			{
				// single sided line
				dc_yl = yl;
				dc_yh = yh;
				dc_texturemid = rw_midtexturemid;

				tex = midtexture;
				col = texturecolumn;
				col &= texturewidthmask[tex];
				lump = texturecolumnlump[tex][col];
				ofs = texturecolumnofs[tex][col];

				if (lump > 0)
				{
					dc_source = (byte *)W_CacheLumpNum(lump, PU_CACHE) + ofs;
				}
				else
				{
					if (!texturecomposite[tex])
						R_GenerateComposite(tex);

					dc_source = texturecomposite[tex] + ofs;
				}

				#if defined(MODE_VGA16) || defined(MODE_CGA16) || defined(MODE_CVB) || defined(MODE_EGA16)
				if ((dc_x & 1) == 0){
					colfunc();
				}
				#elif defined(MODE_CGA136) || defined(MODE_VGA136) || defined(MODE_EGA136)
				if ((dc_x & 3) == 0){
					colfunc();
				}
				#else
					colfunc();
				#endif

				cc_rwx = viewheight;
				fc_rwx = -1;
			}
		}
		else
		{
			// two sided line
			if (toptexture)
			{
				// top wall
				mid = pixhigh >> HEIGHTBITS;
				pixhigh += pixhighstep;

				if (mid >= fc_rwx)
					mid = fc_rwx - 1;

				if (mid < yl)
				{
					cc_rwx = yl - 1;
				}
				else
				{
					dc_yl = yl;
					dc_yh = mid;
					dc_texturemid = rw_toptexturemid;

					tex = toptexture;
					col = texturecolumn;
					col &= texturewidthmask[tex];
					lump = texturecolumnlump[tex][col];
					ofs = texturecolumnofs[tex][col];

					if (lump > 0)
					{
						dc_source = (byte *)W_CacheLumpNum(lump, PU_CACHE) + ofs;
					}
					else
					{
						if (!texturecomposite[tex])
							R_GenerateComposite(tex);

						dc_source = texturecomposite[tex] + ofs;
					}

					#if defined(MODE_VGA16) || defined(MODE_CGA16) || defined(MODE_CVB) || defined(MODE_EGA16)
					if ((dc_x & 1) == 0){
						colfunc();
					}
					#elif defined(MODE_CGA136) || defined(MODE_VGA136) || defined(MODE_EGA136)
					if ((dc_x & 3) == 0){
						colfunc();
					}
					#else
						colfunc();
					#endif

					cc_rwx = mid;
				}
			}
			else
			{
				// no top wall
				if (markceiling)
					cc_rwx = yl - 1;
			}

			if (bottomtexture)
			{
				// bottom wall
				mid = (pixlow + HEIGHTUNIT - 1) >> HEIGHTBITS;
				pixlow += pixlowstep;

				// no space above wall?
				if (mid <= cc_rwx)
					mid = cc_rwx + 1;

				if (mid > yh)
				{
					fc_rwx = yh + 1;
				}
				else
				{
					dc_yl = mid;
					dc_yh = yh;
					dc_texturemid = rw_bottomtexturemid;

					tex = bottomtexture;
					col = texturecolumn;
					col &= texturewidthmask[tex];
					lump = texturecolumnlump[tex][col];
					ofs = texturecolumnofs[tex][col];

					if (lump > 0)
					{
						dc_source = (byte *)W_CacheLumpNum(lump, PU_CACHE) + ofs;
					}
					else
					{
						if (!texturecomposite[tex])
							R_GenerateComposite(tex);

						dc_source = texturecomposite[tex] + ofs;
					}

					#if defined(MODE_VGA16) || defined(MODE_CGA16) || defined(MODE_CVB) || defined(MODE_EGA16)
					if ((dc_x & 1) == 0){
						colfunc();
					}
					#elif defined(MODE_CGA136) || defined(MODE_VGA136) || defined(MODE_EGA136)
					if ((dc_x & 3) == 0){
						colfunc();
					}
					#else
						colfunc();
					#endif

					fc_rwx = mid;
				}
			}
			else
			{
				// no bottom wall
				if (markfloor)
					fc_rwx = yh + 1;
			}

			if (maskedtexture)
			{
				// save texturecol
				//  for backdrawing of masked mid texture
				maskedtexturecol[rw_x] = texturecolumn;
			}
		}

		rw_scale += rw_scalestep;
		topfrac += topstep;
		bottomfrac += bottomstep;

		ceilingclip[rw_x] = cc_rwx;
		floorclip[rw_x] = fc_rwx;
	}
}

//
// R_StoreWallRange
// A wall segment will be drawn
//  between start and stop pixels (inclusive).
//
void R_StoreWallRange(int start,
					  int stop)
{
	fixed_t hyp;
	angle_t distangle, offsetangle;
	fixed_t vtop;
	int lightnum;

	// don't overflow and crash
	if (ds_p == &drawsegs[MAXDRAWSEGS])
		return;

	sidedef = curline->sidedef;
	linedef = curline->linedef;

	// mark the segment as visible for auto map
	linedef->flags |= ML_MAPPED;

	// calculate rw_distance for scale calculation
	rw_normalangle = curline->angle + ANG90;
	offsetangle = abs(rw_normalangle - rw_angle1);

	distangle = ANG90 - offsetangle;
	hyp = R_PointToDist(curline->v1->x, curline->v1->y);
	rw_distance = FixedMul(hyp, finesine[distangle >> ANGLETOFINESHIFT]);

	ds_p->x1 = rw_x = start;
	ds_p->x2 = stop;
	ds_p->curline = curline;
	rw_stopx = stop + 1;

	// calculate scale at both ends and step
	ds_p->scale1 = rw_scale = R_ScaleFromGlobalAngle(viewangle + xtoviewangle[start]);

	if (stop > start)
	{
		// VITI95: OPTIMIZE
		ds_p->scale2 = R_ScaleFromGlobalAngle(viewangle + xtoviewangle[stop]);

		switch (stop - start)
		{
		case 1:
			ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale);
			break;
		case 2:
			ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale) >> 1;
			break;
		case 3:
			ds_p->scalestep = rw_scalestep = Div003(ds_p->scale2 - rw_scale);
			break;
		case 4:
			ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale) >> 2;
			break;
		case 5:
			ds_p->scalestep = rw_scalestep = Div005(ds_p->scale2 - rw_scale);
			break;
		case 6:
			ds_p->scalestep = rw_scalestep = Div006(ds_p->scale2 - rw_scale);
			break;
		case 7:
			ds_p->scalestep = rw_scalestep = Div007(ds_p->scale2 - rw_scale);
			break;
		case 8:
			ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale) >> 3;
			break;
		case 9:
			ds_p->scalestep = rw_scalestep = Div009(ds_p->scale2 - rw_scale);
			break;
		case 10:
			ds_p->scalestep = rw_scalestep = Div010(ds_p->scale2 - rw_scale);
			break;
		case 11:
			ds_p->scalestep = rw_scalestep = Div011(ds_p->scale2 - rw_scale);
			break;
		case 12:
			ds_p->scalestep = rw_scalestep = Div012(ds_p->scale2 - rw_scale);
			break;
		case 13:
			ds_p->scalestep = rw_scalestep = Div013(ds_p->scale2 - rw_scale);
			break;
		case 14:
			ds_p->scalestep = rw_scalestep = Div014(ds_p->scale2 - rw_scale);
			break;
		case 15:
			ds_p->scalestep = rw_scalestep = Div015(ds_p->scale2 - rw_scale);
			break;
		case 16:
			ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale) >> 4;
			break;
		case 17:
			ds_p->scalestep = rw_scalestep = Div017(ds_p->scale2 - rw_scale);
			break;
		case 18:
			ds_p->scalestep = rw_scalestep = Div018(ds_p->scale2 - rw_scale);
			break;
		case 19:
			ds_p->scalestep = rw_scalestep = Div019(ds_p->scale2 - rw_scale);
			break;
		case 20:
			ds_p->scalestep = rw_scalestep = Div020(ds_p->scale2 - rw_scale);
			break;
		case 21:
			ds_p->scalestep = rw_scalestep = Div021(ds_p->scale2 - rw_scale);
			break;
		case 22:
			ds_p->scalestep = rw_scalestep = Div022(ds_p->scale2 - rw_scale);
			break;
		case 23:
			ds_p->scalestep = rw_scalestep = Div023(ds_p->scale2 - rw_scale);
			break;
		case 24:
			ds_p->scalestep = rw_scalestep = Div024(ds_p->scale2 - rw_scale);
			break;
		case 25:
			ds_p->scalestep = rw_scalestep = Div025(ds_p->scale2 - rw_scale);
			break;
		case 26:
			ds_p->scalestep = rw_scalestep = Div026(ds_p->scale2 - rw_scale);
			break;
		case 27:
			ds_p->scalestep = rw_scalestep = Div027(ds_p->scale2 - rw_scale);
			break;
		case 28:
			ds_p->scalestep = rw_scalestep = Div028(ds_p->scale2 - rw_scale);
			break;
		case 29:
			ds_p->scalestep = rw_scalestep = Div029(ds_p->scale2 - rw_scale);
			break;
		case 30:
			ds_p->scalestep = rw_scalestep = Div030(ds_p->scale2 - rw_scale);
			break;
		case 31:
			ds_p->scalestep = rw_scalestep = Div031(ds_p->scale2 - rw_scale);
			break;
		case 32:
			ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale) >> 5;
			break;
		case 33:
			ds_p->scalestep = rw_scalestep = Div033(ds_p->scale2 - rw_scale);
			break;
		case 34:
			ds_p->scalestep = rw_scalestep = Div034(ds_p->scale2 - rw_scale);
			break;
		case 35:
			ds_p->scalestep = rw_scalestep = Div035(ds_p->scale2 - rw_scale);
			break;
		case 36:
			ds_p->scalestep = rw_scalestep = Div036(ds_p->scale2 - rw_scale);
			break;
		case 37:
			ds_p->scalestep = rw_scalestep = Div037(ds_p->scale2 - rw_scale);
			break;
		case 38:
			ds_p->scalestep = rw_scalestep = Div038(ds_p->scale2 - rw_scale);
			break;
		case 39:
			ds_p->scalestep = rw_scalestep = Div039(ds_p->scale2 - rw_scale);
			break;
		case 40:
			ds_p->scalestep = rw_scalestep = Div040(ds_p->scale2 - rw_scale);
			break;
		case 41:
			ds_p->scalestep = rw_scalestep = Div041(ds_p->scale2 - rw_scale);
			break;
		case 42:
			ds_p->scalestep = rw_scalestep = Div042(ds_p->scale2 - rw_scale);
			break;
		case 43:
			ds_p->scalestep = rw_scalestep = Div043(ds_p->scale2 - rw_scale);
			break;
		case 44:
			ds_p->scalestep = rw_scalestep = Div044(ds_p->scale2 - rw_scale);
			break;
		case 45:
			ds_p->scalestep = rw_scalestep = Div045(ds_p->scale2 - rw_scale);
			break;
		case 46:
			ds_p->scalestep = rw_scalestep = Div046(ds_p->scale2 - rw_scale);
			break;
		case 47:
			ds_p->scalestep = rw_scalestep = Div047(ds_p->scale2 - rw_scale);
			break;
		case 48:
			ds_p->scalestep = rw_scalestep = Div048(ds_p->scale2 - rw_scale);
			break;
		case 49:
			ds_p->scalestep = rw_scalestep = Div049(ds_p->scale2 - rw_scale);
			break;
		case 50:
			ds_p->scalestep = rw_scalestep = Div050(ds_p->scale2 - rw_scale);
			break;
		case 51:
			ds_p->scalestep = rw_scalestep = Div051(ds_p->scale2 - rw_scale);
			break;
		case 52:
			ds_p->scalestep = rw_scalestep = Div052(ds_p->scale2 - rw_scale);
			break;
		case 53:
			ds_p->scalestep = rw_scalestep = Div053(ds_p->scale2 - rw_scale);
			break;
		case 54:
			ds_p->scalestep = rw_scalestep = Div054(ds_p->scale2 - rw_scale);
			break;
		case 55:
			ds_p->scalestep = rw_scalestep = Div055(ds_p->scale2 - rw_scale);
			break;
		case 56:
			ds_p->scalestep = rw_scalestep = Div056(ds_p->scale2 - rw_scale);
			break;
		case 57:
			ds_p->scalestep = rw_scalestep = Div057(ds_p->scale2 - rw_scale);
			break;
		case 58:
			ds_p->scalestep = rw_scalestep = Div058(ds_p->scale2 - rw_scale);
			break;
		case 59:
			ds_p->scalestep = rw_scalestep = Div059(ds_p->scale2 - rw_scale);
			break;
		case 60:
			ds_p->scalestep = rw_scalestep = Div060(ds_p->scale2 - rw_scale);
			break;
		case 61:
			ds_p->scalestep = rw_scalestep = Div061(ds_p->scale2 - rw_scale);
			break;
		case 62:
			ds_p->scalestep = rw_scalestep = Div062(ds_p->scale2 - rw_scale);
			break;
		case 63:
			ds_p->scalestep = rw_scalestep = Div063(ds_p->scale2 - rw_scale);
			break;
		case 64:
			ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale) >> 6;
			break;
		case 65:
			ds_p->scalestep = rw_scalestep = Div065(ds_p->scale2 - rw_scale);
			break;
		case 66:
			ds_p->scalestep = rw_scalestep = Div066(ds_p->scale2 - rw_scale);
			break;
		case 67:
			ds_p->scalestep = rw_scalestep = Div067(ds_p->scale2 - rw_scale);
			break;
		case 68:
			ds_p->scalestep = rw_scalestep = Div068(ds_p->scale2 - rw_scale);
			break;
		case 69:
			ds_p->scalestep = rw_scalestep = Div069(ds_p->scale2 - rw_scale);
			break;
		case 70:
			ds_p->scalestep = rw_scalestep = Div070(ds_p->scale2 - rw_scale);
			break;
		case 71:
			ds_p->scalestep = rw_scalestep = Div071(ds_p->scale2 - rw_scale);
			break;
		case 72:
			ds_p->scalestep = rw_scalestep = Div072(ds_p->scale2 - rw_scale);
			break;
		case 73:
			ds_p->scalestep = rw_scalestep = Div073(ds_p->scale2 - rw_scale);
			break;
		case 74:
			ds_p->scalestep = rw_scalestep = Div074(ds_p->scale2 - rw_scale);
			break;
		case 75:
			ds_p->scalestep = rw_scalestep = Div075(ds_p->scale2 - rw_scale);
			break;
		case 76:
			ds_p->scalestep = rw_scalestep = Div076(ds_p->scale2 - rw_scale);
			break;
		case 77:
			ds_p->scalestep = rw_scalestep = Div077(ds_p->scale2 - rw_scale);
			break;
		case 78:
			ds_p->scalestep = rw_scalestep = Div078(ds_p->scale2 - rw_scale);
			break;
		case 79:
			ds_p->scalestep = rw_scalestep = Div079(ds_p->scale2 - rw_scale);
			break;
		case 80:
			ds_p->scalestep = rw_scalestep = Div080(ds_p->scale2 - rw_scale);
			break;
		case 81:
			ds_p->scalestep = rw_scalestep = Div081(ds_p->scale2 - rw_scale);
			break;
		case 82:
			ds_p->scalestep = rw_scalestep = Div082(ds_p->scale2 - rw_scale);
			break;
		case 83:
			ds_p->scalestep = rw_scalestep = Div083(ds_p->scale2 - rw_scale);
			break;
		case 84:
			ds_p->scalestep = rw_scalestep = Div084(ds_p->scale2 - rw_scale);
			break;
		case 85:
			ds_p->scalestep = rw_scalestep = Div085(ds_p->scale2 - rw_scale);
			break;
		case 86:
			ds_p->scalestep = rw_scalestep = Div086(ds_p->scale2 - rw_scale);
			break;
		case 87:
			ds_p->scalestep = rw_scalestep = Div087(ds_p->scale2 - rw_scale);
			break;
		case 88:
			ds_p->scalestep = rw_scalestep = Div088(ds_p->scale2 - rw_scale);
			break;
		case 89:
			ds_p->scalestep = rw_scalestep = Div089(ds_p->scale2 - rw_scale);
			break;
		case 90:
			ds_p->scalestep = rw_scalestep = Div090(ds_p->scale2 - rw_scale);
			break;
		case 91:
			ds_p->scalestep = rw_scalestep = Div091(ds_p->scale2 - rw_scale);
			break;
		case 92:
			ds_p->scalestep = rw_scalestep = Div092(ds_p->scale2 - rw_scale);
			break;
		case 93:
			ds_p->scalestep = rw_scalestep = Div093(ds_p->scale2 - rw_scale);
			break;
		case 94:
			ds_p->scalestep = rw_scalestep = Div094(ds_p->scale2 - rw_scale);
			break;
		case 95:
			ds_p->scalestep = rw_scalestep = Div095(ds_p->scale2 - rw_scale);
			break;
		case 96:
			ds_p->scalestep = rw_scalestep = Div096(ds_p->scale2 - rw_scale);
			break;
		case 97:
			ds_p->scalestep = rw_scalestep = Div097(ds_p->scale2 - rw_scale);
			break;
		case 98:
			ds_p->scalestep = rw_scalestep = Div098(ds_p->scale2 - rw_scale);
			break;
		case 99:
			ds_p->scalestep = rw_scalestep = Div099(ds_p->scale2 - rw_scale);
			break;
		case 100:
			ds_p->scalestep = rw_scalestep = Div100(ds_p->scale2 - rw_scale);
			break;
		case 101:
			ds_p->scalestep = rw_scalestep = Div101(ds_p->scale2 - rw_scale);
			break;
		case 102:
			ds_p->scalestep = rw_scalestep = Div102(ds_p->scale2 - rw_scale);
			break;
		case 103:
			ds_p->scalestep = rw_scalestep = Div103(ds_p->scale2 - rw_scale);
			break;
		case 104:
			ds_p->scalestep = rw_scalestep = Div104(ds_p->scale2 - rw_scale);
			break;
		case 105:
			ds_p->scalestep = rw_scalestep = Div105(ds_p->scale2 - rw_scale);
			break;
		case 106:
			ds_p->scalestep = rw_scalestep = Div106(ds_p->scale2 - rw_scale);
			break;
		case 107:
			ds_p->scalestep = rw_scalestep = Div107(ds_p->scale2 - rw_scale);
			break;
		case 108:
			ds_p->scalestep = rw_scalestep = Div108(ds_p->scale2 - rw_scale);
			break;
		case 109:
			ds_p->scalestep = rw_scalestep = Div109(ds_p->scale2 - rw_scale);
			break;
		case 110:
			ds_p->scalestep = rw_scalestep = Div110(ds_p->scale2 - rw_scale);
			break;
		case 111:
			ds_p->scalestep = rw_scalestep = Div111(ds_p->scale2 - rw_scale);
			break;
		case 112:
			ds_p->scalestep = rw_scalestep = Div112(ds_p->scale2 - rw_scale);
			break;
		case 113:
			ds_p->scalestep = rw_scalestep = Div113(ds_p->scale2 - rw_scale);
			break;
		case 114:
			ds_p->scalestep = rw_scalestep = Div114(ds_p->scale2 - rw_scale);
			break;
		case 115:
			ds_p->scalestep = rw_scalestep = Div115(ds_p->scale2 - rw_scale);
			break;
		case 116:
			ds_p->scalestep = rw_scalestep = Div116(ds_p->scale2 - rw_scale);
			break;
		case 117:
			ds_p->scalestep = rw_scalestep = Div117(ds_p->scale2 - rw_scale);
			break;
		case 118:
			ds_p->scalestep = rw_scalestep = Div118(ds_p->scale2 - rw_scale);
			break;
		case 119:
			ds_p->scalestep = rw_scalestep = Div119(ds_p->scale2 - rw_scale);
			break;
		case 120:
			ds_p->scalestep = rw_scalestep = Div120(ds_p->scale2 - rw_scale);
			break;
		case 121:
			ds_p->scalestep = rw_scalestep = Div121(ds_p->scale2 - rw_scale);
			break;
		case 122:
			ds_p->scalestep = rw_scalestep = Div122(ds_p->scale2 - rw_scale);
			break;
		case 123:
			ds_p->scalestep = rw_scalestep = Div123(ds_p->scale2 - rw_scale);
			break;
		case 124:
			ds_p->scalestep = rw_scalestep = Div124(ds_p->scale2 - rw_scale);
			break;
		case 125:
			ds_p->scalestep = rw_scalestep = Div125(ds_p->scale2 - rw_scale);
			break;
		case 126:
			ds_p->scalestep = rw_scalestep = Div126(ds_p->scale2 - rw_scale);
			break;
		case 127:
			ds_p->scalestep = rw_scalestep = Div127(ds_p->scale2 - rw_scale);
			break;
		case 128:
			ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale) >> 7;
			break;
		case 129:
			ds_p->scalestep = rw_scalestep = Div129(ds_p->scale2 - rw_scale);
			break;
		case 130:
			ds_p->scalestep = rw_scalestep = Div130(ds_p->scale2 - rw_scale);
			break;
		case 131:
			ds_p->scalestep = rw_scalestep = Div131(ds_p->scale2 - rw_scale);
			break;
		case 132:
			ds_p->scalestep = rw_scalestep = Div132(ds_p->scale2 - rw_scale);
			break;
		case 133:
			ds_p->scalestep = rw_scalestep = Div133(ds_p->scale2 - rw_scale);
			break;
		case 134:
			ds_p->scalestep = rw_scalestep = Div134(ds_p->scale2 - rw_scale);
			break;
		case 135:
			ds_p->scalestep = rw_scalestep = Div135(ds_p->scale2 - rw_scale);
			break;
		case 136:
			ds_p->scalestep = rw_scalestep = Div136(ds_p->scale2 - rw_scale);
			break;
		case 137:
			ds_p->scalestep = rw_scalestep = Div137(ds_p->scale2 - rw_scale);
			break;
		case 138:
			ds_p->scalestep = rw_scalestep = Div138(ds_p->scale2 - rw_scale);
			break;
		case 139:
			ds_p->scalestep = rw_scalestep = Div139(ds_p->scale2 - rw_scale);
			break;
		case 140:
			ds_p->scalestep = rw_scalestep = Div140(ds_p->scale2 - rw_scale);
			break;
		case 141:
			ds_p->scalestep = rw_scalestep = Div141(ds_p->scale2 - rw_scale);
			break;
		case 142:
			ds_p->scalestep = rw_scalestep = Div142(ds_p->scale2 - rw_scale);
			break;
		case 143:
			ds_p->scalestep = rw_scalestep = Div143(ds_p->scale2 - rw_scale);
			break;
		case 144:
			ds_p->scalestep = rw_scalestep = Div144(ds_p->scale2 - rw_scale);
			break;
		case 145:
			ds_p->scalestep = rw_scalestep = Div145(ds_p->scale2 - rw_scale);
			break;
		case 146:
			ds_p->scalestep = rw_scalestep = Div146(ds_p->scale2 - rw_scale);
			break;
		case 147:
			ds_p->scalestep = rw_scalestep = Div147(ds_p->scale2 - rw_scale);
			break;
		case 148:
			ds_p->scalestep = rw_scalestep = Div148(ds_p->scale2 - rw_scale);
			break;
		case 149:
			ds_p->scalestep = rw_scalestep = Div149(ds_p->scale2 - rw_scale);
			break;
		case 150:
			ds_p->scalestep = rw_scalestep = Div150(ds_p->scale2 - rw_scale);
			break;
		case 151:
			ds_p->scalestep = rw_scalestep = Div151(ds_p->scale2 - rw_scale);
			break;
		case 152:
			ds_p->scalestep = rw_scalestep = Div152(ds_p->scale2 - rw_scale);
			break;
		case 153:
			ds_p->scalestep = rw_scalestep = Div153(ds_p->scale2 - rw_scale);
			break;
		case 154:
			ds_p->scalestep = rw_scalestep = Div154(ds_p->scale2 - rw_scale);
			break;
		case 155:
			ds_p->scalestep = rw_scalestep = Div155(ds_p->scale2 - rw_scale);
			break;
		case 156:
			ds_p->scalestep = rw_scalestep = Div156(ds_p->scale2 - rw_scale);
			break;
		case 157:
			ds_p->scalestep = rw_scalestep = Div157(ds_p->scale2 - rw_scale);
			break;
		case 158:
			ds_p->scalestep = rw_scalestep = Div158(ds_p->scale2 - rw_scale);
			break;
		case 159:
			ds_p->scalestep = rw_scalestep = Div159(ds_p->scale2 - rw_scale);
			break;
		case 160:
			ds_p->scalestep = rw_scalestep = Div160(ds_p->scale2 - rw_scale);
			break;
		case 161:
			ds_p->scalestep = rw_scalestep = Div161(ds_p->scale2 - rw_scale);
			break;
		case 162:
			ds_p->scalestep = rw_scalestep = Div162(ds_p->scale2 - rw_scale);
			break;
		case 163:
			ds_p->scalestep = rw_scalestep = Div163(ds_p->scale2 - rw_scale);
			break;
		case 164:
			ds_p->scalestep = rw_scalestep = Div164(ds_p->scale2 - rw_scale);
			break;
		case 165:
			ds_p->scalestep = rw_scalestep = Div165(ds_p->scale2 - rw_scale);
			break;
		case 166:
			ds_p->scalestep = rw_scalestep = Div166(ds_p->scale2 - rw_scale);
			break;
		case 167:
			ds_p->scalestep = rw_scalestep = Div167(ds_p->scale2 - rw_scale);
			break;
		case 168:
			ds_p->scalestep = rw_scalestep = Div168(ds_p->scale2 - rw_scale);
			break;
		case 169:
			ds_p->scalestep = rw_scalestep = Div169(ds_p->scale2 - rw_scale);
			break;
		case 170:
			ds_p->scalestep = rw_scalestep = Div170(ds_p->scale2 - rw_scale);
			break;
		case 171:
			ds_p->scalestep = rw_scalestep = Div171(ds_p->scale2 - rw_scale);
			break;
		case 172:
			ds_p->scalestep = rw_scalestep = Div172(ds_p->scale2 - rw_scale);
			break;
		case 173:
			ds_p->scalestep = rw_scalestep = Div173(ds_p->scale2 - rw_scale);
			break;
		case 174:
			ds_p->scalestep = rw_scalestep = Div174(ds_p->scale2 - rw_scale);
			break;
		case 175:
			ds_p->scalestep = rw_scalestep = Div175(ds_p->scale2 - rw_scale);
			break;
		case 176:
			ds_p->scalestep = rw_scalestep = Div176(ds_p->scale2 - rw_scale);
			break;
		case 177:
			ds_p->scalestep = rw_scalestep = Div177(ds_p->scale2 - rw_scale);
			break;
		case 178:
			ds_p->scalestep = rw_scalestep = Div178(ds_p->scale2 - rw_scale);
			break;
		case 179:
			ds_p->scalestep = rw_scalestep = Div179(ds_p->scale2 - rw_scale);
			break;
		case 180:
			ds_p->scalestep = rw_scalestep = Div180(ds_p->scale2 - rw_scale);
			break;
		case 181:
			ds_p->scalestep = rw_scalestep = Div181(ds_p->scale2 - rw_scale);
			break;
		case 182:
			ds_p->scalestep = rw_scalestep = Div182(ds_p->scale2 - rw_scale);
			break;
		case 183:
			ds_p->scalestep = rw_scalestep = Div183(ds_p->scale2 - rw_scale);
			break;
		case 184:
			ds_p->scalestep = rw_scalestep = Div184(ds_p->scale2 - rw_scale);
			break;
		case 185:
			ds_p->scalestep = rw_scalestep = Div185(ds_p->scale2 - rw_scale);
			break;
		case 186:
			ds_p->scalestep = rw_scalestep = Div186(ds_p->scale2 - rw_scale);
			break;
		case 187:
			ds_p->scalestep = rw_scalestep = Div187(ds_p->scale2 - rw_scale);
			break;
		case 188:
			ds_p->scalestep = rw_scalestep = Div188(ds_p->scale2 - rw_scale);
			break;
		case 189:
			ds_p->scalestep = rw_scalestep = Div189(ds_p->scale2 - rw_scale);
			break;
		case 190:
			ds_p->scalestep = rw_scalestep = Div190(ds_p->scale2 - rw_scale);
			break;
		case 191:
			ds_p->scalestep = rw_scalestep = Div191(ds_p->scale2 - rw_scale);
			break;
		case 192:
			ds_p->scalestep = rw_scalestep = Div192(ds_p->scale2 - rw_scale);
			break;
		case 193:
			ds_p->scalestep = rw_scalestep = Div193(ds_p->scale2 - rw_scale);
			break;
		case 194:
			ds_p->scalestep = rw_scalestep = Div194(ds_p->scale2 - rw_scale);
			break;
		case 195:
			ds_p->scalestep = rw_scalestep = Div195(ds_p->scale2 - rw_scale);
			break;
		case 196:
			ds_p->scalestep = rw_scalestep = Div196(ds_p->scale2 - rw_scale);
			break;
		case 197:
			ds_p->scalestep = rw_scalestep = Div197(ds_p->scale2 - rw_scale);
			break;
		case 198:
			ds_p->scalestep = rw_scalestep = Div198(ds_p->scale2 - rw_scale);
			break;
		case 199:
			ds_p->scalestep = rw_scalestep = Div199(ds_p->scale2 - rw_scale);
			break;
		case 200:
			ds_p->scalestep = rw_scalestep = Div200(ds_p->scale2 - rw_scale);
			break;
		case 201:
			ds_p->scalestep = rw_scalestep = Div201(ds_p->scale2 - rw_scale);
			break;
		case 202:
			ds_p->scalestep = rw_scalestep = Div202(ds_p->scale2 - rw_scale);
			break;
		case 203:
			ds_p->scalestep = rw_scalestep = Div203(ds_p->scale2 - rw_scale);
			break;
		case 204:
			ds_p->scalestep = rw_scalestep = Div204(ds_p->scale2 - rw_scale);
			break;
		case 205:
			ds_p->scalestep = rw_scalestep = Div205(ds_p->scale2 - rw_scale);
			break;
		case 206:
			ds_p->scalestep = rw_scalestep = Div206(ds_p->scale2 - rw_scale);
			break;
		case 207:
			ds_p->scalestep = rw_scalestep = Div207(ds_p->scale2 - rw_scale);
			break;
		case 208:
			ds_p->scalestep = rw_scalestep = Div208(ds_p->scale2 - rw_scale);
			break;
		case 209:
			ds_p->scalestep = rw_scalestep = Div209(ds_p->scale2 - rw_scale);
			break;
		case 210:
			ds_p->scalestep = rw_scalestep = Div210(ds_p->scale2 - rw_scale);
			break;
		case 211:
			ds_p->scalestep = rw_scalestep = Div211(ds_p->scale2 - rw_scale);
			break;
		case 212:
			ds_p->scalestep = rw_scalestep = Div212(ds_p->scale2 - rw_scale);
			break;
		case 213:
			ds_p->scalestep = rw_scalestep = Div213(ds_p->scale2 - rw_scale);
			break;
		case 214:
			ds_p->scalestep = rw_scalestep = Div214(ds_p->scale2 - rw_scale);
			break;
		case 215:
			ds_p->scalestep = rw_scalestep = Div215(ds_p->scale2 - rw_scale);
			break;
		case 216:
			ds_p->scalestep = rw_scalestep = Div216(ds_p->scale2 - rw_scale);
			break;
		case 217:
			ds_p->scalestep = rw_scalestep = Div217(ds_p->scale2 - rw_scale);
			break;
		case 218:
			ds_p->scalestep = rw_scalestep = Div218(ds_p->scale2 - rw_scale);
			break;
		case 219:
			ds_p->scalestep = rw_scalestep = Div219(ds_p->scale2 - rw_scale);
			break;
		case 220:
			ds_p->scalestep = rw_scalestep = Div220(ds_p->scale2 - rw_scale);
			break;
		case 221:
			ds_p->scalestep = rw_scalestep = Div221(ds_p->scale2 - rw_scale);
			break;
		case 222:
			ds_p->scalestep = rw_scalestep = Div222(ds_p->scale2 - rw_scale);
			break;
		case 223:
			ds_p->scalestep = rw_scalestep = Div223(ds_p->scale2 - rw_scale);
			break;
		case 224:
			ds_p->scalestep = rw_scalestep = Div224(ds_p->scale2 - rw_scale);
			break;
		case 225:
			ds_p->scalestep = rw_scalestep = Div225(ds_p->scale2 - rw_scale);
			break;
		case 226:
			ds_p->scalestep = rw_scalestep = Div226(ds_p->scale2 - rw_scale);
			break;
		case 227:
			ds_p->scalestep = rw_scalestep = Div227(ds_p->scale2 - rw_scale);
			break;
		case 228:
			ds_p->scalestep = rw_scalestep = Div228(ds_p->scale2 - rw_scale);
			break;
		case 229:
			ds_p->scalestep = rw_scalestep = Div229(ds_p->scale2 - rw_scale);
			break;
		case 230:
			ds_p->scalestep = rw_scalestep = Div230(ds_p->scale2 - rw_scale);
			break;
		case 231:
			ds_p->scalestep = rw_scalestep = Div231(ds_p->scale2 - rw_scale);
			break;
		case 232:
			ds_p->scalestep = rw_scalestep = Div232(ds_p->scale2 - rw_scale);
			break;
		case 233:
			ds_p->scalestep = rw_scalestep = Div233(ds_p->scale2 - rw_scale);
			break;
		case 234:
			ds_p->scalestep = rw_scalestep = Div234(ds_p->scale2 - rw_scale);
			break;
		case 235:
			ds_p->scalestep = rw_scalestep = Div235(ds_p->scale2 - rw_scale);
			break;
		case 236:
			ds_p->scalestep = rw_scalestep = Div236(ds_p->scale2 - rw_scale);
			break;
		case 237:
			ds_p->scalestep = rw_scalestep = Div237(ds_p->scale2 - rw_scale);
			break;
		case 238:
			ds_p->scalestep = rw_scalestep = Div238(ds_p->scale2 - rw_scale);
			break;
		case 239:
			ds_p->scalestep = rw_scalestep = Div239(ds_p->scale2 - rw_scale);
			break;
		case 240:
			ds_p->scalestep = rw_scalestep = Div240(ds_p->scale2 - rw_scale);
			break;
		case 241:
			ds_p->scalestep = rw_scalestep = Div241(ds_p->scale2 - rw_scale);
			break;
		case 242:
			ds_p->scalestep = rw_scalestep = Div242(ds_p->scale2 - rw_scale);
			break;
		case 243:
			ds_p->scalestep = rw_scalestep = Div243(ds_p->scale2 - rw_scale);
			break;
		case 244:
			ds_p->scalestep = rw_scalestep = Div244(ds_p->scale2 - rw_scale);
			break;
		case 245:
			ds_p->scalestep = rw_scalestep = Div245(ds_p->scale2 - rw_scale);
			break;
		case 246:
			ds_p->scalestep = rw_scalestep = Div246(ds_p->scale2 - rw_scale);
			break;
		case 247:
			ds_p->scalestep = rw_scalestep = Div247(ds_p->scale2 - rw_scale);
			break;
		case 248:
			ds_p->scalestep = rw_scalestep = Div248(ds_p->scale2 - rw_scale);
			break;
		case 249:
			ds_p->scalestep = rw_scalestep = Div249(ds_p->scale2 - rw_scale);
			break;
		case 250:
			ds_p->scalestep = rw_scalestep = Div250(ds_p->scale2 - rw_scale);
			break;
		case 251:
			ds_p->scalestep = rw_scalestep = Div251(ds_p->scale2 - rw_scale);
			break;
		case 252:
			ds_p->scalestep = rw_scalestep = Div252(ds_p->scale2 - rw_scale);
			break;
		case 253:
			ds_p->scalestep = rw_scalestep = Div253(ds_p->scale2 - rw_scale);
			break;
		case 254:
			ds_p->scalestep = rw_scalestep = Div254(ds_p->scale2 - rw_scale);
			break;
		case 255:
			ds_p->scalestep = rw_scalestep = Div255(ds_p->scale2 - rw_scale);
			break;
		case 256:
			ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale) >> 8;
			break;
		case 257:
			ds_p->scalestep = rw_scalestep = Div257(ds_p->scale2 - rw_scale);
			break;
		case 258:
			ds_p->scalestep = rw_scalestep = Div258(ds_p->scale2 - rw_scale);
			break;
		case 259:
			ds_p->scalestep = rw_scalestep = Div259(ds_p->scale2 - rw_scale);
			break;
		case 260:
			ds_p->scalestep = rw_scalestep = Div260(ds_p->scale2 - rw_scale);
			break;
		case 261:
			ds_p->scalestep = rw_scalestep = Div261(ds_p->scale2 - rw_scale);
			break;
		case 262:
			ds_p->scalestep = rw_scalestep = Div262(ds_p->scale2 - rw_scale);
			break;
		case 263:
			ds_p->scalestep = rw_scalestep = Div263(ds_p->scale2 - rw_scale);
			break;
		case 264:
			ds_p->scalestep = rw_scalestep = Div264(ds_p->scale2 - rw_scale);
			break;
		case 265:
			ds_p->scalestep = rw_scalestep = Div265(ds_p->scale2 - rw_scale);
			break;
		case 266:
			ds_p->scalestep = rw_scalestep = Div266(ds_p->scale2 - rw_scale);
			break;
		case 267:
			ds_p->scalestep = rw_scalestep = Div267(ds_p->scale2 - rw_scale);
			break;
		case 268:
			ds_p->scalestep = rw_scalestep = Div268(ds_p->scale2 - rw_scale);
			break;
		case 269:
			ds_p->scalestep = rw_scalestep = Div269(ds_p->scale2 - rw_scale);
			break;
		case 270:
			ds_p->scalestep = rw_scalestep = Div270(ds_p->scale2 - rw_scale);
			break;
		case 271:
			ds_p->scalestep = rw_scalestep = Div271(ds_p->scale2 - rw_scale);
			break;
		case 272:
			ds_p->scalestep = rw_scalestep = Div272(ds_p->scale2 - rw_scale);
			break;
		case 273:
			ds_p->scalestep = rw_scalestep = Div273(ds_p->scale2 - rw_scale);
			break;
		case 274:
			ds_p->scalestep = rw_scalestep = Div274(ds_p->scale2 - rw_scale);
			break;
		case 275:
			ds_p->scalestep = rw_scalestep = Div275(ds_p->scale2 - rw_scale);
			break;
		case 276:
			ds_p->scalestep = rw_scalestep = Div276(ds_p->scale2 - rw_scale);
			break;
		case 277:
			ds_p->scalestep = rw_scalestep = Div277(ds_p->scale2 - rw_scale);
			break;
		case 278:
			ds_p->scalestep = rw_scalestep = Div278(ds_p->scale2 - rw_scale);
			break;
		case 279:
			ds_p->scalestep = rw_scalestep = Div279(ds_p->scale2 - rw_scale);
			break;
		case 280:
			ds_p->scalestep = rw_scalestep = Div280(ds_p->scale2 - rw_scale);
			break;
		case 281:
			ds_p->scalestep = rw_scalestep = Div281(ds_p->scale2 - rw_scale);
			break;
		case 282:
			ds_p->scalestep = rw_scalestep = Div282(ds_p->scale2 - rw_scale);
			break;
		case 283:
			ds_p->scalestep = rw_scalestep = Div283(ds_p->scale2 - rw_scale);
			break;
		case 284:
			ds_p->scalestep = rw_scalestep = Div284(ds_p->scale2 - rw_scale);
			break;
		case 285:
			ds_p->scalestep = rw_scalestep = Div285(ds_p->scale2 - rw_scale);
			break;
		case 286:
			ds_p->scalestep = rw_scalestep = Div286(ds_p->scale2 - rw_scale);
			break;
		case 287:
			ds_p->scalestep = rw_scalestep = Div287(ds_p->scale2 - rw_scale);
			break;
		case 288:
			ds_p->scalestep = rw_scalestep = Div288(ds_p->scale2 - rw_scale);
			break;
		case 289:
			ds_p->scalestep = rw_scalestep = Div289(ds_p->scale2 - rw_scale);
			break;
		case 290:
			ds_p->scalestep = rw_scalestep = Div290(ds_p->scale2 - rw_scale);
			break;
		case 291:
			ds_p->scalestep = rw_scalestep = Div291(ds_p->scale2 - rw_scale);
			break;
		case 292:
			ds_p->scalestep = rw_scalestep = Div292(ds_p->scale2 - rw_scale);
			break;
		case 293:
			ds_p->scalestep = rw_scalestep = Div293(ds_p->scale2 - rw_scale);
			break;
		case 294:
			ds_p->scalestep = rw_scalestep = Div294(ds_p->scale2 - rw_scale);
			break;
		case 295:
			ds_p->scalestep = rw_scalestep = Div295(ds_p->scale2 - rw_scale);
			break;
		case 296:
			ds_p->scalestep = rw_scalestep = Div296(ds_p->scale2 - rw_scale);
			break;
		case 297:
			ds_p->scalestep = rw_scalestep = Div297(ds_p->scale2 - rw_scale);
			break;
		case 298:
			ds_p->scalestep = rw_scalestep = Div298(ds_p->scale2 - rw_scale);
			break;
		case 299:
			ds_p->scalestep = rw_scalestep = Div299(ds_p->scale2 - rw_scale);
			break;
		case 300:
			ds_p->scalestep = rw_scalestep = Div300(ds_p->scale2 - rw_scale);
			break;
		case 301:
			ds_p->scalestep = rw_scalestep = Div301(ds_p->scale2 - rw_scale);
			break;
		case 302:
			ds_p->scalestep = rw_scalestep = Div302(ds_p->scale2 - rw_scale);
			break;
		case 303:
			ds_p->scalestep = rw_scalestep = Div303(ds_p->scale2 - rw_scale);
			break;
		case 304:
			ds_p->scalestep = rw_scalestep = Div304(ds_p->scale2 - rw_scale);
			break;
		case 305:
			ds_p->scalestep = rw_scalestep = Div305(ds_p->scale2 - rw_scale);
			break;
		case 306:
			ds_p->scalestep = rw_scalestep = Div306(ds_p->scale2 - rw_scale);
			break;
		case 307:
			ds_p->scalestep = rw_scalestep = Div307(ds_p->scale2 - rw_scale);
			break;
		case 308:
			ds_p->scalestep = rw_scalestep = Div308(ds_p->scale2 - rw_scale);
			break;
		case 309:
			ds_p->scalestep = rw_scalestep = Div309(ds_p->scale2 - rw_scale);
			break;
		case 310:
			ds_p->scalestep = rw_scalestep = Div310(ds_p->scale2 - rw_scale);
			break;
		case 311:
			ds_p->scalestep = rw_scalestep = Div311(ds_p->scale2 - rw_scale);
			break;
		case 312:
			ds_p->scalestep = rw_scalestep = Div312(ds_p->scale2 - rw_scale);
			break;
		case 313:
			ds_p->scalestep = rw_scalestep = Div313(ds_p->scale2 - rw_scale);
			break;
		case 314:
			ds_p->scalestep = rw_scalestep = Div314(ds_p->scale2 - rw_scale);
			break;
		case 315:
			ds_p->scalestep = rw_scalestep = Div315(ds_p->scale2 - rw_scale);
			break;
		case 316:
			ds_p->scalestep = rw_scalestep = Div316(ds_p->scale2 - rw_scale);
			break;
		case 317:
			ds_p->scalestep = rw_scalestep = Div317(ds_p->scale2 - rw_scale);
			break;
		case 318:
			ds_p->scalestep = rw_scalestep = Div318(ds_p->scale2 - rw_scale);
			break;
		case 319:
			ds_p->scalestep = rw_scalestep = Div319(ds_p->scale2 - rw_scale);
			break;

		default:
		ds_p->scalestep = rw_scalestep = (ds_p->scale2 - rw_scale) / (stop - start);
			break;
		};
	}
	else
	{
		ds_p->scale2 = ds_p->scale1;
	}

	// calculate texture boundaries
	//  and decide if floor / ceiling marks are needed
	worldtop = frontsector->ceilingheight - viewz;
	worldbottom = frontsector->floorheight - viewz;

	midtexture = toptexture = bottomtexture = maskedtexture = 0;
	ds_p->maskedtexturecol = NULL;

	if (!backsector)
	{
		// single sided line
		midtexture = texturetranslation[sidedef->midtexture];
		// a single sided line is terminal, so it must mark ends
		markfloor = markceiling = 1;
		if (linedef->flags & ML_DONTPEGBOTTOM)
		{
			vtop = frontsector->floorheight +
				   textureheight[sidedef->midtexture];
			// bottom of texture at bottom
			rw_midtexturemid = vtop - viewz;
		}
		else
		{
			// top of texture at top
			rw_midtexturemid = worldtop;
		}
		rw_midtexturemid += sidedef->rowoffset;

		ds_p->silhouette = SIL_BOTH;
		ds_p->sprtopclip = screenheightarray;
		ds_p->sprbottomclip = negonearray;
		ds_p->bsilheight = MAXINT;
		ds_p->tsilheight = MININT;
	}
	else
	{
		// two sided line
		ds_p->sprtopclip = ds_p->sprbottomclip = NULL;
		ds_p->silhouette = SIL_NONE;

		if (frontsector->floorheight > backsector->floorheight)
		{
			ds_p->silhouette = SIL_BOTTOM;
			ds_p->bsilheight = frontsector->floorheight;
		}
		else if (backsector->floorheight > viewz)
		{
			ds_p->silhouette = SIL_BOTTOM;
			ds_p->bsilheight = MAXINT;
		}

		if (frontsector->ceilingheight < backsector->ceilingheight)
		{
			ds_p->silhouette |= SIL_TOP;
			ds_p->tsilheight = frontsector->ceilingheight;
		}
		else if (backsector->ceilingheight < viewz)
		{
			ds_p->silhouette |= SIL_TOP;
			ds_p->tsilheight = MININT;
		}

		if (backsector->ceilingheight <= frontsector->floorheight)
		{
			ds_p->sprbottomclip = negonearray;
			ds_p->bsilheight = MAXINT;
			ds_p->silhouette |= SIL_BOTTOM;
		}

		if (backsector->floorheight >= frontsector->ceilingheight)
		{
			ds_p->sprtopclip = screenheightarray;
			ds_p->tsilheight = MININT;
			ds_p->silhouette |= SIL_TOP;
		}

		worldhigh = backsector->ceilingheight - viewz;
		worldlow = backsector->floorheight - viewz;

		// hack to allow height changes in outdoor areas
		if (frontsector->ceilingpic == skyflatnum && backsector->ceilingpic == skyflatnum)
		{
			worldtop = worldhigh;
		}

		markfloor = worldlow != worldbottom || backsector->floorpic != frontsector->floorpic || backsector->lightlevel != frontsector->lightlevel;
		markceiling = worldhigh != worldtop || backsector->ceilingpic != frontsector->ceilingpic || backsector->lightlevel != frontsector->lightlevel;

		if (backsector->ceilingheight <= frontsector->floorheight || backsector->floorheight >= frontsector->ceilingheight)
		{
			// closed door
			markceiling = markfloor = 1;
		}

		if (worldhigh < worldtop)
		{
			// top texture
			toptexture = texturetranslation[sidedef->toptexture];
			if (linedef->flags & ML_DONTPEGTOP)
			{
				// top of texture at top
				rw_toptexturemid = worldtop;
			}
			else
			{
				vtop = backsector->ceilingheight + textureheight[sidedef->toptexture];

				// bottom of texture
				rw_toptexturemid = vtop - viewz;
			}
		}
		if (worldlow > worldbottom)
		{
			// bottom texture
			bottomtexture = texturetranslation[sidedef->bottomtexture];

			if (linedef->flags & ML_DONTPEGBOTTOM)
			{
				// bottom of texture at bottom
				// top of texture at top
				rw_bottomtexturemid = worldtop;
			}
			else // top of texture at top
				rw_bottomtexturemid = worldlow;
		}
		rw_toptexturemid += sidedef->rowoffset;
		rw_bottomtexturemid += sidedef->rowoffset;

		// allocate space for masked texture tables
		if (sidedef->midtexture)
		{
			// masked midtexture
			maskedtexture = 1;
			ds_p->maskedtexturecol = maskedtexturecol = lastopening - rw_x;
			lastopening += rw_stopx - rw_x;
		}
	}

	// calculate rw_offset (only needed for textured lines)
	segtextured = midtexture | toptexture | bottomtexture | maskedtexture;

	if (segtextured)
	{
		offsetangle = rw_normalangle - rw_angle1;

		if (offsetangle > ANG180)
			offsetangle = -offsetangle;

		rw_offset = FixedMul(hyp, finesine[offsetangle >> ANGLETOFINESHIFT]);

		if (rw_normalangle - rw_angle1 < ANG180)
			rw_offset = -rw_offset;

		rw_offset += sidedef->textureoffset + curline->offset;
		rw_centerangle = ANG90 + viewangle - rw_normalangle;

		// calculate light table
		//  use different light tables
		//  for horizontal / vertical / diagonal
		// OPTIMIZE: get rid of LIGHTSEGSHIFT globally
		if (!fixedcolormap)
		{
			lightnum = (frontsector->lightlevel >> LIGHTSEGSHIFT) + extralight;

			if (curline->v1->y == curline->v2->y)
				lightnum--;
			else lightnum += curline->v1->x == curline->v2->x;

			// Lightnum between 0 and 15
			if (lightnum < 0)
				walllights = scalelight[0];
			else if (lightnum > LIGHTLEVELS - 1)
				walllights = scalelight[LIGHTLEVELS - 1];
			else
				walllights = scalelight[lightnum];
		}
	}

	// if a floor / ceiling plane is on the wrong side
	//  of the view plane, it is definitely invisible
	//  and doesn't need to be marked.

	if (frontsector->floorheight >= viewz)
	{
		// above view plane
		markfloor = 0;
	}

	if (frontsector->ceilingheight <= viewz && frontsector->ceilingpic != skyflatnum)
	{
		// below view plane
		markceiling = 0;
	}

	// calculate incremental stepping values for texture edges
	worldtop >>= 4;
	worldbottom >>= 4;

	topstep = -FixedMul(rw_scalestep, worldtop);
	topfrac = centeryfracshifted - FixedMul(worldtop, rw_scale);

	bottomstep = -FixedMul(rw_scalestep, worldbottom);
	bottomfrac = centeryfracshifted - FixedMul(worldbottom, rw_scale);

	if (backsector)
	{
		worldhigh >>= 4;
		worldlow >>= 4;

		if (worldhigh < worldtop)
		{
			pixhigh = centeryfracshifted - FixedMul(worldhigh, rw_scale);
			pixhighstep = -FixedMul(rw_scalestep, worldhigh);
		}

		if (worldlow > worldbottom)
		{
			pixlow = centeryfracshifted - FixedMul(worldlow, rw_scale);
			pixlowstep = -FixedMul(rw_scalestep, worldlow);
		}
	}

	// render it
	if (markceiling)
		ceilingplane = R_CheckPlane(ceilingplane, rw_x, rw_stopx - 1);

	if (markfloor)
		floorplane = R_CheckPlane(floorplane, rw_x, rw_stopx - 1);

	R_RenderSegLoop();

	// save sprite clipping info
	if (((ds_p->silhouette & SIL_TOP) || maskedtexture) && !ds_p->sprtopclip)
	{
		CopyWords(ceilingclip + start, lastopening, rw_stopx - start);
		//memcpy(lastopening, ceilingclip + start, 2 * (rw_stopx - start));
		ds_p->sprtopclip = lastopening - start;
		lastopening += rw_stopx - start;
	}

	if (((ds_p->silhouette & SIL_BOTTOM) || maskedtexture) && !ds_p->sprbottomclip)
	{
		CopyWords(floorclip + start, lastopening, rw_stopx - start);
		//memcpy(lastopening, floorclip + start, 2 * (rw_stopx - start));
		ds_p->sprbottomclip = lastopening - start;
		lastopening += rw_stopx - start;
	}

	if (maskedtexture)
	{
		if (!(ds_p->silhouette & SIL_TOP))
		{
			ds_p->silhouette |= SIL_TOP;
			ds_p->tsilheight = MININT;
		}
		if (!(ds_p->silhouette & SIL_BOTTOM))
		{
			ds_p->silhouette |= SIL_BOTTOM;
			ds_p->bsilheight = MAXINT;
		}
	}

	ds_p++;
}
