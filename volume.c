/*
 * PROJECT:     ReactOS RAMDisk Creator
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     volume.c
 * COPYRIGHT:   Copyright 2021 Arnav Bhatt (arnavbhatt288@gmail.com)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#include "bool.h"
#include "volume.h"

FileHandle* OpenVolume(char* VolumeName)
{
    FileHandle* fhandle = malloc(sizeof(*fhandle));
    printf("Opening volume %s\n", VolumeName);
    
    fhandle->file = open(VolumeName, O_RDWR | O_SYNC);
    
    if (fhandle->file < 0)
    {
        perror("OpenVolume() failed!");
        return NULL;
    }
    
    return fhandle;
}

void CloseVolume(FileHandle* fhandle)
{
    close(fhandle->file);
    fhandle->file = -1;
    free(fhandle);
}

bool ReadVolumeSector(FileHandle* fhandle, long SectorNumber, void* SectorBuffer)
{
    int NumberOfBytesRead;
    int FilePosition;
    
    FilePosition = lseek(fhandle->file, (SectorNumber* 512), SEEK_SET);
    
    if (FilePosition != (SectorNumber * 512))
    {
        perror("ReadVolumeSector() failed!");
        return false;
    }
    
    NumberOfBytesRead = read(fhandle->file, SectorBuffer, 512);
    
    if (NumberOfBytesRead != 512)
    {
        perror("ReadVolumeSector() failed!");
        return false;
    }
    
    return true;
}

bool  WriteVolumeSector(FileHandle* fhandle, long SectorNumber, void* SectorBuffer)
{
    int NumberOfBytesWritten;
    int FilePosition;
    
    FilePosition = lseek(fhandle->file, (SectorNumber * 512), SEEK_SET);
    
    if (FilePosition != (SectorNumber * 512))
    {
        perror("WriteVolumeSector() failed!");
        return false;
    }
    
    NumberOfBytesWritten = write(fhandle->file, SectorBuffer, 512);
    
    if (NumberOfBytesWritten != 512)
    {
        perror("WriteVolumeSector() failed!");
        return false;
    }
    
    return true;
}
