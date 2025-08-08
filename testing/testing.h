#include <cstdio>
#include <stdexcept>

void assert_that(bool statement, std::string msg) {
  if(!statement)
    throw std::runtime_error(msg);
}

void run_test(void(*test)(), const char* name) {
  try {
    test();
    printf("[+] '%s' test successful.\n", name);
  }
  catch (const std::exception& e) {
    printf("[-] '%s' test failed. %s\n", name, e.what());
  } 
}

enum ImagePool {TEST_IMAGES_COLOR, TEST_IMAGES_GRAY};

const std::vector<std::string> test_images_names = {
"almonds.png",
"apples.png",
"baloons.png",
"bananas.png",
"billiard_balls_a.png",
"billiard_balls_b.png",
"building.png",
"cards_a.png",
"cards_b.png",
"carrots.png",
"chairs.png",
"clips.png",
"coins.png",
"cushions.png",
"ducks.png",
"fence.png",
"flowers.png",
"garden_table.png",
"guitar_bridge.png",
"guitar_fret.png",
"guitar_head.png",
"keyboard_a.png",
"keyboard_b.png",
"lion.png",
"multimeter.png",
"pencils_a.png",
"pencils_b.png",
"pillar.png",
"plastic.png",
"roof.png",
"scarf.png",
"screws.png",
"snails.png",
"socks.png",
"sweets.png",
"tomatoes_a.png",
"tomatoes_b.png",
"tools_a.png",
"tools_b.png",
"wood_game.png"};

std::vector<std::string> get_image_list(enum ImagePool ip) {
  static std::string images_dir;
  std::vector<std::string> images;
  switch(ip) {
    case TEST_IMAGES_COLOR:
      images_dir = "testing/samples/color/";
      for (const auto& entry : test_images_names)
        images.push_back(images_dir + "img_300x300_3x8bit_C00C00_RGB_" + entry);
    break;
    case TEST_IMAGES_GRAY:
      images_dir = "testing/samples/grey/";
      for (const auto& entry : test_images_names)
        images.push_back(images_dir + "img_300x300_1x8bit_C00C00_GRAY_" + entry);
    break;
  }

  return images;
}

#if 0
void print_ref(enum ImagePool ip, const size_t clusters_size) {
  std::vector<std::string> images = get_image_list(ip);
  double d[images.size()*images.size()];

  const size_t tot_methods = 6;
  std::cout << "{" << std::endl;
  for(int method=0; method<tot_methods; method++) {
    std::cout << "{";
    compute_distance_matrix(d, images, method, true);
    std::vector<std::vector<int>> clusters = compute_clusters(d, images, clusters_size, true);

    std::cout.clear();
    for(size_t i=0; i<clusters.size(); i++) {
      std::cout << "{" ;
      for(size_t j=0; j<clusters[i].size(); j++) {
        std::cout << clusters[i][j];
        if(j != clusters[i].size()-1)
          std::cout << ", ";
      }
      std::cout << "}" ;
      if(i != clusters.size()-1)
        std::cout << ", ";
    }
    if(method != tot_methods-1)
      std::cout << "}, " << std::endl;
    else
      std::cout << "}" << std::endl;
  }
  std::cout << "}";
}
#endif

const std::vector<std::vector<int>> refs_test_images_gray_10_clusters[6] {
  {{1}, {11}, {5, 28}, {15, 10, 2, 17}, {13, 7, 23}, {14, 31, 33, 26, 0, 12}, {22, 34, 25, 37, 6, 27}, {32, 29, 8, 39}, {19, 35, 16, 9, 18}, {24, 20, 30, 21, 36, 38, 3, 4}}, 
  {{6}, {21}, {19, 35}, {18, 1, 7, 9}, {36, 38, 5, 20, 24}, {28, 2, 14, 25, 34, 22, 37}, {29, 8, 39}, {30, 33, 26, 31, 11, 16, 4, 13, 0, 12, 17}, {10, 15, 27, 32}, {3, 23}}, 
  {{3}, {23}, {28}, {25, 22, 34, 37, 19, 35}, {0, 17, 5, 12, 20, 24}, {21, 36, 38}, {1, 7, 9, 18}, {26, 31, 30, 33, 11, 16, 4, 13, 6, 27, 32}, {10, 15, 2, 14}, {29, 8, 39}}, 
  {{3}, {10}, {23}, {29}, {6, 33}, {8, 39}, {21, 20, 24, 36, 38}, {28, 14, 31, 25, 34, 22, 37}, {19, 35, 1, 7, 9, 18}, {17, 0, 12, 5, 32, 13, 11, 16, 4, 26, 30, 15, 2, 27}}, 
  {{3}, {10}, {23}, {28}, {19, 35, 25, 34, 22, 37}, {21, 20, 24, 36, 38}, {1, 7, 9, 18}, {6, 33, 26, 30, 4, 13, 11, 16}, {17, 0, 12, 5, 32, 15, 14, 31, 2, 27}, {29, 8, 39}}, 
  {{3}, {23}, {9, 18}, {29, 39}, {25, 28}, {8, 1, 7}, {4, 11, 16, 13, 26, 30, 19, 35, 34, 22, 37, 14, 31}, {6, 5, 17, 32, 20, 24, 0, 12}, {10, 15, 2, 27}, {21, 33, 36, 38}}
};

const std::vector<std::vector<int>> refs_test_images_color_10_clusters[6] {
  {{19, 20, 9, 12}, {4, 18}, {2, 34, 11, 21}, {16, 6, 15, 31}, {23, 22, 30}, {25, 26, 0, 35, 14, 36}, {29, 8, 27, 39, 1, 32, 7, 17}, {38, 3, 24}, {5, 10}, {28, 37, 13, 33}}, 
  {{29}, {20, 19, 23}, {16, 24}, {12, 11, 38}, {2, 5}, {1, 9, 4, 18}, {32, 37, 0, 14, 35}, {3, 10, 28, 33}, {21, 6, 36, 22, 30, 26, 34, 7, 25}, {13, 15, 8, 39, 17, 27, 31}}, 
  {{28}, {9, 14, 35, 12, 19, 20}, {15, 31}, {2, 10}, {6, 32, 16, 27, 17, 30}, {25, 26, 13, 37}, {29, 8, 39}, {18, 21}, {22, 23, 3, 24}, {38, 33, 11, 34, 4, 5, 7, 0, 1, 36}}, 
  {{28}, {29}, {14, 9, 35, 12, 19, 20}, {2, 10}, {38, 3, 24}, {37, 13, 25}, {23, 22, 31}, {8, 39, 6, 15}, {18, 21}, {4, 5, 7, 32, 0, 1, 36, 26, 33, 11, 34, 16, 27, 17, 30}}, 
  {{28}, {29}, {14, 9, 35, 12, 19, 20}, {2, 10}, {31, 6, 32, 16, 27, 17, 30}, {15, 8, 39}, {25, 26, 13, 37}, {4, 5, 7, 0, 1, 36}, {22, 23, 3, 24}, {18, 21, 38, 33, 11, 34}}, 
  {{10}, {28}, {23, 22, 31}, {7, 8, 16}, {18, 21}, {29, 15, 39}, {9, 35, 19, 20, 14, 36, 12, 32, 0, 34}, {4, 5, 24, 3, 38}, {1, 11, 17, 30, 6, 27}, {13, 37, 25, 26, 2, 33}}
};
