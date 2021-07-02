/*
 * PROJECT:     ReactOS RAMDisk Creator
 * LICENSE:     GPL-2.0-or-later (https://spdx.org/licenses/GPL-2.0-or-later)
 * PURPOSE:     Precompiler
 * COPYRIGHT:   Copyright 2021 Arnav Bhatt (arnavbhatt288@gmail.com)
 */


#include "precomp.h"

static int hDiskVolume = 0;

bool OpenVolume(char* lpszVolumeName)
{
	char RealVolumeName[512];
	
	strcpy(RealVolumeName, lpszVolumeName);
	
	printf("Opening volume %s\n", lpszVolumeName);
	
	hDiskVolume = open(lpszVolumeName, O_RDWR | O_SYNC);
	
	if (hDiskVolume < 0)
	{
		perror("OpenVolume() failed!");
		return false;
	}
	
	return true;
}

void CloseVolume(void)
{
    close(hDiskVolume);
}

bool ReadVolumeSector(long SectorNumber, void* SectorBuffer)
{
	int dwNumberOfBytesRead;
	int dwFilePosition;
	
	dwFilePosition = lseek(hDiskVolume, (SectorNumber* 512), SEEK_SET);
	
	if (dwFilePosition != (SectorNumber * 512))
	{
		perror("ReadVolumeSector() failed!");
		return false;
	}
	
	dwNumberOfBytesRead = read(hDiskVolume, SectorBuffer, 512);
	
	if (dwNumberOfBytesRead != 512)
	{
		perror("ReadVolumeSector() failed!");
		return false;
	}
	
	return true;
}

bool WriteVolumeSector(long SectorNumber, void* SectorBuffer)
{
	int dwNumberOfBytesWritten;
	int dwFilePosition;
	
	dwFilePosition = lseek(hDiskVolume, (SectorNumber * 512), SEEK_SET);
	
	if (dwFilePosition != (SectorNumber * 512))
	{
		perror("WriteVolumeSector() failed!");
		return false;
	}
	
	dwNumberOfBytesWritten = write(hDiskVolume, SectorBuffer, 512);
	
	if (dwNumberOfBytesWritten != 512)
	{
		perror("WriteVolumeSector() failed!");
		return false;
	}
	
	return true;
}
