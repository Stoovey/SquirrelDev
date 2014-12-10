#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "ServiceBase.h"

class Config : public ServiceBase {

public:
	//ctor / dtor
	Config(){}
	~Config(){}

	//display details
	int winWidth;	
	int winHeight;

	int GetWinWidth() const { return winWidth; }
	void SetWinWidth(int val) { winWidth = val; }
	int GetWinHeight() const { return winHeight; }
	void SetWinHeight(int val) { winHeight = val; } 
};

#endif