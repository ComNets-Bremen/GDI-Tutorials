/*
 * This program simulates a traffic light situation
 * with an one-way road and a pedestrian crossing.
 *
 * ─────────┼─┼─────
 *  🚘 🚘 🚥 ┊ ┊
 * ─────────┼─┼─────
 *           🚶🚥
 *
 * The logic implemented in this program is
 * derived from the finite state machine shown below:
 *
 *     ╭───────────╮
 *     │ Start     │
 *     ├┄┄┄┄┄┄┄┄┄┄┄┤
 *     │ ped:off   │
 *     │ car:off   │
 *     ╰────┬──────╯
 *          │
 *          ▼
 *     ╭───────────╮
 * ┌─▶ │ ped_green │◀────────────┐
 * │   ├┄┄┄┄┄┄┄┄┄┄┄┤             │
 * │   │ ped:green │             │
 * │   │ car:red   ├╼!car_detect╾┘
 * │   ╰────┬──────╯
 * │        ╽
 * │    car_detect
 * │        ╿
 * │        │
 * │        ▼
 * │   ╭─────────────╮
 * │   │ pre_ped_red │◀─────────────┐
 * │   ├┄┄┄┄┄┄┄┄┄┄┄┄┄┤              │
 * │   │ ped:green   │              │
 * │   │ car:red     ├╼!elapsed_20s╾┘
 * │   ╰────┬────────╯
 * │        ╽
 * │    elapsed_20s
 * │        ╿
 * │        │
 * │        ▼
 * │   ╭──────────╮
 * │   │ ped_red  │◀─────────────┐
 * │   ├┄┄┄┄┄┄┄┄┄┄┤              │
 * │   │ ped:red  │              │
 * │   │ car:red  ├╼!elapsed_20s╾┘
 * │   ╰────┬─────╯
 * │        ╽
 * │    elapsed_20s
 * │        ╿
 * │        │
 * │        ▼
 * │   ╭───────────────╮
 * │   │ pre_car_green │◀────────────┐
 * │   ├┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┤             │
 * │   │ ped:red       │             │
 * │   │ car:yellow    ├╼!elapsed_2s╾┘
 * │   ╰────┬──────────╯
 * │        ╽
 * │    elapsed_2s
 * │        ╿
 * │        │
 * │        ▼
 * │   ╭───────────╮
 * │   │ car_green │◀────────────┐
 * │   ├┄┄┄┄┄┄┄┄┄┄┄┤             │
 * │   │ ped:red   │             │
 * │   │ car:green ├╼!elapsed_1m╾┘
 * │   ╰────┬──────╯
 * │        ╽
 * │    elapsed_1m
 * │        ╿
 * │        │
 * │        ▼
 * │   ╭─────────────╮
 * │   │ pre_car_red │◀────────────┐
 * │   ├┄┄┄┄┄┄┄┄┄┄┄┄┄┤             │
 * │   │ ped:red     │             │
 * │   │ car:yellow  ├╼!elapsed_5s╾┘
 * │   ╰────┬────────╯
 * │        ╽
 * │    elapsed_5s
 * │        ╿
 * │        │
 * │        ▼
 * │   ╭─────────╮
 * │   │ car_red │◀─────────────┐
 * │   ├┄┄┄┄┄┄┄┄┄┤              │
 * │   │ ped:red │              │
 * │   │ car:red ├╼!elapsed_10s╾┘
 * │   ╰────┬────╯
 * │        ╽
 * │    elapsed_10s
 * │        ╿
 * └────────┘
 */

/* Derive all delays between state changes from a
 * common time base to simplyfy speeding up the
 * process for debugging */
#define TIME_BASE (1000)
#define TIME_PRE_PED_RED (20*TIME_BASE)
#define TIME_PED_RED (20*TIME_BASE)
#define TIME_PRE_CAR_GREEN (2*TIME_BASE)
#define TIME_CAR_GREEN (60*TIME_BASE)
#define TIME_PRE_CAR_RED (5*TIME_BASE)
#define TIME_CAR_RED (10*TIME_BASE)

/* Using an enum (enumeration) to define
 * the states is roughly equivalent to
 * #define ISCTN_START 0
 * #define ISCTN_PED_GREEN 1
 * ... */
enum isctn_state {
  ISCTN_START,
  ISCTN_PED_GREEN,
  ISCTN_PRE_PED_RED,
  ISCTN_PED_RED,
  ISCTN_PRE_CAR_GREEN,
  ISCTN_CAR_GREEN,
  ISCTN_PRE_CAR_RED,
  ISCTN_CAR_RED,
  ISCTN_ERR,
};

/* Colors the traffic
 * lights may have */
enum tl_color {
  TL_OFF,
  TL_GREEN,
  TL_YELLOW,
  TL_RED,
};

/* The states in the same order as in the enum
 * for pretty printing */
char *isctn_state_names[] = {
  "start",
  "ped_green",
  "pre_ped_red",
  "ped_red",
  "pre_car_green",
  "car_green",
  "pre_car_red",
  "car_red",
  "err",
};

