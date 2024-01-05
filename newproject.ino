//Είσοδος βιβλιθοθηκών που χρησιμοποιήθηκαν
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Ορισμός μεταβλητών για την ώρα και ημερομηνία
int sec =0 , min =0, hour=0 ,day=1 ,month=1 ,year=2022;
//Ορισμός μεταβλητών που χρησιμεύουν μόνο στο ξυπνητήρι
int Hour=1, Min=0;
//Ορισμός μεταβλητών που χρησιμοποιούνται μόνο για το χρονόμετρο
int MIN =0 ,SEC=0;
//Καθορισμός των pin που χρησιμοποιούνται ως buttons
int pushbutton1 = 7 , pushbutton2= 8, pushbutton3 =9,pushbutton4 = 10, pushbutton5=4 , pushbutton6=5;
//Καθορισμός του Buzzer
int buzzer=2 ;
unsigned long now=millis();
int event=1000;
//Η συνάρτηση setup θα τρέξει μόνο μια φορά στην αρχή του προγράμματος.
void setup() {
 //Αρχικοποίηση της lcd οθόνης
 lcd.begin();
 //Έναρξη σειριακής επικοινωνίας
 Serial.begin(9600);
//Oρισμός των Buttons και του Buzzer σαν είσοδος ή έξοδος
  pinMode(pushbutton1,INPUT_PULLUP);
  pinMode(pushbutton2,INPUT_PULLUP);
  pinMode(pushbutton3,INPUT_PULLUP);
  pinMode(pushbutton4,INPUT_PULLUP);
  pinMode(pushbutton5,INPUT_PULLUP);
  pinMode(pushbutton6,INPUT_PULLUP);
  pinMode(buzzer,OUTPUT);
}

//Η συνάρτηση loop θα επαναλαμβάνεται συνέχεια σαν ατέρμονος βρόγχος
void loop() {
  //Ανάγνωση των ψηφιακών θυρών
  int buttonState1=digitalRead(pushbutton1);
  int buttonState2=digitalRead(pushbutton2);
  int buttonState3=digitalRead(pushbutton3);
  int buttonState4=digitalRead(pushbutton4);
  int buttonState5=digitalRead(pushbutton5);
  int buttonState6=digitalRead(pushbutton6);

  
  //Στη συνάρτηση long αναθέτω το χρόνο απο τη στιγμή που ξεκίνησε το πρόγραμμα
 
  if(millis()-now>=event){
    Serial.println(millis()-now);
    now=millis();
    sec=sec+1;
    //Οπτικοποίηση της πρώτης γραμμής της lcd οθόνης
    lcd.setCursor(0,0);
    lcd.print("TIME:");
    lcd.print(hour);
    lcd.print(":");
    lcd.print(min);
    lcd.print(":");
    lcd.print(sec);
    lcd.print("        ");
    //Τοποθέτηση ορίων και μηδενισμός στις μεταβλητές του χρόνου και της ημερομηνίας
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
  //Ξεκίνημα αλγορίθμου για τη χρησιμότητητα των κουμπιών 
  //Αρχή με το κουμπι1 που αντιστοιχει στην αλλαγή των λεπτων
  if(buttonState1==HIGH && buttonState6==LOW && buttonState5==LOW){
    min=min+1;
    }
 
  //Το κουμπί 2 αντιστοιχεί στην αλλαγή των ωρών
  if(buttonState2==HIGH && buttonState6==LOW && buttonState5==LOW){
    hour=hour+1;
    } 
  //Το κουμπι 3 αντιστοιχεί στην αλλαγή των ημερών
  if(buttonState3==HIGH){
    day=day+1;
    }
  //Τέλος το κουμπί 3 αντιστοιχεί στην αύξηση των μηνών
  if(buttonState4==HIGH&& buttonState5==LOW){
    month=month+1;
    //Αμα θελήσω να αλλάξω το έτος πρέπει να το κάνω μέσω του pushbutton4 
    //Δηλαδή να αυξήσω του μήνες
    if(month==12){
      year=year+1;
    }
  }
  //Οπτικοποίηση της δεύτερης γραμμής της lcd οθόνης
  //Δηλαδή αν δεν πατάω το Button 5 και 6 τότε στη δεύτερη γραμμή εμφανίζεται η ημερομηνία 
  //Αν πατάω το Button5 και δεν πατάω το Button 6 τότε εμφανίζεται το ξυπνητήρι και μπορώ να το ρυθμίζω στην ώρα που εγώ θέλω
  //Αν πατάω το Button6 και δεν πατάω το Button 5 τότε εμφανίζεται το χρονόμετρο με ακρίβεια δευτερολέπτου  
    if(buttonState5==LOW &&buttonState6==LOW) { //ΗΜΕΡΟΜΗΝΊΑ
    lcd.setCursor(0, 1);
    lcd.print("DATE:");
    lcd.print(day);
    lcd.print(":");
    lcd.print(month);
    lcd.print(":");
    lcd.print(year);
    lcd.print("         ");
    //Όποτε βγαίνω από το χρονόμετρο ,οι μεταβλητές που χρησιμοποιώ εκεί θα μηδενίζονται.
    SEC=0;
    MIN=0;
    }
     if(buttonState5==HIGH && buttonState6==LOW){ //ΞΥΠΝΗΤΗΡΙ

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
     if (buttonState6==HIGH && buttonState5==LOW){ // ΧΡΟΝΌΜΕΤΡΟ
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
  if(min==Min && hour==Hour){
    tone(buzzer,5000);}
    else noTone(buzzer);
  }
}

