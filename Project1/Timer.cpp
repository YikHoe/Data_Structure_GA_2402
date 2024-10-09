#include "Timer.h"


TimeNode::TimeNode(microseconds time) : duration(time), next(nullptr) {}

Timer::Timer() : head(nullptr), counter(0) {}
Timer::~Timer() {
	TimeNode* current = head;
	while (current != nullptr) {
		TimeNode* temp = current;
		current = current->next;
		delete temp;
	}
}

void Timer::insertFront(microseconds time) {
	TimeNode* newNode = new TimeNode(time);
	newNode->next = head;
	head = newNode;
	counter++;
}

int Timer::getCount() {
	return counter;
}

microseconds Timer::getInterval() {
	if (head == nullptr) {
		return microseconds(0);
	}

	return head->duration;
}

void Timer::start() {
	startTime = high_resolution_clock::now();
}

void Timer::stop() {
	stopTime = high_resolution_clock::now();

	microseconds duration = duration_cast<microseconds>(stopTime - startTime);

	insertFront(duration);
}

microseconds Timer::totalTime() {
	if (head == nullptr) {
		return microseconds(0);
	}

	TimeNode* current = head;
	microseconds totalTime(0);

	while (current != nullptr) {
		totalTime += current->duration;
		current = current->next;
	}

	return totalTime;
}

microseconds Timer::averageRunTime() {
	if (head == nullptr) {
		return microseconds(0);
	}

	TimeNode* current = head;
	microseconds total = totalTime();

	return total / counter;
}

microseconds Timer::maxRunTime() {
	if (head == nullptr) {
		return microseconds(0);
	}

	TimeNode* current = head->next;
	microseconds maxTime = head->duration;

	while (current != nullptr) {
		if (current->duration > maxTime) {
			maxTime = current->duration;
		}
		current = current->next;
	}

	return maxTime;
}

microseconds Timer::minRunTime() {
	if (head == nullptr) {
		return microseconds(0);
	}

	TimeNode* current = head->next;
	microseconds minTime = head->duration;

	while (current != nullptr) {
		if (current->duration < minTime) {
			minTime = current->duration;
		}
		current = current->next;
	}

	return minTime;
}