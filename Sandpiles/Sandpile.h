#include <iostream>
#include <vector>
#include <iterator>
#include <string>

typedef std::vector<std::vector<int>> array;
typedef std::vector<Sandpile> SandpileCollection;
class Sandpile;

class Sandpile{
 public:
  ////////////////////////////////////////////////
  // Statics
  ////////////////////////////////////////////////
  static const int top = 4;
  static const bool DEBUG = true;
  static Sandpile generate_random(int rows=3, int cols=3);
  static const SandpileCollection generate_full_set(int rows=3, int cols=3);
  
  ////////////////////////////////////////////////
  // Attributes
  ////////////////////////////////////////////////
  int nrows, ncols;
  array values;
  const Sandpile* zero = nullptr;
  const Sandpile* opposite = nullptr;
  bool verbose = true;
  
  ////////////////////////////////////////////////
  // Constructors
  ////////////////////////////////////////////////
  Sandpile(const Sandpile& s);
  Sandpile(const array vals);
  Sandpile(int rows=3, int cols=3, int value=0);
  Sandpile(const char* filename);
  Sandpile(const std::string filename);
  
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  std::vector<int>& operator[](int row);
  std::vector<int>  operator[](int row) const;
  array& get_values();
  array  get_values() const;
  int sum() const;
  bool assert_dims(const Sandpile& s) const;
  Sandpile  operator+(const Sandpile& s) const;
  Sandpile  operator+(const int n) const;
  Sandpile  operator*(const int n) const;
  Sandpile& operator+=(const Sandpile& s);
  Sandpile& operator+=(const int n);
  Sandpile& operator*=(const int n);
  bool      operator==(const Sandpile& s) const;
  bool      operator!=(const Sandpile& s) const;
  void topple();
  void expand(int rows, int cols, bool absolute=false);
  void dump_to_file(const char* filename);
  void dump_to_file(const std::string filename);
  void find_zero();
  void find_opposite();
};

////////////////////////////////////////////////
// Inline implementations
////////////////////////////////////////////////
inline std::vector<int>& Sandpile::operator[](int row){
  return values[row];
}

inline std::vector<int> Sandpile::operator[](int row) const{
  return values[row];
}

inline array& Sandpile::get_values(){
  return values;
}

inline array  Sandpile::get_values() const{
  return values;
}

inline bool Sandpile::assert_dims(const Sandpile& s) const{
  return (nrows == s.nrows) && (ncols == s.ncols);
}

inline bool Sandpile::operator!=(const Sandpile& s) const{
  return !(*this == s);
}

////////////////////////////////////////////////
// Externals
////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& os, const Sandpile& s);
array vector_to_array(std::vector<int> v, int rows, int cols);
