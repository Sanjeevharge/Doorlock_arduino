
#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, 10, 11, 12, 13);
int c=0;
String pad;
Servo ServoMotor;
char* password = "5842";  // change the password here, pick any 4 numbers
int position = 0;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = { 8, 7, 6, 9 };
byte colPins[COLS] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  ServoMotor.attach(A2); //servos motor
  pinMode(1, OUTPUT);  //led
  digitalWrite(1, LOW);
  LockedPosition(true);
  lcd.begin(20, 4);
  pinMode(A3,OUTPUT); //buzzer
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    String konv = String(key);
    pad += konv;
    lcd.setCursor(0, 0);
    lcd.print("Enter pin:");
    lcd.setCursor(0, 1);
    lcd.print(pad);
    delay(100);

    if (key == '*' || key == '#') {
      position = 0;
      LockedPosition(true);
    }

    if (key == password[position]) {
      position++;
    }
    c++;
    if (position == 4) {
      LockedPosition(false);
      digitalWrite(1, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Lock Opened");
      delay(2000);
      lcd.clear();
      position = 0;
      c=0;
      pad = "";
      delay(2000);
      digitalWrite(1,LOW);  
    }

    if (c==5 && position != 4) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Wrong Password");
      lcd.setCursor(0,1);
      lcd.print("Entered");
      delay(2000); // Display the error message for 2 seconds
      lcd.clear();
      position = 0;
      c=0;
      pad = "";
      tone(A3,4000);
      delay(1000);
      noTone(A3);
      delay(1000);
    }
  }
}

void LockedPosition(int locked) {
  if (locked) {
    ServoMotor.write(11);
  } else {
    ServoMotor.write(90);
  }
}
