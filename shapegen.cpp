#include <iostream>

using namespace std;

int[] buildRectangle(int pos_[], int width_, int height_, Color color_) {
    int shapeOut[(3 * (width_ * height_) + 4];
    r = color_.getRed();
    g = color_.getGreen();
    b = color_.getBlue();
    shapeOut[0] = width_;
    shapeOut[1] = height_;
    shapeOut[2] = pos_[0];
    shapeOut[3] = pos_[1];
    for (int h = 0; h < height_; h++) {
        for (int w = 0; w < width_; w++) {
            shapeOut[(3 * ((h * width_) + w)) + 4] = r;
            shapeOut[(3 * ((h * width_) + w)) + 5] = g;
            shapeOut[(3 * ((h * width_) + w)) + 6] = b;
        }
    }
    return shapeOut;
}

int main() {
    
    return 0;
}