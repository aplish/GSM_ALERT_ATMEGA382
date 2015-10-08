//PROGRAM FOR ATMEGA 328

int sw1=0;
int sw2=0;

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900(12, 13);
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
void setup()
{
  SIM900.begin(9600);
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, OUTPUT);
  lcd.setCursor(3,0);
  lcd.print("CAR THEFT");
  lcd.setCursor(1,1);
  lcd.print("DETECTION SYS");
  delay(2000);
  lcd.clear();
}

void loop()
{
 sw1= digitalRead(8);
sw2= digitalRead(9);

if (sw1==0 && sw2==0)
{
  lcd.setCursor(1,0);

lcd.print("ACCESS GRANTED");
  lcd.setCursor(4,1);
  lcd.print("CAR ON ");
  digitalWrite(10, HIGH);
}
 
 if (sw1==1 && sw2==0)
{
  lcd.setCursor(1,0);
  lcd.print("ACCESS DENIED ");
  lcd.setCursor(4,1);
  lcd.print("CAR OFF");
  digitalWrite(10, LOW);
  SIM900.print("AT+CMGF=1\r");  
Serial.print("AT+CMGF=1\r");   // AT command to send SMS message
  delay(2000);
  SIM900.println("AT + CMGS = \"9625450453\"");
Serial.println("AT + CMGS = \"9625450453\"");  // recipient's mobile number, in international format
  delay(1000);
  SIM900.println("Someone is trying to access your car");        // message to send
  Serial.println("Someone is trying to access your car");   
  delay(200);
  SIM900.println((char)26);                       // End AT command with a ^Z, ASCII code 26
   Serial.println((char)26); 
  delay(200); 
  SIM900.println();
  delay(5000);                                     // give module time to send SMS
} 
}
