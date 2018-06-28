#include "FileConfig.h"


FileConfig::FileConfig(SDLib::File file) : SDLib::File(file) {
  // Init
} 

FileConfig::~FileConfig() {

}

uint16_t FileConfig::getFreeSram() {
  uint8_t newVariable;
  // Heap is empty, use bss as start memory address
  if ((uint16_t)__brkval == 0)
    return (((uint16_t)&newVariable) - ((uint16_t)&__bss_end));
  // Use heap end as the start of the memory address
  else
    return (((uint16_t)&newVariable) - ((uint16_t)__brkval));
}

void FileConfig::rewind() {
  seek(0);
}

bool FileConfig::isHeader(const String& line) {
  if (line.length() > 0) {
    int opening = line.indexOf('[');
    int closing = line.lastIndexOf(']');
    
    if (opening >= 0 && closing > 0 && closing > opening) {
      return true;
    }
  }
  return false;
}

bool FileConfig::isKeyValue(const String& line) {
  if (line.length() > 0 && line.indexOf('=') > 0) {
    return true;
  }
  return false;
}

char FileConfig::readNextSkip() {
  char symbol;
  
  if (!available()) {
    return symbol;
  }
  
  do { 
    symbol = read();
  } while (available() && (symbol == ' ' || symbol == '\t'));
  
  if (symbol == '#') {
    while (available() && symbol != '\n') {
      symbol = read();
    } 
  }
  return symbol;
}

String FileConfig::readNextLine() {
  String linebuffer;
  char symbol = readNextSkip();
  
  while (available() && symbol != '\n') {
    // Add character to linebuffer
    linebuffer += symbol;
    
    // Read next character
    symbol = readNextSkip();
  }

  return linebuffer;
}

String FileConfig::readNextHeader() {
  while (available()) {
    String line = readNextLine();
    
    if (isHeader(line)) {
      int opening = line.indexOf('[');
      int closing = line.lastIndexOf(']');
      lastLine = line;
      return line.substring(opening+1, closing);
    }
  }
  return String();
}

String FileConfig::readNextKeyValue() {
  while(available()) {
    String line = readNextLine();
    
    if (isKeyValue(line)) {
      lastLine = line;
      return line;
    }
  }
  return String();
}

bool FileConfig::readNextKeyValue(String& key, String& value) {
  String pair = readNextKeyValue();
  
  if (pair.length() > 0) {
    int index = pair.indexOf('=');
    key   = pair.substring(0, index);
    value = pair.substring(index + 1, pair.length());
    return true;
  }
  
  return false;
}

bool FileConfig::findHeader(const String& header, const bool& fromBeginning) {
  if (fromBeginning) {
    rewind();
  }
  
  while(available()) {
    if (header.equalsIgnoreCase(readNextHeader())) {
      return true;
    }
  }
  
  return false;
}

bool FileConfig::findKey(const String& key, const bool& fromBeginning) {
  if (fromBeginning) {
    rewind();
  }
  
  String candKey, candValue;
  while(readNextKeyValue(candKey, candValue)) {
    if (key.equalsIgnoreCase(candKey)) {
      return true;
    }
  }
  
  return false;
}

String FileConfig::getValue(const String& key, const String& header) {
  // Search from beginning
  rewind();
  counter = 0;
  
  // Search for header, if given
  if (header.length() > 0) {
    // Find right section
    if (!findHeader(header, false)) {
      return String();
    }
  }
  
  // Search key value pair
  String candKey, candValue;
  while(readNextKeyValue(candKey, candValue)) {
    if (key.equalsIgnoreCase(candKey)) {
      return candValue;
    }
  }
  
  return String();
}

String FileConfig::getLastLine() {
  return lastLine;
}

void FileConfig::clearLastLine() {
  lastLine = String();
}

