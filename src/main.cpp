#include <Arduino.h>

#define POT_MIN_RANGE 0
#define POT_MAX_RANGE 1024
#define PWM_MIN_RANGE 0
#define PWM_MAX_RANGE 320


void analogWrite25k(int pin, int value);
double mapToRange(double value, double minSource, double maxSource, double minDest, double maxDest);




void setup() {

  Serial.begin(9600);

  /// Setting PWM output to 25mHz  using 16bit timer.
    TCCR1A = 0;           // undo the configuration done by...
    TCCR1B = 0;           // ...the Arduino core library
    TCNT1  = 0;           // reset timer
    TCCR1A = _BV(COM1A1)  // non-inverted PWM on ch. A
           | _BV(COM1B1)  // same on ch; B
           | _BV(WGM11);  // mode 10: ph. correct PWM, TOP = ICR1
    TCCR1B = _BV(WGM13)   // ditto
           | _BV(CS10);   // prescaler = 1
    ICR1   = 320;         // TOP = 320

    // Set the PWM pins as output.
    pinMode( 9, OUTPUT);
    pinMode(10, OUTPUT);


}

int channel01;
int channel02;

void loop()
{
  channel01 =  analogRead(1);
  channel02 =  analogRead(2);

  analogWrite25k( 9, mapToRange(channel01, POT_MIN_RANGE, POT_MAX_RANGE, PWM_MIN_RANGE, PWM_MAX_RANGE));
  analogWrite25k(10, mapToRange(channel02, POT_MIN_RANGE, POT_MAX_RANGE, PWM_MIN_RANGE, PWM_MAX_RANGE));
  

  Serial.print(channel01);
  Serial.print("/");
  Serial.print(mapToRange(channel01, POT_MIN_RANGE, POT_MAX_RANGE, PWM_MIN_RANGE, PWM_MAX_RANGE));
  Serial.print(" - ");

  Serial.print(channel02);
  Serial.print("/");
  Serial.println(mapToRange(channel02, POT_MIN_RANGE, POT_MAX_RANGE, PWM_MIN_RANGE, PWM_MAX_RANGE));


  delay(100);
}



/**
 * @brief Sets PWM fill using low level registers.
 * 
 * @param pin Number of the pin to be controlled. For ATmega168 and 328 based boards
 * this can be only  pins 9 or 10.
 * @param value Amount of the PWM fill in range between 0 for 0% fill and 320 
 * for 100% fill.
 */
void analogWrite25k(int pin, int value)
{
    switch (pin) {
        case 9:
            OCR1A = value;
            break;
        case 10:
            OCR1B = value;
            break;
        default:
            // no other pin will work
            break;
    }
}


/**
 * @brief Maps proportianally a value from a range to a new range.
 * 
 * @param value Value beeing converted.
 * @param minSource Low end of the original range. 
 * @param maxSource High end of the original range.
 * @param minDest Low end of the converted range.
 * @param maxDest High end of the converted range.
 * @return double Value mapped to the new range.
 */
double mapToRange(double value, double minSource, double maxSource, double minDest, double maxDest) 
{
  return (((value - minSource) * (maxDest - minDest)) / (maxSource - minSource)) + minDest;
}