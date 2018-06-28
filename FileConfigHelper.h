#ifndef _FILECONFIGHELPER_H_
#define _FILECONFIGHELPER_H_

#include <Arduino.h>
#include <TimeLib.h>

bool toBool(const String& value) {
  return value.equalsIgnoreCase(F("true")) ? true : false;
}

String fromBool(const bool& value) {
  return value == true ? F("true") : F("false");
}

unsigned long toSeconds(const String& value) {
  byte newHour {0}, newMinute {0}, newSecond {0};
  int i = value.indexOf(':');
  if (i != -1) {
    // Duration in HH:MM format
    newHour = value.substring(0).toInt();
    newMinute = value.substring(i+1).toInt();
    
    int j = value.indexOf(':', i+1);
    if (j != -1) {
     // Duration in HH:MM:SS format
     newSecond = value.substring(j+1).toInt();
    }
    return newHour * SECS_PER_HOUR + newMinute * SECS_PER_MIN + newSecond;
  }
  else {
    // Duration in SSSS format
    return value.toInt();
  }
}

String fromSeconds(const unsigned long& value) {
  String timeString("");
  if (day(value) != 0) {
    timeString = String(day(value));
    timeString += String(F(" days, "));
  }
  
  if (hour(value) < 10)
    timeString += '0';
  timeString += hour(value);
  timeString += ':';
  
  if (minute(value) < 10)
    timeString += '0';
  timeString += minute(value);
  timeString += ':';
  
  if (second(value) < 10)
    timeString += '0';
  timeString += second(value);
  
  return timeString;
}

#endif // _FILECONFIGHELPER_H_
