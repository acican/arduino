//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

This program will test the LCD panel and the buttons
Mark Bramwell, July 2010

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define actActive  	0
#define actPause   	1
#define actRun		2

#define firstDigit 	7
#define lastDigit  	12

#define delayStart  9

int tipCrt, timeActiv, timePause, timePush, nrDigit, nrCicli, nrStart;
boolean isSetActiv, isSetDigit, _canMove;
unsigned long _lastMs;

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  

 // For V1.0 comment the other threshold and use the one below:
/*
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 195)  return btnUP; 
 if (adc_key_in < 380)  return btnDOWN; 
 if (adc_key_in < 555)  return btnLEFT; 
 if (adc_key_in < 790)  return btnSELECT;   
*/


 return btnNONE;  // when all others fail, return this...
}

int LED = 13; // Use the onboard Uno LED

void setup()
{
 Serial.begin(9600);
 Serial.println("LCD test!");
  
 lcd.begin(16, 2);              // start the library
 lcd.cursor();
 lcd.setCursor(0,0);
 lcd.print("Selecteaza"); // print a simple message
 
 tipCrt = actActive;
 timeActiv = 10000;
 timePause = 5000;
 timePush = 500;
 nrDigit = lastDigit;
 nrCicli = 0;
 nrStart = delayStart;

 _lastMs = 0;
 _canMove = false;

 isSetActiv = true;
 isSetDigit = false;
 
 pinMode(LED, OUTPUT);
}
 
void loop() {
//  lcd.cursor();
  lcd_key = read_LCD_buttons();  	// read the buttons
  
 
  switch (lcd_key) {
    case btnRIGHT: {
      isSetDigit = true;
      isSetActiv = false;
      
      if ((nrDigit + 1) > lastDigit)
        nrDigit = firstDigit;
      else 
        nrDigit = nrDigit + 1;

      lcd.setCursor(nrDigit,0);
	  
      delay(timePush); 
      break;
    }
	
    case btnLEFT: {
      isSetDigit = true;
      isSetActiv = false;
      
      if ((nrDigit - 1) >= firstDigit)
        nrDigit = nrDigit - 1;
      else
        nrDigit = lastDigit;

      lcd.setCursor(nrDigit,0);
	  
      delay(timePush);   
      break;
    }
	
    case btnUP: {
      if (isSetDigit)  
        setDigit(btnUP);
      else
        setTime(btnUP);
	 
      delay(timePush); 
      break;
    }
   
    case btnDOWN: {
      if (isSetDigit)  
        setDigit(btnDOWN);
      else
        setTime(btnDOWN);
	 
      delay(timePush); 
      break;
    }
	
    case btnSELECT: {
      isSetActiv = true;
      isSetDigit = false;

      if ((tipCrt + 1) < 3)
        tipCrt = tipCrt + 1;
      else
        tipCrt = 0;
      
      setActiv();
      Serial.println(tipCrt); 
     
      delay(timePush);  
      break;
    }
	
    case btnNONE: {

      break;
    }
  }
 
  startCiclu(); 
 

}
 
void setActiv() {
  _canMove = false;
  _lastMs = 0;
  switch (tipCrt) {
  
    case actActive: {
      lcd.setCursor(0,0);
      lcd.print("Activ   "); 
      lcd.setCursor(firstDigit,0);
      lcd.print("       ms");
      printNum(timeActiv);

      lcd.setCursor(0,1);
      lcd.print("durata start    ");

      lcd.setCursor(lastDigit,0);
      break;
    }
	
    case actPause: {
      lcd.setCursor(0,0);
      lcd.print("Pauza   "); 
      lcd.setCursor(firstDigit,0);
      lcd.print("       ms");
      printNum(timePause);

      lcd.setCursor(0,1);
      lcd.print("durata stop     ");
	 
      lcd.setCursor(lastDigit,0);
      break;
    }
	
    case actRun: {
      lcd.setCursor(0,0);
      lcd.print("Cicli   "); 
      lcd.setCursor(firstDigit,0);
      lcd.print("       nr");
      printNum(0);

      _canMove = true;  
      break;
    }

  }
}


void printNum(int iNum) {
  int valLen, poz;
  
  if(iNum > 9999)
    valLen = 5;
  else if(iNum > 999)
    valLen = 4;
  else if(iNum > 99)
    valLen = 3;
  else if(iNum > 9)
    valLen = 2;
  else
    valLen = 1;

  poz = 8 + 5 - valLen;
  lcd.setCursor(firstDigit,0);
  lcd.print("       ");
  lcd.setCursor(poz,0);
  lcd.print(iNum);

  lcd.setCursor(lastDigit,0);
}

