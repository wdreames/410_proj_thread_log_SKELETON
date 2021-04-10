//============================================================================
// Name        : 410_proj_thread_log.cpp
// Author      : William Reames
// Version     : 2021.04.09
//============================================================================
#include <thread>
#include <iostream>
#include <vector>
#include "../includes/constants.h"
#include "../includes/Logger.h"

using namespace std;

//Declare globals
bool bDoWork = true;
Logger logConsole(LOG_CONSOLE);
Logger logFile(LOG_FILE);

/***
 * Log info to both file and console. You can do this with 2 Logger objects.
 * 		Note:  These logger objects cannot be local variables, they must be shared 
 * 		amongst the threads. (why?)
 * This function should run until main (or another thread) asks it to quit
 * @param info  to log
 * returns void
 */
void fun(string info) {
	while (bDoWork) {
		//Log to console and file
		logConsole.Log(info);
		logFile.Log(info);
	}
}
int main() {

	//Start as many threads as you have cores (see std::thread::hardware_concurrency())
	int numCores = thread::hardware_concurrency();

	//Save these threads in a vector
	vector<thread> threads;
	for (int i = 0; i < numCores; i++) {
		string inputStr = "Testing thread logging (" + to_string(i) + ")";
		threads.push_back(thread(fun, inputStr));
	}

	//Let threads run a bit (5 seconds)
	this_thread::sleep_for(chrono::milliseconds(5000));

	//Ask them all to stop
	bDoWork = false;

	//Wait for all threads to finish
	for (auto &t : threads) {
		t.join();
	}

	cout << "All threads done!" << endl;

	return 0;
}
