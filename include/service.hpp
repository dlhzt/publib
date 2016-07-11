#ifndef SERVICE_HPP
#define SERVICE_HPP

#include <string>
#include <windows.h>

using namespace std;

class ServiceOperation
{
public:
    ServiceOperation(LPCSTR pSrvName, LPCSTR pSrvDispName):
        m_sSrvName(pSrvName), m_sSrvDispName(pSrvDispName),
        m_schSCManager(NULL), m_schService(NULL),
        m_ssStatusHandle(0){};
    ~ServiceOperation(){};

    bool InstallService(const char* pszPath,
         const char* pszDependcies = NULL,
         const char* pszDescription = NULL);
    bool RemoveService();
    bool StartService();
    bool StopService();
    const char *ShowStatus();
    
    SERVICE_STATUS_HANDLE& GetStatusHandle()
         {return m_ssStatusHandle;};
    bool SendStatusToSCM(DWORD dwCurrentState,
         DWORD dwWin32ExitCode,
         DWORD dwServiceSpecificExitCode,
         DWORD dwCheckPoint,
         WORD dwWaitHint);

private:
    string                 m_sSrvName;
    string                 m_sSrvDispName;
    
    SC_HANDLE              m_schSCManager;
    SC_HANDLE              m_schService;
    SERVICE_STATUS_HANDLE  m_ssStatusHandle;
    SERVICE_STATUS         m_ssStatus;
};


#endif

