#include <iostream>
#include <utility>
#include <cmath>
#include <algorithm>
#include <functional>
#include <time.h>
#include <string>
#include "lodepng.h"
#include "unistd.h"

using namespace std;

struct Ant {
	int vector = 90; // face north
	int x = 0;
	int y = 0;
};

struct RGB {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct HSV {
	unsigned char h;
	unsigned char s;
	unsigned char v;
};

void printColor(HSV &c);
void printColor(RGB &c);

void convertColor(const HSV&, RGB&);
void convertColor(const RGB&, HSV&);

void decodeOneStep(string, vector<unsigned char>&, unsigned int&, unsigned int&);
void encodeOneStep(string, vector<unsigned char>&, int, int);

HSV generateColor(HSV&);

void workAnt(vector<unsigned char>&, const vector<int>&, const unsigned char&, const int&, const int&, Ant&);
int moveAnt(Ant&);
int trapAnt(Ant&, int, int);

int createBox(int, int, int, int, int, int, vector<unsigned char>&);

int main(int argc, char * argv[]) {
	unsigned char colorLength; // number of colors ie., length of LR sequence
	long long steps; // number of iterations
	
	if (argc > 1) {
		colorLength = strlen(argv[1]); // first argument is a sequence of LR characters
		steps = stoll(argv[2]); // second argument is the number of steps
	}else return 0;
	
	cout << colorLength << endl;
	cout << steps << endl;
	
	vector<int> dirs; // translate LR into angle deltas ie., L -> +90, R -> -90
	
	for (int i = 0; i < colorLength; i++) {
		if (argv[1][i] == 'R') {
			dirs.emplace_back(-90);
		} else if (argv[1][i] == 'L') {
			dirs.emplace_back(90);
		}
	}
	
	for (auto &d : dirs) {
		cout << d << " ";
	}
	
	cout << endl;
	
	Ant ant; // create an ant!
	vector<unsigned char> image; // make the image
	
	unsigned int height = 2000; unsigned int width = 2000; // image properties
	
	image.resize(height * width);
	
	ant.x = width / 2 - 1;
	ant.y = height / 2 - 1;
	cout << ant.x << " " << ant.y << endl;
	
	vector<HSV> colors_h;
	vector<RGB> colors_r;
	
	srand(time(NULL));
	
	HSV c1;
	c1.h = rand() % 255;
	c1.s = rand() % 255;
	c1.v = rand() % 255;
	
	colors_h.push_back(c1);
	
	for (int i = 1; i < colorLength; i++) {
		colors_h.push_back(generateColor(colors_h.at(i - 1)));
	}
	
	for (HSV c : colors_h) {
		printColor(c);
	}
	
	RGB c2;
	for (HSV c : colors_h) {
		convertColor(c, c2);
		colors_r.push_back(c2);
		printColor(c2);
	}
	
	/*sleep(2);
	srand(time(NULL));
	int shuf = 0;
	for (int i = colorLength; i > 0; i--) {
		shuf = rand() % i;
		iter_swap(colors_r.begin() + i, colors_r.begin() + shuf);
	}*/
	
	for (long long i = 0; i < steps; i++) {
		workAnt(image, dirs, colorLength, width, height, ant);
		moveAnt(ant);
		trapAnt(ant, width, height);
	}
	
	cout << "Poor ant is tired!" << endl;
	
	vector<unsigned char> imageFinal; // make the image
	imageFinal.resize(4 * width * height);
	unsigned char c = 0;
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++) {
			c = image[width * y + x];
			imageFinal[4 * width * y + x * 4 + 0] = colors_r[c].r;
    		imageFinal[4 * width * y + x * 4 + 1] = colors_r[c].g;
    		imageFinal[4 * width * y + x * 4 + 2] = colors_r[c].b;
    		imageFinal[4 * width * y + x * 4 + 3] = 255;
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
	
	cout << "Encoding now..." << endl;
	
	string outputString = string(argv[1]) + argv[2];
	
	encodeOneStep(outputString, imageFinal, width, height);
	
	return 0;
}

void decodeOneStep(const char* filename, vector<unsigned char>& image, unsigned int& width, unsigned int& height) {

  //decode
  unsigned error = lodepng::decode(image, width, height, filename);

  //if there's an error, display it
  if(error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
}

void encodeOneStep(string filename, std::vector<unsigned char>& image, int width, int height) {
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

void workAnt(vector<unsigned char>& image, const vector<int>& dirs, const unsigned char& colors, const int& width, const int& height, Ant& ant) {
	int x = ant.x;
	int y = ant.y;
	
	unsigned char c = image[width * y + x]; // find the color of the square
	
	ant.vector += dirs[c]; // turn the ant based on color
	
	while (ant.vector >= 360) {
		ant.vector -= 360;
	}
	
	while (ant.vector < 0) {
		ant.vector += 360;
	}
	
	c++; // flip the color of the square
	if (c == colors) { // check color bound
		c = 0;
	}
	
	image[width * y + x] = c;
	
	// legacy code
	/*unsigned char image_a = image[4 * width * y + 4 * x + 3]; // alpha
	unsigned char image_r = image[4 * width * y + 4 * x + 0]; // red
	unsigned char image_g = image[4 * width * y + 4 * x + 1]; // green
	unsigned char image_b = image[4 * width * y + 4 * x + 2]; // blue
	*/
	
	return;
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

void convertColor(const HSV& c1, RGB& c2) {
	float r, g, b, h, s, v;
	h = c1.h / 255.0;
	s = c1.s / 255.0;
	v = c1.v / 255.0;
	
	if (s == 0) r = g = b = v;
	else {
		float f, p, q, t;
		int i;
		
		h *= 6;
		i = int(floor(h));
		f = h - i;
		p = v * (1 - s);
		q = v * (1 - (s * f));
		t = v * (1 - (s * (1 - f)));
		
		switch(i)       
        {         
			case 0: r = v; g = t; b = p; break;
			case 1: r = q; g = v; b = p; break;
			case 2: r = p; g = v; b = t; break;
			case 3: r = p; g = q; b = v; break;
			case 4: r = t; g = p; b = v; break;
            case 5: r = v; g = p; b = q; break;
        }
    }
	
	c2.r = char(r * 255);
	c2.g = char(g * 255);
	c2.b = char(b * 255);
	
	return;
}

void convertColor(const RGB& c1, HSV& c2) {
	float r, g, b, h, s, v;
	
	r = c1.r / 255.0;
	g = c1.g / 255.0;
	b = c1.b / 255.0;
	
	float maxColor = max(r, max(g, b));
	float minColor = min(r, min(g, b));
	
	v = maxColor;
	
	if (maxColor == 0) s = 0;
	else s = (maxColor - minColor) / maxColor;
	
	if (s == 0) h = 0;
	else {
		if (r == maxColor) h = (g - b) / (maxColor - minColor);
		else if (g == maxColor) h = 2.0 + (b - r) / (maxColor - minColor);
		else h = 4.0 + (r - g) / (maxColor - minColor);
		h /= 6.0;
		
		if (h < 0) h++;
	}
	
	c2.h = int(h * 255);
	c2.s = int(s * 255);
	c2.v = int(v * 255);
	
	return;
}

HSV generateColor(HSV& c1) {
	HSV c2;
	float next = c1.h / 255.0;
	
	c2.s = 0.5 * 255;
	c2.v = 0.95 * 255;
	
	float inversePhi = 0.618033988749895;
	
	next += inversePhi;
	next = fmod(next, 1);
	
	c2.h = (unsigned char)(next * 255);	
	
	return c2;
}

void printColor(HSV &c) {
	cout << "H:" << int(c.h);
	cout << " S:" << int(c.s);
	cout << " V:" << int(c.v);
	cout << endl;
	
	return;
}

void printColor(RGB &c) {
	cout << "R:" << int(c.r);
	cout << " G:" << int(c.g);
	cout << " B:" << int(c.b);
	cout << endl;

	return;
}
