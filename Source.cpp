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
	DWORD bytereq = 0;
	wchar_t chprocessname[MAX_PATH] = L"unkonwn";
	wchar_t chprocesspath[MAX_PATH] = L"unkonwn";
	hprocess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processid);
	if (NULL != hprocess)
	{
		benumprocessmodule = EnumProcessModulesEx(hprocess, &hmod, sizeof(hmod), &bytereq, LIST_MODULES_ALL);
		if (benumprocessmodule == TRUE)
		{
			GetModuleBaseName(hprocess, hmod, chprocessname, sizeof(chprocessname) / sizeof(wchar_t));
			GetModuleFileNameEx(hprocess, hmod, chprocesspath, sizeof(chprocesspath) / sizeof(wchar_t));
		}
	}

	wcout << "modulebasename:" << chprocessname << endl;
	wcout << "process path:" << chprocesspath << endl;
	wcout << "process id:" << processid << endl;
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
	for (size_t i = 0; i < totalprocess; i++)
	{
		listallprocessname(process1[i]);
	}

}