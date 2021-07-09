/*
 * PROJECT:     ReactOS FreeLoader installer for Linux
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     ini.h file
 * COPYRIGHT:   Copyright 2019 Arnav Bhatt (arnavbhatt2004@gmail.com)
 */

#ifndef INI_H
#define INI_H

#include "bool.h"

bool CreateINI(char *pacPath, char *pacTopic, char *pacItem, char *pacValue);

#endif