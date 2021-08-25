#include <iostream>
#include <string>
#include <string.h>
using namespace std;

int Test1()
{
        const char *vmInfo = "<DesktopPolicy EnableVirPrint=\"0\" EnableUSBWrite=\"0\" EnableVideoRedirect=\"1\" EnableFolderRedirect=\"1\">\n"
                "<!-- diskmap policy -->\n"
                    "<User><![CDATA[sangfor]]></User>\n"
                        "<XML><![CDATA[<DiskMapConf LocalDiskRight=\"3\" USBCDRight=\"2\"/>]]></XML>\n"
                            "</DesktopPolicy>";

            
            const char *pos = strstr(vmInfo, "<![CDATA[");
                cout << pos << endl;
                    return 0;
}

int main()
{
        Test1();
            return 0;
}
