/*
 * PROJECT:     ReactOS RAMDisk Creator
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     main.c file
 * COPYRIGHT:   Copyright 2021 Arnav Bhatt (arnavbhatt288@gmail.com)
 */

#define countof(array) (sizeof(array) / sizeof(array[0]))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arg.h"
#include "bool.h"
#include "fs_data.h"
#include "ini.h"
#include "ini_data.h"

#ifdef _WIN32
    #include <windows.h>
	#include "win32_volume.h"
#else
	#include "volume.h"
#endif

char *argv0;

bool InstallBootSector(FileHandle* fhandle, char* VolumeType);
static void ProgramUsage(void);

int main(int argc, char *argv[])
{
    bool Ret = false;
    bool bootcd = false;
    bool livecd = false;
    char* drive = "";
    char* IniDest = "";
    char* fs_type = "";

    FileHandle* fhandle;

    ARGBEGIN
    {
        case 'b':
        {
            bootcd = true;
            break;
        }
        
        case 'd':
        {
            drive = EARGF(ProgramUsage());
            break;
        }
        
        case 'f':
        {
            fs_type = EARGF(ProgramUsage());
            break;
        }
        
        case 'i':
        {
            IniDest = EARGF(ProgramUsage());
            break;
        }
        
        case 'l':
        {
            livecd = true;
            break;
        }
        
        default:
        {
            ProgramUsage();
            break;
        }
    } ARGEND

    if (strcmp(drive, "") != 0 && strcmp(fs_type, "") != 0)
    {
        fhandle = OpenVolume(drive);
        if (fhandle == NULL)
        {
            return -1;
        }
        
        if (!InstallBootSector(fhandle, fs_type))
        {
            CloseVolume(fhandle);
            return -1;
        }
        CloseVolume(fhandle);
    }
    else if((strcmp(IniDest, "") != 0))
    {
        for (int i = 0; i < countof(MainIniData); i++)
        {
            Ret = CreateINI(IniDest, MainIniData[i].pacTopic, MainIniData[i].pacItem, MainIniData[i].pacValue);
            if (!Ret)
            {
                return -1;
            }
        }

        if (bootcd)
        {
            for (int i = 0; i < countof(BootCDIniData); i++)
            {
            Ret = CreateINI(IniDest, BootCDIniData[i].pacTopic, BootCDIniData[i].pacItem, BootCDIniData[i].pacValue);
                if (!Ret)
                {
                    return -1;
                }
            }
        }

        if (livecd)
        {
            for (int i = 0; i < countof(LiveCDIniData); i++)
            {
                Ret = CreateINI(IniDest, LiveCDIniData[i].pacTopic, LiveCDIniData[i].pacItem, LiveCDIniData[i].pacValue);
                if (!Ret)
                {
                    return -1;
                }
            }
        }

        printf("INI sucessfully created.\n");
    }
    else
    {
        ProgramUsage();
    }

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

static void ProgramUsage(void)
{
    const char *opts1 = "[-d drive] [-f fs]";
    const char *opts2 = "[-i] path-to-freeldr.ini [-b] [-l]";

    printf("usage: %s %s for installing bootloader\n", argv0, opts1);
    printf("usage: %s %s for generating freeldr.ini.\n", argv0, opts2);
}
