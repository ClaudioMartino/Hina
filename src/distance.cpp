// The following code is based on this example:
// https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/Histograms_Matching/compareHist_Demo.cpp

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

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

void calc_histogram(const Mat *image, OutputArray hist) {
  // 50 bins for hue and 60 for saturation
  int histSize_hsv[] = { 50, 60 };
  int histSize_gray[] = { 256 };

  // hue varies from 0 to 179, saturation from 0 to 255
  float h_ranges[] = { 0, 180 };
  float s_ranges[] = { 0, 256 };
  const float* ranges_hsv[] = { h_ranges, s_ranges };
  const float* ranges_gray[] = { s_ranges };

  // channels
  int channels_gray[1] = { 0 };
  int channels_hsv[2] = { 0, 1 };

  if(image->channels() != 1) {
    Mat hsv;
    cvtColor(*image, hsv, COLOR_BGR2HSV); // converto to HSV
    calcHist(&hsv, 1, channels_hsv, Mat(), hist, 2, histSize_hsv, ranges_hsv, true, false);
  }
  else {
    calcHist(image, 1, channels_gray, Mat(), hist, 1, histSize_gray, ranges_gray, true, false);
  }
}

void compute_distance_matrix(double* dContent, vector<string> images, int method, bool quiet) {
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
      cv::HISTCMP_CORREL = 0,
      cv::HISTCMP_CHISQR = 1,
      cv::HISTCMP_INTERSECT = 2, 
      cv::HISTCMP_BHATTACHARYYA = 3, 
      cv::HISTCMP_CHISQR_ALT = 4,    
      cv::HISTCMP_KL_DIV = 5         
      */
      double base_test = compareHist( hist_base, hist_test, method );

      if(method == 0 || method == 2)
        base_test = 1 - base_test;

      // Save results in lower triangular matrix
      dContent[base + tot * test] = base_test;

      // Print status bar
      cnt++;
      printProgress(cnt, comp);
    }
  }
  std::cout << endl;

  // Restore output verbosity
  std::cout.clear();
}
