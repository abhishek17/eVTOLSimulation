#pragma once
#ifndef COMMON_STRUCTS
#define COMMON_STRUCTS

#include<string>

struct ErrorReport
{
	std::string mErrorMessage;
	bool mDidSucceed; 
};

//Error checking
static	ErrorReport LastErrorReported;

#endif //COMMON_STRUCTS
