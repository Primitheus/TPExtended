#pragma once
#include "includes.h"
#include "scanner.h"
#include "memory.h"

class Patch
{
private:
	bool active;
	DWORD address;
	std::string enabled, disabled;

public:
	Patch(DWORD address, std::string enabled, std::string disabled);
	void toggle();
};

class TPEXTENDED
{
private:
	bool initialized = false;
	DWORD Multiclient;
	DWORD WindowOpts;
	DWORD WinParams_Base;
	DWORD WinH;
	DWORD WinW;
	DWORD MouseFix;
	DWORD RemoveFPSLimit1;
	DWORD RemoveFPSLimit2;
	DWORD RemoveFPSLimit3;

public:
	void Init(bool isMulticlient, int width, int height);

};
