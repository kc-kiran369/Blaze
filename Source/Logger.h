#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include<Windows.h>
//#include<window>

class Logger
{
	//HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	template<typename... Args>
	static void Info(const char* message, Args... args)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("[Info]\t");
		printf(message, args...);
		printf("\n");
	}

	template<typename... Args>
	static void Warn(const char* message, Args... args)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		printf("[Warn]\t");
		printf(message, args...);
		printf("\n");
	}

	template<typename... Args>
	static void Error(const char* message, Args... args)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("[Error]\t");
		printf(message, args...);
		printf("\n");
	}
};
#endif