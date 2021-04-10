/*
 * Logger.cpp
 *
 *  Created on: Apr 09, 2021
 *      Author: William Reames
 */
#include <iostream>
#include "../includes/Logger.h"
using namespace std;

/***
 * creates a logger object, if lt=FILE then log to the file given by fn
 * if lt=LOG_CONSOLE the send log info to console via cout
 * @param lt either LOG_FILE or LOG_CONSOLE
 * @param fn if above is LOG_FILE then this is where info logged to
 *           otherwise it is not used
 */
Logger::Logger(LOG_TYPE lt, std::string fn) {
	this->lt = lt;
	if (lt == LOG_FILE) {
		this->fn = fn;
		this->fs.open(fn);
	}
}

/***
 * Information to log, either to a file or to console
 * @param info to log
 */
void Logger::Log(std::string info) {
	if (lt == LOG_FILE) {
		{
			lock_guard<mutex> lck(mtx);
			fs << info << endl;
		}
	} else {
		{
			lock_guard<mutex> lck(mtx);
			cout << info << endl;
		}
	}
}

/***
 * close any open streams
 */
Logger::~Logger() {
	if (fs.is_open()) {
		fs.close();
	}
}
