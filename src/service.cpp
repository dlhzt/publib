#include "Service.hpp"

bool ServiceOperation::InstallService(const char* pszPath,
    const char* pszDependcies,
    const char* pszDescription)
{
    bool        bInstalled = false;

    m_schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(m_schSCManager != NULL)
    {
        m_schService = CreateService(m_schSCManager,
                m_sSrvName.c_str(),
                m_sSrvDispName.c_str(),
                SERVICE_ALL_ACCESS,
                SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
                SERVICE_AUTO_START,
                SERVICE_ERROR_NORMAL,
                pszPath,
                NULL,
                NULL,
                pszDependcies,
                NULL,
                NULL);
        if(m_schService != NULL)
        {
            if(pszDescription != NULL)
            {
                SERVICE_DESCRIPTION sdDescription;
                sdDescription.lpDescription = (char *)pszDescription;
                ChangeServiceConfig2(m_schService,
                                SERVICE_CONFIG_DESCRIPTION,
                                (LPVOID)&sdDescription
                );
            }
            CloseServiceHandle(m_schService);
            CloseServiceHandle(m_schSCManager);
            bInstalled = true;
        }
        else
        {
            CloseServiceHandle(m_schSCManager);
        }
    }
    
    return bInstalled;
}

bool ServiceOperation::RemoveService()
{
    bool              bRemoved = false;

    m_schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(m_schSCManager != NULL)
    {
        m_schService = OpenService(m_schSCManager, m_sSrvName.c_str(), SERVICE_ALL_ACCESS);
        if(m_schService != NULL)
        {
            QueryServiceStatus(m_schService, &m_ssStatus);
            if(m_ssStatus.dwCurrentState == SERVICE_RUNNING)
            {
                if(ControlService(m_schService, SERVICE_CONTROL_STOP, &m_ssStatus))
                {
                    Sleep(1000);
                
                    while(QueryServiceStatus(m_schService, &m_ssStatus))
                    {
                        if(m_ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
                            Sleep(1000);
                        else
                            break;
                    }
                }
            }

            if(m_ssStatus.dwCurrentState == SERVICE_STOPPED)
            {
                 if(DeleteService(m_schService) != 0)
                      bRemoved = true;
            }
        }
        CloseServiceHandle(m_schService);
    }
    CloseServiceHandle(m_schSCManager);

    return bRemoved;
}

bool ServiceOperation::StartService()
{
    bool              bStarted = false;

    m_schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(m_schSCManager != NULL)
    {
        m_schService = OpenService(m_schSCManager, m_sSrvName.c_str(), SERVICE_ALL_ACCESS);
        if(m_schService != NULL)
        {
            if(QueryServiceStatus(m_schService, &m_ssStatus))
            {
                if(m_ssStatus.dwCurrentState == SERVICE_RUNNING)
                    bStarted = true;
            }

            if(!bStarted)
            {
                if(::StartService(m_schService, 0, NULL) != 0)
                {
                    Sleep(1000);
                    
                    while(QueryServiceStatus(m_schService, &m_ssStatus))
                    {
                        if(m_ssStatus.dwCurrentState == SERVICE_START_PENDING)
                            Sleep( 1000 );
                        else
                            break;
                    }
    
                    if(m_ssStatus.dwCurrentState == SERVICE_RUNNING)
                        bStarted = true;
                }
            }
        }
        CloseServiceHandle(m_schService);
    }
    CloseServiceHandle(m_schSCManager);

    return bStarted;                    
}

bool ServiceOperation::StopService()
{
    bool              bStoped = false;

    m_schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(m_schSCManager != NULL)
    {
        m_schService = OpenService(m_schSCManager, m_sSrvName.c_str(), SERVICE_ALL_ACCESS);
        if(m_schService != NULL)
        {
            if(QueryServiceStatus(m_schService, &m_ssStatus))
            {
                if(m_ssStatus.dwCurrentState == SERVICE_STOPPED)
                    bStoped = true;
            }
            
            if(!bStoped)
            {
                if(ControlService(m_schService, SERVICE_CONTROL_STOP, &m_ssStatus))
                {
                    Sleep(1000);
                    
                    while(QueryServiceStatus(m_schService, &m_ssStatus))
                    {
                        if(m_ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
                            Sleep( 1000 );
                        else
                            break;
                    }
    
                    if(m_ssStatus.dwCurrentState == SERVICE_STOPPED)
                            bStoped = true;
                }
            }
        }
        CloseServiceHandle(m_schService);
    }
    CloseServiceHandle(m_schSCManager);

    return bStoped;
}

bool ServiceOperation::SendStatusToSCM(DWORD dwCurrentState,
     DWORD dwWin32ExitCode,
     DWORD dwServiceSpecificExitCode,
     DWORD dwCheckPoint,
     WORD dwWaitHint)
{
    bool bSuccess = false;
   
    if(m_ssStatusHandle == (SERVICE_STATUS_HANDLE)0)
    {
        return bSuccess;
    }

    m_ssStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_ssStatus.dwCurrentState = dwCurrentState;
    
    // If in the process of doing something, then accept
    // no control events, else accept anything
    if (dwCurrentState == SERVICE_START_PENDING)
        m_ssStatus.dwControlsAccepted = 0;
    else
        m_ssStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    
    // if a specific exit code is defined, set up
    // the win32 exit code properly
    if (dwServiceSpecificExitCode == 0)
        m_ssStatus.dwWin32ExitCode = dwWin32ExitCode;
    else
        m_ssStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
    m_ssStatus.dwServiceSpecificExitCode = dwServiceSpecificExitCode;
    
    m_ssStatus.dwCheckPoint = dwCheckPoint;
    m_ssStatus.dwWaitHint = dwWaitHint;
    
    // Pass the status record to the SCM
    bSuccess = SetServiceStatus(m_ssStatusHandle, &m_ssStatus);
    
    return bSuccess;
}

const char* ServiceOperation::ShowStatus()
{
	bool   bStoped = false;
	string strStatus;

    m_schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if(m_schSCManager != NULL)
    {
        m_schService = OpenService(m_schSCManager, m_sSrvName.c_str(), SERVICE_ALL_ACCESS);
        if(m_schService != NULL)
        {
            if(QueryServiceStatus(m_schService, &m_ssStatus))
            {
                if(m_ssStatus.dwCurrentState == SERVICE_STOPPED)
                    bStoped = true;
            }
            
            if(bStoped)
            	strStatus = m_sSrvName + " is stoped.";
            else
            	strStatus = m_sSrvName + " is running.";
            	
        }
        CloseServiceHandle(m_schService);
    }
    CloseServiceHandle(m_schSCManager);

	return strStatus.c_str();
}
