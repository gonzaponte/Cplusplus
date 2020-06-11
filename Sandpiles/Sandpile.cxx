#include "Sandpile.h"
#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <fstream>
#include <functional>

////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////
Sandpile::Sandpile(const Sandpile& s){
  array vals = s.get_values();
  values = array(vals);
  nrows = values.size();
  ncols = values[0].size();
}

Sandpile::Sandpile(const array vals){
  values = vals;
  nrows = values.size();
  ncols = values[0].size();
}

Sandpile::Sandpile(int rows, int cols, int value){
  nrows = rows;
  ncols = cols;
  for (int i=0; i<rows; ++i)
    values.emplace_back(cols, value);
}

Sandpile::Sandpile(const char* filename){
  std::ifstream inputfile;
  inputfile.open(filename);
  if (!inputfile.good()){
    std::cerr << "Input file not found" << std::endl;
    return;
  }
  values = array();
  std::string line;
  std::vector<int> row;
  int start, pos;
  while (std::getline(inputfile, line)){
    start = 0;
    row = std::vector<int>();
    while ( (pos=line.find(" ", start)) != std::string::npos){
      row.emplace_back(std::stoi(line.substr(pos-1, 1)));
      start = pos+1;
    }
    values.emplace_back(row);
  }
  inputfile.close();
  nrows = values.size();
  ncols = values[0].size();
}

Sandpile::Sandpile(const std::string filename) : Sandpile(filename.c_str()){
}

////////////////////////////////////////////////
// Statics
////////////////////////////////////////////////
const SandpileCollection Sandpile::generate_full_set(int rows, int cols){
  if (Sandpile::DEBUG){
    std::cout << "Computing full set of sandpiles of dimmension ("
    << rows << "x" << cols << ") ..." << std::endl;
  }
  int size = rows * cols;
  std::vector<int> A(size, 0);
  SandpileCollection SC = SandpileCollection();
  std::function<void(int)> recursive;
  
  recursive = [&recursive, &A, &SC, size, rows, cols](int k){
    if (k == size){
      SC.emplace_back(vector_to_array(A, rows, cols));
      return;
    }
    for (int i=0; i<Sandpile::top; ++i) {
      A[k] = i;
      recursive(k+1);
    }
  };

  recursive(0);
  if (Sandpile::DEBUG){
    std::cout << "Total #sandpiles " << Sandpile::full_set.size() << std::endl;
  }
  return SC;
}

Sandpile Sandpile::generate_random(int rows, int cols){
  std::chrono::system_clock::time_point seed;
  std::mt19937 generator;
  std::uniform_int_distribution<int> distribution;
  
  seed         = std::chrono::system_clock::now();
  generator    = std::mt19937(seed.time_since_epoch().count());
  distribution = std::uniform_int_distribution<int>(0, Sandpile::top-1);
  
  Sandpile s(rows, cols);
  for(int i=0; i<s.nrows; ++i){
    for(int j=0; j<s.nrows; ++j){
      s[i][j] = distribution(generator);
    }
  }
  return s;
}

////////////////////////////////////////////////
// Methods
////////////////////////////////////////////////
int Sandpile::sum() const{
  int ssum = 0;
  std::for_each(values.begin(), values.end(),
                [&ssum](std::vector<int> row){
                  ssum += std::accumulate(row.begin(), row.end(), 0);
                });
  return ssum;
}

Sandpile Sandpile::operator+(const Sandpile& s) const{
  Sandpile summed(*this);
  summed += s;
  return summed;
}

Sandpile Sandpile::operator+(const int n) const{
  Sandpile summed(*this);
  summed += n;
  return summed;
}

Sandpile Sandpile::operator*(const int n) const{
  Sandpile scaled(*this);
  scaled *= n;
  return scaled;
}

Sandpile& Sandpile::operator+=(const Sandpile& s){
  if (!assert_dims(s)){
    std::cerr << "Cannot add sandpiles of different dimmension:" << std::endl
              << "(" <<   nrows << ", " <<   ncols << ") vs "
              << "(" << s.nrows << ", " << s.ncols << ")" << std::endl;
  }
  for (int i=0; i<nrows; ++i){
    for (int j=0; j<ncols; ++j){
      values[i][j] += s[i][j];
    }
  }
  this->topple();
  return *this;
}

