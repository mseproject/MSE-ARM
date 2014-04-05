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
boolean mailbox1 = false; 
boolean mailbox2 = false; 
boolean mailbox3 = false; 
boolean mailbox4 = false; 
int flag = 0; 
int incoming;
int outgoing;



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
    int distance = 0; 
    int shortdistance = 0;


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
  
  pinMode(lateral_motor, OUTPUT); 
  servo_lateral.attach(lateral_motor);
 
  pinMode(left_tracker, INPUT);
  pinMode(right_tracker, INPUT);

  pinMode (left_lightsensor, INPUT); 
  pinMode (right_lightsensor, INPUT); 
}
//check for line trackers
void loop()
{
                    right = analogRead(A4); 
                    left = analogRead(A5); 
                    Serial.println("Right");
                    Serial.println(right);
                    Serial.println("Left");
                    Serial.println(left);
                    
                    
                    if (right < 50 && left < 50)
                    {
                      Serial.println("Room 1");
                    }
                    
                    if (right > 400 && left < 50)
                    {
                      Serial.println("Room 2/3");
                    }
                    
                    if (((right > 60)&&(right < 200)) && ((left > 60)&&(left < 200)))
                    {
                      Serial.println("No mail");
                    }
}
void blank()
{ 

 switch (stage) 
         {
           case 0: //FIND CENTRE OF MAILBOX
           {
             flag = 0; 
             //Serial.println("Blinking");
             rightblink = blinking(); 
             //Serial.println(rightblink); 
             
             //Serial.println("Brightness Left"); 
             brightness_left = analogRead (A1); 
             //Serial.println(brightness_left); 
             
             //Serial.println("Distance");
             distance = Ping(); 
             //Serial.println(distance);  
int shit;
  Serial.available(); 
    
      incoming = Serial.parseInt(); 
      if (incoming == 1)
      {
          shit = 1;
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
          break;
      }
      
      case 2:
      {
        int distance = 0; 
         do
         {
           servo_lateral.writeMicroseconds(1800);
           delay(500); 
           servo_lateral.writeMicroseconds(1500); 
           distance = Ping(); 
         }
         while(distance>1500);
      }
      
           
           
        
        
    }
    
    
    
      
  if (check = 1)
      {           
         if (rightblink == 1)
     {
          flag=1;
     }
         else 
     {
          flag = 0; 
     }    
           
           if ((rightblink == 1) && (brightness_left<50) && (distance <1400))
         {
               Serial.println("Center"); 
         }  
      
        stage = 1; 
        break;
           }
           }
           
           
       case 1: //ROBOT MAIL/MAILBOX MAIL
           {
               rightblink = blinking(); 
               //Serial.println("Left"); 
               //Serial.println(analogRead(A5)); 
               //Serial.println("Right"); 
               //Serial.println(analogRead(A4)); 
               right = analogRead(A4); 
               left = analogRead(A5); 

            if ((left>left_light_threshold)||(left<left_dark_threshold)||(right>right_light_threshold)||(right<right_dark_threshold))  
                   {
                     Serial.println("HAS MAIL"); 
                     stage = 2; 
                     break;
                   }
                   
            else 
            {
              if (rightblink == 1)
              {
                Serial.println("MAILBOX HAS MAIL, MOVE RIGHT");
                stage = 3; 
                break;
              }
              
              if (rightblink == 0)
              {
                Serial.println("ARM IS DONE, BASE MOVE TO NEXT MAILBOX"); 
                stage = 5;
                break;
              }
            }
            break;
         }
         
         case 2: //ROBOT HAS MAIL, MOVE LEFT 
           {
             Serial.println("ROBOT HAS MAIL, MOVE LEFT"); 
               
               switch(dropoff) 
               {
                      case 0:
                          {
                            Serial.println("MOVING LEFT");     
                            moveleft();
                            if (leftposition == 1)
                                {
                                  dropoff = 1; 
                                  break;
                                }
                          }
                      
                      case 1: 
                          {
                             Serial.println("MOVING FORWARD"); 
                             moveforward();    
                             if (forwardposition == 1)
                                {
                                   dropoff = 2; 
                                   break;
                                 }
                          }
                          
                      case 2:
                          {
                             Serial.println("PUSHING OUT MAIL");
                             push(); 
                             dropoff = 3; 
                             break;
                          }
                          
                     case 3:
                          {
                             Serial.println("MOVE BACKWARDS"); 
                             movebackwards(); 
                             if (backwardsposition == 1)
                             {
                               dropoff = 4; 
                               break;
                             }
                          }
                          
                     case 4:
                         {
                            if (flag == 1)
                              {
                                stage = 3;
                                break;
                              }
                              
                              else if (flag == 0)
                              {
                                stage = 4; 
                                break;
                              }
                         }
               }
               break;
           }
              
              case 3: //ROBOT NEEDS TO PICK-UP MAIL
              {
                forwardposition = 0; 
                backwardsposition = 0; 
                Serial.println("PICK-UP MAIL"); 
                 switch(pickup) 
                   {
                      case 0:
                        {
                            Serial.println("MOVING RIGHT"); 
                            moveright(); 
                            if (rightposition == 1)
                                {
                                   pickup = 1;
                                   break;
                                }    
                        }
                        
                        case 1:
                          {
                             Serial.println("MOVING FORWARD"); 
                             moveforward(); 
                             if (forwardposition == 1)
                                 {
                                    pickup = 2; 
                                    break;
                                 }
                          }
                          
                          case 2: 
                            {
                               Serial.println("PULLING IN MAIL"); 
                               pull(); 
                               right = analogRead(A4); 
                               left = analogRead(A5); 

                               if ((left>left_light_threshold)||(left<left_dark_threshold)||(right>right_light_threshold)||(right<right_dark_threshold))
                                  {
                                    Serial.println("Picked up the mail"); 
                                    pickup = 3; 
                                    break;
                                  }

                              else
                                  {
                                    pull(); 
                                  }
                              }
                          
                          case 3:
                            {
                             Serial.println("MOVE BACKWARDS"); 
                             movebackwards(); 
                             
                             if (backwardsposition == 1)
                             {
                               stage = 4; 
                               break; 
                             }
                            }
                   }
                   break;
              }
           
               case 4: //READ ENVELOPE AND DETERMINE MAILBOX
                 {
                    right = analogRead(A4); 
                    left = analogRead(A5); 
                    
                    if ((right<150) && (left<150))
                    {
                      mailbox1 = true; 
                      break;
                    }
                    
                    else if ((right<150) && (left>500))
                    {
                      mailbox2 = true; 
                      break; 
                    }
                    
                    else if ((right>500) && (left<150))
                    {
                      mailbox3 = true; 
                      break; 
                    }
                    
                    else if ((right>500)&&(left>500))
                    {
                      mailbox4 = true; 
                      break; 
                    }
                 break; 
                 }
             
             case 5:
               {
                 if (mailbox1 == true)
                 {
                   //Arm tells base to move to mailbox 1
                   break;
                 }
                 
                 else if (mailbox2 == true)
                 {
                   //Arm tells base to move to mailbox 2
                   break; 
                 }
                 
                 else if (mailbox3 == true)
                 {
                   //Arm tells base to move to mailbox 3
                   break; 
                 }
                 
                 else if (mailbox4 == true)
                 {
                   //Arm tells base to move to mailbox 4
                   break;
                 }
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
  return 1; 
}

else 
{
  //Serial.println("Not Blinking"); 
  return 0; 
}
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
             
