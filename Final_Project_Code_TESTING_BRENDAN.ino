#include <Servo.h>
#include <EEPROM.h>

//VARIABLES
int stage = 0; 
int dropoff = 0; 

boolean leftposition = 0; 
boolean forwardposition = 0; 
boolean backwardsposition = 0; 
boolean rightposition = 0; 
int pickup = 0; 
boolean mailbox1 = false; 
boolean mailbox2 = false; 
boolean mailbox3 = false; 
boolean mailbox4 = false; 
int flag = 0; 
int incoming = 0; 
int outgoing = 0; 
int shit =0;
int blinkright;
int testblink = 0; 
int forward = 0;

//SERVOS
Servo servo_frontmotor; 
Servo servo_basemotor; 
Servo servo_lateral; 
Servo servo_lateral2;

//PIN DECLARATIONS
const int right_lightsensor = A0; 
const int left_lightsensor = A1; 
const int right_tracker = A4; 
const int left_tracker = A5; 
const int front_motor = 8; 
const int lateral_motor = 9;
const int lateral_motor2 = 10;
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
    int distance = 0; 
    int shortdistance = 0;


//Linetrackers 
    int right = 0; 
    int left = 0; 
    int right_light_threshold = 100; 
    int right_dark_threshold = 400; 
    int left_light_threshold = 100; 
    int left_dark_threshold = 400; 
    

void setup() 
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);

  pinMode(ultrasonic_input_ping, OUTPUT);
  pinMode(ultrasonic_output_data, INPUT);
  
  pinMode(front_motor, OUTPUT);
  servo_frontmotor.attach(front_motor);
  
  pinMode(lateral_motor, OUTPUT); 
  servo_lateral.attach(lateral_motor);
  
  pinMode(lateral_motor2, OUTPUT);
  servo_lateral2.attach(lateral_motor2); 
 
  pinMode(left_tracker, INPUT);
  pinMode(right_tracker, INPUT);

  pinMode (left_lightsensor, INPUT); 
  pinMode (right_lightsensor, INPUT); 
}


void loop()
{        
  
  
  switch (stage)
  {
    case 0:
    {
      
  Serial.available(); 
    
      incoming = Serial.parseInt(); 
      if (incoming == 1)
      {
          shit = 1;
      } 
      else 
      {
        stage = 0;
      }

    switch(shit)
    {
      case 1:
      {
        outgoing = Ping(); 
          
          if (outgoing < 2100)
          {
             Serial.println(7);
             shit = 2;
          }
          
          else 
          {
            Serial.println(5); 
             
          }
          if(shit ==  2)
          {
          break;
          }
      }
      
         case 2:
      {
                 

         do
         {
           servo_lateral.writeMicroseconds(1800);
           servo_lateral2.writeMicroseconds(1800);
           delay(50); 
           servo_lateral.writeMicroseconds(1500); 
           servo_lateral2.writeMicroseconds(1500);
           distance = Ping(); 
           brightness_right == analogRead(A1);
         }
         while(distance>1500);
         shit = 3; 
         break;
      
      }
      case 3:
      {
                    brightness_left = analogRead(A0); 

         if(brightness_left > 30)
         {
            Serial.println(10);
            //distance = Ping(); 
         }
       
         if (brightness_left <30)
         {
           //blinkright = blinking();
           //lighttest = brightness_left; 
           //Serial.println(); 
           Serial.println(11);
         }
         break;
      }

    break;
}
        stage = 1; 
        break;
 }//case 0 ends here 
        
       case 1: //ROBOT MAIL/MAILBOX MAIL
           {
               blinker = false; 
               //rightblink = blinking(); 
               //Serial.println("Left"); 
               //Serial.println(analogRead(A5)); 
               //Serial.println("Right"); 
               //Serial.println(analogRead(A4)); 
               right = analogRead(A4); 
               left = analogRead(A5); 

            if ((left<left_light_threshold)||(left>left_dark_threshold)||(right<right_light_threshold)||(right>right_dark_threshold))  
                   {
                     //Serial.println("I HAVE MAIL"); 
                     //stage = 2;
                    testblink = blinking();
                    
                     if( testblink == 1) 
                          {
                               //Serial.println("MAILBOX HAS MAIL, MOVE LEFT AND THEN RIGHT");
                               stage = 2; 
                          }
                    else
                          {
                                //Serial.println("MAILBOX HAS NO MAIL, MOVE LEFT AND THEN DIP!!!!!!!!");
                                stage = 3;
                          }
                   }
                                                                                                              
                                    
            else 
             {
               //Serial.println("I DON'T HAVE MAIL");
                    testblink = blinking();
                    
                    if (testblink == 1)
                        {
                            //Serial.println("MAILBOX HAS MAIL, MOVE RIGHT"); 
                            stage = 4;
                        }
                    else
                        {
                            //Serial.println("MAILBOX HAS NO MAIL, get da fuck outta here");
                            stage = 5;
                        }
           
             }
             break;
         }

            
        
         
         case 3: //ROBOT HAS MAIL, MAILBOX HAS no MAIL //   while ( (brightness_right >= 15) && (brightness_left<=40) && (Ping()<=2000) ); 
           {
             outgoing = Ping(); 
          if (outgoing < 1600)
          {
             Serial.println(21);
          }
          
          else 
          {
            Serial.println(22); 
            forward++;
          }
          
          if (forward == 1)
          {
            outgoing = Ping();
            do
            {
              outgoing = Ping();
              servo_lateral.writeMicroseconds(1100);
              servo_lateral2.writeMicroseconds(1100); 
              servo_frontmotor.writeMicroseconds(1500);
            }while( outgoing > 1925);
             
             
              servo_lateral.writeMicroseconds(1500);
              servo_lateral2.writeMicroseconds(1500);
             if ( outgoing < 1925)
            { 
              servo_frontmotor.writeMicroseconds(1900);
             
            }
            stage = 4; 
          }  
           break;
         }
         
         case 4:
         {
              servo_lateral.writeMicroseconds(1500);
              servo_lateral2.writeMicroseconds(1500);
              servo_frontmotor.writeMicroseconds(1500);
              Serial.println(25); 
              break;
         }
         
         break;
  }
}

                 
//FUNCTIONS
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
    servo_lateral.writeMicroseconds(1500); 
    delay(500);
   }
   while ( (brightness_right >= 15) && (brightness_left<=70) && (Ping()<=2000) ); 
   leftposition = 1; 
   servo_lateral.writeMicroseconds(1500); 

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
   while ((leftblink = 0) && (brightness_right <=70 ) && (Ping()<=2150)); 
   rightposition = 1; 
   servo_lateral.writeMicroseconds(1500);
}

