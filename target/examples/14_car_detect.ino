/* The car detection works via a
 * coil embedded in the road.
 *
 * If you just want to see the code in action
 * you can replace the content of this file
 * with a stub that implements coil_detect
 * and return true when e.g. a button is pressed.
 *
 * The coil is driven using the circuit
 * shown below.
 *
 *   3.3V──┐
 *   ┌─────┼────╼ D6
 *   C     B
 *  B E─┬─E C──┬╼ D7
 *  │   ╽      │
 *  │   R      │
 *  │   ╿  ┌╼L╾┤
 *  │  GND╾┤   │
 *  │      └╼C╾┤
 *  └──────────┘
 *
 * The compontents used are:
 *  [EBC]  2*Transistor NPN 2N3004
 *      R  1kΩ
 *      C  100nF Ceramic capacitor
 *      L  15 Windings ⌀ 3cm
 *
 * The circuit is an emitter coupled
 * oscillator.
 *
 * The frequency at which the oscillator
 * works is influenced by ferromagnetic materials
 * near the coil.
 * The frequency is measured by counting
 * the transitions of the analog comparator output.
 * The analog comparator is a feature of the
 * Atmega328 used in the Arduino UNO */

uint16_t coil_mean_freq= 0;

uint16_t coil_get_freq()
{
  uint32_t time_end= micros() + 10000;
  uint16_t transitions= 0;
  uint8_t acsr_old= 0;

  while(micros() < time_end) {
    uint8_t acsr_new= ACSR;

    /* Count changes in the analog comparator
     * output bit */
    transitions+= ((acsr_new ^ acsr_old) >> 5) & 1;

    acsr_old= acsr_new;
  }

  return(transitions);
}

boolean coil_detect()
{
  uint16_t freq_now= coil_get_freq();

  uint16_t freq_low= coil_mean_freq - 32;
  uint16_t freq_high= coil_mean_freq + 32;

  return(freq_now < freq_low || freq_now > freq_high);
}

void coil_calibrate()
{
  uint32_t acc= 0;

  for(uint16_t i=0; i<256; i++) {
    acc+= coil_get_freq();
  }

  coil_mean_freq= acc / 256;

  while(coil_detect());

  Serial.print("Calibration freq: ");
  Serial.println(coil_mean_freq);
}
