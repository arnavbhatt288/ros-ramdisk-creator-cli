/*
 * PROJECT:     ReactOS RAMDisk Creator
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     volume.h file
 * COPYRIGHT:   Copyright 2021 Arnav Bhatt (arnavbhatt288@gmail.com)
 */

#ifndef VOLUME_H
#define VOLUME_H

#include "bool.h"

typedef struct
{
    int file;
} FileHandle;

bool ReadVolumeSector(FileHandle* fhandle, long SectorNumber, void* SectorBuffer);
bool WriteVolumeSector(FileHandle* fhandle, long SectorNumber, void* SectorBuffer);
FileHandle* OpenVolume(char* VolumeName);
void CloseVolume(FileHandle* fhandle);

#endif