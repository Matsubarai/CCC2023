#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void view_block_data(int data[], int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << std::setw(6) << std::left << data[i*width + j];
		}
		cout << std::endl;
	}
}

int main(int argc, char** argv) {
	if (argc != 4) {
		cout << "Usage: ./view_block_data [FILENAME] [WIDTH] [HEIGHT]" << std::endl;
	}
	else {
		string filename(argv[1]);
		int width = stoi(argv[2]);
		int height = stoi(argv[3]);

		ifstream infile;
		int* data = new int[width*height];
		infile.open(filename);

		for (int i = 0; i < width * height; i++) {
			string num;
			getline(infile, num);
			data[i] = stoi(num);
		}

		view_block_data(data, width, height);
	}

	return 0;
}
