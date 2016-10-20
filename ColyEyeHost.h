#pragma once

#include <string>

typedef struct {
	std::string boat_name;
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

	BOOL  Load();
	BOOL  SetWatchTime(DWORD begining, DWORD span);
	BOOL  SetBoatName(std::string name);
};

