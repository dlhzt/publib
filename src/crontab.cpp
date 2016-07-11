//=============================================================================
// File:          crontab.cpp
// Author:        Zhaojunwei
// CreateTime:    2005/04/19
// Descripiton:   Implementation file for invoking a procdure in crontab format.
//                Notice: this class is a virtual base class, which could not
//                be instanced without subclassing.
// ----------------------------------------------------------------------------
// Version:
//         2005/04/19   1.0 First work release.
//=============================================================================

#include "crontab.hpp"

Crontab::Crontab(const string& strFmt, const string& strTag, const string& strCmd) :
	m_strTag(strTag), m_strCmd(strCmd), m_status(IDLE), m_lifecycle(0, 0)
{
	if(!Resolv(strFmt))
		throw runtime_error("Error in resolving crontab time setting!");
}

bool Crontab::Check(uint uMinute, uint uHour, uint uDay, uint uMonth, uint uWeek) const
{
	if( m_minutes.find(uMinute) != m_minutes.end() &&
		m_hours.find(uHour)  != m_hours.end() &&
		m_days.find(uDay) != m_days.end() &&
		m_months.find(uMonth) != m_months.end() &&
		m_weeks.find(uWeek) != m_weeks.end())
	{
		return true;
	}
	
	return false;
}

bool Crontab::Resolv(const string& strFmt)
{
	string str = strFmt;
	string::size_type pos1;
	bool bMin, bHour, bDay, bMonth, bWeek;
	
	if((pos1 = str.find(' ')) != string::npos)
		bMin = MakeTime(m_minutes, str.substr(0, pos1), 0, 59);
	else
		bMin = false;
	str = str.substr(pos1+1);
	if((pos1 = str.find(' ')) != string::npos)
		bHour = MakeTime(m_hours, str.substr(0, pos1), 0, 23);
	else
		bHour = false;
	str = str.substr(pos1+1);
	if((pos1 = str.find(' ')) != string::npos)
		bDay = MakeTime(m_days, str.substr(0, pos1), 1, 31);
	else
		bDay = false;
	str = str.substr(pos1+1);
	if((pos1 = str.find(' ')) != string::npos)
		bMonth = MakeTime(m_months, str.substr(0, pos1), 0, 11);
	else
		bMonth = false;
	str = str.substr(pos1+1);
	bWeek = MakeTime(m_weeks, str, 0, 6);
	
	return (bMin && bHour && bDay && bMonth && bWeek);
}

bool Crontab::MakeTime(set<uint>& scope, const string& strSetting, uint uMin, uint uMax)
{
	if(strSetting.length() < 1)
		return false;
	scope.clear();	
	if(strSetting == "*")
	{
		for(uint i=uMin; i <= uMax; ++i)
			scope.insert(i);
	}
	else
	{
		string::size_type pos;
		string str = strSetting;
		for(;;)
		{
			if((pos = str.find(',')) != string::npos)
			{
				scope.insert(atoi(str.substr(0, pos).c_str()));
				str = str.substr(pos + 1);
			}
			else
			{
				break;
			}
		}
		scope.insert(atoi(str.c_str()));
	}
		
	return true;
}
