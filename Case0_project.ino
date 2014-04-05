#include <Servo.h>
#include <EEPROM.h>

//VARIABLES
int stage = 0; 
int check=0; 
int incoming = 0; 
int outgoing = 0; 
int test = 0;


//SERVOS
Servo servo_frontmotor; 
Servo servo_basemotor; 
Servo servo_lateral; 

//PIN DECLARATIONS
const int right_lightsensor = A0; 
const int left_lightsensor = A1; 
const int right_tracker = A4; 
const int left_tracker = A5; 
const int front_motor = 8; 
const int lateral_motor = 9;
const int ultrasonic_output_data = 12; 
const int ultrasonic_input_ping = 13;

//SENSOR OPTIONS 
// Motors 
   const int pulling = 1750; 
   const int pushing = 1250; 
   const int pushtime = 200; 
   const int pulltime = 300;     

//Light Sensors 
    int brightness_right = 0; 
    int brightness_left = 0;
    int bright = 0; 
    int dark = 0;  
    int rightblink = 0; 
    int leftblink = 0; 
    boolean blinker = false; 

//Ultrasonic 
    int closedistance = 0; 
    int fardistance = 0; 
    int stopdistance = 0; 
    unsigned long ul_PingTime = 0;
    unsigned long pingDistance = 100000; 
    int distance = 0; 
    unsigned long ul_Echo_Time;

//Linetrackers 
    int right = 0; 
    int left = 0; 
    int right_light_threshold = 350; 
    int right_dark_threshold = 80; 
    int left_light_threshold = 170; 
    int left_dark_threshold = 80; 
    

void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);

  pinMode(ultrasonic_input_ping, OUTPUT);
  pinMode(ultrasonic_output_data, INPUT);
  
  pinMode(front_motor, OUTPUT);
  servo_frontmotor.attach(front_motor);
 
  pinMode(left_tracker, INPUT);
  pinMode(right_tracker, INPUT);

  pinMode (left_lightsensor, INPUT); 
  pinMode (right_lightsensor, INPUT); 
}

void loop()
{        
Serial.println(Ping());   
  Serial.available(); 
    while (Serial.available())
    {
      incoming = Serial.parseInt(); 
      if (incoming == 1)
      {
          outgoing = Ping(); 
          
          if (outgoing < 2100)
          {
             Serial.println(7);
          }
          
          else 
          {
            Serial.println(5); 
          }
      } 
    }
}

int blinking()
{
  for (int i=0; i<50; i++)
{
  brightness_right = analogRead (A0); 
  //Serial.println(brightness_right); 
  
  if (brightness_right<40)
  {
    blinker = true; 
  }
}

if (blinker == true)
{
  //Serial.println("Blinking"); 
  return 1; 
}

else if (blinker == false)
{
  //Serial.println("Not Blinking"); 
  return 0; 
}

}

int Ping() 
{
  while(millis() - ul_PingTime < 16)
  delay(2);
  digitalWrite(ultrasonic_input_ping, HIGH);
  delayMicroseconds(10);
  digitalWrite(ultrasonic_input_ping,LOW);
  ul_Echo_Time = pulseIn (ultrasonic_output_data, HIGH, 10000);
  ul_PingTime = millis();
  return ul_Echo_Time;
}

