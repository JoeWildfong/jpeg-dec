#pragma once

#include <string>
#include <vector>

class JPEGFrame {
  public:
    JPEGFrame(std::string& data);
    struct {
      unsigned char precision;
      unsigned short height;
      unsigned short width;
      unsigned char component_count;
    } header;
    typedef struct {
      unsigned char h_sampling;
      unsigned char v_sampling;
      unsigned char q_table;
    } FrameComponent;
    std::vector<FrameComponent> components;
};