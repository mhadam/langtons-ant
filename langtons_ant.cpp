#include <iostream>
#include <utility>
#include "lodepng.h"

using namespace std;

struct Ant {
	int vector = 90; // face north
	int x = 0;
	int y = 0;
};

int checkAngle();
void encodeOneStep(const char*, vector<unsigned char>&, int, int);
int iterateAnt(vector<unsigned char>&, Ant&);
int createBox(int, int, int, int, int, int, vector<unsigned char>&);

int main() {
	// create an ant!! play god, you are the master of l'univers
	Ant ant;
	
	// create image
	vector<unsigned char> image;
	int height = 1200; int width = 1920;
	image.resize(height * width * 4);
	
	ant.x = width / 2 - 1;
	ant.y = height / 2 - 1;
	cout << ant.x << " " << ant.y << endl;
	
	iterateAnt(image, ant);
	createBox(0, width/2-1, 0, height/2-1, 1920, 1080, image);
	createBox(width/2-1, width, height/2-1, height, 1920, 1080, image);
	
	/*for (int y = 0; y < height; y++)
	for (int x = 0; x < width; x++) {
		image[4 * width * y + x * 4 + 0] = 100;
    	image[4 * width * y + x * 4 + 1] = 50;
    	image[4 * width * y + x * 4 + 2] = 50;
    	image[4 * width * y + x * 4 + 3] = 255;
	}*/
	
	encodeOneStep("test.png", image, width, height);
	
	//Ant ant;
	// long long iteration = 0;
	
	/*// write header info
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
	*/
	return 0;
}

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, int width, int height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

int checkAngle() {

	return 0;
}

int iterateAnt(vector<unsigned char>& image, Ant& ant) {
	
	return 0;
}

int createBox(int x1, int x2, int y1, int y2, int width, int height, vector<unsigned char>& image) {
	for (int x = x1; x < x2; x++){
	for (int y = y1; y < y2; y++) {
		if (true) {
			image[4 * width * y + 4 * x + 0] = 100;
    		image[4 * width * y + 4 * x + 1] = 50;
    		image[4 * width * y + 4 * x + 2] = 50;
    		image[4 * width * y + 4 * x + 3] = 255;
    	}
	}
	}
	return 0;
}
