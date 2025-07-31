#include <iostream>
#include <vector>

#include "testing.h"
#include "hina.h"

std::vector<std::string> get_image_list() {
  static std::string opencv_dir = "opencv-4.12.0"; // TODO generic
  static std::string images_dir = opencv_dir + "/doc/tutorials/imgproc/histograms/histogram_comparison/images/";

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
  compute_distance_matrix(d, images, method, true);
  std::vector<std::vector<int>> clusters = compute_clusters(d, images, clusters_size, true);
  assert_that(clusters.size() == clusters_size, "Wrong cluster size, " + std::to_string(clusters.size()) + " instead of " + std::to_string(clusters_size) + ".");
}

void check_clusters_size_overflow() {
  std::vector<std::string> images = get_image_list();
  double d[images.size()*images.size()];

  const size_t clusters_size = images.size() + 1;

  const int method = 0;
  compute_distance_matrix(d, images, method, true);
  try {
    std::vector<std::vector<int>> clusters = compute_clusters(d, images, clusters_size, true);
  }
  catch (const std::runtime_error& e) {
    return;
  }
  throw std::runtime_error("Exception has not been thrown with clusters size = images size + 1.");
}

void check_clusters() {
  std::vector<std::string> images = get_image_list();
  double d[images.size()*images.size()];

  const size_t clusters_size = 2;
  std::vector<std::vector<std::vector<int>>> refs{
    {{2}, {0, 1}},
    {{0}, {1, 2}},
    {{2}, {0, 1}},
    {{2}, {0, 1}},
    {{2}, {0, 1}},
    {{2}, {0, 1}}
  };

  for(int method=0; method<6; method++) {
    compute_distance_matrix(d, images, method, true);
    std::vector<std::vector<int>> clusters = compute_clusters(d, images, clusters_size, true);
    assert_that(clusters == refs[method], "Wrong clusters with method " + std::to_string(method));
  }
}

int main() {
  run_test(check_clusters_size, "cluster size");
  run_test(check_clusters_size_overflow, "cluster size overflow");
  run_test(check_clusters, "clusters");

  return 0;
}
