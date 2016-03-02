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
printf("������ƣ����̼�����\n");
printf("�����λ���������ѧ��Ϣ��ȫרҵ\n");
printf("������ߣ�KaiFeng Zhang\n");
printf("����汾: Alpha\n");
printf("**************************************************************\n");
printf("\n\n\n");
}