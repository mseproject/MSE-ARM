#include <Servo.h>
#include <EEPROM.h>

//VARIABLES
int stage = 0; 
int dropoff = 0; 
int check=0; 
boolean leftposition = 0; 
boolean forwardposition = 0; 
boolean backwardsposition = 0; 
boolean rightposition = 0; 
int pickup = 0; 




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
  Serial.println("MOVING RIGHT"); 
  moveright(); 
  if (rightposition == 1)
      {
        pickup = 1;
      }
}

int moveright()
{
   do {
     Serial.println("BLINKING");
     leftblink = blinkingleft();
     Serial.println(leftblink);  
     
     Serial.println("LONG DISTANCE"); 
     fardistance = Ping();
     Serial.println(fardistance);
     
     Serial.println("RIGHT SENSOR");
     brightness_right = analogRead(A0);
     Serial.println(brightness_right); 

    //move the base motors forward
    delay(100);
    //turn off the base motors
    servo_lateral.writeMicroseconds(1500); 
    delay(500);
   }
   while (leftblink = 0) && (brightness_right <=70 )) && (Ping()<=2150)); 
   rightposition = 1; 
   servo_lateral.writeMicroseconds(1500);
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

int blinkingleft()
{
  for (int i=0; i<100; i++)
{
  brightness_left = analogRead (A1); 
  
  if (brightness_left<20)
  {
    blinker = true; 
  }
}

if (blinker == true)
{
  //Serial.println("Blinking"); 
  return 1; 
}

else 
{
  //Serial.println("Not Blinking"); 
  return 0; 
}
}
