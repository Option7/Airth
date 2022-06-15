






/*    //////////  ///////  //////    /////      ///////      ////////////  /////////              
 *      ///         ///      /////    ///      ///              ///           ///  ///               
 *      //////      ///      ///  //  ///      ///    /////     //////        ///////                 
 *      ///         ///      ///    /////      ///     ///      ///           ///  ///               
 *     /////      ///////  //////    //////      ////////     ////////////   ////    ///              
 *
 *
 *    ////////    /////////        ///////     //////    /////     ///////////    
 *     ///  ///      ///  ///        ///         /////    ///          ///         
 *     ///////       ///////         ///         ///  //  ///          ///         
 *     ///           ///  ///        ///         ///    /////          ///          
 *    /////         /////   ///    ///////     //////    //////       /////         
 *
 *
 *        ///      //////////  ////////////   ////////////    //////   /////    //////////        ///      //////   /////     /////////   ////////////
 *      // //         ///          ///          ///             /////   ///       ///   ///      // //       /////   ///    ///             ///           ////////////////////////////////////////////
 *     ///////        ///          ///          //////          ///  // ///       ///   ///     ///////      ///  // ///    ///             //////         //////////////////////////////////
 *   ///     ///      ///          ///          ///             ///    ////       ///   ///   ///     ///    ///    ////    ///             ///          ////////////////////////////////////////////////////
 *  /////   /////   //////       //////       ////////////    //////    //////  //////////   /////   ///// //////    /////   /////////    ////////////    ///
 *
 *
 *
 *    ///////   ///       ///    ///////    ////////////   ////////////   ///////      ///////          ///////////////////////////////////////////////////////////////////////////////
 *  ///          ///    ///    ///              ///          ///            /// ///  /// ///         /   ////////////////////////////////////////////////////////////////////////////////////////////////
 *  /////////      //////      /////////        ///          ////////       ///  //////  ///          /     /    ///////////////////////////////////////////////////////////////////////////////
 *        ////      ///              ////       ///          ///            ///   ///    ///         /    /    /////////////////////////////////////////////////////////////////////////////////////////////////////
 *  ////////      //////     //////////       //////     //////////////  ///////      //////// /    //////////////////////////////////////////////////////////////////////
 *
 */



















//#include <HTTPClient.h>
//#include <WiFi.h>
//#include <WiFiClient.h>
//#include <WiFiClientSecure.h>
#include <WebServer.h>
#include "Arduino.h"
#include "SPIFFS.h"
#include "xbm.h"             // Sketch tab header for xbm images
#include "time.h"
#include "ota.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0;

uint8_t hh,mm,ss;
byte omm = 99, oss = 99;
byte xcolon = 0, xsecs = 0;
unsigned int colour = 0;

#define TFT_GREY 0x5AEB
uint32_t targetTime = 0;                    // for next 1 second timeout

#include <TFT_eSPI.h>        // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();   // Invoke library

int del = false;
int fing = true;
int wifiReset = true;
#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial2);

uint8_t id;
String firstName ;
String lastName ;
String dateOfBirth ;
String telephone ;
String fingerId;
String wifissid;
String wifipassword;
int fnPosition;
int lnPosition;
int dobPosition;
int tPosition;
int idPosition;
int wifissidPosition;
int wifipasswordPosition;


String WIFI_SSID ;
String WIFI_PASSWORD ;

const char* ssid = "HavennG";
const char* password = "HHHHHHHH";


// Your GPRS credentials (leave empty, if not needed)
const char apn[]      = "internet"; // APN (example: internet.vodafone.pt) use https://wiki.apnchanger.org
const char gprsUser[] = ""; // GPRS User
const char gprsPass[] = ""; // GPRS Password

// SIM card PIN (leave empty, if not defined)
const char simPIN[]   = ""; 

// Server details
// The server variable can be just a domain name or it can have a subdomain. It depends on the service you are using
const char serve[] = "maker.ifttt.com"; // domain name: example.com, maker.ifttt.com, etc
//const char serve[] = "navantrics.com"; // domain name: example.com, maker.ifttt.com, etc


//const char resourceC[] = "/trigger/children/with/key/cVMHR0LbEitAZVeyAf-2DS";         // resource path, for example: /post-data.php
const char resourceT[] = "/trigger/teens/with/key/cVMHR0LbEitAZVeyAf-2DS";         // resource path, for example: /post-data.php
//const char resourceYA[] = "/trigger/young_adults/with/key/cVMHR0LbEitAZVeyAf-2DS";         // resource path, for example: /post-data.php
const char resourceA[] = "/trigger/adults/with/key/cVMHR0LbEitAZVeyAf-2DS";         // resource path, for example: /post-data.php
//const char resourceA[] = "/n/jel/api/add_fingerprint.php";         // resource path, for example: /post-data.php

//const char resourceA[] = "/trigger/attendance/with/key/cVMHR0LbEitAZVeyAf-2DS";         // resource path, for example: /post-data.php
//const char resourceV[] = "/trigger/visitors/with/key/cVMHR0LbEitAZVeyAf-2DS";         // resource path, for example: /post-data.php
const char url[] = "navantrics.com/n/jel/api/add_fingerprint.php";
const int  port = 80;

// TTGO T-Call pins
#define MODEM_RST            5
#define MODEM_PWKEY          4
#define MODEM_POWER_ON       23
#define MODEM_TX             27
#define MODEM_RX             26
#define I2C_SDA              21
#define I2C_SCL              22


//   TFT_MISO  19 // (leave TFT SDO disconnected if other SPI devices share MISO)
//   TFT_MOSI  23
//   TFT_SCLK  18
//   TFT_CS    15  // Chip select control pin
//   TFT_DC    2  // Data Command control pin
//   TFT_RST   4  // Reset pin (could connect to RST pin)


//#define DISPLAY         1
//#define FINGER          2
//#define WEBSERVER       3

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to SIM800 module)
#define SerialAT Serial1

// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM800   // Modem is SIM800
#define TINY_GSM_RX_BUFFER   1024  // Set RX buffer to 1Kb

// Define the serial console for debug prints, if needed
//#define DUMP_AT_COMMANDS

#include <Wire.h>
#include <TinyGsmClient.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch

#ifdef DUMP_AT_COMMANDS
  #include <StreamDebugger.h>
  StreamDebugger debugger(SerialAT, SerialMon);
  TinyGsm modem(debugger);
#else
  TinyGsm modem(SerialAT);
#endif

// I2C for SIM800 (to keep it running when powered from battery)
TwoWire I2CPower = TwoWire(0);

// TinyGSM Client for Internet connection
//TinyGsmClient client(modem);
 WiFiClientSecure client;

#define IP5306_ADDR          0x75
#define IP5306_REG_SYS_CTL0  0x00

bool setPowerBoostKeepOn(int en){
  I2CPower.beginTransmission(IP5306_ADDR);
  I2CPower.write(IP5306_REG_SYS_CTL0);
  if (en) {
    I2CPower.write(0x37); // Set bit1: 1 enable 0 disable boost keep on
  } else {
    I2CPower.write(0x35); // 0x37 is default reg value
  }
  return I2CPower.endTransmission() == 0;
}


/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
WebServer server(80);


uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      SerialMon.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      SerialMon.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      SerialMon.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      SerialMon.println("Imaging error");
      return p;
    default:
      SerialMon.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      SerialMon.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      SerialMon.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      SerialMon.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      SerialMon.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      SerialMon.println("Could not find fingerprint features");
      return p;
    default:
      SerialMon.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    SerialMon.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    SerialMon.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    SerialMon.println("Did not find a match");
    return p;
  } else {
    SerialMon.println("Unknown error");
    return p;
  }   
  
  // found a match!
  SerialMon.print("Found ID #"); SerialMon.print(finger.fingerID); 
  SerialMon.print(" with confidence of "); SerialMon.println(finger.confidence); 

  return finger.fingerID;
}





uint8_t deleteFingerprint(uint8_t id) {
  uint8_t p = -1;
  
  p = finger.deleteModel(id);
String delMsg ;
  if (p == FINGERPRINT_OK) {
    Serial.println("Deleted!");
    delMsg = "Deleted!";
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    delMsg = "Communication error";
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not delete in that location");
    delMsg = "Could not delete in that location";
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    delMsg = "Error writing to flash";
    return p;
  } else {
    Serial.print("Unknown error: 0x"); Serial.println(p, HEX);
    delMsg = "Unknown error: 0x" + (p, HEX);
    return p;
  }

         tft.fillScreen(TFT_BLUE);
         tft.setTextColor(TFT_WHITE);
         
         tft.setCursor(40, 150);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print("DELETION STATUS:");
         tft.setCursor(50, 200);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print(delMsg);
         delay(2000);
         tft.fillScreen(TFT_BLUE);
}

