/********************************************************
Copyright (C),  2016-2018,
FileName:		AutoStart
Author:        	woniu201
Email:         	wangpengfei.201@163.com
Created:       	2019/05/05
Description:	开机自启动
********************************************************/
#pragma execution_character_set("utf-8")
#include <windows.h>

/************************************
@ Brief:		判断是否开机自启动
@ Author:		woniu201 
@ Created:		2019/05/05
@ Return:            
************************************/
bool IsAutoStart()
{
	HKEY hKey;
	char value[1024] = { 0 };
	int ret = RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_EXECUTE, &hKey);
	if (ret != ERROR_SUCCESS)
	{
		return false;
	}

	//读取KEY
	DWORD dwType = REG_SZ; //数据类型
	DWORD cbData = 256;
	ret = RegQueryValueExA(hKey, "AlarmClock", NULL, &dwType, (LPBYTE)value, &cbData);
	if (ret == ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		if (strlen(value) == 0)
		{
			return true;
		}
	}
	else
	{
		RegCloseKey(hKey);
		return false;
	}
}

/************************************
@ Brief:		设置开机自启动
@ Author:		woniu201 
@ Created:		2019/05/05
@ Return:            
************************************/
bool SetAutoStart()
{
	HKEY hKey;
	DWORD dwDisp;
	DWORD dwType = REG_SZ; //数据类型

	int ret = RegCreateKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp);
	if (ret != ERROR_SUCCESS)
	{
		return false;
	}

	char path[1024] = { 0 };
	char pBuf[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, path);
	strcpy(path + strlen(path), "\\AlarmClock.exe");

	ret = RegSetValueExA(hKey, "AlarmClock", 0, dwType, (BYTE*)path, strlen(path));
	if (ret != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return false;
	}
	RegCloseKey(hKey);
	return true;
}