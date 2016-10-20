#pragma once

typedef struct {
	CString boat_name;
	DWORD   watch_time_begining;
	DWORD   watch_time_span;
}HostConfiguration;

class ColyEyeHost
{
public:
	ColyEyeHost();
	~ColyEyeHost();

public:
	HostConfiguration mConfuration;
};

