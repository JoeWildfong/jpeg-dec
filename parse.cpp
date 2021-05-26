#include "parse.h"
#include <iostream>

constexpr struct {
  unsigned char SOI = 0xD8;
  unsigned char EOI = 0xD9;
  unsigned char SOF0 = 0xC0;
  unsigned char SOF2 = 0xC2;
  unsigned char DHT = 0xC4;
  unsigned char DQT = 0xDB;
  unsigned char DRI = 0xDD;
  unsigned char SOS = 0xDA;
  unsigned char RSTmin = 0xD0;
  unsigned char RSTmax = 0xD7;
  unsigned char APPmin = 0xE0;
  unsigned char APPmax = 0xEF;
  unsigned char COM = 0xFE;
} Markers;
constexpr unsigned char TAGMARKER = 0xFF;

std::pair<std::string, std::string> pair(std::string a, std::string b) {
  return std::pair<std::string, std::string> (a, b);
}

std::string readUntilTag(std::ifstream& data) {
  std::string out = "";
  while (!data.eof()) {
    unsigned char read = data.get();
    if (data.eof()) {
      return out;
    }
    unsigned char next = data.peek();
    if (read == 0xFF) {
      if (next == 0x00) {
        out += read;
        data.get(); // advance stream to skip 0x00; 
      } else {
        break;
      }
    } else {
      out += read;
    }
  }
  return out;
}

JPEGParse::JPEGParse(std::ifstream& data) {
  tags.empty();
  tagNames.empty();
  if (readUntilTag(data) != "") {
    std::cout << "image does not start with marker";
  }
  unsigned char marker;
  std::string tagName;
  std::string tagValue;
  while (!data.eof()) {
    bool invalidTag = false;
    marker = data.get();
    switch (marker) {
      case Markers.SOI:
        // start of image
        tagName = "SOI";
        break;
      case Markers.EOI:
        // end of image reached
        return;
      case Markers.SOF0:
        // JPEG baseline
        tagName = "SOF0";
        break;
      case Markers.SOF2:
        // JPEG progressive
        tagName = "SOF2";
        break;
      case Markers.DHT:
        // Huffman tables
        tagName = "DHT";
        break;
      case Markers.DQT:
        // Quantization tables
        tagName = "DQT";
        break;
      case Markers.DRI:
        // Restart interval
        tagName = "DRI";
        break;
      case Markers.SOS:
        // Start of scan
        tagName = "SOS";
        break;
      case Markers.COM:
        // JPEG comment
        tagName = "COM";
        break;
      default:
        invalidTag = true;
    }
    // check for RSTn and APPn tags
    if (marker >= Markers.RSTmin && 
        marker <= Markers.RSTmax) {
      // RST tag
      char num = (marker & 0b00000111) + 0x30;
      tagName = std::string("RST") + num;
      invalidTag = false;
    }
    else if (marker >= Markers.APPmin && marker <= Markers.APPmax) {
      // APP tag
      char num;
      sprintf(&num, "%x", marker & 0b00001111);
      tagName = std::string("APP") + num;
      invalidTag = false;
    }
    if (invalidTag) {
      printf("Invalid tag found at offset %x: %#x\n", (unsigned int)data.tellg() - 1, marker);
      tagName = "";
    }
    if (tagName != "") {
      tagValue = readUntilTag(data);
      tagNames.push_back(tagName);
      tags.push_back(tagValue);
      //tags.insert(pair(tagName, tagValue));
    }
  }
}

std::vector<std::string> JPEGParse::getTags(std::string name) {
  std::vector<std::string> out;
  for (int i = 0; i < tagNames.size(); i++) {
    if (tagNames[i] == name) {
      out.push_back(tags[i]);
    }
  }
  return out;
}

std::string JPEGParse::toString() {
  std::string out = "";
  for (int i = 0; i < tags.size(); i++) {
    out += tagNames[i] + ": " + std::to_string(tags[i].length()) + "\n";
  }
  return out;
}