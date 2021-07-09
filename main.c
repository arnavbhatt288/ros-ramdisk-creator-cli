/*
 * PROJECT:     ReactOS RAMDisk Creator
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     main.c file
 * COPYRIGHT:   Copyright 2021 Arnav Bhatt (arnavbhatt288@gmail.com)
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arg.h"
#include "ini.h"
#include "fs_data.h"
#include "volume.h"

char *argv0;

bool InstallBootSector(FileHandle* fhandle, char* VolumeType);
static void ProgramUsage(void);

int main(int argc, char *argv[])
{
    bool GenerateINI = false;
    bool Ret = false;
    bool bootcd = "";
    char* dest = "";
    char* fs_type = "";
    bool livecd = "";

    FileHandle* fhandle;

    if (argc == 1)
    {
        ProgramUsage();
        return -1;
    }

    ARGBEGIN
    {
        case 'b':
        {
            bootcd = true;
            break;
        }
        
        case 'd':
        {
            dest = EARGF(ProgramUsage());
            break;
        }
        
        case 'f':
        {
            fs_type = EARGF(ProgramUsage());
            break;
        }
        
        case 'i':
        {
            GenerateINI = true;
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

    if (strcmp(dest, "") != 0 && strcmp(fs_type, "") != 0)
    {
        fhandle = OpenVolume(dest);
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
    else if(GenerateINI && (strcmp(dest, "") != 0))
    {
        Ret = CreateINI(dest, "FREELOADER", "DefaultOS", "Setup");
        Ret = CreateINI(dest, "FREELOADER", "TimeOut", "5");
        Ret = CreateINI(dest, "Display", "TitleText", "ReactOS Setup (RAM Disk)");
        Ret = CreateINI(dest, "Display", "StatusBarColor", "Cyan");
        Ret = CreateINI(dest, "Display", "StatusBarTextColor", "Black");
        Ret = CreateINI(dest, "Display", "BackdropTextColor", "White");
        Ret = CreateINI(dest, "Display", "BackdropColor", "Blue");
        Ret = CreateINI(dest, "Display", "BackdropFillStyle", "Medium");
        Ret = CreateINI(dest, "Display", "TitleBoxTextColor", "White");
        Ret = CreateINI(dest, "Display", "TitleBoxColor", "Red");
        Ret = CreateINI(dest, "Display", "MessageBoxTextColor", "White");
        Ret = CreateINI(dest, "Display", "MessageBoxColor", "Blue");
        Ret = CreateINI(dest, "Display", "MenuTextColor", "Gray");
        Ret = CreateINI(dest, "Display", "MenuColor", "Black");
        Ret = CreateINI(dest, "Display", "TextColor", "Gray");
        Ret = CreateINI(dest, "Display", "SelectedTextColor", "Black");
        Ret = CreateINI(dest, "Display", "SelectedColor", "Gray");
        Ret = CreateINI(dest, "Display", "ShowTime", "No");
        Ret = CreateINI(dest, "Display", "MenuBox", "No");
        Ret = CreateINI(dest, "Display", "CenterMenu", "No");
        Ret = CreateINI(dest, "Display", "MinimalUI", "Yes");
        Ret = CreateINI(dest, "Display", "TimeText", "Seconds until highlighted choice will be started automatically:");

        if (bootcd)
        {
            Ret = CreateINI(dest, "Operating Systems", "Setup", "\"Setup\"");
            Ret = CreateINI(dest, "Setup", "BootType", "ReactOSSetup");
            Ret = CreateINI(dest, "Setup", "SystemPath", "ramdisk(0)");
            Ret = CreateINI(dest, "Setup", "Options", "/RDPATH=bootcd.iso");
        }

        if (livecd)
        {
            Ret = CreateINI(dest, "Operating Systems", "LiveCD", "\"LiveCD\"");
            Ret = CreateINI(dest, "LiveCD", "BootType", "Windows2003");
            Ret = CreateINI(dest, "LiveCD", "SystemPath", "ramdisk(0)\\reactos");
            Ret = CreateINI(dest, "LiveCD", "Options", "/MININT /RDPATH=livecd.iso /RDEXPORTASCD");
            // BootCD already has debug by default, therefore end-user will also have option to turn it on for LiveCD.
            Ret = CreateINI(dest, "Operating Systems", "LiveCD_Debug", "\"LiveCD (Debug)\"");
            Ret = CreateINI(dest, "LiveCD_Debug", "BootType", "Windows2003");
            Ret = CreateINI(dest, "LiveCD_Debug", "SystemPath", "ramdisk(0)\\reactos");
            Ret = CreateINI(dest, "LiveCD_Debug", "Options", "/MININT /RDPATH=livecd.iso /RDEXPORTASCD /DEBUG /DEBUGPORT=COM1 /BAUDRATE=115200 /SOS");
            // ...and screen for those unfortunate without a Serial connector or cable.
            Ret = CreateINI(dest, "Operating Systems", "LiveCD_Screen", "\"LiveCD (Screen)\"");
            Ret = CreateINI(dest, "LiveCD_Screen", "BootType", "Windows2003");
            Ret = CreateINI(dest, "LiveCD_Screen", "SystemPath", "ramdisk(0)\\reactos");
            Ret = CreateINI(dest, "LiveCD_Screen", "Options", "/MININT /RDPATH=livecd.iso /RDEXPORTASCD /DEBUG /DEBUGPORT=SCREEN /SOS");
        }

        if (!Ret)
        {
            return -1;
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
    const char *opts2 = "[-i] [-d freeldr.ini] [-b] [-l]";

    printf("usage: %s %s for installing bootloader\n", argv0, opts1);
    printf("usage: %s %s for generating freeldr.ini.\n", argv0, opts2);
}
