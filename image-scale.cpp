/* 
Author: Lasha Zibzibadze
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Lab 8 Task E

This program scales given image to 200%.
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;
int out_file[MAX_H][MAX_W];

void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
	char c;
	int x;
	ifstream instr;
	instr.open("inImage.pgm");

	instr >> c;
	assert(c == 'P');
	instr >> c;
	assert(c == '2');

	while ((instr>>ws).peek() == '#') {
		instr.ignore(4096, '\n');
	}

	instr >> width;
	instr >> height;

	assert(width <= MAX_W);
	assert(height <= MAX_H);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[row][col];
	instr.close();
	return;

}

void writeImage(int image[MAX_H][MAX_W], int height, int width) {
	ofstream ostr;
	ostr.open("outImage.pgm");
	if (ostr.fail()) {
		cout << "Unable to write file\n";
		exit(1);
	};

	ostr << "P2" << endl;
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
			ostr << image[row][col] << ' '; 
			ostr << endl;
		}
	}
	ostr.close();
	return;

}

int Scaleimage(int image[MAX_H][MAX_W], int h, int w){

    int new_image;
    for(int row = 0; row < h * 2; row += 2) {
        for(int col = 0; col < w * 2; col += 2){
            new_image = image[row / 2][col / 2];
            out_file[row][col] = new_image;
            out_file[row + 1][col] = new_image;
            out_file[row][col + 1] = new_image;
            out_file[row + 1][col + 1] = new_image;
        }
    }
    
    return out_file[MAX_H][MAX_W];
}

int main() {

    int img[MAX_H][MAX_W];
    int h, w;

    readImage(img, h, w);
    Scaleimage(img, h, w);

    writeImage(out_file, h*2, w*2);
    return 0;

}
