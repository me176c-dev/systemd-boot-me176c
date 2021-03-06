/* SPDX-License-Identifier: LGPL-2.1+ */
#pragma once

EFI_STATUS disk_get_part_uuid(EFI_HANDLE *handle, CHAR16 uuid[static 37]);
EFI_STATUS disk_find_by_part_uuid(EFI_HANDLE **handle, EFI_GUID *guid);
