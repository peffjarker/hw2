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

    pixel_count[0][0] = image[0][0];
    for (int i = 0; i < image.size(); i++) {
      for (int j = 0; j < image[0].size(); j++) {
        int up;
        int left;
        int diag;
        if (valid(i, j - 1, image))
          left = pixel_count[i][j - 1];
        else
          left = 0;
        if (valid(i - 1, j, image))
          up = pixel_count[i - 1][j];
        else
          up = 0;
        if (valid(i - 1, j - 1, image))
          diag = pixel_count[i - 1][j - 1];
        else
          diag = 0;
        pixel_count[i][j] = image[i][j] + left + up - diag;
      }
    }
  }

  vector<int> count_pixels_in_regions(
      vector<vector<int>> &image,
      vector<pair<pair<int, int>, pair<int, int>>> &regions) {
    vector<vector<int>> pixel_count;
    process_regions(image, pixel_count);
    vector<int> sums;

    for (int i = 0; i < regions.size(); ++i) {
      int total = 0;
      int e, f, g, h;

      e = regions[i].first.first;
      f = regions[i].first.second;
      g = regions[i].second.first;
      h = regions[i].second.second;

      total = pixel_count[g][h] - pixel_count[g][f - 1] -
              pixel_count[e - 1][h] + pixel_count[e - 1][f - 1];

      sums.push_back(total);
    }
    return sums;
  }
};