/* Global state of the intersection
 * _state is the current position in the FSM,
 * _wakeup keeps track of the timing */
int isctn_state= ISCTN_START;
uint32_t isctn_wakeup= 0;

/**
 * Set the color of the car
 * traffic light
 */
void tl_car(int color)
{
  digitalWrite(2, color==TL_GREEN);
  digitalWrite(3, color==TL_YELLOW);
  digitalWrite(4, color==TL_RED);
}

/**
 * Set the color of the pedestrian
 * traffic light
 */
void tl_pedestrian(int color)
{
  digitalWrite(8, color==TL_GREEN);
  digitalWrite(9, color==TL_RED);
}

/**
 * Take the state of the intersection as argument
 * and return the new state.
 *
 * This function does not use delay() as it
 * should implement a pure moore state machine.
 * E.g. only map from (input + state) -> (output + state)
 * This is also why every step explicitly sets the
 * outputs and next state.
 */
int isctn_step(int state_old)
{
  enum isctn_state state_new= ISCTN_ERR;

  uint32_t now= millis();

  switch(state_old) {
  case ISCTN_START:
    tl_car(TL_OFF);
    tl_pedestrian(TL_OFF);

    state_new= ISCTN_PED_GREEN;
    break;

  case ISCTN_PED_GREEN:
    tl_car(TL_RED);
    tl_pedestrian(TL_GREEN);

    if(coil_detect()) state_new= ISCTN_PRE_PED_RED;
    else              state_new= ISCTN_PED_GREEN;

    break;

  case ISCTN_PRE_PED_RED:
    tl_car(TL_RED);
    tl_pedestrian(TL_GREEN);

    if(!isctn_wakeup) {
      isctn_wakeup= now + TIME_PRE_PED_RED;
    }

    if(now >= isctn_wakeup) {
      isctn_wakeup= 0;
      state_new= ISCTN_PED_RED;
    }
    else {
      state_new= ISCTN_PRE_PED_RED;
    }

    break;

  case ISCTN_PED_RED:
    tl_car(TL_RED);
    tl_pedestrian(TL_RED);

    if(!isctn_wakeup) {
      isctn_wakeup= now + TIME_PED_RED;
    }

    if(now >= isctn_wakeup) {
      isctn_wakeup= 0;
      state_new= ISCTN_PRE_CAR_GREEN;
    }
    else {
      state_new= ISCTN_PED_RED;
    }

    break;


  case ISCTN_PRE_CAR_GREEN:
    tl_car(TL_YELLOW);
    tl_pedestrian(TL_RED);

    if(!isctn_wakeup) {
      isctn_wakeup= now + TIME_PRE_CAR_GREEN;
    }

    if(now >= isctn_wakeup) {
      isctn_wakeup= 0;
      state_new= ISCTN_CAR_GREEN;
    }
    else {
      state_new= ISCTN_PRE_CAR_GREEN;
    }

    break;

  case ISCTN_CAR_GREEN:
    tl_car(TL_GREEN);
    tl_pedestrian(TL_RED);

    if(!isctn_wakeup) {
      isctn_wakeup= now + TIME_CAR_GREEN;
    }

    if(now >= isctn_wakeup) {
      isctn_wakeup= 0;
      state_new= ISCTN_PRE_CAR_RED;
    }
    else {
      state_new= ISCTN_CAR_GREEN;
    }

    break;

  case ISCTN_PRE_CAR_RED:
    tl_car(TL_YELLOW);
    tl_pedestrian(TL_RED);

    if(!isctn_wakeup) {
      isctn_wakeup= now + TIME_PRE_CAR_RED;
    }

    if(now >= isctn_wakeup) {
      isctn_wakeup= 0;
      state_new= ISCTN_CAR_RED;
    }
    else {
      state_new= ISCTN_PRE_CAR_RED;
    }

    break;

  case ISCTN_CAR_RED:
    tl_car(TL_RED);
    tl_pedestrian(TL_RED);

    if(!isctn_wakeup) {
      isctn_wakeup= now + TIME_CAR_RED;
    }

    if(now >= isctn_wakeup) {
      isctn_wakeup= 0;
      state_new= ISCTN_PED_GREEN;
    }
    else {
      state_new= ISCTN_CAR_RED;
    }

    break;
  }

  return(state_new);
}

void setup()
{
  Serial.begin(9600);

  // Car traffic light pins
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  // Pedestrian traffic light pins
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  /* Determine the idle frequency of the LC-Network.
   * There must not be a car near the
   * coil while calibration */
  coil_calibrate();
}

void loop()
{
  /*
   * Uncomment for verbose debug output
   *
   * Serial.print("State: ");
   * Serial.print(isctn_state_names[isctn_state]);
   * Serial.print(", wakeup: ");
   * Serial.print(isctn_wakeup);
   * Serial.print(", time: ");
   * Serial.println(millis());
   *
   * delay(TIME_BASE);
   */

  isctn_state= isctn_step(isctn_state);
}
