#include <fstream>
#include <string>
#include <vector>

class JPEGParse {
  public:
    JPEGParse(std::ifstream& data);
    std::vector<std::string> getTags(std::string name);
    std::string toString();
  private:
    std::vector<std::string> tagNames;
    std::vector<std::string> tags;
};