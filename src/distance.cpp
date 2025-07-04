// The following code is based on this example:
// https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/Histograms_Matching/compareHist_Demo.cpp

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void compute_distance_matrix(double* dContent, vector<string> images, int method) {
  size_t tot = images.size();
  Mat src_base, src_test;
  Mat hsv_base, hsv_test;
  Mat hist_base, hist_test;

  // Using 50 bins for hue and 60 for saturation
  int h_bins = 50, s_bins = 60;
  int histSize[] = { h_bins, s_bins };

  // hue varies from 0 to 179, saturation from 0 to 255
  float h_ranges[] = { 0, 180 };
  float s_ranges[] = { 0, 256 };
  const float* ranges[] = { h_ranges, s_ranges };

  // Use the 0-th and 1-st channels
  int channels[] = { 0, 1 };

  int comp = (tot * tot -tot) / 2;
  cout << "Number of distances to compute: " << comp << endl;

  int cnt = 0;
  for(int base = 0; base<tot; base++) {
    src_base = imread(images[base]);
    if(src_base.empty()) {
      cout << "Could not open or find the image" << images[base] << endl;
      return;
    }

    // Convert to HSV
    cvtColor( src_base, hsv_base, COLOR_BGR2HSV );

    // Calculate the histograms for the HSV images
    calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
    normalize( hist_base, hist_base, 1, 0, NORM_L1, -1, Mat() );

    for(int test = base+1; test<tot; test++) {
      src_test = imread(images[test]);
      if(src_test.empty()) {
        cout << "Could not open or find the image" << images[test] << endl;
        return;
      }
  
      // Convert to HSV
      cvtColor( src_test, hsv_test, COLOR_BGR2HSV );
  
      // Calculate the histograms for the HSV images
      calcHist( &hsv_test, 1, channels, Mat(), hist_test, 2, histSize, ranges, true, false );
      normalize( hist_test, hist_test, 1, 0, NORM_L1, -1, Mat() );
  
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

      dContent[base + tot * test] = base_test;

      // Print status
      cnt++;
      if (cnt % (comp/10) == 0)
        cout << cnt *100 / comp << "%" << endl;
    }
  }
}
