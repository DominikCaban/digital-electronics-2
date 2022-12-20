#include <avr/interrupt.h>
#include <timer.h>
#include <stdlib.h>
#include <util/delay.h>

// Pins definitions
// SERVO1: PB1 (15)
// SERVO2: PB2 (16)
// Joystick SW: PC2 (A2)
// Joystick X: PC0 (A0)
// Joystick Y: PC1 (A1)

volatile uint8_t invert_controls = 0;

void init_joystick()
{
  // Initialize TIM0 to 16ms (~62.5Hz)
  TIM0_overflow_16ms();
  TIM0_overflow_interrupt_enable();

  // Configure ADC
  // ADCMUX register:
  // Voltage Reference: AVCC with external capacitor at AREF pin (REFS0 = 1, REFS1 =0)
  // ADC Left Adjust Result: Disabled
  // Initial Analog Channel Select: ADC0 (MUX = 0)
  ADMUX = (1 << REFS0);

  // ADCSRA register:
  // Enable ADC module and conversion complete interrupt.
  ADCSRA = (1 << ADEN) | (1 << ADIE);
  // Set clock prescaler to 128
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // Initialize SW button on PC2
  // Set pin A2 as input in C bank
  DDRC &= ~(1 << 2);
  // Pull-up pin 4 in C bank
  PORTC |= (1 << 2);

  // Configure joystick switch
  // Enable pin change interrupt for PCINT14..8
  PCICR |= 1 << PCIE1;
  // PC interrupt mask only for PCINT10
	PCMSK1 |= 1 << PCINT10;
}

void init_pwm()
{
  // Set PB1 and PB2 as outputs for PWM
  DDRB |= (1 << 1);
  DDRB |= (1 << 2);
  // Set OC1A/OC1B on compare match, clear OC1A/OC1B at BOTTOM (inverting mode)
  TCCR1A = (1 << COM1A1) | (1 << COM1B1);
  // Set Waveform Generation Mode to 10 -> PWM, phase correct
  TCCR1A |= (1 << WGM11);
  TCCR1B = (1 << WGM13);
  // Set prescaler clkI/O / 8
  TCCR1B |= (1 << CS11);
  // Set PWM period
  ICR1 = 20000;
  
  // Set PWM duty cycle to default values
  OCR1A = 1500;
  OCR1B = 1500;
}

int main(void)
{
  init_joystick();
  init_pwm();

  sei();
  while (1) {

  }
  return 0;
}

ISR(PCINT1_vect)
{
  // Read joystick SW button PC2
  if (PINC & (1 << 2)) {
    invert_controls = !invert_controls;
    _delay_ms(200); // Simple debouncing
  }
}

ISR(TIMER0_OVF_vect)
{
  static uint8_t overflows = 0;

  // since TIMER0 running every 16ms,
  // we will trigger first ADC every 64ms, so every 4th overflow
  if (++overflows >= 4) {
      overflows = 0;
      // Set first ADC channel, thus channel 0
      ADMUX = (ADMUX & ~0xF) | 0;
      // Trigger ADC conversion
      ADCSRA |= (1 << ADSC);
  }
}

ISR(ADC_vect)
{
  // gets value from ADC
  float adc_value = ADC;
  // gets current mux channel
  uint8_t mux_channel = ADMUX & 0xF;

  if (mux_channel == 0) {
    // we sampled PC0, thus joystick X
    // we need to reconfigure ADC to sample also PC1
    ADMUX = (ADMUX & ~0xF) | 1;
    // and trigger adc conversion for second channel
    ADCSRA |= (1 << ADSC);

    if (invert_controls) {
      OCR1B = 1000.0f + ((adc_value / 1024.0f) * 1000.0f);
    } else {
      OCR1A = 1000.0f + ((adc_value / 1024.0f) * 1000.0f);
    }
  } else if (mux_channel == 1) {
    // we sampled PC1, thus joystick Y
    // we don't need to trigger next adc conversion, since TIMER0 will trigger it
    
    if (invert_controls) {
      OCR1A = 1000.0f + ((adc_value / 1024.0f) * 1000.0f);
    } else {
      OCR1B = 1000.0f + ((adc_value / 1024.0f) * 1000.0f);
    }
  }
}