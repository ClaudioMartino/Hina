// The following code is based on this example:
// https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/Histograms_Matching/compareHist_Demo.cpp

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

#include "hina.h"

using namespace std;
using namespace cv;

void printProgress(int cnt, int comp) {
  const int barWidth = 70;
  double progress = (double)cnt/comp;

  std::cout << "[";
  int pos = barWidth * progress;
  for (int i = 0; i < barWidth; ++i) {
    if (i < pos)
      std::cout << "=";
    else
      std::cout << " ";
  }
  std::cout << "] " << cnt << "/" << comp << "\r";
  std::cout.flush();
}

DistanceMatrix::DistanceMatrix(size_t tot) : tot { tot } {
  val = new double[tot*tot];
}

DistanceMatrix::~DistanceMatrix() {
  delete[] val;
}

double* DistanceMatrix::get() {
  return val;
}

void DistanceMatrix::print() {
  for(size_t i=0; i<tot; i++) {
    for(size_t j=0; j<tot; j++) {
      printf("%.2f ", val[i*tot+j]);
    }
    printf("\n");
  }
}

void calc_histogram(const Mat *image, OutputArray hist) {
  int nimages = 1;
  InputArray mask = Mat(); // empty mask
  int dims = image->channels();
  bool uniform = true;
  bool accumulate = false;

  float ranges180[] = { 0, 180 };
  float ranges256[] = { 0, 256 };
  const float* ranges_hsv[] = { ranges180, ranges256, ranges256 };
  const float* ranges_gray[] = { ranges256 };
  const float* ranges_rgb[] = { ranges256, ranges256, ranges256 };

  int* channels;
  const float** ranges;
  int* histSize;
  const Mat* img;
  Mat hsv;

  if(dims != 1) {
    channels = new int[3] { 0, 1, 2 };
    bool convert = true;
    if(convert) {
      cvtColor(*image, hsv, COLOR_BGR2HSV); // convert to HSV
      dims -= 1; // take only H and S

      ranges = ranges_hsv;
      histSize = new int[2] { 50, 60 };
      img = &hsv;
    }
    else {
      ranges = ranges_rgb;
      histSize = new int[3] { 256, 256, 256 };
      img = image;
    }
  }
  else {
    channels = new int[1] { 0 };
    ranges = ranges_gray;
    histSize = new int[1] { 256 };
    img = image;
  }

  calcHist(img, nimages, channels, mask, hist, dims, histSize, ranges, uniform, accumulate);

  delete[] histSize;
  delete[] channels;
}

void DistanceMatrix::compute(vector<string> images, int method, bool quiet) {
  if(quiet)
    std::cout.setstate(std::ios_base::failbit);

  size_t tot = images.size();
  Mat src_base, src_test;
  Mat hist_base, hist_test;
  int comp = (tot*tot - tot) / 2;
  cout << "Number of distances to compute: " << comp << endl;

  int cnt = 0;
  for(int base = 0; base<tot; base++) {
    src_base = imread(images[base], IMREAD_ANYCOLOR);
    if(src_base.empty()) {
      cout << "Could not open or find the image" << images[base] << endl;
      return;
    }

    // Calculate the histogram of base image
    calc_histogram(&src_base, hist_base);
    normalize(hist_base, hist_base, 1, 0, NORM_L1, -1, Mat());

    for(int test = base+1; test<tot; test++) {
      src_test = imread(images[test], IMREAD_ANYCOLOR);
      if(src_test.empty()) {
        cout << "Could not open or find the image" << images[test] << endl;
        return;
      }
  
      // Calculate the histogram of test image
      calc_histogram(&src_test, hist_test);
      normalize(hist_test, hist_test, 1, 0, NORM_L1, -1, Mat());
  
      // Apply the histogram comparison method
      /*
      CORREL = 0,
      CHISQR = 1,
      INTERSECT = 2, 
      BHATTACHARYYA = 3, 
      CHISQR_ALT = 4,    
      KL_DIV = 5         
      */
      double base_test = compareHist( hist_base, hist_test, method );
      if(method == 0 || method == 2)
        base_test = 1 - base_test;

      // Save results in lower triangular matrix
      val[base + tot * test] = base_test;

      // Print status bar
      cnt++;
      printProgress(cnt, comp);
    }
  }
  std::cout << endl;

  // Restore output verbosity
  std::cout.clear();
}
