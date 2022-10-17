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

DEFINE_GUID (GUID_DEVINTERFACE_DefaultKMDFUSBDriver,
    0xbbee4a5a,0xe407,0x446e,0x97,0xb0,0xe2,0xe2,0x99,0x1b,0xa7,0xef);
// {bbee4a5a-e407-446e-97b0-e2e2991ba7ef}
