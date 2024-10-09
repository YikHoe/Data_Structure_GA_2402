#pragma once
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;


struct TimeNode
{
	microseconds duration;
	TimeNode* next;

	TimeNode(microseconds time);
};

class Timer {
private:
	TimeNode* head;
	time_point<high_resolution_clock> startTime, stopTime;
	int counter;

public:
	Timer();
	~Timer();
	void insertFront(microseconds time);
	int getCount();
	microseconds getInterval();

	// timer operations
	void start();
	void stop();

	// calculation operations
	microseconds totalTime();
	microseconds averageRunTime();
	microseconds maxRunTime();
	microseconds minRunTime();


};