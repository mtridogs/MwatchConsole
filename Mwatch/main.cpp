#include <Userenv.h>
#include "base.h"
#pragma comment(lib, "Userenv.lib")
DWORD GetProcessIDByName( LPCTSTR szProcessName );
int main(int argc, char* argv[])
{
		if(argc<2)
	{
		printf("��������  ��ʹ��-������.exe��Ϊ���������\n�����˳���\n");
		getchar();
		return 0;
	}
//******************************************************************************
	init_printf();
	HANDLE openprocess;
	HANDLE openthread;
	HANDLE hToken;
	HANDLE thread_process;
	CONTEXT thread_context;
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	THREADENTRY32 th32;
	th32.dwSize = sizeof(THREADENTRY32);
	BOOL bRet;
    LUID luid;
	//argv[1]="chrome.exe";
	char *command_line_T = (char*)malloc(sizeof(char)*strlen(argv[1]));
	strcpy(command_line_T,argv[1]);
	DWORD pid = GetProcessIDByName(command_line_T);
//*****************************
		//if(argv[1]=="N")
		//    pid=(DWORD)argv[2];
//*****************************
	TOKEN_PRIVILEGES tp;
	bool tryup = true;
	DWORD getints;
	char getchars;
	int index_T=0;
	//***************
	vector<DWORD> verc;
	LISTINT list_thread;
	LISTINT::iterator i_list_thread;
	INSTRUCTION inst;
	char *memery_context = (char*)malloc(sizeof(char));
	char *memory_context = (char*)malloc(sizeof(char));
	//******************
	DWORD thread_32[70];
	for(int s=0;s<30;s++)
		thread_32[s]=0;
	int threadindex=0;
	//******************
	//********************************************************************************************
				//if((openthread =OpenThread(THREAD_ALL_ACCESS,FALSE,pid))==NULL)
				//{
				//printf("���ӽ��̳���������룺%d",GetLastError());
				//getchar();
				//return 0;
				//}
	
				if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES, &hToken))
				{
					printf("��Ȩ����,Token�򿪴���\n  ������룺 %d",GetLastError());
					return 0;
				}
				if(!LookupPrivilegeValue(NULL,SE_DEBUG_NAME, &luid))
				{
				printf("��Ȩ����,PrivilegeValue�򿪴���\n  ������룺 %d",GetLastError());
				CloseHandle(hToken);
				return 0;
				}
				tp.PrivilegeCount = 1;
				tp.Privileges[0].Luid = luid;
				if(tryup)
				{
				tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
				}
				else
				{
				tp.Privileges[0].Attributes = 0;
				}

				if(!AdjustTokenPrivileges(hToken,FALSE, &tp, sizeof(tp), NULL, NULL))
				{
				printf("��Ȩʧ�ܣ� �������:%d",GetLastError());
				CloseHandle(hToken);
				return 0;
				}
			//**********************************************************************
				if((openprocess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid))==NULL)
				{
				printf("���󣡽��̸���ʧ�ܣ� �������%d\n",GetLastError());
				printf("�ǵò�Ҫ����SYSTEMȨ�޽��̣�\n");
			    getchar();
				return 0;
				}
				thread_process = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,pid);
				bRet = Process32First(thread_process, &pe32);
				if (thread_process == INVALID_HANDLE_VALUE)
				{
				printf("������Ϣ��ȡʧ�ܣ�\n");
				getchar();
				return 0;
				}
				if (!Thread32First(thread_process, &th32)) 
				{
				printf("�߳���Ϣ��ȡʧ��\n");
				return 0;
				}
				//*******
				do 
				{ 
				if (th32.th32OwnerProcessID == pid) 
				{ 
				list_thread.push_front(th32.th32ThreadID);
				thread_32[threadindex]=th32.th32ThreadID;
				threadindex++;
				} 
				}while(Thread32Next(thread_process, &th32));
				//*******
				printf("******************************\n");
				printf("����������%s\n",command_line_T);
				printf("������PID��%d\n",pid);
				printf("�ý����߳���Ŀ��%d\n",list_thread.size());
				printf("******************************\n");
				printf("�Ƿ���ʾ�����̣߳�Y/N\n");
				scanf("%c",&getchars);
				if(getchars!='Y')
				{
					printf("������ɲ��˳���\n");
					getchar();
					return 0;
				}
				printf("**********************\n");
				printf("   NUM ******* TID     \n");
				threadindex=0;
				for (i_list_thread = list_thread.begin(); i_list_thread != list_thread.end(); ++i_list_thread)
					{
						printf("**%d     |    %ld**\n",threadindex+1,thread_32[threadindex]);
						threadindex++;
					}
				printf("**********************\n\n");

				printf("��������Ҫ�����̣߳�\n");
				scanf("%lu",&getints);
				printf("���ڼ���߳�%d\n",getints);
				if((openthread =OpenThread(THREAD_ALL_ACCESS,FALSE,getints))==NULL)
			{
				
				printf("���ӽ��̳���������룺%d",GetLastError());
				getchar();
				getchar();
				return 0;
			}
			printf("[!]���̸��ӳɹ����������߳��ڴ棡����.....ok\n");
			printf("[!]���ڶ�ȡ�Ĵ���״̬��...................ok\n\n\n");
			thread_context.ContextFlags= CONTEXT_FULL;
			while(1)
			{
		//if(SuspendThread(openthread)==-1)
		//{
		//	printf("�����߳�ʧ�ܣ�������� ��%d",GetLastError());
		//	return 0;
		//}
			if(GetThreadContext(openthread,&thread_context)==0)
			{
			printf("��ȡ������Ϣʧ�ܣ� ������룺%d\n",GetLastError());
			Sleep(1111111);
			getchar();
			return 0;
			}
			ReadProcessMemory(openprocess,(void*)thread_context.Eip,memery_context,32,NULL);
			//*****************************************
			get_instruction(&inst,(BYTE *)memery_context,MODE_32);
			get_instruction_string(&inst,FORMAT_INTEL,0,memory_context,64);
			printf("[*]����״̬\n CPU:  EIP [%x] EAX [%x] EBX [%x] ECX [%x] EDX [%x]\n ",thread_context.Eip,thread_context.Eax,thread_context.Ebx,thread_context.Ecx,thread_context.Edx);
			printf("[*]ESI [%x] EDI [%x] EBP [%x]\n",thread_context.Esi,thread_context.Edi,thread_context.Ebp);
			printf("[*] �����ڴ�״̬��%s\n\n",memory_context);
			printf("[*] �����ڴ�״̬��%x\n\n",memory_context);
			//ResumeThread(openthread);
			Sleep(1000);
			//*****************************************
			}


Sleep(1111111);
	return 0;
}


		DWORD GetProcessIDByName(LPCTSTR szProcessName )
		{
		STARTUPINFO st;
		PROCESS_INFORMATION pi;
		PROCESSENTRY32 ps;  
		HANDLE hSnapshot;
		DWORD dwPID;
		ZeroMemory(&st, sizeof(STARTUPINFO));  
		ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));  
		st.cb = sizeof(STARTUPINFO);  
		ZeroMemory(&ps,sizeof(PROCESSENTRY32));  
		ps.dwSize = sizeof(PROCESSENTRY32);   
		hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0);  
		if(hSnapshot == INVALID_HANDLE_VALUE){  
		return 0;}  
		if(!Process32First(hSnapshot,&ps)){
		return 0;}  
		do{
		if(lstrcmpi(ps.szExeFile,szProcessName)==0)  {  
		dwPID = ps.th32ProcessID;  
		CloseHandle(hSnapshot);  
		return dwPID;}}  
		while(Process32Next(hSnapshot,&ps));
		CloseHandle(hSnapshot);  
		return 0; 
		}