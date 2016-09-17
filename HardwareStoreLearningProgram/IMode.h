#pragma once


#define WRONG 0
#define RIGHT 1
#define TIP   2


struct IMode {
	virtual int NextWord() = 0;
	virtual void Reset() = 0;
	virtual void Save() = 0;
};