uint8_t getFingerprintEnroll() {
 String enrMsg;
int p = -1;
SerialMon.print("Waiting for valid finger to enroll as #"); SerialMon.println(id);
         tft.fillScreen(TFT_BLUE);
         tft.setTextColor(TFT_WHITE);
         
         tft.setCursor(40, 150);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print("WAITING FOR VALID");
         tft.setCursor(50, 200);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print("FINGER TO ENROLL");
         delay(2000);

while (p != FINGERPRINT_OK) {
p = finger.getImage();
switch (p) {
case FINGERPRINT_OK:
SerialMon.println("Image taken");
enrMsg = "Image taken";
break;
case FINGERPRINT_NOFINGER:
SerialMon.println(".");
enrMsg = "Waiting for finger";
break;
case FINGERPRINT_PACKETRECIEVEERR:
SerialMon.println("Communication error");
enrMsg = "Communication error";
break;
case FINGERPRINT_IMAGEFAIL:
SerialMon.println("Imaging error");
enrMsg = "Imaging error";
break;
default:
SerialMon.println("Unknown error");
enrMsg = "Unknown error";
break;
}
         tft.fillScreen(TFT_BLUE);
         tft.setTextColor(TFT_WHITE);
         
         tft.setCursor(40, 150);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print(enrMsg);
         delay(2000);
 
}

 
// OK success!
 
p = finger.image2Tz(1);
switch (p) {
case FINGERPRINT_OK:
SerialMon.println("Image converted");
enrMsg = "Image converted";
break;
case FINGERPRINT_IMAGEMESS:
SerialMon.println("Image too messy");
enrMsg = "Image too messy";
return p;
case FINGERPRINT_PACKETRECIEVEERR:
SerialMon.println("Communication error");
enrMsg = "Communication error";
return p;
case FINGERPRINT_FEATUREFAIL:
SerialMon.println("Could not find fingerprint features");
enrMsg = "Could not find fingerprint features";
return p;
case FINGERPRINT_INVALIDIMAGE:
SerialMon.println("Could not find fingerprint features");
enrMsg = "Could not find fingerprint features";
return p;
default:
SerialMon.println("Unknown error");
enrMsg = "Unknown error";
return p;

         tft.fillScreen(TFT_BLUE);
         tft.setTextColor(TFT_WHITE);
         
         tft.setCursor(40, 150);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print(enrMsg);
         delay(2000);
}
 
SerialMon.println("Remove finger");
enrMsg = "Remove finger";
         tft.fillScreen(TFT_BLUE);
         tft.setTextColor(TFT_WHITE);
         
         tft.setCursor(40, 150);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print(enrMsg);
         
delay(2000);
p = 0;
while (p != FINGERPRINT_NOFINGER) {
p = finger.getImage();
}
SerialMon.print("ID "); SerialMon.println(id);
p = -1;
SerialMon.println("Place same finger again");
enrMsg = "Place same finger again";
         tft.fillScreen(TFT_BLUE);
         tft.setTextColor(TFT_WHITE);
         
         tft.setCursor(40, 150);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print(enrMsg);
         delay(2000);
while (p != FINGERPRINT_OK) {
p = finger.getImage();
switch (p) {
case FINGERPRINT_OK:
SerialMon.println("Image taken");
enrMsg = "Image taken";
break;
case FINGERPRINT_NOFINGER:
SerialMon.print(".");
enrMsg = "Waiting for finger";
break;
case FINGERPRINT_PACKETRECIEVEERR:
SerialMon.println("Communication error");
enrMsg = "Communication error";
break;
case FINGERPRINT_IMAGEFAIL:
SerialMon.println("Imaging error");
enrMsg = "Imaging error";
break;
default:
SerialMon.println("Unknown error");
enrMsg = "Unknown error";
break;
}
         tft.fillScreen(TFT_BLUE);
         tft.setTextColor(TFT_WHITE);
         
         tft.setCursor(40, 150);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print(enrMsg);
         delay(2000);
}
 
// OK success!
 
p = finger.image2Tz(2);
switch (p) {
case FINGERPRINT_OK:
SerialMon.println("Image converted");
break;
case FINGERPRINT_IMAGEMESS:
SerialMon.println("Image too messy");
return p;
case FINGERPRINT_PACKETRECIEVEERR:
SerialMon.println("Communication error");
return p;
case FINGERPRINT_FEATUREFAIL:
SerialMon.println("Could not find fingerprint features");
return p;
case FINGERPRINT_INVALIDIMAGE:
SerialMon.println("Could not find fingerprint features");
return p;
default:
SerialMon.println("Unknown error");
return p;
}
 
// OK converted!
SerialMon.print("Creating model for #"); SerialMon.println(id);
 
p = finger.createModel();
if (p == FINGERPRINT_OK) {
SerialMon.println("Prints matched!");
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
SerialMon.println("Communication error");
return p;
} else if (p == FINGERPRINT_ENROLLMISMATCH) {
SerialMon.println("Fingerprints did not match");
return p;
} else {
SerialMon.println("Unknown error");
return p;
}
 
SerialMon.print("ID "); SerialMon.println(id);
p = finger.storeModel(id);
if (p == FINGERPRINT_OK) {
SerialMon.println("Stored!");
} else if (p == FINGERPRINT_PACKETRECIEVEERR) {
SerialMon.println("Communication error");
return p;
} else if (p == FINGERPRINT_BADLOCATION) {
SerialMon.println("Could not store in that location");
return p;
} else if (p == FINGERPRINT_FLASHERR) {
SerialMon.println("Error writing to flash");
return p;
} else {
SerialMon.println("Unknown error");
return p;
}

tft.fillScreen(TFT_BLUE);
}






// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  SerialMon.print("Found ID #"); SerialMon.print(finger.fingerID); 
  SerialMon.print(" with confidence of "); SerialMon.println(finger.confidence);
  return finger.fingerID; 

}

uint8_t readnumber(void) {
uint8_t num = 0;
 
while (num == 0) {
while (! SerialMon.available());
num = SerialMon.parseInt();
}
return num;
}





void animation(){
  unsigned long tn = 0;
  
  tn = micros();
  tft.fillScreen(TFT_BLACK);

  yield(); Serial.println(F("Benchmark                Time (microseconds)"));

  yield(); Serial.print(F("Screen fill              "));
  yield(); Serial.println(testFillScreen());
  //total+=testFillScreen();
  //delay(500);

  yield(); Serial.print(F("Text                     "));
  yield(); Serial.println(testText());
  //total+=testText();
  //delay(3000);

  yield(); Serial.print(F("Lines                    "));
  yield(); Serial.println(testLines(TFT_CYAN));
  //total+=testLines(TFT_CYAN);
  //delay(500);

  yield(); Serial.print(F("Horiz/Vert Lines         "));
  yield(); Serial.println(testFastLines(TFT_RED, TFT_BLUE));
  //total+=testFastLines(TFT_RED, TFT_BLUE);
  //delay(500);

  yield(); Serial.print(F("Rectangles (outline)     "));
  yield(); Serial.println(testRects(TFT_GREEN));
  //total+=testRects(TFT_GREEN);
  //delay(500);

  yield(); Serial.print(F("Rectangles (filled)      "));
  yield(); Serial.println(testFilledRects(TFT_YELLOW, TFT_MAGENTA));
  //total+=testFilledRects(TFT_YELLOW, TFT_MAGENTA);
  //delay(500);

  yield(); Serial.print(F("Circles (filled)         "));
  yield(); Serial.println(testFilledCircles(10, TFT_MAGENTA));
  //total+= testFilledCircles(10, TFT_MAGENTA);

  yield(); Serial.print(F("Circles (outline)        "));
  yield(); Serial.println(testCircles(10, TFT_WHITE));
  //total+=testCircles(10, TFT_WHITE);
  //delay(500);

  yield(); Serial.print(F("Triangles (outline)      "));
  yield(); Serial.println(testTriangles());
  //total+=testTriangles();
  //delay(500);

  yield(); Serial.print(F("Triangles (filled)       "));
  yield(); Serial.println(testFilledTriangles());
  //total += testFilledTriangles();
  //delay(500);

  yield(); Serial.print(F("Rounded rects (outline)  "));
  yield(); Serial.println(testRoundRects());
  //total+=testRoundRects();
  //delay(500);

  yield(); Serial.print(F("Rounded rects (filled)   "));
  yield(); Serial.println(testFilledRoundRects());
  //total+=testFilledRoundRects();
  //delay(500);

  yield(); Serial.println(F("Done!")); yield();
  //Serial.print(F("Total = ")); Serial.println(total);
  
  //yield();Serial.println(millis()-tn);
  
  }

unsigned long testFillScreen() {
  unsigned long start = micros();
  tft.fillScreen(TFT_BLACK);
  tft.fillScreen(TFT_RED);
  tft.fillScreen(TFT_GREEN);
  tft.fillScreen(TFT_BLUE);
  tft.fillScreen(TFT_BLACK);
  return micros() - start;
}

unsigned long testText() {
  tft.fillScreen(TFT_BLACK);
  unsigned long start = micros();
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(TFT_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
  tft.setTextColor(TFT_RED);    tft.setTextSize(3);
  tft.println(0xDEADBEEF, HEX);
  tft.println();
  tft.setTextColor(TFT_GREEN);
  tft.setTextSize(5);
  tft.println("Groop");
  tft.setTextSize(2);
  tft.println("I implore thee,");
  //tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setTextSize(1);
  tft.println("my foonting turlingdromes.");
  tft.println("And hooptiously drangle me");
  tft.println("with crinkly bindlewurdles,");
  tft.println("Or I will rend thee");
  tft.println("in the gobberwarts");
  tft.println("with my blurglecruncheon,");
  tft.println("see if I don't!");
  return micros() - start;
}

unsigned long testLines(uint16_t color) {
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(TFT_BLACK);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing
  yield();
  tft.fillScreen(TFT_BLACK);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;
  yield();
  tft.fillScreen(TFT_BLACK);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;
  yield();
  tft.fillScreen(TFT_BLACK);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  yield();
  return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
  unsigned long start;
  int           x, y, w = tft.width(), h = tft.height();

  tft.fillScreen(TFT_BLACK);
  start = micros();
  for (y = 0; y < h; y += 5) tft.drawFastHLine(0, y, w, color1);
  for (x = 0; x < w; x += 5) tft.drawFastVLine(x, 0, h, color2);

  return micros() - start;
}

unsigned long testRects(uint16_t color) {
  unsigned long start;
  int           n, i, i2,
                cx = tft.width()  / 2,
                cy = tft.height() / 2;

  tft.fillScreen(TFT_BLACK);
  n     = min(tft.width(), tft.height());
  start = micros();
  for (i = 2; i < n; i += 6) {
    i2 = i / 2;
    tft.drawRect(cx - i2, cy - i2, i, i, color);
  }

  return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
  unsigned long start, t = 0;
  int           n, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(TFT_BLACK);
  n = min(tft.width(), tft.height());
  for (i = n - 1; i > 0; i -= 6) {
    i2    = i / 2;
    start = micros();
    tft.fillRect(cx - i2, cy - i2, i, i, color1);
    t    += micros() - start;
    // Outlines are not included in timing results
    tft.drawRect(cx - i2, cy - i2, i, i, color2);
  }

  return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

  tft.fillScreen(TFT_BLACK);
  start = micros();
  for (x = radius; x < w; x += r2) {
    for (y = radius; y < h; y += r2) {
      tft.fillCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
  unsigned long start;
  int           x, y, r2 = radius * 2,
                      w = tft.width()  + radius,
                      h = tft.height() + radius;

  // Screen is not cleared for this one -- this is
  // intentional and does not affect the reported time.
  start = micros();
  for (x = 0; x < w; x += r2) {
    for (y = 0; y < h; y += r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }

  return micros() - start;
}

unsigned long testTriangles() {
  unsigned long start;
  int           n, i, cx = tft.width()  / 2 - 1,
                      cy = tft.height() / 2 - 1;

  tft.fillScreen(TFT_BLACK);
  n     = min(cx, cy);
  start = micros();
  for (i = 0; i < n; i += 5) {
    tft.drawTriangle(
      cx    , cy - i, // peak
      cx - i, cy + i, // bottom left
      cx + i, cy + i, // bottom right
      tft.color565(0, 0, i));
  }

  return micros() - start;
}

unsigned long testFilledTriangles() {
  unsigned long start, t = 0;
  int           i, cx = tft.width()  / 2 - 1,
                   cy = tft.height() / 2 - 1;

  tft.fillScreen(TFT_BLACK);
  start = micros();
  for (i = min(cx, cy); i > 10; i -= 5) {
    start = micros();
    tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(0, i, i));
    t += micros() - start;
    tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                     tft.color565(i, i, 0));
  }

  return t;
}

unsigned long testRoundRects() {
  unsigned long start;
  int           w, i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(TFT_BLACK);
  w     = min(tft.width(), tft.height());
  start = micros();
  for (i = 0; i < w; i += 6) {
    i2 = i / 2;
    tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(i, 0, 0));
  }

  return micros() - start;
}

unsigned long testFilledRoundRects() {
  unsigned long start;
  int           i, i2,
                cx = tft.width()  / 2 - 1,
                cy = tft.height() / 2 - 1;

  tft.fillScreen(TFT_BLACK);
  start = micros();
  for (i = min(tft.width(), tft.height()); i > 20; i -= 6) {
    i2 = i / 2;
    tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(0, i, 0));
    yield();
  }

  return micros() - start;
}

