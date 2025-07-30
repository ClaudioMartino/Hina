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

  const size_t clusters_size = 2;

  for(int method=0; method<6; method++) {
    double d[images.size()*images.size()];
    compute_distance_matrix(d, images, method);
    std::vector<std::vector<int>> clusters = compute_clusters(d, images, clusters_size);
    assert_that(clusters.size() == clusters_size, "Wrong cluster size.");
  }
}

int main() {
  run_test(check_clusters_size, "cluster size");

  return 0;
}
