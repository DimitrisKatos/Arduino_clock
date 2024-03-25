// Create a arduino clock without rtc.
// Import the libraries
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define the variables for the time and date.
int sec =0 , min =0, hour=0 ,day=1 ,month=1 ,year=2022;

// Define the variables for the alarm.
int Hour=1, Min=0;

// Define variables that is used only for the counter. 
int MIN =0 ,SEC=0;

// Define the pins for the buttons. 
int pushbutton1 = 7 , pushbutton2= 8, pushbutton3 =9,pushbutton4 = 10, pushbutton5=4 , pushbutton6=5;

// Define the pin for the buzzer.
int buzzer=2 ;

// Define the varible now as millis. 
unsigned long now=millis();
int event=1000;

void setup() {
 // initialization of the lcd display.
 lcd.begin();

 // Enable the serial communication.
 Serial.begin(9600);

// Define the buttons and buzzer as output or inputs.
  pinMode(pushbutton1,INPUT_PULLUP);
  pinMode(pushbutton2,INPUT_PULLUP);
  pinMode(pushbutton3,INPUT_PULLUP);
  pinMode(pushbutton4,INPUT_PULLUP);
  pinMode(pushbutton5,INPUT_PULLUP);
  pinMode(pushbutton6,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
}

void loop() {
  int buttonState1=digitalRead(pushbutton1);
  int buttonState2=digitalRead(pushbutton2);
  int buttonState3=digitalRead(pushbutton3);
  int buttonState4=digitalRead(pushbutton4);
  int buttonState5=digitalRead(pushbutton5);
  int buttonState6=digitalRead(pushbutton6);

   
  if(millis()-now>=event){
    Serial.println(millis()-now);
    now=millis();
    sec=sec+1;

    // First raw of the lcd display for the hour.
    lcd.setCursor(0,0);
    lcd.print("TIME:");
    lcd.print(hour);
    lcd.print(":");
    lcd.print(min);
    lcd.print(":");
    lcd.print(sec);
    lcd.print("        ");

    // We define the boundaries for the seconds, minutes, hours and date.

    if(sec==59){
      min=min+1;
      sec=-1;
    }
    if(min==60){
      hour=hour+1;
      min=0;
    }
    if(hour==24){
      day=day+1;
      hour=0;
    }
    if(day==31){
      month=month+1;
      day=1;
    }
    if(month==13){
      year=year+1;
      month=1;
    }

  // The first push button help us to change the minutes of the clock.
  if(buttonState1==HIGH && buttonState6==LOW && buttonState5==LOW){
    min=min+1;
    }
 
  // The second push button help for changing the hours.
  if(buttonState2==HIGH && buttonState6==LOW && buttonState5==LOW){
    hour=hour+1;
    } 

  // The third push button changes the days.
  if(buttonState3==HIGH){
    day=day+1;
    }
    
  // The fourth button changes the months.
  if(buttonState4==HIGH&& buttonState5==LOW){
    month=month+1;

    // If you want to change the year, you are doing it by increasing the months over 12.
    if(month==12){
      year=year+1;
    }
  }
  
  // The second raw of the lcd display is for Date, alram and counter.
  // At first the second row will display the Date.

  if(buttonState5==LOW &&buttonState6==LOW) { //Date
    lcd.setCursor(0, 1);
    lcd.print("DATE:");
    lcd.print(day);
    lcd.print(":");
    lcd.print(month);
    lcd.print(":");
    lcd.print(year);
    lcd.print("         ");

    // When i return to the Date format, the counter return to zero.
    SEC=0;
    MIN=0;
    }

  // If you press button 5, in the second row you can format the alarm.
  if(buttonState5==HIGH && buttonState6==LOW){ //Alarm.

      lcd.setCursor(0,1);
      lcd.print("ALARM:");
      lcd.print(Hour);
      lcd.print(":");
      lcd.print(Min);
      lcd.print("         ");
      if(buttonState1==HIGH){
        Min=Min+1;
        if (Min==60) Min=0;
      }
      if (buttonState2==HIGH){
        Hour =Hour+1;
        if(Hour==24) Hour=0;
      }
    }

  // Enable counter by pressing the button 6.
  if (buttonState6==HIGH && buttonState5==LOW){ // Counter.

      // In this mode, you can press the second button to refresh the hour and date.
      if(buttonState2==HIGH){
        hour=0;
        min=0;
        day=1;
        month=1;
        year=2022;
        }
        lcd.setCursor(0,1);
        lcd.print("TIMER:");
        lcd.print(MIN);
        lcd.print(":");
        lcd.print(SEC);
        lcd.print("        ");
      if(buttonState1==HIGH){
        SEC=SEC+1;
        if(SEC==60) {
          MIN=MIN+1;
          SEC=0;
        }
      }
     }
  // The buzzer will be set to HIGH.
  if(min==Min && hour==Hour){
    tone(buzzer,5000);}
    else noTone(buzzer);
  }
}

