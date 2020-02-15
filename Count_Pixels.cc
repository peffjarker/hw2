#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

class Count_Pixels {
public:
  bool valid(int i, int j, vector<vector<int>> &image) {
    if (i >= 0 && i < image.size()) {
      if (j >= 0 && j < image[0].size()) {
        return true;
      }
    }
    return false;
  }

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
          int total = image[i][j] + left + up - diag;
          pixel_count[i][j] = total;
        }
      }
    }
  }

  vector<int> count_pixels_in_regions(
      vector<vector<int>> &image,
      vector<pair<pair<int, int>, pair<int, int>>> &regions) {
    vector<vector<int>> pixel_count;
    pixel_count.resize(image.size());
    for (int i = 0; i < pixel_count.size(); ++i) {
      pixel_count[i].resize(image[i].size());
    }
    process_regions(image, pixel_count);
    vector<int> sums;
    sums.resize(regions.size());
    for (int i = 0; i < regions.size(); ++i) {
      int total = 0;
      int e, f, g, h;

      e = regions[i].first.first;
      f = regions[i].first.second;
      g = regions[i].second.first;
      h = regions[i].second.second;

      cout << "e: " << e;
      cout << "f: " << f;
      cout << "g: " << g;
      cout << "h: " << h << endl;

      total = pixel_count[g][h] - pixel_count[g][f - 1] -
              pixel_count[e - 1][h] + pixel_count[e - 1][f - 1];

      cout << total << endl;

      sums[i] = total;
    }
    return sums;
  }
};
