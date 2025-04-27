#include <Keypad.h>

// Define the keypad layout
char keys[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pin_rows[4] = {10, 9, 8, 7};
byte pin_column[3] = {6, 5, 4};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, 4, 3);

const String password = "1357";
String input_password;

int countdown = 0;
bool warnSucess = false;
bool active = false;
bool armed = false;

void setup() {
  // Configure pins
  pinMode(2, INPUT);     // Sensor input
  pinMode(3, OUTPUT);    // Horn output
  pinMode(11, OUTPUT);   // LED output

  // Ensure horn and LED are off initially
  digitalWrite(3, LOW);
  digitalWrite(11, LOW);

  // Start serial communication
  Serial.begin(9600);

  // Reserve memory for input password
  input_password.reserve(32);
}



void loop() {
  char key = keypad.getKey();  // Get the pressed key

  if (key) {
    Serial.println(key);

    // Flash the LED to indicate key press
    digitalWrite(11, HIGH);
    digitalWrite(3, HIGH);
    delay(100);
    digitalWrite(11, LOW);
    digitalWrite(3, LOW);

    // Arm system if '*' is pressed and password is correct
    if (key == '*' && !active) {
      if (password == input_password) {
        Serial.println("Arming in 10 seconds...");

        for (int i = 0; i < 10; i++) {
          digitalWrite(11, HIGH);
          digitalWrite(3, HIGH);
          delay(50);
          digitalWrite(3, LOW);
          delay(500);
          digitalWrite(11, LOW);
          delay(500);
          countdown--;
          Serial.println(countdown);
        }
        
        armed = true;
        Serial.println("System armed.");
        
        while (digitalRead(2) == HIGH){
          Serial.println("clearing motion sensor");
        }
        for (int i = 0; i < 3; i++) {
          digitalWrite(3, HIGH);
          delay(250);
          digitalWrite(3, LOW);
          delay(250);
        }
        input_password = ""; //reset the input password, bugfix
      } else {
        Serial.println("Wrong password");

        digitalWrite(11, HIGH); 
        delay(1000);
        digitalWrite(11, LOW);
      }
    }

    // Disarm system if '#' is pressed and password is correct
    else if (key == '#') {
      if (password == input_password) {
        if (armed){
          Serial.println("Password is correct");
  
          // Disarm the system
          active = false;
          armed = false;
          Serial.println("System disarmed.");
          delay(500);
        } else {
          Serial.println("Password is correct...  but the system is not armed");
        }

      } else {
        Serial.println("Wrong password");

        digitalWrite(11, HIGH);
        delay(1000);
        digitalWrite(11, LOW);
      }

      // Clear input
      input_password = "";
    }

    // Accumulate digits into password input
    else {
      input_password += key;
    }

    delay(100);  // Debounce delay
  }

  // Trigger alarm after delay if sensor is activated and system is armed
  if (digitalRead(2) == HIGH && armed) {
    active = true;
  }

  if (active) {
    digitalWrite(3, HIGH);  // Turn on the horn
    digitalWrite(11, HIGH);  // Turn on the led
  } else {
    digitalWrite(3, LOW);  // Turn off the horn
    digitalWrite(11, LOW);  // Turn off the LED
  }
}
