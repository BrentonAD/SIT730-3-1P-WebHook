/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "c:/Users/brent/OneDrive/Documents/_UNIVERSITY/_MASTEROFAI/2022Tri1/SIT730-EmbeddedSystemDevelopment/Tasks/3/SIT730-Task3-1P-WebHook/3-1P-WebHook/src/3-1P-WebHook.ino"
/*
 * Project 3-1P-WebHook
 * Description: Example of reading data from DHT Temperature Sensor and publishing via webhook.
 * Author: Brenton Adey @BrentonAD
 * Date: 2022-04-25
 */
#include "../lib/PietteTech_DHT/src/PietteTech_DHT.h"

// Allows your code to run before the cloud is connected.
void setup();
void loop();
#line 10 "c:/Users/brent/OneDrive/Documents/_UNIVERSITY/_MASTEROFAI/2022Tri1/SIT730-EmbeddedSystemDevelopment/Tasks/3/SIT730-Task3-1P-WebHook/3-1P-WebHook/src/3-1P-WebHook.ino"
SYSTEM_THREAD(ENABLED);

// This uses the USB serial port for debugging logs.
SerialLogHandler logHandler;

int DHTTYPE = DHT11;
pin_t DHT_PIN = D5;          // Digital pin for communications

float tempValue;

PietteTech_DHT DHT(DHT_PIN, DHTTYPE);

void setup() {
  DHT.begin();
  
  delay(1000);  
}

void loop() {
  int result = DHT.acquireAndWait(1000); // wait up to 1 sec (default indefinitely)

  switch (result) {
  case DHTLIB_OK:
    Log.info("OK"); 
    tempValue = DHT.getCelsius();
    Log.info("tempValue=%f", tempValue);
    //Push value to integration
    Particle.publish("temp", String(tempValue), PRIVATE);
    break;
  case DHTLIB_ERROR_CHECKSUM:
    Log.info("Error\n\r\tChecksum error");
    break;
  case DHTLIB_ERROR_ISR_TIMEOUT:
    Log.info("Error\n\r\tISR time out error");
    break;
  case DHTLIB_ERROR_RESPONSE_TIMEOUT:
    Log.info("Error\n\r\tResponse time out error");
    break;
  case DHTLIB_ERROR_DATA_TIMEOUT:
    Log.info("Error\n\r\tData time out error");
    break;
  case DHTLIB_ERROR_ACQUIRING:
    Log.info("Error\n\r\tAcquiring");
    break;
  case DHTLIB_ERROR_DELTA:
    Log.info("Error\n\r\tDelta time to small");
    break;
  case DHTLIB_ERROR_NOTSTARTED:
    Log.info("Error\n\r\tNot started");
    break;
  default:
    Log.info("Unknown error");
    break;
  }

  delay(30000);
}