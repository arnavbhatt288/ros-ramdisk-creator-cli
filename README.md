# ReactOS RAMDisk Creator

## About:
A program written in C for creating RAMDisks of ReactOS for Windows and Linux.
This helps you installing the bootsector as well as creating freeldr.ini file.

## Compiling:
Use provided makefile to compile the program. There is a precompiled version for Windows.

## Usage:
### For installing bootsector:
Before using this tool, your drive's partition table must be set on "loop". Otherwise it may fail.

Linux: `./ramdisk-creator -d /dev/sd[x] -f [fs]`
Windows `ramdisk-creator.exe -d [drive_letter] -f [fs]`

### For creating freeldr.ini:
`./ramdisk-creator -d -i freeldr.ini -b -l`
Either choose `-b` for bootcd or `-l` for livecd or both.

Copyright Arnav Bhatt 2021.
