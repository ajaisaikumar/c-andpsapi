#include<windows.h>
#include<psapi.h>
#include<iostream>
#include<wchar.h>

using namespace std;
void listallprocessname(DWORD processid)
{
	HANDLE hprocess;
	BOOL benumprocessmodule=FALSE;
	HMODULE hmod;
	PROCESS_MEMORY_COUNTERS pmc;
	DWORD bytereq = 0;
	MODULEINFO info={};
	DWORD bp = sizeof(info);
	wchar_t processname[MAX_PATH] = L"unkonwn";
	wchar_t processpath[MAX_PATH] = L"unkonwn";
	hprocess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ|PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processid);
	if (NULL == hprocess)
	{
		return;
	}
	
	if (NULL != hprocess)
	{
		benumprocessmodule = EnumProcessModulesEx(hprocess, &hmod, sizeof(hmod), &bytereq, LIST_MODULES_ALL);
		if (benumprocessmodule == TRUE)
		{
			GetModuleBaseName(hprocess, hmod, processname, sizeof(processname) / sizeof(wchar_t));
			GetModuleFileNameEx(hprocess, hmod, processpath, sizeof(processpath) / sizeof(wchar_t));
			GetModuleInformation(hprocess, hmod, &info, bp);
			
		}
	
	}
	
	wcout << "modulebasename:" << processname << endl;
	wcout << "process path:" << processpath << endl;
	wcout << "load address of the module:" << info.lpBaseOfDll << endl;
	wcout << "entry point of the module:" << info.EntryPoint << endl;
	
    if (GetProcessMemoryInfo(hprocess, &pmc, sizeof(pmc)))
	{
		
		wcout << "pagefileusage:" << pmc.PagefileUsage << endl;
		wcout << "pagefaultcount:" << pmc.PageFaultCount << endl;
	}
	
	wcout << "process id:" << processid << endl;
	wcout << "===================================================================================" << endl;
	CloseHandle(hprocess);
}

int main()
{
	DWORD process1[2048] = { 0 };
	BOOL benumprocess = FALSE;
	DWORD bytesreq = 0;
	DWORD totalprocess = 0;
	
	benumprocess = EnumProcesses(process1, sizeof(process1), &bytesreq );

	if (benumprocess == FALSE)
	{
		wcout << "failed" << endl;
	}
	totalprocess = bytesreq/ sizeof(DWORD);
	
	
	wcout << "total number of processes:" << totalprocess<<endl;
	wcout << "============================================================================" << endl;
	for (size_t i = 0; i < totalprocess; i++)
	{
		listallprocessname(process1[i]);
	}

}
