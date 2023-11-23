#ifndef __ASCCI_ART_H__
#define __ASCCI_ART_H__

#include <fstream>
#include <iostream>
#include <string>

std::string getArt(std::ifstream& File, const std::string& filename) {
  std::string Lines = "";

  if (File.is_open()) {
    std::string TempLine;
    while (getline(File, TempLine)) {
      TempLine += "\n";
      Lines += TempLine;
    }
    return Lines;
  } else {
    return "ERROR: Could not open file " + filename;
  }
}

void yo() {
  std::ifstream Reader("banner.txt");
  std::string readArt = getArt(Reader, "banner.txt");
  Reader.close();

  if (readArt.find("ERROR") != std::string::npos) {
    std::cerr << readArt << std::endl;
  } else {
    std::cout << readArt << std::endl;
  }
}

#endif  // __ASCCI_ART_H__