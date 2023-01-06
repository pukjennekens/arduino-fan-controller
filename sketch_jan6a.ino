/**
  * Global settings
  * Go to the section 'Keypad setup' to set the rowPins and colPins variables that are used for reading the keypad
  */
bool debugOn = true; // Turn the debug menu on or off

// Keys
int temp1    = 25;   // Temperature when key 1 is pressed
int temp2    = 30;   // Temperature when key 2 is pressed
int temp3    = 40;   // Temperature when key 3 is pressed
int temp4    = 50;   // Temperature when key 4 is pressed
int temp5    = 55;   // Temperature when key 5 is pressed
int temp6    = 60;   // Temperature when key 6 is pressed
int temp7    = 70;   // Temperature when key 7 is pressed
int temp8    = 80;   // Temperature when key 8 is pressed
int temp9    = 90;   // Temperature when key 9 is pressed

// DHT Sensor pin
#define DHTPIN 9      // What pin is the DHT sensor connected to?
#define DHTTYPE DHT11 // What type of DHT sensor?

/**
 * END GLOBAL SETTINGS
 */

// Inlcudes
#include <Keypad.h>
#include <DHT.h>

/**
 * Keypad setup
 */
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' },
};

const byte rowPins[ROWS] = { 2, 3, 4, 5 };
const byte colPins[COLS] = { 6, 7, 8 };

Keypad keypad = Keypad( makeKeymap( keys ), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin( 9600 );
}

/**
 * DHT Sensor setup
 */
DHT dht( DHTPIN, DHTTYPE );

/**
 * Global variables
 */
bool on        = false;
int targetTemp = 40;
bool fanOn     = false;
bool autoMode  = false;

/**
 * Timer variables
 */
int currentMillis     = 0;

int debugInterval     = 1000;
int prevDebugInterval = 0;

void loop() {
  char key = keypad.getKey();

  // Current milliseconds for timer functions
  currentMillis = millis();

  /**
   * Temperature and humidity
   */
  float humidity    = dht.readHumidity();    // Humidity
  float temperature = dht.readTemperature(); // Temerature in celcius

  Serial.println( temperature );

  // Check if key is pressed
  if ( key ) {
    // Check what key and perform actions
    switch( key ) {
      // Set the temps
      case '1': targetTemp = temp1; break;
      case '2': targetTemp = temp2; break;
      case '3': targetTemp = temp3; break;
      case '4': targetTemp = temp4; break;
      case '5': targetTemp = temp5; break;
      case '6': targetTemp = temp6; break;
      case '7': targetTemp = temp7; break;
      case '8': targetTemp = temp8; break;
      case '9': targetTemp = temp9; break;
      // Turn the system on
      case '*': on = true; break;

      // Turn the system off
      case '#': on = false; break;

      case '0': autoMode = !autoMode; break;
    }
  }

  // Debug the variables on debug interval
  if( currentMillis - prevDebugInterval >= debugInterval && debugOn ) {
    prevDebugInterval = currentMillis;
    Serial.print( "\n" );

    Serial.println( "====== DEBUG MENU ======" );

    if( on ) {
      Serial.println( "SYSTEM STATUS: ON" );
    } else {
      Serial.println( "SYSTEM STATUS: OFF" );
    }

    String targetTempDesc = "TARGET TEMP: ";
    String TargetTempLine = targetTempDesc + targetTemp;
    Serial.println( TargetTempLine );

    if( fanOn ) {
      Serial.println( "FAN: ON" );
    } else {
      Serial.println( "FAN: OFF" );
    }

    if( autoMode ) {
      Serial.println( "AUTO MODE: ON" );
    } else {
      Serial.println( "AUTO MODE: OFF" );
    }

    Serial.println( "========================" );
  }
}
