/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_KMDFUSBDriver,
    0x696ab136,0x33be,0x47b8,0x9d,0xb3,0x65,0xa3,0x51,0x4a,0x8c,0x89);
// {696ab136-33be-47b8-9db3-65a3514a8c89}
