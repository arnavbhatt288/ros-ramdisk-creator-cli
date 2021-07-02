/*
 * PROJECT:     ReactOS RAMDisk Creator
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Precompiler
 * COPYRIGHT:   Copyright 2021 Arnav Bhatt (arnavbhatt288@gmail.com)
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "volume.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
