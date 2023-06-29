// LogFile.cpp: implementation of the CLogFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "../include/Oki/LogFile.h"
#include "stdio.h"
#include "yhUsbFilter.h"
#include "Windows.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogFile::CLogFile()
{
	char *p = 0;
	::GetModuleFileName (theApp.m_hInstance, m_acFilePath, sizeof (m_acFilePath));
	for (p = m_acFilePath + lstrlen (m_acFilePath); *(p - 1) != '.'; p--);
	lstrcpy (p, "txt");
}

CLogFile::~CLogFile()
{
}
#if 0
BOOL CLogFile::LogMsgWrite (char *fmt, ...)
{
  va_list	ap_list;
    FILE	*fp = NULL;

    va_start(ap_list,fmt);

    fp = fopen ("c:\\UsbFilter.txt", "at+");
    if (fp != NULL) 
    {
	/*	fseek (fp, 0, SEEK_END);

		vsprintf (m_acTextBuf, fmt, ap_list);
		fwrite (m_acTextBuf, 1, lstrlen (m_acTextBuf), fp);
		

        vfprintf(fp, fmt, ap_list);

		va_list	argp;

		va_start (argp, pacMsg);
		sprintf (acTextBuf, "DEBUG[%s][%s][%s][%s][%d]:", GetTimeInfo (acTmInfo), pacModName, pacFunName, pacType, iLineInfo);
		vsprintf (acTextBuf + strlen (acTextBuf), pacMsg, argp);
		va_end (argp);

		LogOutput (acTextBuf);
		*/



        fclose(fp);
    }
    va_end(ap_list);	
    
    return TRUE;
}
#endif
BOOL CLogFile::LogMsg (char *fmt, ...)
{
	va_list	ap_list;
    FILE	*fp = NULL;

    va_start(ap_list,fmt);

    fp = fopen (m_acFilePath, "at+");
    if (fp != NULL) 
    {
		vfprintf(fp, fmt, ap_list);
        fclose(fp);
    }
    va_end(ap_list);	
    
    return TRUE;
}

BOOL CLogFile::LogMsgData (LPBYTE pData, DWORD dwLen)
{
	TCHAR *pstrMsg = new TCHAR[dwLen * 5];
	TCHAR *pMove   = pstrMsg;

	if (dwLen > 0)
	{
		for (DWORD dw = 0; dw < dwLen; )
		{
			sprintf (pMove, "%02x,", pData[dw]);
			
			pMove += 3;
			if (++dw % 20 == 0)
			{
				sprintf (pMove, "\n");
				pMove += 1;
			}
		}
		if (lstrlen(pstrMsg) > 0)
		{
			if (pstrMsg[lstrlen(pstrMsg) - 1] != '\n')
				sprintf (pMove, "\n");
		}

		BOOL bRet = LogMsg (pstrMsg);
		delete []pstrMsg;

		return bRet;
	}
	return FALSE;
}