void checkFinger(){
  int ID = getFingerprintIDez();
 if (ID > 0){
 delay(50);

  String path = "/";
   path += ID;
    path += ".txt";
         tft.fillScreen(TFT_BLUE); // Clear screen to navy background
        
         tft.setCursor(150, 60);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print("ID#:");
         tft.print(ID);
        // delay(2000);
 
  File  testFile = SPIFFS.open(path);
    if (testFile){
      String datum = testFile.readString();
        SerialMon.println("Read file content!");
        SerialMon.println(datum);
        /**
         * File derivate from Stream so you can use all Stream method
         * readBytes, findUntil, parseInt, println etc
         */
       
       // const String dat = testFile.readString();
         
         //tft.drawString(testFile.readString(), 0, 70, 6);
        
         
        
          //tft.setTextColor(TFT_BLUE, TFT_BLACK);
         //tft.fillScreen(TFT_BLUE);
         tft.setTextColor(TFT_WHITE);
         
         tft.setCursor(40, 150);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print("FINGER LOGGED");
         tft.setCursor(50, 200);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print("SUCCESSFULLY");
         delay(2000);

         tft.fillScreen(TFT_BLUE);
         tft.setTextColor(TFT_WHITE);
         
         tft.setCursor(120, 100);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print("WELCOME");
         tft.setCursor(50, 200);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print(datum);
         delay(1000);
         logIFTTTAttendance(ID, datum);
        testFile.close();


/*

if(WiFi.status() == WL_CONNECTED) 
   { Serial.println("wifi connected"); }
else
   { connect_wifi();    }
  

    SerialMon.print("Connecting to ");
    SerialMon.print(serve);
    if (client.connect(serve, port)) {
      SerialMon.println(" OK");
    }
    else {
      SerialMon.println(" FAIL");
    }
    //delay(3000);
  
        // Making an HTTP POST request
      SerialMon.println("Performing HTTP POST request...");
      // Prepare your HTTP POST request data (Temperature in Celsius degrees)
      String jsonObject =  "value1=" + String(ID)
                             + "&value2=" + String(testFile.readString()) 
                                + "&value3=" + String("PRESENT") + "";
                                     
      client.print(String("POST ") + resourceT + " HTTP/1.1/r/n");
      client.print(String("Host: ") + serve + "/r/n");
      client.println("Connection: close");
      client.println("Content-Type: application/x-www-form-urlencoded");
      client.print("Content-Length: ");
      client.println(jsonObject.length());
      client.println();
      client.println(jsonObject);

      unsigned long timeout = millis();
      while (client.connected() && millis() - timeout < 10000L) {
        // Print available data (HTTP response from server)
        while (client.available()) {
          char c = client.read();
          SerialMon.print(c);
          timeout = millis();
        }
      }
      SerialMon.println();
    
      // Close client and disconnect
      client.stop();
      SerialMon.println(F("Server disconnected"));
        
    }else{
        SerialMon.println("Problem on read file!");
    }*/
    }
    tft.fillScreen(TFT_BLUE);
 }
  }






//Check if header is present and correct
bool is_authentified() {
  SerialMon.println("Enter is_authentified");
  if (server.hasHeader("Cookie")) {
    SerialMon.print("Found cookie: ");
    String cookie = server.header("Cookie");
    SerialMon.println(cookie);
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      SerialMon.println("Authentification Successful");
      return true;
    }
  }
  SerialMon.println("Authentification Failed");
  return false;
}


