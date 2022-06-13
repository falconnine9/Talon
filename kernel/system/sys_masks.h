#ifndef _SYS_MASKS_H
#define _SYS_MASKS_H 1

#include "sys.h"

void sysmask_getkey();

void sysmask_putc();
void sysmask_getvgacur();
void sysmask_setvgacur();

void sysmask_malloc();
void sysmask_mfree();

void sysmask_getpit();
void sysmask_getdatetime();
void sysmask_setdatetime();

void sysmask_alert();
void sysmask_setalert();

#endif