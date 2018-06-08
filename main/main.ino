// GPIO pins for each button
const int btnLeft = 2;
const int btnRight = 3;
const int btnUp = 4;
const int btnDown = 5;
const int btnEnter = 6;
const int btnSpace = 7;

// GPIO pins for LED stripe
const int btnLeftLed = 8;
const int btnRightLed = 9;
const int btnUpLed = 10;
const int btnDownLed = 11;

// GPIO pins state
int btnLeftStateCurrent   = LOW;
int btnLeftStatePreviouos = LOW;

int btnRightStateCurrent  = LOW;
int btnRightStatePreviouos= LOW;

int btnUpStateCurrent     = LOW;
int btnUpStatePreviouos   = LOW;

int btnDownStateCurrent   = LOW;
int btnDownStatePreviouos = LOW;



void setup() {
  // init
  
  Serial.begin(9600);      // open the serial port at 9600 bps: 

  // GPIO PIN mode
  // input / output
  pinMode( btnLeft,  INPUT );
  pinMode( btnRight, INPUT );
  pinMode( btnUp,    INPUT );
  pinMode( btnDown,  INPUT );
  pinMode( btnEnter, INPUT );
  pinMode( btnSpace, INPUT );

  pinMode( btnLeftLed,  OUTPUT );
  pinMode( btnRightLed, OUTPUT );
  pinMode( btnUpLed,    OUTPUT );
  pinMode( btnDownLed,  OUTPUT );

  // GPIO initial state
  digitalWrite( btnLeft,  btnLeftStateCurrent );
  digitalWrite( btnRight, btnLeftStateCurrent );
  digitalWrite( btnUp,    btnLeftStateCurrent );
  digitalWrite( btnDown,  btnLeftStateCurrent );
  digitalWrite( btnEnter, btnLeftStateCurrent );
  digitalWrite( btnSpace, btnLeftStateCurrent );

  digitalWrite( btnLeftLed,   LOW );
  digitalWrite( btnRightLed,  LOW );
  digitalWrite( btnUpLed,     LOW);
  digitalWrite( btnDownLed,   LOW );
}

void readCurrentState (){
  // raed current state of each GPIO input pin
  
  btnLeftStateCurrent   = digitalRead( btnLeft );
  btnRightStateCurrent  = digitalRead( btnRight );
  btnUpStateCurrent     = digitalRead( btnUp );
  btnDownStateCurrent   = digitalRead( btnDown );
  //btnLeftStateCurrent = digitalRead( btnEnter );
  //btnLeftStateCurrent = digitalRead( btnSpace );
}

void actionLight( int pin, int state )
{
  // action to control LED lights
  // turn on/off the relay
  
  digitalWrite( pin, state );
}

void actionStateChanged ()
{
  // triger actions if button state is changed
  
  if ( btnLeftStateCurrent != btnLeftStatePreviouos )
  {
    Serial.println( "LEFT" );
    
    btnLeftStatePreviouos = btnLeftStateCurrent;
    actionLight ( btnLeftLed, btnLeftStateCurrent );
  }

  if ( btnRightStateCurrent != btnRightStatePreviouos )
  {
    Serial.println( "RIGHT" );
    
    btnRightStatePreviouos = btnRightStateCurrent;
    actionLight ( btnRightLed, btnRightStateCurrent );
  }

  if ( btnUpStateCurrent != btnUpStatePreviouos )
  {
    Serial.println( "UP" );
    
    btnUpStatePreviouos = btnUpStateCurrent;
    actionLight ( btnUpLed, btnUpStateCurrent );
  }

  if ( btnDownStateCurrent != btnDownStatePreviouos )
  {
    Serial.println( "DOWN" );
    
    btnDownStatePreviouos = btnDownStateCurrent;
    actionLight ( btnDownLed, btnDownStateCurrent );
  }
}

void loop()
{
  // read current state
  readCurrentState();

  // act on state change
  actionStateChanged();

  // sleep
  // 10ms is enough for debounce
  delay(10);
}