void handleConfig() {
  String msg;
  if (server.hasHeader("Cookie")) {
    SerialMon.print("Found cookie: ");
    String cookie = server.header("Cookie");
    SerialMon.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    SerialMon.println("Disconnection");
    server.sendHeader("Location", "/config");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (  server.hasArg("WIFISSID")    && server.hasArg("WIFIPASSWORD")  ) {
   
    wifissid        = server.arg("WIFISSID");
    wifipassword    = server.arg("WIFIPASSWORD");
    

    wifissidPosition = wifissid.indexOf(wifissid );
    wifipasswordPosition = wifipassword.indexOf(wifipassword);

    
if (isAlpha(wifissid.charAt(wifissidPosition)) && isAlpha(wifipassword.charAt(wifipasswordPosition))  ){

 SPIFFS.remove("/wifissid.txt");
 SPIFFS.remove("/wifipassword.txt");
 SerialMon.println("Old wifi details Deleted!");
 delay(50);

 File testFile = SPIFFS.open("/wifissid.txt", FILE_WRITE);
 File testFileDetails = SPIFFS.open("/wifipassword.txt", FILE_WRITE);
 
    if (testFile){
        SerialMon.println("Write file content!");
        testFile.print(wifissid);
        testFile.close();
    }else{
        SerialMon.println("Problem on create wifi ssid file!");
    }

    if (testFileDetails){
        SerialMon.println("Write file content!");
        testFileDetails.print(wifipassword);
        testFileDetails.close();
    }else{
        SerialMon.println("Problem on create wifi password file!");
    }
  }
      wifiReset = true;
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      SerialMon.println("Config Successful");
      return;
}
else{
    msg = "Failed to update ssid/password! try again.";
    SerialMon.println("Failed to update Failed");
}

  String config = "<!DOCTYPE html>";
config += "<html lang=\"en\" dir=\"ltr\">";
config += "<head>";
config += " <meta charset=\"utf-8\">";
config += " <title>Admin Login Form</title>";
config += " <link rel=\"stylesheet\" href=\"https://unpkg.com/ionicons@4.5.10-0/dist/css/ionicons.min.css\">";
config += "<style type=\"text/css\">";
config += "@import url('https://fonts.googleapis.com/css?family=Montserrat:500,700&amp;display=swap');";
config += "  body, html {";
config += " background-color: #EBECF0;";
config += "}";
config += "body, p, input, select, textarea, button {";
config += " font-family: \"Montserrat\", sans-serif;";
config += " letter-spacing: -0.2px;";
config += " font-size: 16px;";
config += "}";
config += "div, p {";
config += " color: #BABECC;";
config += " text-shadow: 1px 1px 1px #FFF;";
config += "}";
config += "form {";
config += " padding: 16px;";
config += " width: 320px;";
config += " margin: 0 auto;";
config += "}";
config += ".segment {";
config += " padding: 32px 0;";
config += " text-align: center;";
config += "}";
config += "button, input {";
config += " border: 0;";
config += " outline: 0;";
config += " font-size: 16px;";
config += " border-radius: 320px;";
config += " padding: 16px;";
config += " background-color: #EBECF0;";
config += " text-shadow: 1px 1px 0 #FFF;";
config += "}";
config += "label {";
config += " display: block;";
config += " margin-bottom: 24px;";
config += " width: 100%;";
config += "}";
config += "input {";
config += " margin-right: 8px;";
config += " box-shadow: inset 2px 2px 5px #BABECC, inset -5px -5px 10px #FFF;";
config += " width: 100%;";
config += " box-sizing: border-box;";
config += " transition: all 0.2s ease-in-out;";
config += " appearance: none;";
config += " -webkit-appearance: none;";
config += "}";
config += "input:focus {";
config += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
config += "}";
config += "button {";
config += " color: #61677C;";
config += " font-weight: bold;";
config += " box-shadow: -5px -5px 20px #FFF, 5px 5px 20px #BABECC;";
config += " transition: all 0.2s ease-in-out;";
config += " cursor: pointer;";
config += " font-weight: 600;";
config += "}";
config += "button:hover {";
config += " box-shadow: -2px -2px 5px #FFF, 2px 2px 5px #BABECC;";
config += "}";
config += "button:active {";
config += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
config += "}";
config += "button .icon {";
config += " margin-right: 8px;";
config += "}";
config += "button.unit {";
config += " border-radius: 8px;";
config += " line-height: 0;";
config += " width: 48px;";
config += " height: 48px;";
config += " display: inline-flex;";
config += " justify-content: center;";
config += " align-items: center;";
config += " margin: 0 8px;";
config += " font-size: 19.2px;";
config += "}";
config += "button.unit .icon {";
config += " margin-right: 0;";
config += "}";
config += "button.red {";
config += " display: block;";
config += " width: 100%;";
config += " color: #00ced1;";
config += "}";
config += ".input-group {";
config += " display: flex;";
config += " align-items: center;";
config += " justify-content: flex-start;";
config += "}";
config += ".input-group label {";
config += " margin: 0;";
config += " flex: 1;";
config += "}";
config += "h1 { color:#00ced1; }";
config += "</style></head>";
config += "<body>";
config += "<form action='/config' method='POST'>";
config += "<div class='segment'>";
config += "<h1>WIFI CREDENTIALS CONFIG</h1></div>";
config += "<label>";
config += "<input type='text' name='WIFISSID' placeholder='Wifi ssid'><br>";
config += "</label>";
config += "<label>";
config += "<input type='password' name='WIFIPASSWORD' placeholder='Wifi password'><br>";
config += "</label>";
config += "<button class='red' type='submit' name='SUBMIT' value='Submit'><i class=\"icon ion-md-lock\"></i>Save</button>";
config += "</form></body></html>";
 fing = true; 
  server.send(200, "text/html", config);
}




//login page, also called for disconnect
void handleLogin() {
  String msg;
  if (server.hasHeader("Cookie")) {
    SerialMon.print("Found cookie: ");
    String cookie = server.header("Cookie");
    SerialMon.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    SerialMon.println("Disconnection");
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")) {
    if (server.arg("USERNAME") == "admin" &&  server.arg("PASSWORD") == "admin") {
      server.sendHeader("Location", "/");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      SerialMon.println("Log in Successful");
      return;
    }
    msg = "Wrong username/password! try again.";
    SerialMon.println("Log in Failed");
  }
  String login = "<!DOCTYPE html>";
login += "<html lang=\"en\" dir=\"ltr\">";
login += "<head>";
login += " <meta charset=\"utf-8\">";
login += " <title>Admin Login Form</title>";
login += " <link rel=\"stylesheet\" href=\"https://unpkg.com/ionicons@4.5.10-0/dist/css/ionicons.min.css\">";
login += "<style type=\"text/css\">";
login += "@import url('https://fonts.googleapis.com/css?family=Montserrat:500,700&amp;display=swap');";
login += "  body, html {";
login += " background-color: #EBECF0;";
login += "}";
login += "body, p, input, select, textarea, button {";
login += " font-family: \"Montserrat\", sans-serif;";
login += " letter-spacing: -0.2px;";
login += " font-size: 16px;";
login += "}";
login += "div, p {";
login += " color: #BABECC;";
login += " text-shadow: 1px 1px 1px #FFF;";
login += "}";
login += "form {";
login += " padding: 16px;";
login += " width: 320px;";
login += " margin: 0 auto;";
login += "}";
login += ".segment {";
login += " padding: 32px 0;";
login += " text-align: center;";
login += "}";
login += "button, input {";
login += " border: 0;";
login += " outline: 0;";
login += " font-size: 16px;";
login += " border-radius: 320px;";
login += " padding: 16px;";
login += " background-color: #EBECF0;";
login += " text-shadow: 1px 1px 0 #FFF;";
login += "}";
login += "label {";
login += " display: block;";
login += " margin-bottom: 24px;";
login += " width: 100%;";
login += "}";
login += "input {";
login += " margin-right: 8px;";
login += " box-shadow: inset 2px 2px 5px #BABECC, inset -5px -5px 10px #FFF;";
login += " width: 100%;";
login += " box-sizing: border-box;";
login += " transition: all 0.2s ease-in-out;";
login += " appearance: none;";
login += " -webkit-appearance: none;";
login += "}";
login += "input:focus {";
login += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
login += "}";
login += "button {";
login += " color: #61677C;";
login += " font-weight: bold;";
login += " box-shadow: -5px -5px 20px #FFF, 5px 5px 20px #BABECC;";
login += " transition: all 0.2s ease-in-out;";
login += " cursor: pointer;";
login += " font-weight: 600;";
login += "}";
login += "button:hover {";
login += " box-shadow: -2px -2px 5px #FFF, 2px 2px 5px #BABECC;";
login += "}";
login += "button:active {";
login += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
login += "}";
login += "button .icon {";
login += " margin-right: 8px;";
login += "}";
login += "button.unit {";
login += " border-radius: 8px;";
login += " line-height: 0;";
login += " width: 48px;";
login += " height: 48px;";
login += " display: inline-flex;";
login += " justify-content: center;";
login += " align-items: center;";
login += " margin: 0 8px;";
login += " font-size: 19.2px;";
login += "}";
login += "button.unit .icon {";
login += " margin-right: 0;";
login += "}";
login += "button.red {";
login += " display: block;";
login += " width: 100%;";
login += " color: #00ced1;";
login += "}";
login += ".input-group {";
login += " display: flex;";
login += " align-items: center;";
login += " justify-content: flex-start;";
login += "}";
login += ".input-group label {";
login += " margin: 0;";
login += " flex: 1;";
login += "}";
login += "h1 { color:#00ced1; }";
login += "</style></head>";
login += "<body>";
login += "<form action='/login' method='POST'>";
login += "<div class='segment'>";
login += "<h1>ADMINISTRATOR LOGIN</h1></div>";
login += "<label>";
login += "<input type='text' name='USERNAME' placeholder='Username'><br>";
login += "</label>";
login += "<label>";
login += "<input type='password' name='PASSWORD' placeholder='Password'><br>";
login += "</label>";
login += "<button class='red' type='submit' name='SUBMIT' value='Submit'><i class=\"icon ion-md-lock\"></i> Log in</button>";
login += "</form></body></html>";
 fing = true; 
  server.send(200, "text/html", login);
}

//root page can be accessed only if authentification is ok
void handleHome() {
  
  SerialMon.println("Enter handleHome");
  String header;
  if (!is_authentified()) {
    server.sendHeader("Location", "/login");
    server.sendHeader("Cache-Control", "no-cache");
    server.send(301);
    return;
  }
  String home = "<html>";
  home += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\" >";
  home += "<head>";
  home += "<style type=\"text/css\">";
  home += ".form-style-6{";
  home += " font: 95% Arial, Helvetica, sans-serif;" ;
  home += " max-width: 400px;" ;
  home += " margin: 10px auto;" ;
  home += " padding: 16px;" ;
  home += " background: #F7F7F7;" ;
  home += " } ";
  home += ".form-style-6 h1{";
  home += " background: #43D1AF;" ;
  home += " padding: 20px 0;" ;
  home += " font-size: 140%;" ;
  home += " font-weight: 300;" ;
home += "text-align: center;";
home += "color: #fff;";
home += "margin: -16px -16px 16px -16px;";
home += "}";
home += ".form-style-6 input[type=\"text\"],";
home += ".form-style-6 input[type=\"text\"],";
home += "{";
home += "-webkit-transition: all 0.30s ease-in-out;";
home += "-moz-transition: all 0.30s ease-in-out;";
home += "-ms-transition: all 0.30s ease-in-out;";
home += "-o-transition: all 0.30s ease-in-out;";
home += "outline: none;";
home += "box-sizing: border-box;";
home += "-webkit-box-sizing: border-box;";
home += "-moz-box-sizing: border-box;";
home += "width: 100%;";
home += "background: #fff;";
home += "margin-bottom: 4%;";
home += "border: 1px solid #ccc;";
home += "padding: 3%;";
home += "color: #555;";
home += "font: 95% Arial, Helvetica, sans-serif;";
home += "}";
home += ".form-style-6 input[type=\"text\"]:focus,";
home += ".form-style-6 input[type=\"text\"]:focus,";
home += "{";
home += "box-shadow: 0 0 5px #43D1AF;";
home += "padding: 3%;";
home += "border: 1px solid #43D1AF;";
home += "}";
home += ".form-style-6 input[type=\"submit\"],";
home += ".form-style-6 input[type=\"button\"],";
home += "box-sizing: border-box;";
home += "-webkit-box-sizing: border-box;";
home += "-moz-box-sizing: border-box;";
home += "width: 100%;";
home += "padding: 3%;";
home += "background: #43D1AF;";
home += "border-bottom: 2px solid #30C29E;";
home += "border-top-style: none;";
home += "border-right-style: none;";
home += "border-left-style: none;";  
home += "color: #fff;";
home += "}";
home += ".form-style-6 input[type=\"submit\"]:hover,";
home += ".form-style-6 input[type=\"button\"]:hover,";
home += "background: #2EBC99;";
home += "}";
home += "</style></head>";
home += "<body><div class='form-style-6'>";
home += "<h1>HOME PAGE</h1>";
home += "<p><a class=\"button\" href=\"/logOut\">LOG OUT</a><br>";
home += "<br>";
home += "<a class=\"button\" href=\"/enrollNewFinger\">ADD NEW FINGER</a><br>";
home += "<br>";
home += "<a class=\"button\" href=\"/deleteExistingFinger\">DELETE EXISTING FINGER</a><br>";
home += "<br>";
home += "<a class=\"button\" href=\"/modifyExistingFinger\">UPDATE EXISTING FINGER</a><br>";
home += "<br>";
home += "<a class=\"button\" href=\"/config\">WIFI CONFIGURATION</a></div></body></html>";
 fing = true;
  server.send(200, "text/html", home);
}

void handleDeleteExistingFinger(){

 
String msg;
  if (server.hasHeader("Cookie")) {
    SerialMon.print("Found cookie: ");
    String cookie = server.header("Cookie");
    SerialMon.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    SerialMon.println("Disconnection");
    server.sendHeader("Location", "/teenRegistration");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (  server.hasArg("FINGERID") ) {
   
    
   fingerId        = server.arg("FINGERID");


    idPosition = fingerId .indexOf(fingerId );
    
    
if ( isDigit(fingerId.charAt(idPosition))  ){

id = fingerId.toInt();//readnumber();
if (id == 0) {// ID #0 not allowed, try again!
return;
}
 Serial.print("Deleting ID #");
  Serial.println(id);
  
//for (int i=0; i<10; i++){
    deleteFingerprint(id);
//}
  
  
    Serial.print("Delete ID #");
    Serial.println(id);
    
  
delay(50);
   
    int ID = id;
  String path = "/";
   path += ID;
    path += ".txt";

  String pathDetails = "/";
   pathDetails += ID;
    pathDetails += "details.txt";

 SPIFFS.remove(path);
 SPIFFS.remove(pathDetails);
    
    
  }
  
    
      server.sendHeader("Location", "/dataUploadMembers");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      SerialMon.println("Deletion Successful");
      return;
}
  else{
    msg = "Some Fields Are Blank! try again.";
    SerialMon.println("Deletion Failed ");
  }
      

  
    String dele = "<!DOCTYPE html>";
dele += "<html lang=\"dele\" dir=\"ltr\">";
dele += "<head>";
dele += " <meta charset=\"utf-8\">";
dele += " <title>Admin dele Form</title>";
dele += " <link rel=\"stylesheet\" href=\"https://unpkg.com/ionicons@4.5.10-0/dist/css/ionicons.min.css\">";
dele += "<style type=\"text/css\">";
dele += "@import url('https://fonts.googleapis.com/css?family=Montserrat:500,700&amp;display=swap');";
dele += "  body, html {";
dele += " background-color: #EBECF0;";
dele += "}";
dele += "body, p, input, select, textarea, button {";
dele += " font-family: \"Montserrat\", sans-serif;";
dele += " letter-spacing: -0.2px;";
dele += " font-size: 16px;";
dele += "}";
dele += "div, p {";
dele += " color: #BABECC;";
dele += " text-shadow: 1px 1px 1px #FFF;";
dele += "}";
dele += "form {";
dele += " padding: 16px;";
dele += " width: 320px;";
dele += " margin: 0 auto;";
dele += "}";
dele += ".segmdelet {";
dele += " padding: 32px 0;";
dele += " text-align: cdeleter;";
dele += "}";
dele += "button, input {";
dele += " border: 0;";
dele += " outline: 0;";
dele += " font-size: 16px;";
dele += " border-radius: 320px;";
dele += " padding: 16px;";
dele += " background-color: #EBECF0;";
dele += " text-shadow: 1px 1px 0 #FFF;";
dele += "}";
dele += "label {";
dele += " display: block;";
dele += " margin-bottom: 24px;";
dele += " width: 100%;";
dele += "}";
dele += "input {";
dele += " margin-right: 8px;";
dele += " box-shadow: inset 2px 2px 5px #BABECC, inset -5px -5px 10px #FFF;";
dele += " width: 100%;";
dele += " box-sizing: border-box;";
dele += " transition: all 0.2s ease-in-out;";
dele += " appearance: none;";
dele += " -webkit-appearance: none;";
dele += "}";
dele += "input:focus {";
dele += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
dele += "}";
dele += "button {";
dele += " color: #61677C;";
dele += " font-weight: bold;";
dele += " box-shadow: -5px -5px 20px #FFF, 5px 5px 20px #BABECC;";
dele += " transition: all 0.2s ease-in-out;";
dele += " cursor: pointer;";
dele += " font-weight: 600;";
dele += "}";
dele += "button:hover {";
dele += " box-shadow: -2px -2px 5px #FFF, 2px 2px 5px #BABECC;";
dele += "}";
dele += "button:active {";
dele += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
dele += "}";
dele += "button .icon {";
dele += " margin-right: 8px;";
dele += "}";
dele += "button.unit {";
dele += " border-radius: 8px;";
dele += " line-height: 0;";
dele += " width: 48px;";
dele += " height: 48px;";
dele += " display: inline-flex;";
dele += " justify-contdelet: cdeleter;";
dele += " align-items: cdeleter;";
dele += " margin: 0 8px;";
dele += " font-size: 19.2px;";
dele += "}";
dele += "button.unit .icon {";
dele += " margin-right: 0;";
dele += "}";
dele += "button.red {";
dele += " display: block;";
dele += " width: 100%;";
dele += " color: #00ced1;";
dele += "}";
dele += ".input-group {";
dele += " display: flex;";
dele += " align-items: cdeleter;";
dele += " justify-contdelet: flex-start;";
dele += "}";
dele += ".input-group label {";
dele += " margin: 0;";
dele += " flex: 1;";
dele += "}";
dele += "h1 { color:#00ced1; }";
dele += "</style></head>";
dele += "<body>";
dele += "<form action='/deleteExistingFinger' method='POST'><br>";
dele += "<div class='segmdelet'>";
dele += "<h1>DELETE EXISTING FINGER</h1></div>";
dele += "<label>";
dele += "<input type='text' name='FINGERID' placeholder='Finger ID'><br>";
dele += "</label>";
dele += "<label>";
dele += "<button class='red' type='submit' name='SUBMIT' value='Submit'><i class=\"icon ion-md-lock\"></i>Delete</button>";
dele += "</form></body></html>";
  fing = false;
  del = true;
  server.send(200, "text/html", dele);
  }


  void handleModifyExistingFinger(){

 
String msg;
  if (server.hasHeader("Cookie")) {
    SerialMon.print("Found cookie: ");
    String cookie = server.header("Cookie");
    SerialMon.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    SerialMon.println("Disconnection");
    server.sendHeader("Location", "/teenRegistration");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (  server.hasArg("FIRSTNAME")    && server.hasArg("LASTNAME") 
           
                && server.hasArg("DATEOFBIRTH")   && server.hasArg("TELEPHONE")   
      ) {
   
    firstName        = server.arg("FIRSTNAME");
    lastName         = server.arg("LASTNAME");
    dateOfBirth      = server.arg("DATEOFBIRTH");
    telephone        = server.arg("TELEPHONE");
    fingerId        = server.arg("FINGERID");

    fnPosition = firstName.indexOf(firstName);
    lnPosition = lastName.indexOf(lastName);
    dobPosition = dateOfBirth.indexOf(dateOfBirth);
    tPosition = telephone.indexOf(telephone);
    idPosition = fingerId.indexOf(fingerId);
    
    
if (isAlpha(firstName.charAt(fnPosition)) && isAlpha(lastName.charAt(lnPosition)) 
        && isDigit(dateOfBirth.charAt(dobPosition))  && isDigit(telephone.charAt(tPosition)) 
            && isDigit(fingerId.charAt(idPosition))
            ){




    SerialMon.println("Ready to update a fingerprint!");
SerialMon.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
id = fingerId.toInt();//readnumber();
if (id == 0) {// ID #0 not allowed, try again!
return;
}
SerialMon.print("Updating details of ID #");
SerialMon.println(id);
 

  
  
delay(50);

String   fullName = firstName ;//+ "" + lastName ; 
   fullName += " ";
   fullName += lastName;
   
    int ID = id;
  String path = "/";
   path += ID;
    path += ".txt";

  String pathDetails = "/";
   pathDetails  += ID;
    pathDetails  += "details.txt";
  
 SPIFFS.remove(path);
 SPIFFS.remove(pathDetails);
 SerialMon.println("Old details Deleted!");
 delay(50);

 File testFile = SPIFFS.open(path, FILE_WRITE);
 File testFileDetails = SPIFFS.open(pathDetails, FILE_WRITE);
 
    if (testFile){
        SerialMon.println("Write file content!");
        testFile.print(fullName);
 
        testFile.close();
    }else{
        SerialMon.println("Problem on create file!");
    }

    if (testFileDetails){
        SerialMon.println("Write file content!");
        testFileDetails.print(fullName);
 
        testFileDetails.close();
    }else{
        SerialMon.println("Problem on create file!");
    }
 
    testFile = SPIFFS.open(path);
    if (testFile){
        SerialMon.println("Read file content!");
        /**
         * File derivate from Stream so you can use all Stream method
         * readBytes, findUntil, parseInt, println etc
         */
        SerialMon.println(testFile.readString());
        testFile.close();
    }else{
        SerialMon.println("Problem on read file!");
    }

    testFileDetails = SPIFFS.open(pathDetails);
    if (testFileDetails){
        SerialMon.println("Read file content!");
        /**
         * File derivate from Stream so you can use all Stream method
         * readBytes, findUntil, parseInt, println etc
         */
        SerialMon.println(testFileDetails.readString());
        testFileDetails.close();
    }else{
        SerialMon.println("Problem on read file!");
    }

SerialMon.println("Details Updated!");







    }
  
  
    
      server.sendHeader("Location", "/dataUploadMembers");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      SerialMon.println("Modification Successful");
      return;
  }
  else{
    msg = "Some Fields Are Blank! try again.";
    SerialMon.println("Modification Failed");
  }
      

  
    String mod = "<!DOCTYPE html>";
mod += "<html lang=\"en\" dir=\"ltr\">";
mod += "<head>";
mod += " <meta charset=\"utf-8\">";
mod += " <title>Admin mod Form</title>";
mod += " <link rel=\"stylesheet\" href=\"https://unpkg.com/ionicons@4.5.10-0/dist/css/ionicons.min.css\">";
mod += "<style type=\"text/css\">";
mod += "@import url('https://fonts.googleapis.com/css?family=Montserrat:500,700&amp;display=swap');";
mod += "  body, html {";
mod += " background-color: #EBECF0;";
mod += "}";
mod += "body, p, input, select, textarea, button {";
mod += " font-family: \"Montserrat\", sans-serif;";
mod += " letter-spacing: -0.2px;";
mod += " font-size: 16px;";
mod += "}";
mod += "div, p {";
mod += " color: #BABECC;";
mod += " text-shadow: 1px 1px 1px #FFF;";
mod += "}";
mod += "form {";
mod += " padding: 16px;";
mod += " width: 320px;";
mod += " margin: 0 auto;";
mod += "}";
mod += ".segment {";
mod += " padding: 32px 0;";
mod += " text-align: center;";
mod += "}";
mod += "button, input {";
mod += " border: 0;";
mod += " outline: 0;";
mod += " font-size: 16px;";
mod += " border-radius: 320px;";
mod += " padding: 16px;";
mod += " background-color: #EBECF0;";
mod += " text-shadow: 1px 1px 0 #FFF;";
mod += "}";
mod += "label {";
mod += " display: block;";
mod += " margin-bottom: 24px;";
mod += " width: 100%;";
mod += "}";
mod += "input {";
mod += " margin-right: 8px;";
mod += " box-shadow: inset 2px 2px 5px #BABECC, inset -5px -5px 10px #FFF;";
mod += " width: 100%;";
mod += " box-sizing: border-box;";
mod += " transition: all 0.2s ease-in-out;";
mod += " appearance: none;";
mod += " -webkit-appearance: none;";
mod += "}";
mod += "input:focus {";
mod += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
mod += "}";
mod += "button {";
mod += " color: #61677C;";
mod += " font-weight: bold;";
mod += " box-shadow: -5px -5px 20px #FFF, 5px 5px 20px #BABECC;";
mod += " transition: all 0.2s ease-in-out;";
mod += " cursor: pointer;";
mod += " font-weight: 600;";
mod += "}";
mod += "button:hover {";
mod += " box-shadow: -2px -2px 5px #FFF, 2px 2px 5px #BABECC;";
mod += "}";
mod += "button:active {";
mod += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
mod += "}";
mod += "button .icon {";
mod += " margin-right: 8px;";
mod += "}";
mod += "button.unit {";
mod += " border-radius: 8px;";
mod += " line-height: 0;";
mod += " width: 48px;";
mod += " height: 48px;";
mod += " display: inline-flex;";
mod += " justify-content: center;";
mod += " align-items: center;";
mod += " margin: 0 8px;";
mod += " font-size: 19.2px;";
mod += "}";
mod += "button.unit .icon {";
mod += " margin-right: 0;";
mod += "}";
mod += "button.red {";
mod += " display: block;";
mod += " width: 100%;";
mod += " color: #00ced1;";
mod += "}";
mod += ".input-group {";
mod += " display: flex;";
mod += " align-items: center;";
mod += " justify-content: flex-start;";
mod += "}";
mod += ".input-group label {";
mod += " margin: 0;";
mod += " flex: 1;";
mod += "}";
mod += "h1 { color:#00ced1; }";
mod += "</style></head>";
mod += "<body>";
mod += "<form action='/modifyExistingFinger' method='POST'><br>";
mod += "<div class='segment'>";
mod += "<h1>UPDATE EXISTING FINGER</h1></div>";
mod += "<label>";
mod += "<input type='text' name='FINGERID' placeholder='Finger ID'><br>";
mod += "</label>";
mod += "<label>";
mod += "<input type='text' name='FIRSTNAME' placeholder='First Name'><br>";
mod += "</label>";
mod += "<label>";
mod += "<input type='text' name='LASTNAME' placeholder='Last Name'><br>";
mod += "</label>";
mod += "<label>";
mod += "<input type='text' name='DATEOFBIRTH' placeholder='Date of Birth'><br>";
mod += "</label>";
mod += "<label>";
mod += "<input type='text' name='TELEPHONE' placeholder='Telephone'><br>";
mod += "</label>";
mod += "<label>";
mod += "<button class='red' type='submit' name='SUBMIT' value='Submit'><i class=\"icon ion-md-lock\"></i>Submit</button>";
mod += "</form></body></html>";
  fing = false;
  server.send(200, "text/html", mod);
  }


  void handleEnrollNewFinger(){

 
String msg;
  if (server.hasHeader("Cookie")) {
    SerialMon.print("Found cookie: ");
    String cookie = server.header("Cookie");
    SerialMon.println(cookie);
  }
  if (server.hasArg("DISCONNECT")) {
    SerialMon.println("Disconnection");
    server.sendHeader("Location", "/teenRegistration");
    server.sendHeader("Cache-Control", "no-cache");
    server.sendHeader("Set-Cookie", "ESPSESSIONID=0");
    server.send(301);
    return;
  }
  if (  server.hasArg("FIRSTNAME")    && server.hasArg("LASTNAME") 
           
                && server.hasArg("DATEOFBIRTH")   && server.hasArg("TELEPHONE") && server.hasArg("FINGERID")   
      ) {
   
    firstName        = server.arg("FIRSTNAME");
    lastName         = server.arg("LASTNAME");
    dateOfBirth      = server.arg("DATEOFBIRTH");
    telephone        = server.arg("TELEPHONE");
    fingerId        = server.arg("FINGERID");



    fnPosition = firstName.indexOf(firstName);
    lnPosition = lastName.indexOf(lastName);
    dobPosition = dateOfBirth.indexOf(dateOfBirth);
    tPosition = telephone.indexOf(telephone);
    idPosition = fingerId.indexOf(fingerId);
    
    
if (isAlpha(firstName.charAt(fnPosition)) && isAlpha(lastName.charAt(lnPosition)) 
        && isDigit(dateOfBirth.charAt(dobPosition))  && isDigit(telephone.charAt(tPosition))  
             && isDigit(fingerId.charAt(idPosition))
        ){

SerialMon.println("Ready to enroll a fingerprint!");
SerialMon.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
id = fingerId.toInt();//readnumber();
if (id == 0) {// ID #0 not allowed, try again!
return;
}
SerialMon.print("Enrolling ID #");
SerialMon.println(id);
 
getFingerprintEnroll();
  
  
delay(50);

logIFTTTRegister(id, firstName, lastName, dateOfBirth, telephone);


String   fullName = firstName ;//+ "" + lastName ; 
   fullName += " ";
   fullName += lastName;

String details = fullName;
       details += " ";
       details += dateOfBirth;
       details += " ";
       details += telephone;


    int ID = id;
  String path = "/";
   path += ID;
    path += ".txt";

  String pathDetails = "/";
   pathDetails  += ID;
    pathDetails  += "details.txt";
  



 File testFile = SPIFFS.open(path, FILE_WRITE);
 File testFileDetails = SPIFFS.open(pathDetails, FILE_WRITE);
 
    if (testFile){
        SerialMon.println("Write file content!");
        testFile.print(fullName);
 
        testFile.close();
    }else{
        SerialMon.println("Problem on create file!");
    }

    if (testFileDetails){
        SerialMon.println("Write file content!");
        testFileDetails.print(details);
 
        testFileDetails.close();
    }else{
        SerialMon.println("Problem on create file!");
    }
 
    testFile = SPIFFS.open(path);
    if (testFile){
        SerialMon.println("Read file content!");
        /**
         * File derivate from Stream so you can use all Stream method
         * readBytes, findUntil, parseInt, println etc
         */
        SerialMon.println(testFile.readString());
        testFile.close();
    }else{
        SerialMon.println("Problem on read file!");
    }

    testFileDetails = SPIFFS.open(pathDetails);
    if (testFileDetails){
        SerialMon.println("Read file content!");
        /**
         * File derivate from Stream so you can use all Stream method
         * readBytes, findUntil, parseInt, println etc
         */
        SerialMon.println(testFileDetails.readString());
        testFileDetails.close();
    }else{
        SerialMon.println("Problem on read file!");
    }
      
    
  }
     
    
      server.sendHeader("Location", "/dataUploadMembers");
      server.sendHeader("Cache-Control", "no-cache");
      server.sendHeader("Set-Cookie", "ESPSESSIONID=1");
      server.send(301);
      SerialMon.println("Enrollment Successful");
      return;
  }
  else{
    msg = "Some Fields Are Blank! try again.";
    SerialMon.println("Enrollment Failed");
  }
      

  
    String en = "<!DOCTYPE html>";
en += "<html lang=\"en\" dir=\"ltr\">";
en += "<head>";
en += " <meta charset=\"utf-8\">";
en += " <title>Admin en Form</title>";
en += " <link rel=\"stylesheet\" href=\"https://unpkg.com/ionicons@4.5.10-0/dist/css/ionicons.min.css\">";
en += "<style type=\"text/css\">";
en += "@import url('https://fonts.googleapis.com/css?family=Montserrat:500,700&amp;display=swap');";
en += "  body, html {";
en += " background-color: #EBECF0;";
en += "}";
en += "body, p, input, select, textarea, button {";
en += " font-family: \"Montserrat\", sans-serif;";
en += " letter-spacing: -0.2px;";
en += " font-size: 16px;";
en += "}";
en += "div, p {";
en += " color: #BABECC;";
en += " text-shadow: 1px 1px 1px #FFF;";
en += "}";
en += "form {";
en += " padding: 16px;";
en += " width: 320px;";
en += " margin: 0 auto;";
en += "}";
en += ".segment {";
en += " padding: 32px 0;";
en += " text-align: center;";
en += "}";
en += "button, input {";
en += " border: 0;";
en += " outline: 0;";
en += " font-size: 16px;";
en += " border-radius: 320px;";
en += " padding: 16px;";
en += " background-color: #EBECF0;";
en += " text-shadow: 1px 1px 0 #FFF;";
en += "}";
en += "label {";
en += " display: block;";
en += " margin-bottom: 24px;";
en += " width: 100%;";
en += "}";
en += "input {";
en += " margin-right: 8px;";
en += " box-shadow: inset 2px 2px 5px #BABECC, inset -5px -5px 10px #FFF;";
en += " width: 100%;";
en += " box-sizing: border-box;";
en += " transition: all 0.2s ease-in-out;";
en += " appearance: none;";
en += " -webkit-appearance: none;";
en += "}";
en += "input:focus {";
en += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
en += "}";
en += "button {";
en += " color: #61677C;";
en += " font-weight: bold;";
en += " box-shadow: -5px -5px 20px #FFF, 5px 5px 20px #BABECC;";
en += " transition: all 0.2s ease-in-out;";
en += " cursor: pointer;";
en += " font-weight: 600;";
en += "}";
en += "button:hover {";
en += " box-shadow: -2px -2px 5px #FFF, 2px 2px 5px #BABECC;";
en += "}";
en += "button:active {";
en += " box-shadow: inset 1px 1px 2px #BABECC, inset -1px -1px 2px #FFF;";
en += "}";
en += "button .icon {";
en += " margin-right: 8px;";
en += "}";
en += "button.unit {";
en += " border-radius: 8px;";
en += " line-height: 0;";
en += " width: 48px;";
en += " height: 48px;";
en += " display: inline-flex;";
en += " justify-content: center;";
en += " align-items: center;";
en += " margin: 0 8px;";
en += " font-size: 19.2px;";
en += "}";
en += "button.unit .icon {";
en += " margin-right: 0;";
en += "}";
en += "button.red {";
en += " display: block;";
en += " width: 100%;";
en += " color: #00ced1;";
en += "}";
en += ".input-group {";
en += " display: flex;";
en += " align-items: center;";
en += " justify-content: flex-start;";
en += "}";
en += ".input-group label {";
en += " margin: 0;";
en += " flex: 1;";
en += "}";
en += "h1 { color:#00ced1; }";
en += "</style></head>";
en += "<body>";
en += "<form action='/enrollNewFinger' method='POST'><br>";
en += "<div class='segment'>";
en += "<h1>ADD NEW FINGER</h1></div>";
en += "<label>";
en += "<input type='text' name='FINGERID' placeholder='Finger ID'><br>";
en += "</label>";
en += "<label>";
en += "<input type='text' name='FIRSTNAME' placeholder='First Name'><br>";
en += "</label>";
en += "<label>";
en += "<input type='text' name='LASTNAME' placeholder='Last Name'><br>";
en += "</label>";
en += "<label>";
en += "<input type='date' name='DATEOFBIRTH' placeholder='Date of Birth'><br>";
en += "</label>";
en += "<label>";
en += "<input type='text' name='TELEPHONE' placeholder='Telephone'><br>";
en += "</label>";
en += "<label>";
en += "<button class='red' type='submit' name='SUBMIT' value='Submit'><i class=\"icon ion-md-lock\"></i>Submit</button>";
en += "</form></body></html>";
  fing = false;
  server.send(200, "text/html", en);
  }

void handleLogOut(){
  String logOut = "<html>";
  logOut += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\" >";
  logOut += "<head>";
  logOut += "<style type=\"text/css\">";
  logOut += ".form-style-6{";
  logOut += " font: 95% Arial, Helvetica, sans-serif;" ;
  logOut += " max-width: 400px;" ;
  logOut += " margin: 10px auto;" ;
  logOut += " padding: 16px;" ;
  logOut += " background: #F7F7F7;" ;
  logOut += " } ";
  logOut += ".form-style-6 h1{";
  logOut += " background: #43D1AF;" ;
  logOut += " padding: 20px 0;" ;
  logOut += " font-size: 140%;" ;
  logOut += " font-weight: 300;" ;
logOut += "text-align: center;";
logOut += "color: #fff;";
logOut += "margin: -16px -16px 16px -16px;";
logOut += "}";
logOut += ".form-style-6 input[type=\"text\"],";
logOut += ".form-style-6 input[type=\"text\"],";
logOut += "{";
logOut += "-webkit-transition: all 0.30s ease-in-out;";
logOut += "-moz-transition: all 0.30s ease-in-out;";
logOut += "-ms-transition: all 0.30s ease-in-out;";
logOut += "-o-transition: all 0.30s ease-in-out;";
logOut += "outline: none;";
logOut += "box-sizing: border-box;";
logOut += "-webkit-box-sizing: border-box;";
logOut += "-moz-box-sizing: border-box;";
logOut += "width: 100%;";
logOut += "background: #fff;";
logOut += "margin-bottom: 4%;";
logOut += "border: 1px solid #ccc;";
logOut += "padding: 3%;";
logOut += "color: #555;";
logOut += "font: 95% Arial, Helvetica, sans-serif;";
logOut += "}";
logOut += ".form-style-6 input[type=\"text\"]:focus,";
logOut += ".form-style-6 input[type=\"text\"]:focus,";
logOut += "{";
logOut += "box-shadow: 0 0 5px #43D1AF;";
logOut += "padding: 3%;";
logOut += "border: 1px solid #43D1AF;";
logOut += "}";
logOut += ".form-style-6 input[type=\"submit\"],";
logOut += ".form-style-6 input[type=\"button\"],";
logOut += "box-sizing: border-box;";
logOut += "-webkit-box-sizing: border-box;";
logOut += "-moz-box-sizing: border-box;";
logOut += "width: 100%;";
logOut += "padding: 3%;";
logOut += "background: #43D1AF;";
logOut += "border-bottom: 2px solid #30C29E;";
logOut += "border-top-style: none;";
logOut += "border-right-style: none;";
logOut += "border-left-style: none;";  
logOut += "color: #fff;";
logOut += "}";
logOut += ".form-style-6 input[type=\"submit\"]:hover,";
logOut += ".form-style-6 input[type=\"button\"]:hover,";
logOut += "background: #2EBC99;";
logOut += "}";
logOut += "</style></head>";
logOut += "<body><div class='form-style-6'>";
logOut += "<h1>YOU HAVE LOGGED OUT</h1>";
  
         logOut += "<a class=\"button\" href=\"/login\">GO TO LOGIN PAGE</a><br>";
         logOut += "</div></body></html>";
 fing = true;
  server.send(200, "text/html", logOut);
  }


 void handleDataUploadMembers(){
  String memReg = "<html>";
  memReg += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\" >";
  memReg += "<head>";
  memReg += "<style type=\"text/css\">";
  memReg += ".form-style-6{";
  memReg += " font: 95% Arial, Helvetica, sans-serif;" ;
  memReg += " max-width: 400px;" ;
  memReg += " margin: 10px auto;" ;
  memReg += " padding: 16px;" ;
  memReg += " background: #F7F7F7;" ;
  memReg += " } ";
  memReg += ".form-style-6 h1{";
  memReg += " background: #43D1AF;" ;
  memReg += " padding: 20px 0;" ;
  memReg += " font-size: 140%;" ;
  memReg += " font-weight: 300;" ;
memReg += "text-align: center;";
memReg += "color: #fff;";
memReg += "margin: -16px -16px 16px -16px;";
memReg += "}";
memReg += ".form-style-6 input[type=\"text\"],";
memReg += ".form-style-6 input[type=\"password\"],";
memReg += "{";
memReg += "-webkit-transition: all 0.30s ease-in-out;";
memReg += "-moz-transition: all 0.30s ease-in-out;";
memReg += "-ms-transition: all 0.30s ease-in-out;";
memReg += "-o-transition: all 0.30s ease-in-out;";
memReg += "outline: none;";
memReg += "box-sizing: border-box;";
memReg += "-webkit-box-sizing: border-box;";
memReg += "-moz-box-sizing: border-box;";
memReg += "width: 100%;";
memReg += "background: #fff;";
memReg += "margin-bottom: 4%;";
memReg += "border: 1px solid #ccc;";
memReg += "padding: 3%;";
memReg += "color: #555;";
memReg += "font: 95% Arial, Helvetica, sans-serif;";
memReg += "}";
memReg += ".form-style-6 input[type=\"text\"]:focus,";
memReg += ".form-style-6 input[type=\"password\"]:focus,";
memReg += "{";
memReg += "box-shadow: 0 0 5px #43D1AF;";
memReg += "padding: 3%;";
memReg += "border: 1px solid #43D1AF;";
memReg += "}";
memReg += ".form-style-6 input[type=\"submit\"],";
memReg += ".form-style-6 input[type=\"button\"],";
memReg += "box-sizing: border-box;";
memReg += "-webkit-box-sizing: border-box;";
memReg += "-moz-box-sizing: border-box;";
memReg += "width: 100%;";
memReg += "padding: 3%;";
memReg += "background: #43D1AF;";
memReg += "border-bottom: 2px solid #30C29E;";
memReg += "border-top-style: none;";
memReg += "border-right-style: none;";
memReg += "border-left-style: none;";  
memReg += "color: #fff;";
memReg += "}";
memReg += ".form-style-6 input[type=\"submit\"]:hover,";
memReg += ".form-style-6 input[type=\"button\"]:hover,";
memReg += "background: #2EBC99;";
memReg += "}";
memReg += "</style></head>";
memReg += "<body><div class='form-style-6'>";
memReg += "<h1>YOU SUCCEEDED</h1>";
         memReg += "<a class=\"button\" href=\"/\">GO TO HOME PAGE</a><br>";
         memReg += "</div></body></html>";
  server.send(200, "text/html", memReg);
  }

void handleNotFound() {
  String message = "AN ERROR OCCURED/n/n";
  message += "URI: ";
  message += server.uri();
  message += "/nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "/nArguments: ";
  message += server.args();
  message += "/n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "/n";
  }
  fing = true;
  server.send(404, "text/plain", "NOT FOUND");
}

void setup() {
  // put your setup code here, to run once:
   int xpos =  0;
   int ypos = 40;



  



  // Draw bitmap with top left corner at x,y with foreground and background colors
  // Bits set to 1 plot as the defined fg color, bits set to 0 are plotted as bg color
  //              x  y  xbm   xbm width  xbm height  fg color   bg color

//animation();
 
//int x = logoHeight;
//int y = logoWidth;
//    x = (0 - 125);
///    y = (0 - 75);

//tft.fillScreen(TFT_NAVY);
//tft.drawXBitmap(x, y, logo, logoWidth, logoHeight, TFT_YELLOW, TFT_BLUE);
//delay(3000);



//tft.fillScreen(TFT_NAVY); // Clear screen to navy background
 // tft.setTextColor(TFT_WHITE, TFT_BLACK);
 // tft.setCursor(xpos, ypos);    // Set cursor near top left corner of screen
  //tft.setFreeFont(FSB18);       // Select Free Serif 12 point font
 // tft.print("Sensor contains "); 
 // tft.print(finger.templateCount); 
//  tft.println(" templates");
//  tft.println("Waiting for valid finger...");
 // delay(3000);

Serial2.begin(57600);


// Set serial monitor debugging window baud rate to 115200
  SerialMon.begin(115200);
    

SerialMon.println("/n/nAdafruit Fingerprint sensor enrollment");
 SerialMon.println(F("Inizializing FS..."));
    if (SPIFFS.begin()){
        SerialMon.println(F("done."));
    }else{
        SerialMon.println(F("fail."));
    }
// set the data rate for the sensor serial port
finger.begin(57600);

if (finger.verifyPassword()) {
SerialMon.println("Found fingerprint sensor!");
} else {
SerialMon.println("Did not find fingerprint sensor :(");
//while (1) { delay(1); }
}


finger.getTemplateCount();
  SerialMon.print("Sensor contains "); 
  Serial.print(finger.templateCount); 
  Serial.println(" templates");
  SerialMon.println("Waiting for valid finger...");

  

   
  // Start I2C communication
  //I2CPower.begin(I2C_SDA, I2C_SCL, 400000);

  // Keep power when running from battery
  bool isOk = setPowerBoostKeepOn(1);
  SerialMon.println(String("IP5306 KeepOn ") + (isOk ? "OK" : "FAIL"));

  // Set modem reset, enable, power pins
  pinMode(MODEM_PWKEY, OUTPUT);
  pinMode(MODEM_RST, OUTPUT);
  pinMode(MODEM_POWER_ON, OUTPUT);
  digitalWrite(MODEM_PWKEY, LOW);
  digitalWrite(MODEM_RST, HIGH);
  digitalWrite(MODEM_POWER_ON, HIGH);

  // Set GSM module baud rate and UART pins
  SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
  delay(3000);

  // Restart SIM800 module, it takes quite some time
  // To skip it, call init() instead of restart()
 // SerialMon.println("Initializing modem...");
  //modem.restart();
  // modem.init(); //if you don't need the complete restart

  // Unlock your SIM card with a PIN if needed
 // if (strlen(simPIN) && modem.getSimStatus() != 3 ) {
 //   modem.simUnlock(simPIN);
 // } 

    
    initWifi();
   
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    //printLocalTime();
  
  

  
  tft.init();
 
  tft.setRotation(3);
  animation();
 
  
    int x = logoHeight;
  int y = logoWidth;
    x = (0 - 125);
    y = (0 - 75);

  tft.fillScreen(TFT_YELLOW);
  tft.drawXBitmap(x, y, logo, logoWidth, logoHeight, TFT_YELLOW, TFT_BLUE);
  delay(3000);
  //tft.invertDisplay(true);
  tft.fillScreen(TFT_BLUE);


  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  SerialMon.println("");


  server.on("/", handleHome);
  server.on("/config", handleConfig);
  server.on("/login", handleLogin);
  server.on("/logOut", handleLogOut);
  server.on("/enrollNewFinger", handleEnrollNewFinger);
  server.on("/deleteExistingFinger", handleDeleteExistingFinger);
  server.on("/modifyExistingFinger", handleModifyExistingFinger);
  server.on("/dataUploadMembers", handleDataUploadMembers);

  server.onNotFound(handleNotFound);
  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent", "Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys) / sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize);
  server.begin();
  SerialMon.println("HTTP server started");

targetTime = millis() + 1000;
 }