void setTime(int tip) {
  switch (tipCrt) {
  
    case actActive: {
      if (tip == btnUP)
        timeActiv = timeActiv + 1;
      else 
        timeActiv = timeActiv - 1;
	  
      printNum(timeActiv);
    
      break;
    }
	
    case actPause: {
      if (tip == btnUP)
        timePause = timePause + 1;
      else 
        timePause = timePause - 1;
	  
      printNum(timePause);
	  
      break;
    }

 }
}

void getDigit(int iNum, int nDig) {
  lcd.setCursor(nDig,0);
}

void setDigit(int tip) {
  switch (tipCrt) {
    case actActive: {
      int d;
      char c;
      char acBuf[14];  // added 1 for NULL termination and 1 for the minus sign
      sprintf( acBuf, "%13d", timeActiv);
      c = acBuf[nrDigit];
      if (c >= 48)
        d = acBuf[nrDigit]-'0'; 
      else
        d = 0;     
      
      Serial.print("buf ");Serial.print(acBuf);Serial.print(" poz ");Serial.print(nrDigit);
      Serial.print(" chr ");Serial.print(acBuf[nrDigit]);Serial.print(" digit ");Serial.println(d);
      
      if (tip == btnUP) {
         if (d < 9)
           d = d + 1;
         else
           d = 0;
      }
	     else  {
         if (d > 0)
           d = d - 1;
         else
           d = 9;
	  }
      
      lcd.setCursor(nrDigit,0);
      lcd.print(d);
      lcd.setCursor(nrDigit,0);

      String str = String(d);
      c = str.charAt(0);
      Serial.print("digitUp ");Serial.print(d);Serial.print(" chrUp ");Serial.println(c);
      acBuf[nrDigit] = c;

      for (int i = 0; i < sizeof(acBuf); i++){
        Serial.print(i, DEC);
        Serial.print(" = ");
        Serial.print(acBuf[i]);
        Serial.print(" = ");
        Serial.println(acBuf[i], DEC);
      }
      
      String str1((char*)acBuf);
      timeActiv = str1.toInt();
      Serial.print("strUp ");Serial.print(str1);Serial.print(" time ");Serial.println(timeActiv);
      Serial.println(str);  
	 
      break;
    }
   
    case actPause: {
      int d;
      char c;
      char acBuf[14];  // added 1 for NULL termination and 1 for the minus sign
      sprintf( acBuf, "%13d", timePause);
	  c = acBuf[nrDigit];
      if (c >= 48)
        d = acBuf[nrDigit]-'0'; 
      else
        d = 0;     
      
      Serial.print("buf ");Serial.print(acBuf);Serial.print(" poz ");Serial.print(nrDigit);
      Serial.print(" chr ");Serial.print(acBuf[nrDigit]);Serial.print(" digit ");Serial.println(d);
      
      if (tip == btnUP) {
         if (d < 9)
           d = d + 1;
         else
           d = 0;
      }
	    else  {
         if (d > 0)
           d = d - 1;
         else
           d = 9;
	   }
      
      lcd.setCursor(nrDigit,0);
      lcd.print(d);
      lcd.setCursor(nrDigit,0);

      String str = String(d);
      c = str.charAt(0);
      Serial.print("digitUp ");Serial.print(d);Serial.print(" chrUp ");Serial.println(c);
      acBuf[nrDigit] = c;

      for (int i = 0; i < sizeof(acBuf) - 1; i++) {
       Serial.print(i, DEC);
       Serial.print(" = ");
       Serial.println(acBuf[i]);
      }
      
      String str1((char*)acBuf);
      timePause = str1.toInt();
      Serial.print("strUp ");Serial.print(str1);Serial.print(" time ");Serial.println(timePause);
      Serial.println(str);
	 
      break;
   }
  }   
}

void startCiclu() {
  if ((_lastMs == 0) && _canMove) {
    _lastMs = millis();
    nrStart = delayStart;
  
    lcd.setCursor(0,1);
    lcd.print("start in    ");
    lcd.setCursor(12,1);
    lcd.print(nrStart);
    lcd.setCursor(13,1);
    lcd.print(" s");
  }          

  if (((millis() - _lastMs) > 1000) && _canMove) {
    if (nrStart > 1) { 
      nrStart = nrStart - 1;
      lcd.setCursor(12,1);
      lcd.print(nrStart);
      _lastMs = millis();
    }
    else {  
      lcd.setCursor(0,1);
      lcd.print("  >> start >>  ");
	    digitalWrite(LED, HIGH);
	    delay(timeActiv);

      lcd.setCursor(0,1);
      lcd.print("  >> stop >>   ");
	    digitalWrite(LED, LOW);
	    delay(timePause);
	  
	    nrCicli = nrCicli + 1;
	    lcd.setCursor(firstDigit,0);
 //      lcd.print("       nr");
      printNum(nrCicli);
	  
     }
      
  } 

}
