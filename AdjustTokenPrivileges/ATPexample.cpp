// Code here made by 64/sixtyfour64-tech
// Give credits if you intend to use it or rewrite this

#include <Windows.h>

BOOL
WINAPI
SetPrivilege(
	_In_ HANDLE hPrivilegeToken,
	_In_ LPCTSTR lpctPrivilege,
	_In_ BOOL bEnablePrivilege
)
{
	LUID luidPrivilege;
	TOKEN_PRIVILEGES tokenPrivileges;

	if (!LookupPrivilegeValue(NULL, lpctPrivilege, &luidPrivilege))
	{
		return FALSE;
	}

	tokenPrivileges.PrivilegeCount = 1;
	tokenPrivileges.Privileges[0].Luid = luidPrivilege;
	tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if (!AdjustTokenPrivileges(hPrivilegeToken, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL))
	{
		return FALSE;
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		return FALSE;
	}

	return TRUE;
}

INT
WINAPI
wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpwCmdLine,
	_In_ INT nShowCmd
)
{
	HANDLE hPrivilegeToken;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hPrivilegeToken))
	{
		MessageBoxW(NULL, L"Failed to open process token", L"Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	if (!SetPrivilege(hPrivilegeToken, SE_DEBUG_NAME, TRUE)) // SeDebugPrivilege 2 :fire:
	{
		MessageBoxW(NULL, L"Failed to enable privilege", L"Error", MB_OK | MB_ICONERROR);
		CloseHandle(hPrivilegeToken);
		ExitProcess(0);
	}

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED) 
	{
		return FALSE;
	}

	MessageBoxW(NULL, L"Privilege has been enabled", L"Success", MB_OK | MB_ICONINFORMATION);
	CloseHandle(hPrivilegeToken);
	return FALSE;
}