#include <Servo.h>
#include <EEPROM.h>

//VARIABLES
int stage = 0; 
int dropoff = 0; 
int check=0; 
boolean leftposition = 0; 



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
       Serial.println("MOVING LEFT"); 
       moveleft();
       if (leftposition == 1)
       {
         dropoff = 1; 
       }
}

int moveleft()
{
   do 
   {
     Serial.println("LONG DISTANCE"); 
     fardistance = Ping();
     Serial.println(fardistance);
     
     Serial.println("RIGHT SENSOR");
     brightness_right = analogRead(A0);
     Serial.println(brightness_right); 
     
     Serial.println("LEFT SENSOR");
     brightness_left = analogRead(A1); 
     Serial.println(brightness_left);
     
    //move the base motors backwards
    delay(100);
    //turn off the base motors 
    delay(500);
   }
   while ( (brightness_right >= 15) && (brightness_left<=40) && (Ping()<=2000) );
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
