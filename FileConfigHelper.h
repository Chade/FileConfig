#ifndef _FILECONFIGHELPER_H_
#define _FILECONFIGHELPER_H_

#include <Arduino.h>
#include <TimeLib.h>

typedef signed long signed_time_t;

bool toBool(String value) {
  value.trim();
  return value.equalsIgnoreCase(F("true"));
}

String fromBool(const bool& value) {
  return (value == true) ? F("true") : F("false");
}

time_t toTime(const String& value) {
  time_t out = 0;
  int i = value.indexOf(':');
  if (i != -1) {
    // Duration in HH:MM format
    out = value.substring(0).toInt() * SECS_PER_HOUR;
    out += value.substring(i+1).toInt() * SECS_PER_MIN;

    int j = value.indexOf(':', i+1);
    if (j != -1) {
      // Duration in HH:MM:SS format
      out += value.substring(j+1).toInt();
    }
  }
  else {
    // Duration in SSSS format
    return value.toInt();
  }

  return out;
}

signed_time_t toSignedTime(const String& value) {
  signed_time_t out = 0;

  int i = value.indexOf(':');
  if (i != -1) {
    // Duration in HH:MM format
    int sign, start;
    if (value.startsWith("+")) {
      sign  =  1;
      start =  1;
    }
    else if (value.startsWith("-")) {
      sign  = -1;
      start =  1;
    }
    else {
      sign  =  1;
      start =  0; 
    }

    out = value.substring(start).toInt() * SECS_PER_HOUR;
    out += value.substring(i+1).toInt() * SECS_PER_MIN;

    int j = value.indexOf(':', i+1);
    if (j != -1) {
      // Duration in HH:MM:SS format
      out += value.substring(j+1).toInt();
    }
    out *= sign;
  }
  else {
    // Duration in SSSS format
    return value.toInt();
  }

  return out;
}

String fromTime(const unsigned int& hour, const unsigned int& minute, const unsigned int& second, const char& prefix = '\0') {
  String timeString(prefix);

  if (hour < 10)
    timeString += '0';
  timeString += hour;
  timeString += ':';

  if (minute < 10)
    timeString += '0';
  timeString += minute;
  timeString += ':';

  if (second < 10)
    timeString += '0';
  timeString += second;

  return timeString;
}

String fromTime(const time_t& value) {
  uint32_t time = value;
  
  uint8_t second = time % 60;
  time /= 60;
  uint8_t minute = time % 60;
  time /= 60;
  uint8_t hour = time % 24;

  return fromTime(hour, minute, second);
}

String fromSignedTime(const signed_time_t& value) {
  uint32_t time = value;
  char prefix = '\0';

  if (value < 0)
  {
    prefix = '-';
    time *= -1;
  }

  uint8_t second = time % 60;
  time /= 60;
  uint8_t minute = time % 60;
  time /= 60;
  uint8_t hour = time % 24;

  return fromTime(hour, minute, second, prefix);
}

unsigned long toSeconds(const String& value) {
  return toTime(value);
}

long toSignedSeconds(const String& value) {
  return toSignedTime(value);
}

String fromSeconds(const unsigned long& value) {
  return fromTime(value);
}

String fromSignedSeconds(const long& value) {
  return fromSignedTime(value);
}

#endif // _FILECONFIGHELPER_H_
