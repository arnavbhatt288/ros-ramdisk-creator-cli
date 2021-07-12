/*
 * PROJECT:     ReactOS FreeLoader installer for Linux
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     ini_data.h file
 * COPYRIGHT:   Copyright 2021 Arnav Bhatt (arnavbhatt288@gmail.com)
 */

#ifndef INI_DATA_H
#define INI_DATA_H

typedef struct
{
    char *pacTopic;
    char *pacItem;
    char *pacValue;
} INI_DATA;

INI_DATA MainIniData[] =
{
    {"FREELOADER", "TimeOut", "5"},
    {"Display", "TitleText", "ReactOS RAMDisk"},
    {"Display", "StatusBarColor", "Cyan"},
    {"Display", "StatusBarTextColor", "Black"},
    {"Display", "BackdropTextColor", "White"},
    {"Display", "BackdropColor", "Blue"},
    {"Display", "BackdropFillStyle", "Medium"},
    {"Display", "TitleBoxTextColor", "White"},
    {"Display", "TitleBoxColor", "Red"},
    {"Display", "MessageBoxTextColor", "White"},
    {"Display", "MessageBoxColor", "Blue"},
    {"Display", "MenuTextColor", "Gray"},
    {"Display", "MenuColor", "Black"},
    {"Display", "TextColor", "Gray"},
    {"Display", "SelectedTextColor", "Black"},
    {"Display", "SelectedColor", "Gray"},
    {"Display", "ShowTime", "No"},
    {"Display", "MenuBox", "No"},
    {"Display", "CenterMenu", "No"},
    {"Display", "MinimalUI", "Yes"},
    {"Display", "TimeText", "Seconds until highlighted choice will be started automatically:"}
};

INI_DATA BootCDIniData[] =
{
    {"FREELOADER", "DefaultOS", "BootCD"},
    {"Operating Systems", "BootCD", "\"BootCD\""},
    {"Operating Systems", "BootCD_Debug", "\"BootCD (Debug)\""},
    {"Operating Systems", "BootCD_Screen", "\"BootCD (Screen)\""},
    {"BootCD", "BootType", "ReactOSSetup"},
    {"BootCD", "SystemPath", "ramdisk(0)\\"},
    {"BootCD", "Options", "/MININT /RDPATH=bootcd.iso /RDEXPORTASCD"},
    {"BootCD_Debug", "BootType", "ReactOSSetup"},
    {"BootCD_Debug", "SystemPath", "ramdisk(0)\\"},
    {"BootCD_Debug", "Options", "/DEBUG /DEBUGPORT=COM1 /BAUDRATE=115200 /SOS /MININT /RDPATH=bootcd.iso /RDEXPORTASCD"},
    {"BootCD_Screen", "BootType", "ReactOSSetup"},
    {"BootCD_Screen", "SystemPath", "ramdisk(0)\\"},
    {"BootCD_Screen", "Options", "/DEBUG /DEBUGPORT=SCREEN /SOS /MININT /RDPATH=bootcd.iso /RDEXPORTASCD"},
};

INI_DATA LiveCDIniData[] =
{
    {"FREELOADER", "DefaultOS", "LiveCD"},
    {"Operating Systems", "LiveCD", "\"LiveCD\""},
    {"Operating Systems", "LiveCD_Debug", "\"LiveCD (Debug)\""},
    {"Operating Systems", "LiveCD_Screen", "\"LiveCD (Screen)\""},
    {"LiveCD", "BootType", "Windows2003"},
    {"LiveCD", "SystemPath", "ramdisk(0)\\reactos"},
    {"LiveCD", "Options", "/MININT /RDPATH=livecd.iso /RDEXPORTASCD"},
    {"LiveCD_Debug", "BootType", "Windows2003"},
    {"LiveCD_Debug", "SystemPath", "ramdisk(0)\\reactos"},
    {"LiveCD_Debug", "Options", "/DEBUG /DEBUGPORT=COM1 /BAUDRATE=115200 /SOS /MININT /RDPATH=livecd.iso /RDEXPORTASCD"},
    {"LiveCD_Screen", "BootType", "Windows2003"},
    {"LiveCD_Screen", "SystemPath", "ramdisk(0)\\reactos"},
    {"LiveCD_Screen", "Options", "/DEBUG /DEBUGPORT=SCREEN /SOS /MININT /RDPATH=livecd.iso /RDEXPORTASCD"},
};

#endif
