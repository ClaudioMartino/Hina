#include <iostream>
#include <unistd.h>
#include <vector>
#include <filesystem>

#include "hina.h"

int main(int argc, char **argv) {
  // Get options
  std::string path;
  size_t final_clusters = 0;
  size_t n = -1;
  int method = 0;
  bool quiet = false;
  for(;;) {
    switch(getopt(argc, argv, "d:c:n:m:qh")) {
      case 'd':
        path = optarg;
        continue;
      case 'c':
        final_clusters = atoi(optarg);
        continue;
      case 'n':
        n = atoi(optarg);
        continue;
      case 'm':
        method = atoi(optarg);
        continue;
      case 'q':
        quiet = true;
        continue;
      case 'h':
      default :
        std::cout << "Usage: hina -d <directory> -c <clusters> [-n <images>] [-m <method>] [-q] [-h]" << std::endl;
        return 0;
        break;
      case -1:
        break;
    }
    break;
  }

  if(path.empty()) {
    std::cout << "Enter a directory!" << std::endl;
    return -1;
  }
  if(method < 0 || method > 5) {
    std::cout << "Invalid method!" << std::endl;
    return -1;
  }

  if(quiet)
    std::cout.setstate(std::ios_base::failbit);

  std::cout << "Image directory: " << path << std::endl;
  std::cout << "Histogram comparison method: " << method << std::endl;
  std::cout << "Number of clusters: " << final_clusters << std::endl;

  // Find all images in directory
  std::vector<std::string> images;
  for (const auto & entry : std::__fs::filesystem::directory_iterator(path)) {
    images.push_back(entry.path());
  }

  // Resize image pool if requested
  if(n != -1 && n < images.size()) {
    std::cout << "Taking only first " << n << " images." << std::endl;
    std::sort(images.begin(), images.end());
    images.resize(n);
  }

  size_t tot = images.size();
  std::cout << "Number of images: " << tot << std::endl;

  if(final_clusters < 1 || final_clusters > tot) {
    std::cout.clear();
    std::cout << "Invalid number of clusters!" << std::endl;
    return -1;
  }

  // Compute distance matrix
  DistanceMatrix d(tot);
  d.compute(images, method, quiet);

  // Compute clusters
  Clusters c;
  c.compute(d, images, final_clusters, quiet);
  c.print(images, path);

  return 0;
}
