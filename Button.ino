class Button{
      public:
          void Initial()
          {
             pinMode(buttonPin, INPUT);
          }

          bool state()
          {
              buttonState = digitalRead(buttonPin);
              
              if (buttonState == HIGH) 
                return 1;
              else
                return 0;
          }

      private:
        const int buttonPin = 4;     // the number of the pushbutton pin 10K resistor attached to pin 7 from ground
        int buttonState = 0;         // variable for reading the pushbutton status  
};
