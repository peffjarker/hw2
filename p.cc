/*
Jeff Parker
2/15/2020
HW2
This program is a parallel version for a program that detects
the amount of pixels turned on in a given region on a black
and white image
*/
#include <iomanip>
#include <iostream>
#include <map>
#include <omp.h>
#include <vector>
using namespace std;

class Count_Pixels {
public:
  /*
  checks to see if given i and j is in the range of the image
  */
  bool valid(int i, int j, vector<vector<int>> &image) {
    if (i >= 0 && i < image.size()) {
      if (j >= 0 && j < image[0].size()) {
        return true;
      }
    }
    return false;
  }
  /*
  preprocesses regions so that calculations can be speedier is subsequent calls
  */
  void process_regions(vector<vector<int>> &image,
                       vector<vector<int>> &pixel_count) {

    for (int i = 0; i < image.size(); i++) {
      for (int j = 0; j < image[0].size(); j++) {
        int up;
        int left;
        int diag;
        if (valid(i, j - 1, image)) {
          left = pixel_count[i][j - 1];
        } else {
          left = 0;
        }
        if (valid(i - 1, j, image)) {
          up = pixel_count[i - 1][j];
        } else {
          up = 0;
        }
        if (valid(i - 1, j - 1, image)) {
          diag = pixel_count[i - 1][j - 1];
        } else {
          diag = 0;
        }
        if (valid(i, j, image)) {
          pixel_count[i][j] = image[i][j] + left + up - diag;
        }
      }
    }
  }
  /*
  creates a vector to store the pixel count in regions and matches the size to
  image then processes the region. After processing a second vector sums is
  created with the size of regions in the .dat file. The for loop iterates
  through the regions calculating the total through the statement in the
  if statement / else statement
  */
  vector<int> count_pixels_in_regions(
      vector<vector<int>> &image,
      vector<pair<pair<int, int>, pair<int, int>>> &regions) {
    vector<vector<int>> pixel_count;
    pixel_count.resize(image.size());
#pragma omp parallel for
    for (int i = 0; i < pixel_count.size(); ++i) {
      pixel_count[i].resize(image[i].size());
    }
    process_regions(image, pixel_count);
    vector<int> sums;
    sums.resize(regions.size());
#pragma omp parallel for
    for (int i = 0; i < regions.size(); ++i) {
      int total = 0;
      int e, f, g, h;

      e = regions[i].first.first;
      f = regions[i].first.second;
      g = regions[i].second.first;
      h = regions[i].second.second;

      if (e > 0) {
        total = pixel_count[g][h] - pixel_count[g][f - 1] -
                pixel_count[e - 1][h] + pixel_count[e - 1][f - 1];
      } else {
        total = pixel_count[g][h] - pixel_count[g][f - 1] - pixel_count[e][h] +
                pixel_count[e][f - 1];
      }

      sums[i] = total;
    }
    return sums;
  }
};
