/*
 * PROJECT:     ReactOS RAMDisk Creator
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Precompiler
 * COPYRIGHT:   Copyright 2021 Arnav Bhatt (arnavbhatt288@gmail.com)
 */
 
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "fs_data.h"
#include "volume.h"

bool InstallBootSector(FileHandle* fhandle, char* VolumeType);

int main(int argc, char *argv[])
{
    FileHandle* fhandle;
    if (argc < 3)
    {
        printf("oy vey");
        return -1;
    }

    fhandle = OpenVolume(argv[1]);
    if (fhandle == NULL || !InstallBootSector(fhandle, argv[2]))
    {
        return -1;
    }

    CloseVolume(fhandle);

    printf("You must now copy freeldr.sys & freeldr.ini to %s.\n", argv[1]);

    return 0;
}


bool InstallBootSector(FileHandle* fhandle, char* VolumeType)
{
    unsigned char BootSectorBuffer[512];

    if (!ReadVolumeSector(fhandle, 0, BootSectorBuffer))
    {
        return false;
    }

    if (strcasecmp(VolumeType, "fat32") == 0)
    {
        //
        // Update the BPB in the new boot sector
        //
        memcpy((fat32_data+3), (BootSectorBuffer+3), 87 /*fat32 BPB length*/);

        //
        // Write out new boot sector
        //
        if (!WriteVolumeSector(fhandle, 0, fat32_data))
        {
            return false;
        }

        //
        // Write out new extra sector
        //
        if (!WriteVolumeSector(fhandle, 14, (fat32_data+512)))
        {
            return false;
        }
    }

    else if (strcasecmp(VolumeType, "fat") == 0)
    {
        //
        // Update the BPB in the new boot sector
         //
        memcpy((fat_data+3), (BootSectorBuffer+3), 59 /*fat BPB length*/);

        //
        // Write out new boot sector
        //
        if (!WriteVolumeSector(fhandle, 0, fat_data))
        {
            return false;
        }
    }

    else
    {
        printf("File system type %s unknown.\n", VolumeType);
        return false;
    }

    printf("%s boot sector installed.\n", VolumeType);

    return true;
}
