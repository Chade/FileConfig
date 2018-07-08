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

String fromTime(const unsigned int& hour, const unsigned int& minute, const unsigned int& second) {
  String timeString("");

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

String fromTime(const time_t& time) {
  String timeString("");

  if (hour(time) < 10)
    timeString += '0';
  timeString += hour(time);
  timeString += ':';

  if (minute(time) < 10)
    timeString += '0';
  timeString += minute(time);
  timeString += ':';

  if (second(time) < 10)
    timeString += '0';
  timeString += second(time);

  return timeString;
}

unsigned long toSeconds(const String& value) {
  return toTime(value);
}

String fromSeconds(const unsigned long& value) {
  return fromTime(value);
}

#endif // _FILECONFIGHELPER_H_
