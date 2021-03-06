#include <iostream>
#include <conio.h>
#include <fstream>
#include <time.h>

using namespace std;

inline bool file_exists(std::string& name);

int main() {

	string labels[] = {"Okay", "Alright" };
	int numLabels = 2;

	char keys[] = { '1','2','3','4','5','6','7','8','9' };
	int numKeys = 9;
	char exit = '0';
	char pause = '-';

	char input = ' ';

	int counts[9]; // To be the same number of elements as keys
	for (int i = 0; i < numKeys; i++) {
		counts[i] = 0;
	}

	char date[9];
	_strdate_s(date);

	bool Timer = false;
	bool isPaused = false;
	time_t startTime, endTime, startPause, endPause, totalPause;

	totalPause = 0;

	string filename = "Stats.txt";
	std::ofstream outfile;

	if (file_exists(filename)) {
		outfile.open("Stats.txt", std::ios_base::app);
	}
	else {
		outfile.open("Stats.txt", std::ios_base::app);
		outfile << "Date,Duration";
		for (int i = 0; i < numLabels; i++) {
			outfile << "," << labels[i].c_str();
		}
		outfile << endl;
	}
	
	while (input != exit) {
		input = _getch();

		for (int i = 0; i < numLabels; i++) {
			if (input == keys[i]) {
				if (!Timer) {
					startTime = time(NULL);
					Timer = true;
				}
				counts[i]++;
				cout << "Running Total for " << labels[i].c_str() << ": " << counts[i] << endl;
				if (isPaused) {
					endPause = time(NULL);
					totalPause += (endPause - startPause);
					isPaused = false;
					cout << "Unpaused with " << totalPause << " total seconds paused." << endl;
				}
			}
			else if (Timer && !isPaused && input == pause) {
				isPaused = true;
				startPause = time(NULL);
				cout << "Paused. . ." << endl;
			}
		}
	}

	endTime = time(NULL);

	outfile << date << "," << ((endTime-startTime) - totalPause);
	for (int i = 0; i < numLabels; i++) {
		outfile << "," << counts[i];
	}
	outfile << endl;
	outfile.close();
	return 0;
}

inline bool file_exists(std::string& name) {
	ifstream f(name.c_str());
	return f.good();
}