void loop() {
       server.handleClient();
      
       /*  tft.setTextColor(TFT_WHITE);
         tft.setCursor(90, 150);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print("PLACE YOUR");
         tft.setCursor(140, 200);    // Set cursor near top left corner of screen
         tft.setFreeFont(FF8);       // Select Free Serif 12 point font
         tft.print("FINGER");
         */
        // printLocalTime();
         timeAnimate();
         
  //tft.drawXBitmap(x, y, logo, logoWidth, logoHeight, TFT_YELLOW, TFT_BLUE);
      if (wifiReset == true){
        initWifi();
        wifiReset = false;
        }
      if (fing == true){
  checkFinger();
  }
  repeatedCall();
    digitalWrite(21, HIGH);
   
}


/*
void initWifi() {
  File  testFile = SPIFFS.open("/wifissid.txt");
  File  testFileDetails = SPIFFS.open("/wifipassword.txt");
    if (testFile){
      WIFI_SSID = testFile.readString();
      testFile.close();
    }
    if (testFileDetails){
       WIFI_PASSWORD = testFileDetails.readString();
      testFileDetails.close();
    }
  const char *wssid = WIFI_SSID.c_str();
  const char *wpwd = WIFI_PASSWORD.c_str();
  
  Serial.print("Connecting to: "); 
  Serial.print(wssid);
  WiFi.begin(wssid, wpwd);  

  int timeout = 10 * 4; // 10 seconds
  while(WiFi.status() != WL_CONNECTED  && (timeout-- > 0)) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");

  if(WiFi.status() != WL_CONNECTED) {
     Serial.println("Failed to connect, going back to sleep");
  }

  Serial.print("WiFi connected in: "); 
  Serial.print(millis());
  Serial.print(", IP address: "); 
  Serial.println(WiFi.localIP());
}
*/
// Make an HTTP request to the IFTTT web service
void logIFTTTRegister(int idNum, String fName, String lName,  String dob, String tel) {
  
  if (WiFi.status() != WL_CONNECTED) {
      initWifi();
  }
  
  if (WiFi.status() != WL_CONNECTED) {
      initWifi();    
  }

  String user = "Lemuel";
String HOST_NAME = "https://navantrics.com"; // change to your PC's IP address
String PATH_NAME   = "/n/jel/api/add_fingerprint.php";
String queryString = String("?id=") + String(idNum) + String("&firstname=") + String(fName)
                                           + String("&surname=") + String(lName)+ String("&dob=") 
                                                                + String(dob)+ String("&tel=") + String(tel);

HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME + queryString); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();

}

