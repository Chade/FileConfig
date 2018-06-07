#ifndef _FILECONFIGHELPER_H_
#define _FILECONFIGHELPER_H_

#include <Arduino.h>
#include <RTClib.h>

bool toBool(const String& value) {
  return value.equalsIgnoreCase(F("true")) ? true : false;
}

String fromBool(const bool& value) {
  return value == true ? F("true") : F("false");
}

unsigned long toSeconds(const String& value) {
  byte hour {0}, minute {0}, second {0};
  int i = value.indexOf(':');
  if (i != -1) {
    // Duration in HH:MM format
    hour = value.substring(0).toInt();
    minute = value.substring(i+1).toInt();
    
    int j = value.indexOf(':', i+1);
    if (j != -1) {
     // Duration in HH:MM:SS format
     second = value.substring(j+1).toInt();
    }
    return TimeSpan(0, hour, minute, second).totalseconds();
  }
  else {
    // Duration in SSSS format
    return value.toInt();
  }
}

String fromSeconds(const unsigned long& value) {
  TimeSpan span(value);
  String timeString("");
  if (span.days() != 0) {
    timeString = String(span.days());
    timeString += String(F(" days, "));
  }
  
  if (span.hours() < 10)
    timeString += '0';
  timeString += span.hours();
  timeString += ':';
  
  if (span.minutes() < 10)
    timeString += '0';
  timeString += span.minutes();
  timeString += ':';
  
  if (span.seconds() < 10)
    timeString += '0';
  timeString += span.seconds();
  
  return timeString;
}

#endif // _FILECONFIGHELPER_H_
