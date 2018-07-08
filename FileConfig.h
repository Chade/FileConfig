#ifndef _FILECONFIG_H_
#define _FILECONFIG_H_

#include <Arduino.h>
#include <SD.h>

extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

class FileConfig : public SDLib::File
{
  public:
    FileConfig(SDLib::File file);
    ~FileConfig();
    
    void   rewind();
    
    bool   findHeader(const String& header, const bool& fromBeginning = true);
    bool   findKey(const String& key, const bool& fromBeginning = true);
    
    String getValue(const String& key, const String& header = String());
	String getValue(const String& key, const String& header, void (* functionPointer)());
    
    String getLastLine();
    void   clearLastLine();
    
    uint16_t getFreeSram();
  
  protected:
    bool   isHeader(const String& line);
    bool   isKeyValue(const String& line);

    char   readNextSkip();
    String readNextLine();
    String readNextHeader();
    String readNextKeyValue();
    bool   readNextKeyValue(String& key, String& value);
    
  private:
    String lastLine;
};

#endif // _FILECONFIG_H_
