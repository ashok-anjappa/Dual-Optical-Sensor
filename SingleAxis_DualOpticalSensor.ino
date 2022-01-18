#define DEBOUNCE_DELAY  50
#define ONE_SECOND 1000
#define ONE_HOUR_MILI_SEC  30000 //3600000

// Optical Sensor pins for UNO Board
const byte interrupt0_pin = 2;
const byte interrupt1_pin = 3;
const byte Sensor0_Anode = 4;
const byte Sensor1_Anode = 5;

// Optical Sensor pins for MEGA Board
/*const byte interrupt0_pin = 18;
const byte interrupt1_pin = 19;
const byte Sensor0_Anode = 20;
const byte Sensor1_Anode = 21;*/

unsigned long int Left_CycleCount = 0;
unsigned long int Right_CycleCount = 0;

unsigned long int current_time = 0;
unsigned long int last_time = 0;

static unsigned long last_interrupt0_time = 0;
static unsigned long last_interrupt1_time = 0;

byte flag0 = 0;
byte flag1 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(interrupt0_pin, INPUT_PULLUP);
  pinMode(interrupt1_pin, INPUT_PULLUP);
  pinMode(Sensor0_Anode, OUTPUT);
  pinMode(Sensor1_Anode, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(interrupt0_pin), isr_handler0, FALLING );
  attachInterrupt(digitalPinToInterrupt(interrupt1_pin), isr_handler1, FALLING );
  digitalWrite(Sensor0_Anode, HIGH);
  digitalWrite(Sensor1_Anode, HIGH);
}

void loop() {

  // put your main code here, to run repeatedly:
  current_time = millis();
  
  if(flag0 == 1){
    Left_CycleCount++;
    flag0 = 0;
  }

    if(flag1 == 1){
    Right_CycleCount++;
    flag1 = 0;
    }

  if(current_time - last_time > ONE_SECOND)
  {
    Serial.print('<');
    Serial.print(Left_CycleCount);
    Serial.print(',');
    Serial.print(Right_CycleCount);
    Serial.println('>');
    last_time = current_time;
  }
}

void isr_handler0()
{
 unsigned long interrupt0_time = millis();
 // If interrupts come faster than 50ms, assume it's a bounce and ignore
 if (interrupt0_time - last_interrupt0_time > DEBOUNCE_DELAY)
 {
   flag0 = 1;
   last_interrupt0_time = interrupt0_time;
 }
}

void isr_handler1()
{
 unsigned long interrupt1_time = millis();
 // If interrupts come faster than 50ms, assume it's a bounce and ignore
 if (interrupt1_time - last_interrupt1_time > DEBOUNCE_DELAY)
 {
   flag1 = 1;
   last_interrupt1_time = interrupt1_time;
 }
}
