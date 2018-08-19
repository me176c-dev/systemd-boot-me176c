/* SPDX-License-Identifier: LGPL-2.1+ */

#include <efi.h>
#include <efilib.h>

#include "util.h"

EFI_STATUS disk_get_part_uuid(EFI_HANDLE *handle, CHAR16 uuid[static 37]) {
        EFI_DEVICE_PATH *device_path;

        /* export the device path this image is started from */
        device_path = DevicePathFromHandle(handle);
        if (device_path) {
                _cleanup_freepool_ EFI_DEVICE_PATH *paths = NULL;
                EFI_DEVICE_PATH *path;

                paths = UnpackDevicePath(device_path);
                for (path = paths; !IsDevicePathEnd(path); path = NextDevicePathNode(path)) {
                        HARDDRIVE_DEVICE_PATH *drive;

                        if (DevicePathType(path) != MEDIA_DEVICE_PATH)
                                continue;
                        if (DevicePathSubType(path) != MEDIA_HARDDRIVE_DP)
                                continue;
                        drive = (HARDDRIVE_DEVICE_PATH *)path;
                        if (drive->SignatureType != SIGNATURE_TYPE_GUID)
                                continue;

                        GuidToString(uuid, (EFI_GUID *)&drive->Signature);
                        return EFI_SUCCESS;
                }
        }

        return EFI_NOT_FOUND;
}

EFI_STATUS disk_find_by_part_uuid(EFI_HANDLE **handle, EFI_GUID *guid) {
        UINTN handle_no;
        _cleanup_freepool_ EFI_HANDLE *handles = NULL;
        EFI_STATUS err = LibLocateHandleByDiskSignature(
                                MBR_TYPE_EFI_PARTITION_TABLE_HEADER, SIGNATURE_TYPE_GUID,
                                guid, &handle_no, &handles);
        if (EFI_ERROR(err))
                return err;

        if (handle_no == 0)
                return EFI_NOT_FOUND;

        *handle = handles[0];
        return EFI_SUCCESS;
}
