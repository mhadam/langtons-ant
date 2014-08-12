#include <iostream>
#include <fstream>

using namespace std;

struct Ant {
	unsigned int vector = 90;
	unsigned long pos = 1152000;
};

int checkAngle();

int main() {
	ofstream outfile ("output.ppm", ofstream::binary);
	
	unsigned char buffer[100] = {};
	
	Ant ant;
	unsigned long long iteration = 0;
	
	// write header info
	outfile << "P3" << endl; // magic number
	outfile << 1920 << " " << 1200 << endl; // dimensions : width : height
	outfile << 255 << endl;
	
	while (iteration < (1920 * 1200)) {
		if (ant.pos % 2 == 0) {
			ant.vector += 90;
		}
		outfile << 
	};
	

	outfile << "255   0   0     0 255   0     0   0 255" << endl;
	outfile << "255 255   0   255 255 255     0   0   0" << endl;
	outfile.close();

	return 0;
}

int checkAngle() {

}
