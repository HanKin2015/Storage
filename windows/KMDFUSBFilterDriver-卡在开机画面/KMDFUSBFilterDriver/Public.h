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

DEFINE_GUID (GUID_DEVINTERFACE_KMDFUSBFilterDriver,
    0xc7a8bbd1,0x02b0,0x475a,0x82,0x02,0xca,0xd0,0xea,0x9c,0x29,0x6b);
// {c7a8bbd1-02b0-475a-8202-cad0ea9c296b}
