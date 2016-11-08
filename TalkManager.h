#pragma once
class CCamera;

class CTalkManager
{
public:
	CTalkManager();
	CTalkManager(CCamera *mpDev)
	{
		this->mpDev = mpDev;
	};
	~CTalkManager();
public:
	void Start();
	void Over();
	void Stop();
protected:
	CCamera *mpDev;
};

