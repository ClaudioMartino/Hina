struct DistanceMatrix {
  DistanceMatrix(size_t tot);
  ~DistanceMatrix();

  void compute(std::vector<std::string> images, int method, bool quiet);
  double* get();

private:
  double* val;
};

struct Clusters {
  Clusters(size_t final_clusters, std::vector<std::string>& images, std::string path);
  ~Clusters() = default;

  void compute(DistanceMatrix& d, bool quiet);
  void print();
  std::vector<std::vector<int>> get();

private:
  size_t final_clusters;
  std::vector<std::string> images;
  std::string path;
  std::vector<std::vector<int>> val;
};
