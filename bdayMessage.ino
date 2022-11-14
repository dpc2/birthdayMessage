/* LCD screen code from an example by:

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 http://www.arduino.cc/en/Tutorial/LiquidCrystalScroll

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Happy birthday song variables

int speakerPin = 9;
int length = 28; // the number of notes
char notes[] = "GGAGcB GGAGdc GGxecBA yyecdc";
int beats[] = { 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8,8, 16, 1, 2,2,8,8,8,8,16, 1,2,2,8,8,8,16 };
int tempo = 150;



// playTone function

void playTone(int tone, int duration) {

  for (long i = 0; i < duration * 1000L; i += tone * 2) {

     digitalWrite(speakerPin, HIGH);
     delayMicroseconds(tone);
     digitalWrite(speakerPin, LOW);
     delayMicroseconds(tone);
  }
}


// playNote function

void playNote(char note, int duration) {

    char names[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',           
                     'c', 'd', 'e', 'f', 'g', 'a', 'b',
                     'x', 'y' };

    int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014,
                     956,  834,  765,  593,  468,  346,  224,
                     655 , 715 };

    int SPEE = 5;

    // play the tone corresponding to the note name

    for (int i = 0; i < 17; i++) {

       if (names[i] == note) {
        int newduration = duration/SPEE;
         playTone(tones[i], newduration);

       }
    }
}




void setup() {
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Happy Birthday, XXX!!");
  delay(1000);
  
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // scroll 13 positions (string length) to the left
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  // scroll 29 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 29; positionCounter++) {
    // scroll one position right:
    lcd.scrollDisplayRight();
    // wait a bit:
    delay(150);
  }

  // scroll 16 positions (display length + string length) to the left
  // to move it back to center:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  // delay at the end of the full loop:
  delay(1000);
  
  
  for (int i = 0; i < length; i++) {
     if (notes[i] == ' ') {
       delay(beats[i] * tempo); // rest
     }
     else {
       playNote(notes[i], beats[i] * tempo);
     }
   
   // pause between notes

   delay(tempo);

}

}

