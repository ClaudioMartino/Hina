// The following code is based on this example:
// https://www.alglib.net/translator/man/manual.cpp.html#example_clst_distance

#include "dataanalysis.h"

using namespace alglib;
using namespace std;

vector<vector<int>> compute_clusters(double * dContent, vector<string> images, size_t final_clusters) {
  std::vector<std::vector<int>> clusters;
  size_t tot = images.size();
  real_2d_array d;
  d.setcontent(tot, tot, dContent);

  // print differences matrix
  //for(size_t i=0; i<tot; i++) {
  //    for(size_t j=0; j<tot; j++)
  //        cout << d[i][j] << ",";
  //    cout << endl;
  //}

  clusterizerstate s;
  ahcreport rep;

  try {
    clusterizercreate(s);
    clusterizersetdistances(s, d, false);
    clusterizerrunahc(s, rep);
  }
  catch(alglib::ap_error alglib_exception) {
    printf("ALGLIB exception with message '%s'\n", alglib_exception.msg.c_str());
    return clusters;
  }

  //printf("Z: %s\n", rep.z.tostring().c_str());
  //printf("P: %s\n", rep.p.tostring().c_str());
  //printf("PM: %s\n", rep.pm.tostring().c_str()); 

  size_t n_merges = tot - 1; // rep.z.size()? TODO
  size_t tot_buffers = tot + n_merges - (final_clusters -1);
  vector<vector<int>> buffers(tot_buffers);

  // [0; tot-1]
  for(size_t i = 0; i<tot; i++) {
    buffers[i].push_back(i);
  }
  // [tot; tot_buffers-1]
  for(size_t i = tot; i<tot_buffers; i++) {
    //cout << "merge cluster " << rep.z[i-tot][0] << " with " << rep.z[i-tot][1] << " in cluster " << i << endl;
    // copy buffer[i][0]
    for(size_t idx : buffers[rep.z[i-tot][0]])
      buffers[i].push_back(idx);
    vector<int>().swap(buffers[rep.z[i-tot][0]]);   // clear vector reallocating
    // copy buffer[i][1]
    for(size_t idx : buffers[rep.z[i-tot][1]])
      buffers[i].push_back(idx);
    vector<int>().swap(buffers[rep.z[i-tot][1]]);   // clear vector reallocating

    //for(size_t idx : buffers[i])
    //  cout << idx << ",";
    //cout << endl;
  }

  // Save final clusters
  for(size_t i=0; i<tot_buffers; i++) {
    if(buffers[i].size() > 0) {
      clusters.push_back(buffers[i]);
    }
  }

  return clusters;

}
