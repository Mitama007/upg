// LogFile.h: interface for the CLogFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFILE_H__6BBF8BC1_76FB_4FE5_B192_C17F6067A068__INCLUDED_)
#define AFX_LOGFILE_H__6BBF8BC1_76FB_4FE5_B192_C17F6067A068__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogFile  
{
private:
	char	m_acFilePath[MAX_PATH];
	//BOOL    LogMsgWrite (char *fmt, ...);
public:
	BOOL LogMsg (char *fmt, ...);	
	BOOL LogMsgData (LPBYTE pData, DWORD dwLen);
public:
	CLogFile();
	virtual ~CLogFile();

};

#endif // !defined(AFX_LOGFILE_H__6BBF8BC1_76FB_4FE5_B192_C17F6067A068__INCLUDED_)