int push ()
{
  servo_frontmotor.writeMicroseconds(1850); 
  delay(5000); 
  servo_frontmotor.writeMicroseconds(1500); 
  }

int pull ()
{
  servo_frontmotor.writeMicroseconds(1200); 
  delay(4000); 
  servo_frontmotor.writeMicroseconds(1500); 
}

void moveforward()
{
 do 
  {
    servo_lateral.writeMicroseconds(1850);
    delay (500); 
    servo_lateral.writeMicroseconds(1500);
    delay(500); 
    Serial.println("Short Distance");
    shortdistance = Ping(); 
    Serial.println(shortdistance); 
  }
 while (shortdistance > 1850); 
 forwardposition = 1; 
servo_lateral.writeMicroseconds(1500);

}

void movebackwards()
{
  do
  {
  Serial.println("Moving Backwards");
  servo_lateral.writeMicroseconds(1100); 
  delay(500);
  servo_lateral.writeMicroseconds(1500); 
  delay(500);
  Serial.println(Ping()); 
  }
  while (Ping()<2250); 
  backwardsposition = 1; 
  servo_lateral.writeMicroseconds(1500);
}

int blinking()
{
  for (int i=0; i<100; i++)
{
  brightness_right = analogRead (A0); 
  
  if (brightness_right<20)
  {
    blinker = true; 
  }
}

if (blinker == true)
{
  //Serial.println("Blinking"); 
  //Serial.println(1); 
  return 1;
}

else 
{
  //Serial.println("Not Blinking"); 
  //Serial.println( 0); 
  return 0;
}
}

int blinkingleft()

{
  blinker = false;
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

void thisistellingmeaboutmailandmailbox()
{        
               blinker = false; 
               //rightblink = blinking(); 
               //Serial.println("Left"); 
               //Serial.println(analogRead(A5)); 
               //Serial.println("Right"); 
               //Serial.println(analogRead(A4)); 
               right = analogRead(A4); 
               left = analogRead(A5); 

            if ((left<left_light_threshold)||(left>left_dark_threshold)||(right<right_light_threshold)||(right>right_dark_threshold))  
                   {
                     //Serial.println("I HAVE MAIL"); 
                     //stage = 2;
                    testblink = blinking();
                   if( testblink == 1) 
            {
             //Serial.println("MAILBOX HAS MAIL, MOVE LEFT AND THEN RIGHT");
               // stage = 3; 
              }
              else
              {
                Serial.println("MAILBOX HAS NO MAIL, MOVE LEFT AND THEN DIP!!!!!!!!");
              }
                   }
                    else 
             {
               Serial.println("I DON'T HAVE MAIL");
             testblink = blinking();
              if (testblink == 1)
              {
                Serial.println("MAILBOX HAS MAIL, MOVE RIGHT"); 
                stage = 5;
              }
              else
              {
                Serial.println("MAILBOX HAS NO MAIL, get da fuck outta here");
              }
            }
         }
             
             
             
             
void testing()
{
          outgoing = Ping(); 
          Serial.print(outgoing);
          if (outgoing < 1600)
          {
            //stop we made it
             Serial.println(21);
             
          }
          
          else 
          {
            // keep going
            Serial.println(22); 
            forward++;
          }
          
          if (forward == 1)
          {
            outgoing = Ping();
            do
            {
              outgoing = Ping();
              servo_lateral.writeMicroseconds(1100);
              servo_lateral2.writeMicroseconds(1100); 
              servo_frontmotor.writeMicroseconds(1500);
            }while( outgoing > 1925);
             
              servo_lateral.writeMicroseconds(1500);
              servo_lateral2.writeMicroseconds(1500);
             if ( outgoing < 1925)
            { 
              servo_frontmotor.writeMicroseconds(1900);
            }
            
          }  
}