Sandpile& Sandpile::operator+=(const int n){
  for (int i=0; i<nrows; ++i){
    for (int j=0; j<ncols; ++j){
      values[i][j] += n;
    }
  }
  this->topple();
  return *this;
}

Sandpile& Sandpile::operator*=(const int n){
  for (int i=0; i<nrows; ++i){
    for (int j=0; j<ncols; ++j){
      values[i][j] *= n;
    }
  }
  this->topple();
  return *this;
}

bool Sandpile::operator==(const Sandpile& s) const{
  if (!assert_dims(s))
    return false;

  for (int i=0; i<nrows; ++i){
    for (int j=0; j<ncols; ++j){
      if (values[i][j] != s[i][j]){
        return false;
      }
    }
  }
  return true;
}

void Sandpile::topple(){
  int i, j;
  bool stay_in_loop = true;
  int nloops = 0;
  while (stay_in_loop){
    if (verbose && (nloops == 10000)){
      nloops = 0;
      std::cout << values[nrows/2][ncols/2] << std::endl;
    }
    ++nloops;
    stay_in_loop = false;
    for (i=0; i<nrows; ++i){
      for (j=0; j<ncols; ++j){
        if (values[i][j] < Sandpile::top) continue;
        stay_in_loop = true;
        
        values[i][j] -= Sandpile::top;
        if (i>0)       ++values[i-1][j];
        if (i<nrows-1) ++values[i+1][j];
        if (j>0)       ++values[i][j-1];
        if (j<ncols-1) ++values[i][j+1];
      }
    }
  }
}

void Sandpile::expand(int rows, int cols, bool absolute){
  if (absolute){
    rows -= nrows;
    cols -= ncols;
  }
  if (rows%2 || cols%2){
    std::cerr << "The increment in rows or columns must be even" << std::endl;
  }
  
  for(int i=0; i<nrows; ++i){
    values[i].insert(values[i].begin(), cols/2, 0);
    values[i].insert(values[i].end(), cols/2, 0);
  }
  ncols = values[0].size();
  
  values.insert(values.begin(), rows/2, std::vector<int>(ncols, 0));
  values.insert(values.end(), rows/2, std::vector<int>(ncols, 0));
  nrows = values.size();
}

void Sandpile::dump_to_file(const char* filename){
  std::ofstream outputfile;
  outputfile.open(filename);
  for(int i=0; i<nrows; ++i){
    for(int j=0; j<ncols; ++j){
      outputfile << values[i][j] << " ";
    }
    outputfile << std::endl;
  }
  outputfile.close();
}

void Sandpile::dump_to_file(const std::string filename){
  dump_to_file(filename.c_str());
}

void Sandpile::find_zero(){
  for (auto it=begin(); it!=end(); ++it) {
    if (*this + *it == *this) {
      zero = &(*it);
      break;
    }
  }
  if (!zero && DEBUG){
    std::cout << "There is no zero for Sandpile"
              << std::endl << *this << std::endl;
  }
}

void Sandpile::find_opposite(){
  if (zero){
    for (auto it=begin(); it!=end(); ++it) {
      if (*this + *it == *zero) {
        opposite = &(*it);
        break;
      }
    }
  }
  if (!opposite && DEBUG){
    std::cout << "There is no opposite for Sandpile"
              << std::endl << *this << std::endl;
  }
}


////////////////////////////////////////////////
// Externals
////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Sandpile& s){
  os << "----------" << std::endl;
  for(int i=0; i<s.nrows; ++i){
    for(int j=0; j<s.ncols; ++j){
      os << s[i][j] << " ";
    }
    os << std::endl;
  }
  os << "----------" << std::endl;
  return os;
}

array vector_to_array(std::vector<int> v, int rows, int cols){
  array a;
  for (int i=0; i<rows; ++i) {
    a.emplace_back(v.begin() + i*cols,
                   v.begin() + (i+1)*cols);
  }
  return a;
}
