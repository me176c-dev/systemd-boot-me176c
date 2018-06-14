/* SPDX-License-Identifier: LGPL-2.1+ */
/*
 * Copyright © 2015 Kay Sievers <kay@vrfy.org>
 */

#ifndef __SDBOOT_PEFILE_H
#define __SDBOOT_PEFILE_H

EFI_STATUS pe_memory_locate_sections(CHAR8 *base,
                                     CHAR8 **sections, UINTN *addrs, UINTN *offsets, UINTN *sizes);
EFI_STATUS pe_file_locate_sections(EFI_FILE *dir, CHAR16 *path,
                                   CHAR8 **sections, UINTN *addrs, UINTN *offsets, UINTN *sizes);
#endif
