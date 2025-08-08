#include <iostream>
#include <vector>

#include "testing.h"
#include "hina.h"

void check_clusters_size_overflow() {
  std::vector<std::string> images = get_image_list(TEST_IMAGES_GRAY);
  const size_t clusters_size = images.size() + 1;
  const int method = 0;

  DistanceMatrix d(images.size());
  d.compute(images, method, true);

  try {
    Clusters c(clusters_size, images, "");
    c.compute(d, true);
  }
  catch (const std::runtime_error& e) {
    return;
  }
  throw std::runtime_error("Exception has not been thrown with clusters size = images size + 1.");
}

void check_clusters(enum ImagePool ip, size_t clusters_size, const std::vector<std::vector<int>> refs[6]) {
  std::vector<std::string> images = get_image_list(ip);

  DistanceMatrix d(images.size());
  for(int method=0; method<6; method++) {
    d.compute(images, method, true);

    Clusters c(clusters_size, images, "");
    c.compute(d, true);

    assert_that(c.get() == refs[method], "Wrong clusters with method " + std::to_string(method));
  }
}

void check_gray_10_clusters() {
  check_clusters(TEST_IMAGES_GRAY, 10, refs_test_images_gray_10_clusters);
}

void check_color_10_clusters() {
  check_clusters(TEST_IMAGES_COLOR, 10, refs_test_images_color_10_clusters);
}

int main() {
  run_test(check_clusters_size_overflow, "cluster size overflow");
  run_test(check_gray_10_clusters, "10 clusters from 40 grayscale images");
  run_test(check_color_10_clusters, "10 clusters from 40 color images");

  return 0;
}
