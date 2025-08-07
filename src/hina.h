struct DistanceMatrix {
  DistanceMatrix(size_t tot);
  ~DistanceMatrix();

  void compute(std::vector<std::string> images, int method, bool quiet);
  double* get();

private:
  double* val;
};

struct Clusters {
  Clusters() = default;
  ~Clusters() = default;

  void compute(DistanceMatrix& d, std::vector<std::string> images, size_t final_clusters, bool quiet);
  void print(std::vector<std::string> images, std::string path);
  std::vector<std::vector<int>> get();

private:
  size_t final_clusters;
  std::vector<std::vector<int>> val;
};
