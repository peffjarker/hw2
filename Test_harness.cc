//
// File:Test_harness.cc
// Purpose: Test harness for the class Count_Pixels for CS 4000 HW #2
// Outline:
//        1.)  Reads two file names from the command line --- one
//          with the name of the pbm file, and one with the name of the box
//          data//          file.
//        2.) Opens the pbm file --> converts it to a vector of 0's and 1's.
//        3.) Opens file containing region descriptions --> store it in a
//        vector. 4.) Calls appropriate code from Count_Pixels to count the
//        number of
//            "on" pixels in a region.
//        5.) Prints out the sum from each region.
//
// Author: David W. Juedes
//
// Note: In PBM files The bit '1' means black, '0' means white.
//       We flip for this assignment.
//
#include <bitset>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
// You write this part !!!
#include "Count_Pixels.cc"
//
// Read pairs of points (e.g., (a,b) (c,d)).
// Store them in the variable "boxes"
//
void read_boxes(istream &in,
                vector<pair<pair<int, int>, pair<int, int>>> &boxes) {
  while (!in.eof()) {
    int a, b, c, d;

    in >> a >> b >> c >> d;
    if (!in.fail()) {
      boxes.push_back(make_pair(make_pair(a, b), make_pair(c, d)));
    }
  }
  // return boxes;
}
//
// Read a PBM file -- store it in variable image.
//
void read_PBM(istream &in, vector<vector<int>> &image, int &n, int &m) {
  string magic;
  int xdim, ydim;

  in >> magic;
  in >> xdim >> ydim;
  // traverse the file data and store it in a 2 dimensional vector
  // run through each column
  string z;
  getline(in, z);                // Consume newline.
  for (int i = 0; i < ydim; i++) // Read per line.
  {
    vector<int> tmp;
    // run though each row in terms of bytes
    int limit = xdim / 8;
    if ((xdim % 8) != 0)
      limit++;
    int p_count = 0;
    for (int j = 0; j < limit; j++) {
      // read byte[i][j]
      unsigned char x;
      x = in.get();
      if (in.fail()) {
        cout << "Error!!!!" << endl;
      } else {
        bitset<16> y(x);
        for (int l = 7; l >= 0; l--) {
          if (p_count < xdim) {
            int clr;
            if (y[l] == 1)
              clr = 0;
            else
              clr = 1;
            tmp.push_back(clr);
            p_count++;
          }
        }
      }
    }
    // push the row onto the matrix vector.
    image.push_back(tmp);
    if (tmp.size() != xdim) {
      cout << i << " " << tmp.size() << endl;
    }
  }
  n = ydim;
  m = xdim;
}

int main(int argc, char *argv[]) {

  ifstream fin;
  fin.open(argv[1]);
  // in case file fails to open for input, output error message
  if (fin.fail()) {
    cout << "Failed to open" << argv[1] << endl;
    exit(-1);
  }
  ifstream fin1;
  fin1.open(argv[2]);
  // in case file fails to open for input, output error message
  if (fin1.fail()) {
    cout << "Failed to open" << argv[2] << endl;
    exit(-1);
  }

  vector<vector<int>> image;
  int n, m;
  read_PBM(fin, image, n, m);

  cerr << "Image Read" << n << "x" << m << endl;

  vector<pair<pair<int, int>, pair<int, int>>> boxes;

  read_boxes(fin1, boxes);

  // Print out the bits.
  // for (int i=0;i<n;i++) {
  //  for (int j=0;j<50;j++) {
  //    cout << image[i][j];
  //  }
  //  cout << endl;
  //}

  Count_Pixels obj;

  vector<int> results;

  results = obj.count_pixels_in_regions(image, boxes);

  for (int i = 0; i < results.size(); i++) {
    cout << "Pixels in region " << boxes[i].first.first << ","
         << boxes[i].first.second << " --- " << boxes[i].second.first << ","
         << boxes[i].second.second << endl;
    cout << " = " << results[i] << endl;
  }
}
