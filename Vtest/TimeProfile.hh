#include <chrono>
#include <string>
#include <memory>
#include <map>
#include <iostream>

namespace util{

  class TimeProfile
  {
  private:
    TimeProfile(){}
  public:
    ~TimeProfile(){}

    static std::unique_ptr<util::TimeProfile> createInstance();
    void begin(std::string);
    int end(std::string,bool print = true);

  private:
    std::map< std::string, std::chrono::high_resolution_clock::time_point > _measurements;
  };

  inline std::unique_ptr<util::TimeProfile> TimeProfile::createInstance()
  {
    return std::unique_ptr<util::TimeProfile>( new TimeProfile() );
  }

  inline void TimeProfile::begin(std::string label)
  {
    _measurements[label] = std::chrono::high_resolution_clock::now();
  }

  inline int TimeProfile::end(std::string label, bool print)
  {
    int counts = (int) std::chrono::duration_cast<std::chrono::nanoseconds>(
      std::chrono::high_resolution_clock::now() - _measurements[label]).count();
    if (print)
      std::cout << "Time lapse for label " << label << ": " << counts << " ns" << std::endl;
    return counts;
  }

  std::unique_ptr<util::TimeProfile> TimeProfiler = TimeProfile::createInstance();
}
