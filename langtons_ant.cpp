#include <iostream>
#include <utility>
#include "lodepng.h"

using namespace std;

struct Ant {
	int vector = 90; // face north
	int x = 0;
	int y = 0;
};

void HSVtoRGB(int, int, int);

void decodeOneStep(const char*, vector<unsigned char>&, unsigned int&, unsigned int&);
void encodeOneStep(const char*, vector<unsigned char>&, int, int);

int generateColor();

int workAnt(vector<unsigned char>&, int, int, Ant&);
int moveAnt(Ant&);
int trapAnt(Ant&, int, int);

int createBox(int, int, int, int, int, int, vector<unsigned char>&);

int main() {
	// create an ant!! play god, you are the master of l'univers
	Ant ant;
	
	// create image
	vector<unsigned char> image;
	unsigned int height = 0; unsigned int width = 0; // image properties
	
	decodeOneStep("test1.png", image, width, height);
	cout << "Decoded!" << endl; // success loading image
	cout << "Width: " << width << endl;
	cout << "Height: " << height << endl;
	
	image.resize(height * width * 4);
	
	ant.x = width / 2 - 1;
	ant.y = height / 2 - 1;
	cout << ant.x << " " << ant.y << endl;
	
	//createBox(0, width, 0, height, 1920, 1200, image);
	
	vector<int> colors = {};
	
	colors.append(rand());
	
	for (long long i = 0; i < 100000000; i++) {
		workAnt(image, width, height, ant);
		moveAnt(ant);
		trapAnt(ant, width, height);
		colors.append() = generateColor(colors.end());
	}
	
	//createBox(0, width/2-1, 0, height/2-1, 1920, 1080, image);
	//createBox(width/2-1, width, height/2-1, height, 1920, 1080, image);
	
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

void decodeOneStep(const char* filename, vector<unsigned char>& image, unsigned int& width, unsigned int& height) {

  //decode
  unsigned error = lodepng::decode(image, width, height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, int width, int height) {
	//Encode the image
	unsigned error = lodepng::encode(filename, image, width, height);

	//if there's an error, display it
	if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

int trapAnt(Ant& ant, int x_lim, int y_lim) {
	if (ant.x >= x_lim)
		ant.x = x_lim - 1;
	else if (ant.x < 0)
		ant.x = 0;
	if (ant.y >= y_lim)
		ant.y = y_lim - 1;
	else if (ant.y < 0)
		ant.y = 0;
		
	return 0;
}

int moveAnt(Ant& ant) {
	switch (ant.vector) {
	case 0:
		ant.x += 1;
		break;
	case 90:
		ant.y += 1;
		break;
	case 180:
		ant.x -= 1;
		break;
	case 270:
		ant.y -= 1;
		break;
	}
	
	return 0;
}

int workAnt(vector<unsigned char>& image, int width, int height, Ant& ant) {
	int x = ant.x;
	int y = ant.y;
	unsigned char image_a = image[4 * width * y + 4 * x + 3]; // alpha
	unsigned char image_r = image[4 * width * y + 4 * x + 0]; // red
	unsigned char image_g = image[4 * width * y + 4 * x + 1]; // green
	unsigned char image_b = image[4 * width * y + 4 * x + 2]; // blue
	if (((image_r + image_g + image_b) / 3) < 128) {
		image[4 * width * y + 4 * x + 0] ^= 0xFF;
    	image[4 * width * y + 4 * x + 1] ^= 0xFF;
    	image[4 * width * y + 4 * x + 2] ^= 0xFF;
    	if ((ant.vector + 90) < 360)
    		ant.vector += 90;
    	else
    		ant.vector = 0;
	} else {
		image[4 * width * y + 4 * x + 0] ^= 0xAA;
    	image[4 * width * y + 4 * x + 1] ^= 0xAA;
    	image[4 * width * y + 4 * x + 2] ^= 0xAA;
    	if ((ant.vector - 90) > 0)
    		ant.vector -= 90;
    	else
    		ant.vector = 270;
	};
	
	
	return 0;
}

int createBox(int x1, int x2, int y1, int y2, int width, int height, vector<unsigned char>& image) {
	for (int x = x1; x < x2; x++){
	for (int y = y1; y < y2; y++) {
		image[4 * width * y + 4 * x + 0] = 0;
    	image[4 * width * y + 4 * x + 1] = 0;
    	image[4 * width * y + 4 * x + 2] = 0;
    	image[4 * width * y + 4 * x + 3] = 255;
	}
	}
	return 0;
}

void HSVtoRGB(unsigned char &R, unsigned char &G, unsigned char &B, int H, unsigned char S, unsigned char V) {
	unsigned char min, max, delta;
	
	if (R < G) min = R else min = g;ls
	
	if (
}

int generateColors(int previous) {
	int inversePhi = 0.618033988749895;
	
	previous += inversePhi;
	previous %= 1;
	
	int R, G, B;
	
	HSVtoRGB(R, G, B, previous, 0.5, 0.95);
	
	return
}
