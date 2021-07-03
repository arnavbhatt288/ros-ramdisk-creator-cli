/*
 *  FreeLoader - volume.h
 *
 *  Copyright (C) 2001  Brian Palmer  <brianp@sginet.com>
 *  Copyright (C) 2021  Arnav Bhatt   <arnavbhatt288@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#pragma once

#include <windows.h>

typedef struct
{
    HANDLE file;
} FileHandle;

FileHandle*    OpenVolume(LPCTSTR lpszVolumeName);
void           CloseVolume(FileHandle* fhandle);
BOOL           ReadVolumeSector(FileHandle* fhandle, ULONG SectorNumber, PVOID SectorBuffer);
BOOL           WriteVolumeSector(FileHandle* fhandle, ULONG SectorNumber, PVOID SectorBuffer);
