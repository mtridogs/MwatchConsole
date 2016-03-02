#include "base.h"
void EnableDebugPriv()  
{  

    HANDLE hToken;  
    LUID sedebugnameValue;  
    TOKEN_PRIVILEGES tkp;  
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);  
    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue);  
    tkp.PrivilegeCount = 1;  
    tkp.Privileges[0].Luid = sedebugnameValue;  
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
    AdjustTokenPrivileges(hToken, false, &tkp, sizeof tkp, NULL, NULL);  
    CloseHandle(hToken);  
}
void init_printf()
{
printf("**************************************************************\n");
printf("软件名称：进程检测软件\n");
printf("软件单位：天津理工大学信息安全专业\n");
printf("软件作者：KaiFeng Zhang\n");
printf("软件版本: Alpha\n");
printf("**************************************************************\n");
printf("\n\n\n");
}