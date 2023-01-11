// EXAMPLE: Buttons and LEDs (Only for Pico Base + Proto)
// Last update: Jan 10, 2023
// contact@PTSolns
//
// DESCRIPTION:
// The Pico Base + Proto has two programmable tactile buttons and two red LEDs. These can be programmed in a number of ways. 
// This example shows a simple application in which button B1 activates LED LED1 while pressed. Similarly for button B2 and LED LED2.
// Note that for this example no external libraries or other hardware is required.
//
// The buttons and LEDs are hardwired to the Pi Pico/Pi Pico W pins. The configuration is as follows:
// Button B1 -> GP16
// Button B2 -> GP17
// LED LED1  -> GP14
// LED LED1  -> GP15

// Setting the pin numbers for the buttons and LEDs. Pin assignments are hardwired and therefore should not be changed here.
const int BUT1 = 16;
const int BUT2 = 17;
const int LED1 = 14;
const int LED2 = 15;

int buttonState1 = 0;  // variable for reading the B1 status
int buttonState2 = 0;  // variable for reading the B2 status

void setup() {
  // initialize the pushbutton pin as an input:
  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);

  // initialize the LED pin as an output:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Set LEDs initially to OFF
  //digitalWrite(LED1, LOW);
  //digitalWrite(LED2, LOW);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(BUT1);
  buttonState2 = digitalRead(BUT2);

  // check if B1 is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    // turn LED1 ON:
    digitalWrite(LED1, HIGH);
  } else {
    // turn LED1 OFF:
    digitalWrite(LED1, LOW);
  }


    // check if B2 is pressed. If it is, the buttonState is HIGH:
  if (buttonState2 == HIGH) {
    // turn LED2 ON:
    digitalWrite(LED2, HIGH);
  } else {
    // turn LED2 OFF:
    digitalWrite(LED2, LOW);
  }

  delay(10);
}
