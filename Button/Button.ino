const int buttonPin = 7;     // the number of the pushbutton pin 10K resistor attached to pin 7 from ground
int buttonState = 0;         // variable for reading the pushbutton status

void Initial() {
  pinMode(buttonPin, INPUT);
}

bool ButtonState() {
  
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH) 
    return 1;
  else
    return 0;
    
}