void logIFTTTAttendance(int idNum, String Name) {

  if (WiFi.status() != WL_CONNECTED) {
      initWifi();    
  }

  String user = "Lemuel";
String HOST_NAME = "https://navantrics.com"; // change to your PC's IP address
String PATH_NAME   = "/n/jel/api/log_attendance.php";
String queryString = String("?id=") + String(idNum) ;//+ String("&firstname=") + String(user);


HTTPClient http;

  http.begin(HOST_NAME + PATH_NAME + queryString); //HTTP
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();



  
  /*
  Serial.print("Connecting to "); 
  Serial.print(serve);
  
  WiFiClient client;
  int retries = 5;
  while(!!!client.connect(serve, 80) && (retries-- > 0)) {
    Serial.print(".");
  }
  Serial.println();
  if(!!!client.connected()) {
    Serial.println("Failed to connect...");
  }
  
  Serial.print("Request resource: "); 
  Serial.println(resourceA);

  //\\ Temperature in Celsius
 //String jsonObject = String("{\"value1\":\"") + "ID# "+idNum + "\",\"&value2\":\"" + Name
  //                    + "\",\"&value3\":\"" + "logged" + "\"}";

//String jsonObject = "id=" +idNum ;//+ 
//"\",\"value2\":\"" + Name
           //           + "\",\"value3\":\"" + "logged" 
                      
     String jsonObject = String("{\"value1\":\"") + "ID# "+idNum + "\",\"&value2\":\"" + Name
                      + "\",\"&value3\":\"" + "logged" + "\"}";
 
                      
 
                      
  client.println(String("GET ") + resourceA + " HTTP\1.1");
  client.println(String("Host: ") + serve); 
  client.println("Connection: close\r\nContent-Type: application\json");
  //  client.println("Connection: close\r\nContent-Type: application\x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(jsonObject.length());
  client.println();
  client.println(jsonObject);
        
  int timeout = 5 * 10; //\\ 5 seconds             
  while(!!!client.available() && (timeout-- > 0)){
    delay(100);
  }
  if(!!!client.available()) {
    Serial.println("No response...");
  }
  while(client.available()){
    Serial.write(client.read());
  }
  
  Serial.println("\nclosing connection");
  client.stop(); 
 */ 
}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  //\\String time = (String) &timeinfo, "%H:%M:%S";
 //\\ String date = (String) &timeinfo, "%A, %B %d %Y ";
  Serial.println(  &timeinfo, "%A, %B %d %Y ");
  Serial.println(  &timeinfo, "%H:%M:%S");
  tft.setCursor(0, 200);    //\\ Set cursor near top left corner of screen
 //\\ tft.setFreeFont(FF4);
 ////\\  tft.print(&timeinfo, "%H:%M:%S");
 //  tft.setCursor(0, 50);    // Set cursor near top left corner of screen
   tft.setFreeFont(FF4);
   tft.print(&timeinfo, "%d %B %Y ");

