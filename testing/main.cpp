#include <iostream>
#include <vector>

#include "testing.h"
#include "hina.h"

static std::string opencv_dir = "opencv-4.12.0";
static std::string images_dir = opencv_dir + "/doc/tutorials/imgproc/histograms/histogram_comparison/images/";

std::vector<std::string> get_image_list() {
  std::vector<std::string> images;
  for (int i=0; i<3; i++)
    images.push_back(images_dir + "Histogram_Comparison_Source_" + std::to_string(i) + ".jpg");
  return images;
}

void check_clusters_size() {
  std::vector<std::string> images = get_image_list();
  double d[images.size()*images.size()];

  const size_t clusters_size = 2;

  const int method = 0;
  compute_distance_matrix(d, images, method);
  std::vector<std::vector<int>> clusters = compute_clusters(d, images, clusters_size);
  assert_that(clusters.size() == clusters_size, "Wrong cluster size.");
}

void check_clusters_size_overflow() {
  std::vector<std::string> images = get_image_list();
  double d[images.size()*images.size()];

  const size_t clusters_size = images.size() + 1;

  const int method = 0;
  compute_distance_matrix(d, images, method);
  try {
    std::vector<std::vector<int>> clusters = compute_clusters(d, images, clusters_size);
  }
  catch (const std::runtime_error& e) {
    return;
  }
  throw std::runtime_error("Exception has not been thrown.");
}

int main() {
  run_test(check_clusters_size, "cluster size is requested one");
  run_test(check_clusters_size_overflow, "cluster size overflow");

  return 0;
}
