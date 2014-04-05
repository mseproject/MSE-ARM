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
    int right_light_threshold = 150; 
    int right_dark_threshold = 500; 
    int left_light_threshold = 150; 
    int left_dark_threshold = 500; 
    
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
Serial.println("PULLING IN MAIL");
pull(); 
right = analogRead(A4); 
left = analogRead(A5); 

if ((left>left_light_threshold)||(left<left_dark_threshold)||(right>right_light_threshold)||(right<right_dark_threshold))
{
    Serial.println("Picked up the mail"); 
    pickup = 3; 
}

else
{
  pull(); 
}
}


int pull ()
{
  servo_frontmotor.writeMicroseconds(1200); 
  delay(4000); 
  servo_frontmotor.writeMicroseconds(1500); 
}
 