int time_yday = timeinfo.tm_yday; //days since January 1
  int time_wday = timeinfo.tm_wday; //days since Sunday
  int time_year = timeinfo.tm_year; // years since 1900
  int time_mon  = timeinfo.tm_mon;   //months since January
  int time_mday = timeinfo.tm_mday; //day of the month
  int time_hr   = timeinfo.tm_hour;
  int time_min  = timeinfo.tm_min;
  int time_sec  = timeinfo.tm_sec;
  Serial.println("tm_yday: " + String(time_yday));
  Serial.println("tm_wday: " + String(time_wday));
  Serial.println("tm_year: " + String(time_year));
  Serial.println("tm_mon:  " + String(time_mon));
  Serial.println("tm_mday: " + String(time_mday));
  Serial.println("tm_hr:   " + String(time_hr));
  Serial.println("tm_min:  " + String(time_min));
  Serial.println("tm_sec:  " + String(time_sec)); 
  hh = time_hr;
  mm = time_min;
  ss = time_sec;
   
}

void timeAnimate(){
  //tft.fillScreen(TFT_BLUE);
  tft.setTextColor(TFT_YELLOW, TFT_BLUE);
  if (targetTime < millis()) {
    // Set next update for 1 second later
    targetTime = millis() + 1000;

    // Adjust the time values by adding 1 second
    ss++;              // Advance second
    if (ss == 60) {    // Check for roll-over
      ss = 0;          // Reset seconds to zero
      omm = mm;        // Save last minute time for display update
      mm++;            // Advance minute
      if (mm > 59) {   // Check for roll-over
        mm = 0;
        hh++;         // Advance hour
        if (hh > 23) { // Check for 24hr roll-over (could roll-over on 13)
          hh = 0;      // 0 for 24 hour clock, set to 1 for 12 hour clock
        }
      }
    }


    /// Update digital time
    int xpos = 0;
    int ypos = 85; /// Top left corner ot clock text, about half way down
    int ysecs = ypos + 24;

    if (omm != mm) { // Redraw hours and minutes time every minute
      omm = mm;
      // Draw hours and minutes
      if (hh < 10) xpos += tft.drawChar('0', xpos, ypos, 8); // Add hours leading zero for 24 hr clock
      xpos += tft.drawNumber(hh, xpos, ypos, 8);             //Draw hours
      xcolon = xpos; // Save colon coord for later to flash on\off later
      xpos += tft.drawChar(':', xpos, ypos - 8, 8);
      if (mm < 10) xpos += tft.drawChar('0', xpos, ypos, 8); //Add minutes leading zero
      xpos += tft.drawNumber(mm, xpos, ypos, 8);             //Draw minutes
      xsecs = xpos; // Sae seconds 'x' position for later display updates
    }
    if (oss != ss) { // Redraw seconds time every second
      oss = ss;
      xpos = xsecs;

      if (ss % 2) { // Flash the colons on\off
        tft.setTextColor(0x39C4,TFT_BLUE);        // Set colour to grey to dim colon
        tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
        xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
        tft.setTextColor(TFT_YELLOW,TFT_BLUE);    // Set colour back to yellow
      }
      else {
        tft.drawChar(':', xcolon, ypos - 8, 8);     // Hour:minute colon
        xpos += tft.drawChar(':', xsecs, ysecs, 6); // Seconds colon
      }

      //\\Draw seconds
      if (ss < 10) xpos += tft.drawChar('0', xpos, ysecs, 6); // Add leading zero
      tft.drawNumber(ss, xpos, ysecs, 6);                     // Draw seconds
    }
  }
  
  
  }
