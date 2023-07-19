#define RELAY_LOW 4
#define RELAY_HIGH 7

#define BUTTON_OFF 9
#define BUTTON_LOW 10
#define BUTTON_HIGH 11
#define BUTTON_RESET 5

#define LED_LOW 1
#define LED_HIGH 2
#define LED_INTERLOCK 0

#define E_STOP 3

enum ContollerState {STATE_OFF, STATE_LOW, STATE_HIGH, STATE_INTERLOCK};
enum ContollerState state;

int buttonOffOld = 0;
int buttonOffNew;
int buttonLowOld = 0;
int buttonLowNew;
int buttonHighOld = 0;
int buttonHighNew;
int buttonResetOld = 0;
int buttonResetNew;

int estop = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY_LOW, OUTPUT);
  pinMode(RELAY_HIGH, OUTPUT);

  pinMode(BUTTON_OFF, INPUT);
  pinMode(BUTTON_LOW, INPUT);
  pinMode(BUTTON_HIGH, INPUT);
  pinMode(BUTTON_RESET, INPUT);

  pinMode(LED_LOW, OUTPUT);
  pinMode(LED_HIGH, OUTPUT);
  pinMode(LED_INTERLOCK, OUTPUT);

  pinMode(E_STOP, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonOffToggled = 0;
  int buttonLowToggled = 0;
  int buttonHighToggled = 0;
  int buttonResetToggled = 0;

  buttonOffNew = digitalRead(BUTTON_OFF);
  if (buttonOffOld == 0 && buttonOffNew == 1)
    buttonOffToggled = 1;
  buttonOffOld = buttonOffNew;
  buttonLowNew = digitalRead(BUTTON_LOW);
  if (buttonLowOld == 0 && buttonLowNew == 1)
    buttonLowToggled = 1;
  buttonLowOld = buttonLowNew;
  buttonHighNew = digitalRead(BUTTON_HIGH);
  if (buttonHighOld == 0 && buttonHighNew == 1)
    buttonHighToggled = 1;
  buttonHighOld = buttonHighNew;
  buttonResetNew = digitalRead(BUTTON_RESET);
  if (buttonResetOld == 0 && buttonResetNew == 1)
    buttonResetToggled = 1;
  buttonResetOld = buttonResetNew;

  estop = digitalRead(E_STOP);

  switch (state) {
    case STATE_OFF:
      digitalWrite(LED_LOW, LOW);
      digitalWrite(LED_HIGH, LOW);
      digitalWrite(LED_INTERLOCK, LOW);
      digitalWrite(RELAY_LOW, LOW);
      digitalWrite(RELAY_HIGH, LOW);
      if (buttonLowToggled)
        state = STATE_LOW;
      if (estop)
        state = STATE_INTERLOCK;
      break;

      case STATE_LOW:
        digitalWrite(LED_LOW, HIGH);
        digitalWrite(LED_HIGH, LOW);
        digitalWrite(LED_INTERLOCK, LOW);
        digitalWrite(RELAY_LOW, HIGH);
        digitalWrite(RELAY_HIGH, LOW);
        if (buttonHighToggled)
          state = STATE_HIGH;
        if (buttonOffToggled)
          state = STATE_OFF;
        if (estop)
        state = STATE_INTERLOCK;
        break;

      case STATE_HIGH:
        digitalWrite(LED_LOW, LOW);
        digitalWrite(LED_HIGH, HIGH);
        digitalWrite(LED_INTERLOCK, LOW);
        digitalWrite(RELAY_LOW, HIGH);
        digitalWrite(RELAY_HIGH, HIGH);
        if (buttonLowToggled)
          state = STATE_LOW;
        if (estop)
          state = STATE_INTERLOCK;
        break;

      case STATE_INTERLOCK:
        digitalWrite(LED_LOW, LOW);
        digitalWrite(LED_HIGH, LOW);
        digitalWrite(LED_INTERLOCK, HIGH);
        digitalWrite(RELAY_LOW, LOW);
        digitalWrite(RELAY_HIGH, LOW);
        if (buttonResetToggled && (estop == 0))
          state = STATE_OFF;     
  }
  delay(20);
}
