// Define all pins used in the program, namely the piano keys E,G,A,B,C, named in left to right order from the starting key
int keyOne = 2;
int keyTwo = 3;
int keyThree = 4;
int keyFour = 5;
int keyFive = 6;
int reset = 7;
int magLock = 8;


void setup() {
pinMode(keyOne, INPUT_PULLUP);
pinMode(keyTwo, INPUT_PULLUP);
pinMode(keyThree, INPUT_PULLUP);
pinMode(keyFour, INPUT_PULLUP);
pinMode(keyFive, INPUT_PULLUP);
pinMode(reset, INPUT_PULLUP);
pinMode(magLock, OUTPUT);
digitalWrite(magLock, LOW);
Serial.begin(9600);

}

int checkKeyPress() {
  //Here we want to check the key that is being pressed
  if(digitalRead(keyOne) == LOW) {
    return 1;    
    }
  else if(digitalRead(keyTwo) == LOW) {
    return 2;
    }
  else if(digitalRead(keyThree) == LOW) {
    return 3;    
    } 
  else if(digitalRead(keyFour) == LOW) {
    return 4;    
    }
  else if(digitalRead(keyFive) == LOW) {
    return 5;    
    } else {
      return 0;
      }   
  }

  //this method is called to detect which key we want pressed and wait for that key to be unpressed before returning true
  static bool waitForKey(int wantedKey) {
    //weve added a delay here to account for some input issues
    delay(50);
    int key = checkKeyPress();
    //This pressedKey variable is in place since the arduino processes too fast, and will always read that no button was pressed upon return
    int pressedKey;
    while(key == 0) {
      //key has not been pressed
      key = checkKeyPress();     
      }
      //when key is pressed, we want to wait for it to be unpressed
      //Here we say what key has been pressed
      pressedKey = key;
      while(true){
      while(key == pressedKey){
        key = checkKeyPress();  
        //so again we do nothing
        }
        delay(50);
        key = checkKeyPress();
        if(key == pressedKey){
          //we do nothing here and let it loop again
        } else{
          break;
          }
      }
        //and finally we return to the main loop, but we tell it whether or not the button that was pressed was correct
        Serial.println(pressedKey);
        if(pressedKey == wantedKey){
          return true;
          }
        if(pressedKey != wantedKey){
          return false;
          }   
    }
  
void loop() {
//So here we want to check for a "key press" or that key one has been connected, and we're basically going to ignore any other keys at this point
bool correct = true;
while(true){
  while(true)
  {
    //We idle here until the key that's pressed is the one we want ie 5
    if(waitForKey(5))
    {
      break;
      }
      Serial.println("Waiting...");
    }
    correct = waitForKey(4);
  if(!correct){break;}
    correct = waitForKey(2);
    break;
  }

  if(!correct){
    //They failed at some point in the loop, so the maglock stays closed
    Serial.println("Incorrect");
    }
  if(correct){
    //They succeeded! mag lock opens!
    digitalWrite(magLock, HIGH);
    Serial.println("Correct");
    //Now we wait for a moment to let the door pop
    delay(5000);
      digitalWrite(magLock, LOW);
    }
    delay(100);
}
