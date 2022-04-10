//
// Copyright (C) 1993-1996 Id Software, Inc.
// Copyright (C) 1993-2008 Raven Software
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
//  Internally used data structures for virtually everything,
//   key definitions, lots of other stuff.
//

#ifndef __FASTDIV__
#define __FASTDIV__

typedef int fixed_t;

int Div003(int value);
#pragma aux Div003 = \
"mov	edx, 1431655766", \
"mov	eax, ecx", \
"imul	edx", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div005(int value);
#pragma aux Div005 = \
"mov	edx, 1717986919", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 1", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div006(int value);
#pragma aux Div006 = \
"mov	edx, 715827883", \
"mov	eax, ecx", \
"imul	edx", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div007(int value);
#pragma aux Div007 = \
"mov	edx, -1840700269", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 2", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div009(int value);
#pragma aux Div009 = \
"mov	edx, 954437177", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 1", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div010(int value);
#pragma aux Div010 = \
"mov	edx, 1717986919", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div011(int value);
#pragma aux Div011 = \
"mov	edx, 780903145", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 1", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div012(int value);
#pragma aux Div012 = \
"mov	edx, 715827883", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 1", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div013(int value);
#pragma aux Div013 = \
"mov	edx, 1321528399", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div014(int value);
#pragma aux Div014 = \
"mov	edx, -1840700269", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 3", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div015(int value);
#pragma aux Div015 = \
"mov	edx, -2004318071", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 3", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div017(int value);
#pragma aux Div017 = \
"mov	edx, 2021161081", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div018(int value);
#pragma aux Div018 = \
"mov	edx, 954437177", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div019(int value);
#pragma aux Div019 = \
"mov	edx, 1808407283", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div020(int value);
#pragma aux Div020 = \
"mov	edx, 1717986919", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div021(int value);
#pragma aux Div021 = \
"mov	edx, 818089009", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div022(int value);
#pragma aux Div022 = \
"mov	edx, 780903145", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div023(int value);
#pragma aux Div023 = \
"mov	edx, -1307163959", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 4", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div024(int value);
#pragma aux Div024 = \
"mov	edx, 715827883", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div025(int value);
#pragma aux Div025 = \
"mov	edx, 1374389535", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div026(int value);
#pragma aux Div026 = \
"mov	edx, 1321528399", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div027(int value);
#pragma aux Div027 = \
"mov	edx, 1272582903", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div028(int value);
#pragma aux Div028 = \
"mov	edx, -1840700269", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 4", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div029(int value);
#pragma aux Div029 = \
"mov	edx, -1925330167", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 4", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div030(int value);
#pragma aux Div030 = \
"mov	edx, -2004318071", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 4", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div031(int value);
#pragma aux Div031 = \
"mov	edx, -2078209981", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 4", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div033(int value);
#pragma aux Div033 = \
"mov	edx, 1041204193", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div034(int value);
#pragma aux Div034 = \
"mov	edx, 2021161081", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div035(int value);
#pragma aux Div035 = \
"mov	edx, -368140053", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div036(int value);
#pragma aux Div036 = \
"mov	edx, 954437177", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div037(int value);
#pragma aux Div037 = \
"mov	edx, -580400985", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div038(int value);
#pragma aux Div038 = \
"mov	edx, 1808407283", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div039(int value);
#pragma aux Div039 = \
"mov	edx, -770891565", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div040(int value);
#pragma aux Div040 = \
"mov	edx, 1717986919", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div041(int value);
#pragma aux Div041 = \
"mov	edx, 1676084799", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div042(int value);
#pragma aux Div042 = \
"mov	edx, 818089009", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div043(int value);
#pragma aux Div043 = \
"mov	edx, 799063683", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div044(int value);
#pragma aux Div044 = \
"mov	edx, 780903145", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div045(int value);
#pragma aux Div045 = \
"mov	edx, -1240768329", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div046(int value);
#pragma aux Div046 = \
"mov	edx, -1307163959", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div047(int value);
#pragma aux Div047 = \
"mov	edx, -1370734243", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div048(int value);
#pragma aux Div048 = \
"mov	edx, 715827883", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div049(int value);
#pragma aux Div049 = \
"mov	edx, 1402438301", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div050(int value);
#pragma aux Div050 = \
"mov	edx, 1374389535", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div051(int value);
#pragma aux Div051 = \
"mov	edx, -1600085855", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div052(int value);
#pragma aux Div052 = \
"mov	edx, 1321528399", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div053(int value);
#pragma aux Div053 = \
"mov	edx, 1296593901", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div054(int value);
#pragma aux Div054 = \
"mov	edx, 1272582903", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div055(int value);
#pragma aux Div055 = \
"mov	edx, 156180629", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 1", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div056(int value);
#pragma aux Div056 = \
"mov	edx, -1840700269", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div057(int value);
#pragma aux Div057 = \
"mov	edx, -1883757585", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div058(int value);
#pragma aux Div058 = \
"mov	edx, -1925330167", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div059(int value);
#pragma aux Div059 = \
"mov	edx, 582368447", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div060(int value);
#pragma aux Div060 = \
"mov	edx, -2004318071", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div061(int value);
#pragma aux Div061 = \
"mov	edx, 1126548799", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div062(int value);
#pragma aux Div062 = \
"mov	edx, -2078209981", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div063(int value);
#pragma aux Div063 = \
"mov	edx, -2113396605", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 5", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div065(int value);
#pragma aux Div065 = \
"mov	edx, 2114445439", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div066(int value);
#pragma aux Div066 = \
"mov	edx, 1041204193", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div067(int value);
#pragma aux Div067 = \
"mov	edx, 128207979", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 1", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div068(int value);
#pragma aux Div068 = \
"mov	edx, 2021161081", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div069(int value);
#pragma aux Div069 = \
"mov	edx, 1991868891", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div070(int value);
#pragma aux Div070 = \
"mov	edx, -368140053", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div071(int value);
#pragma aux Div071 = \
"mov	edx, -423447479", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div072(int value);
#pragma aux Div072 = \
"mov	edx, 954437177", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div073(int value);
#pragma aux Div073 = \
"mov	edx, -529516515", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div074(int value);
#pragma aux Div074 = \
"mov	edx, -580400985", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div075(int value);
#pragma aux Div075 = \
"mov	edx, 458129845", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div076(int value);
#pragma aux Div076 = \
"mov	edx, 1808407283", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div077(int value);
#pragma aux Div077 = \
"mov	edx, 892460737", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div078(int value);
#pragma aux Div078 = \
"mov	edx, -770891565", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div079(int value);
#pragma aux Div079 = \
"mov	edx, 1739733589", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div080(int value);
#pragma aux Div080 = \
"mov	edx, 1717986919", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div081(int value);
#pragma aux Div081 = \
"mov	edx, 424194301", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div082(int value);
#pragma aux Div082 = \
"mov	edx, 1676084799", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div083(int value);
#pragma aux Div083 = \
"mov	edx, 827945503", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div084(int value);
#pragma aux Div084 = \
"mov	edx, 818089009", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div085(int value);
#pragma aux Div085 = \
"mov	edx, 1616928865", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div086(int value);
#pragma aux Div086 = \
"mov	edx, 799063683", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div087(int value);
#pragma aux Div087 = \
"mov	edx, 789879043", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div088(int value);
#pragma aux Div088 = \
"mov	edx, 780903145", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div089(int value);
#pragma aux Div089 = \
"mov	edx, -1206451487", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div090(int value);
#pragma aux Div090 = \
"mov	edx, -1240768329", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div091(int value);
#pragma aux Div091 = \
"mov	edx, -1274330955", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div092(int value);
#pragma aux Div092 = \
"mov	edx, -1307163959", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div093(int value);
#pragma aux Div093 = \
"mov	edx, 738919105", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div094(int value);
#pragma aux Div094 = \
"mov	edx, -1370734243", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div095(int value);
#pragma aux Div095 = \
"mov	edx, -1401515643", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div096(int value);
#pragma aux Div096 = \
"mov	edx, 715827883", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div097(int value);
#pragma aux Div097 = \
"mov	edx, 354224107", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div098(int value);
#pragma aux Div098 = \
"mov	edx, 1402438301", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div099(int value);
#pragma aux Div099 = \
"mov	edx, -1518422781", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div100(int value);
#pragma aux Div100 = \
"mov	edx, 1374389535", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div101(int value);
#pragma aux Div101 = \
"mov	edx, 680390859", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div102(int value);
#pragma aux Div102 = \
"mov	edx, -1600085855", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div103(int value);
#pragma aux Div103 = \
"mov	edx, 333589693", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div104(int value);
#pragma aux Div104 = \
"mov	edx, 1321528399", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div105(int value);
#pragma aux Div105 = \
"mov	edx, -1677082467", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div106(int value);
#pragma aux Div106 = \
"mov	edx, 1296593901", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div107(int value);
#pragma aux Div107 = \
"mov	edx, 1284476201", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div108(int value);
#pragma aux Div108 = \
"mov	edx, 1272582903", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div109(int value);
#pragma aux Div109 = \
"mov	edx, -1773151635", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div110(int value);
#pragma aux Div110 = \
"mov	edx, 156180629", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div111(int value);
#pragma aux Div111 = \
"mov	edx, -1818589755", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div112(int value);
#pragma aux Div112 = \
"mov	edx, -1840700269", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div113(int value);
#pragma aux Div113 = \
"mov	edx, 1216273925", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div114(int value);
#pragma aux Div114 = \
"mov	edx, -1883757585", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div115(int value);
#pragma aux Div115 = \
"mov	edx, 1195121335", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div116(int value);
#pragma aux Div116 = \
"mov	edx, -1925330167", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div117(int value);
#pragma aux Div117 = \
"mov	edx, -1945583475", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div118(int value);
#pragma aux Div118 = \
"mov	edx, 582368447", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div119(int value);
#pragma aux Div119 = \
"mov	edx, 1154949189", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div120(int value);
#pragma aux Div120 = \
"mov	edx, -2004318071", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div121(int value);
#pragma aux Div121 = \
"mov	edx, 70991195", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 1", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div122(int value);
#pragma aux Div122 = \
"mov	edx, 1126548799", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div123(int value);
#pragma aux Div123 = \
"mov	edx, 558694933", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div124(int value);
#pragma aux Div124 = \
"mov	edx, -2078209981", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div125(int value);
#pragma aux Div125 = \
"mov	edx, 274877907", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div126(int value);
#pragma aux Div126 = \
"mov	edx, -2113396605", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div127(int value);
#pragma aux Div127 = \
"mov	edx, -2130574327", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 6", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div129(int value);
#pragma aux Div129 = \
"mov	edx, 266354561", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div130(int value);
#pragma aux Div130 = \
"mov	edx, 2114445439", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div131(int value);
#pragma aux Div131 = \
"mov	edx, 1049152317", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div132(int value);
#pragma aux Div132 = \
"mov	edx, 1041204193", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div133(int value);
#pragma aux Div133 = \
"mov	edx, -161464935", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div134(int value);
#pragma aux Div134 = \
"mov	edx, 128207979", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div135(int value);
#pragma aux Div135 = \
"mov	edx, -222702007", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div136(int value);
#pragma aux Div136 = \
"mov	edx, 2021161081", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div137(int value);
#pragma aux Div137 = \
"mov	edx, 125400505", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div138(int value);
#pragma aux Div138 = \
"mov	edx, 1991868891", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div139(int value);
#pragma aux Div139 = \
"mov	edx, 1977538899", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div140(int value);
#pragma aux Div140 = \
"mov	edx, -368140053", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div141(int value);
#pragma aux Div141 = \
"mov	edx, 974744351", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div142(int value);
#pragma aux Div142 = \
"mov	edx, -423447479", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div143(int value);
#pragma aux Div143 = \
"mov	edx, 961111563", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div144(int value);
#pragma aux Div144 = \
"mov	edx, 954437177", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div145(int value);
#pragma aux Div145 = \
"mov	edx, -503547889", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div146(int value);
#pragma aux Div146 = \
"mov	edx, -529516515", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div147(int value);
#pragma aux Div147 = \
"mov	edx, 1869917735", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div148(int value);
#pragma aux Div148 = \
"mov	edx, -580400985", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div149(int value);
#pragma aux Div149 = \
"mov	edx, 230602271", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div150(int value);
#pragma aux Div150 = \
"mov	edx, 458129845", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div151(int value);
#pragma aux Div151 = \
"mov	edx, 910191745", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div152(int value);
#pragma aux Div152 = \
"mov	edx, 1808407283", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div153(int value);
#pragma aux Div153 = \
"mov	edx, -701792041", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div154(int value);
#pragma aux Div154 = \
"mov	edx, 892460737", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div155(int value);
#pragma aux Div155 = \
"mov	edx, 443351463", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div156(int value);
#pragma aux Div156 = \
"mov	edx, -770891565", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div157(int value);
#pragma aux Div157 = \
"mov	edx, 875407347", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div158(int value);
#pragma aux Div158 = \
"mov	edx, 1739733589", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div159(int value);
#pragma aux Div159 = \
"mov	edx, 432197967", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div160(int value);
#pragma aux Div160 = \
"mov	edx, 1717986919", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div161(int value);
#pragma aux Div161 = \
"mov	edx, -880334911", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div162(int value);
#pragma aux Div162 = \
"mov	edx, 424194301", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div163(int value);
#pragma aux Div163 = \
"mov	edx, 210795941", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div164(int value);
#pragma aux Div164 = \
"mov	edx, 1676084799", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div165(int value);
#pragma aux Div165 = \
"mov	edx, 1665926709", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div166(int value);
#pragma aux Div166 = \
"mov	edx, 827945503", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div167(int value);
#pragma aux Div167 = \
"mov	edx, 1645975491", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div168(int value);
#pragma aux Div168 = \
"mov	edx, 818089009", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div169(int value);
#pragma aux Div169 = \
"mov	edx, 1626496491", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div170(int value);
#pragma aux Div170 = \
"mov	edx, 1616928865", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div171(int value);
#pragma aux Div171 = \
"mov	edx, -1080021015", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div172(int value);
#pragma aux Div172 = \
"mov	edx, 799063683", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div173(int value);
#pragma aux Div173 = \
"mov	edx, 397222409", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div174(int value);
#pragma aux Div174 = \
"mov	edx, 789879043", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div175(int value);
#pragma aux Div175 = \
"mov	edx, 1570730897", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div176(int value);
#pragma aux Div176 = \
"mov	edx, 780903145", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div177(int value);
#pragma aux Div177 = \
"mov	edx, -1189002245", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div178(int value);
#pragma aux Div178 = \
"mov	edx, -1206451487", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div179(int value);
#pragma aux Div179 = \
"mov	edx, -1223705765", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div180(int value);
#pragma aux Div180 = \
"mov	edx, -1240768329", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div181(int value);
#pragma aux Div181 = \
"mov	edx, 759331235", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div182(int value);
#pragma aux Div182 = \
"mov	edx, -1274330955", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div183(int value);
#pragma aux Div183 = \
"mov	edx, -1290837165", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div184(int value);
#pragma aux Div184 = \
"mov	edx, -1307163959", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div185(int value);
#pragma aux Div185 = \
"mov	edx, -1323314247", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div186(int value);
#pragma aux Div186 = \
"mov	edx, 738919105", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div187(int value);
#pragma aux Div187 = \
"mov	edx, -1355096633", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div188(int value);
#pragma aux Div188 = \
"mov	edx, -1370734243", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div189(int value);
#pragma aux Div189 = \
"mov	edx, -1386206375", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div190(int value);
#pragma aux Div190 = \
"mov	edx, -1401515643", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div191(int value);
#pragma aux Div191 = \
"mov	edx, -1416664605", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div192(int value);
#pragma aux Div192 = \
"mov	edx, 715827883", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div193(int value);
#pragma aux Div193 = \
"mov	edx, 356059465", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div194(int value);
#pragma aux Div194 = \
"mov	edx, 354224107", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div195(int value);
#pragma aux Div195 = \
"mov	edx, -1475706711", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div196(int value);
#pragma aux Div196 = \
"mov	edx, 1402438301", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div197(int value);
#pragma aux Div197 = \
"mov	edx, 1395319325", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div198(int value);
#pragma aux Div198 = \
"mov	edx, -1518422781", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div199(int value);
#pragma aux Div199 = \
"mov	edx, 1381296015", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div200(int value);
#pragma aux Div200 = \
"mov	edx, 1374389535", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div201(int value);
#pragma aux Div201 = \
"mov	edx, 42735993", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 1", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div202(int value);
#pragma aux Div202 = \
"mov	edx, 680390859", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div203(int value);
#pragma aux Div203 = \
"mov	edx, -1586810577", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div204(int value);
#pragma aux Div204 = \
"mov	edx, -1600085855", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div205(int value);
#pragma aux Div205 = \
"mov	edx, 1340867839", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div206(int value);
#pragma aux Div206 = \
"mov	edx, 333589693", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div207(int value);
#pragma aux Div207 = \
"mov	edx, 663956297", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div208(int value);
#pragma aux Div208 = \
"mov	edx, 1321528399", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div209(int value);
#pragma aux Div209 = \
"mov	edx, -1664556703", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div210(int value);
#pragma aux Div210 = \
"mov	edx, -1677082467", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div211(int value);
#pragma aux Div211 = \
"mov	edx, 81421181", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div212(int value);
#pragma aux Div212 = \
"mov	edx, 1296593901", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div213(int value);
#pragma aux Div213 = \
"mov	edx, -1713954085", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div214(int value);
#pragma aux Div214 = \
"mov	edx, 1284476201", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div215(int value);
#pragma aux Div215 = \
"mov	edx, 1278501893", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div216(int value);
#pragma aux Div216 = \
"mov	edx, 1272582903", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div217(int value);
#pragma aux Div217 = \
"mov	edx, -1761530365", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div218(int value);
#pragma aux Div218 = \
"mov	edx, -1773151635", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div219(int value);
#pragma aux Div219 = \
"mov	edx, -1784666775", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div220(int value);
#pragma aux Div220 = \
"mov	edx, 156180629", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div221(int value);
#pragma aux Div221 = \
"mov	edx, -1807384427", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div222(int value);
#pragma aux Div222 = \
"mov	edx, -1818589755", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div223(int value);
#pragma aux Div223 = \
"mov	edx, -1829694587", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div224(int value);
#pragma aux Div224 = \
"mov	edx, -1840700269", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div225(int value);
#pragma aux Div225 = \
"mov	edx, -1851608123", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div226(int value);
#pragma aux Div226 = \
"mov	edx, 1216273925", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div227(int value);
#pragma aux Div227 = \
"mov	edx, 605457945", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div228(int value);
#pragma aux Div228 = \
"mov	edx, -1883757585", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div229(int value);
#pragma aux Div229 = \
"mov	edx, 1200340205", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div230(int value);
#pragma aux Div230 = \
"mov	edx, 1195121335", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div231(int value);
#pragma aux Div231 = \
"mov	edx, -1915071997", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div232(int value);
#pragma aux Div232 = \
"mov	edx, -1925330167", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div233(int value);
#pragma aux Div233 = \
"mov	edx, -1935500283", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div234(int value);
#pragma aux Div234 = \
"mov	edx, -1945583475", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div235(int value);
#pragma aux Div235 = \
"mov	edx, -1955580853", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div236(int value);
#pragma aux Div236 = \
"mov	edx, 582368447", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div237(int value);
#pragma aux Div237 = \
"mov	edx, -1975322511", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div238(int value);
#pragma aux Div238 = \
"mov	edx, 1154949189", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div239(int value);
#pragma aux Div239 = \
"mov	edx, -1994733765", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div240(int value);
#pragma aux Div240 = \
"mov	edx, -2004318071", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div241(int value);
#pragma aux Div241 = \
"mov	edx, 285143057", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div242(int value);
#pragma aux Div242 = \
"mov	edx, 70991195", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 2", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div243(int value);
#pragma aux Div243 = \
"mov	edx, -2032597691", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div244(int value);
#pragma aux Div244 = \
"mov	edx, 1126548799", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div245(int value);
#pragma aux Div245 = \
"mov	edx, 1121950641", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div246(int value);
#pragma aux Div246 = \
"mov	edx, 558694933", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div247(int value);
#pragma aux Div247 = \
"mov	edx, -2069235255", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div248(int value);
#pragma aux Div248 = \
"mov	edx, -2078209981", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div249(int value);
#pragma aux Div249 = \
"mov	edx, -2087112621", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div250(int value);
#pragma aux Div250 = \
"mov	edx, 274877907", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div251(int value);
#pragma aux Div251 = \
"mov	edx, -2104705089", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div252(int value);
#pragma aux Div252 = \
"mov	edx, -2113396605", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div253(int value);
#pragma aux Div253 = \
"mov	edx, -2122019415", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div254(int value);
#pragma aux Div254 = \
"mov	edx, -2130574327", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div255(int value);
#pragma aux Div255 = \
"mov	edx, -2139062143", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 7", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div257(int value);
#pragma aux Div257 = \
"mov	edx, 2139127681", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div258(int value);
#pragma aux Div258 = \
"mov	edx, 266354561", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div259(int value);
#pragma aux Div259 = \
"mov	edx, 2122609321", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div260(int value);
#pragma aux Div260 = \
"mov	edx, 2114445439", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div261(int value);
#pragma aux Div261 = \
"mov	edx, 2106344115", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div262(int value);
#pragma aux Div262 = \
"mov	edx, 1049152317", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div263(int value);
#pragma aux Div263 = \
"mov	edx, 2090326289", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div264(int value);
#pragma aux Div264 = \
"mov	edx, 1041204193", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div265(int value);
#pragma aux Div265 = \
"mov	edx, 1037275121", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div266(int value);
#pragma aux Div266 = \
"mov	edx, -161464935", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div267(int value);
#pragma aux Div267 = \
"mov	edx, 2059010539", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div268(int value);
#pragma aux Div268 = \
"mov	edx, 128207979", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div269(int value);
#pragma aux Div269 = \
"mov	edx, 2043701911", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div270(int value);
#pragma aux Div270 = \
"mov	edx, -222702007", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div271(int value);
#pragma aux Div271 = \
"mov	edx, 253577405", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div272(int value);
#pragma aux Div272 = \
"mov	edx, 2021161081", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div273(int value);
#pragma aux Div273 = \
"mov	edx, -267452175", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div274(int value);
#pragma aux Div274 = \
"mov	edx, 125400505", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div275(int value);
#pragma aux Div275 = \
"mov	edx, 1999112051", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div276(int value);
#pragma aux Div276 = \
"mov	edx, 1991868891", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div277(int value);
#pragma aux Div277 = \
"mov	edx, 1984678029", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div278(int value);
#pragma aux Div278 = \
"mov	edx, 1977538899", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div279(int value);
#pragma aux Div279 = \
"mov	edx, 985225473", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div280(int value);
#pragma aux Div280 = \
"mov	edx, -368140053", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div281(int value);
#pragma aux Div281 = \
"mov	edx, 122276649", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 3", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div282(int value);
#pragma aux Div282 = \
"mov	edx, 974744351", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div283(int value);
#pragma aux Div283 = \
"mov	edx, -409767197", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div284(int value);
#pragma aux Div284 = \
"mov	edx, -423447479", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div285(int value);
#pragma aux Div285 = \
"mov	edx, -437031759", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div286(int value);
#pragma aux Div286 = \
"mov	edx, 961111563", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div287(int value);
#pragma aux Div287 = \
"mov	edx, 478881371", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div288(int value);
#pragma aux Div288 = \
"mov	edx, 954437177", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div289(int value);
#pragma aux Div289 = \
"mov	edx, 1902269253", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div290(int value);
#pragma aux Div290 = \
"mov	edx, -503547889", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div291(int value);
#pragma aux Div291 = \
"mov	edx, 1889195237", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div292(int value);
#pragma aux Div292 = \
"mov	edx, -529516515", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div293(int value);
#pragma aux Div293 = \
"mov	edx, -542367883", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div294(int value);
#pragma aux Div294 = \
"mov	edx, 1869917735", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div295(int value);
#pragma aux Div295 = \
"mov	edx, -567809235", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div296(int value);
#pragma aux Div296 = \
"mov	edx, -580400985", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div297(int value);
#pragma aux Div297 = \
"mov	edx, 1851029677", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div298(int value);
#pragma aux Div298 = \
"mov	edx, 230602271", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div299(int value);
#pragma aux Div299 = \
"mov	edx, 1838648207", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div300(int value);
#pragma aux Div300 = \
"mov	edx, 458129845", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div301(int value);
#pragma aux Div301 = \
"mov	edx, 456607819", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div302(int value);
#pragma aux Div302 = \
"mov	edx, 910191745", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div303(int value);
#pragma aux Div303 = \
"mov	edx, 226796953", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 4", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div304(int value);
#pragma aux Div304 = \
"mov	edx, 1808407283", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div305(int value);
#pragma aux Div305 = \
"mov	edx, 1802478079", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div306(int value);
#pragma aux Div306 = \
"mov	edx, -701792041", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div307(int value);
#pragma aux Div307 = \
"mov	edx, -713496195", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div308(int value);
#pragma aux Div308 = \
"mov	edx, 892460737", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div309(int value);
#pragma aux Div309 = \
"mov	edx, 1779145029", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div310(int value);
#pragma aux Div310 = \
"mov	edx, 443351463", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div311(int value);
#pragma aux Div311 = \
"mov	edx, 883851791", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div312(int value);
#pragma aux Div312 = \
"mov	edx, -770891565", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div313(int value);
#pragma aux Div313 = \
"mov	edx, -782150593", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div314(int value);
#pragma aux Div314 = \
"mov	edx, 875407347", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div315(int value);
#pragma aux Div315 = \
"mov	edx, -804454191", \
"mov	eax, ecx", \
"imul	edx", \
"lea	eax, [edx+ecx]", \
"sar	eax, 8", \
"sar	ecx, 31", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div316(int value);
#pragma aux Div316 = \
"mov	edx, 1739733589", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 7", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div317(int value);
#pragma aux Div317 = \
"mov	edx, 867122735", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div318(int value);
#pragma aux Div318 = \
"mov	edx, 432197967", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 5", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]

int Div319(int value);
#pragma aux Div319 = \
"mov	edx, 861686229", \
"mov	eax, ecx", \
"imul	edx", \
"sar	edx, 6", \
"sar	ecx, 31", \
"mov	eax, edx", \
"sub	eax, ecx" parm[ecx] value[eax] modify exact[eax ecx edx]
	
#endif // __FASTDIV__
