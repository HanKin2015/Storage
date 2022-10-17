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

DEFINE_GUID (GUID_DEVINTERFACE_DefaultKMDFDriver,
    0x95efe352,0x49ee,0x4397,0x95,0xf1,0x44,0x32,0xb9,0x8e,0x2d,0x66);
// {95efe352-49ee-4397-95f1-4432b98e2d66}
