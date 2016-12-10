#define MONTHS_PER_YEAR (12)
#define DAYS_PER_YEAR (365)

struct month_info_t {
  char *name;
  uint8_t num_days;
};

/* Added a trailing known-to-be-invalid
 * month at the end so that the program
 * can detect when to wrap around */
struct month_info_t month_info[MONTHS_PER_YEAR+1]= {
  {.name= "January",   .num_days= 31},
  {.name= "February",  .num_days= 28},
  {.name= "March",     .num_days= 31},
  {.name= "April",     .num_days= 30},
  {.name= "May",       .num_days= 31},
  {.name= "June",      .num_days= 30},
  {.name= "July",      .num_days= 31},
  {.name= "August",    .num_days= 31},
  {.name= "September", .num_days= 30},
  {.name= "October",   .num_days= 31},
  {.name= "November",  .num_days= 30},
  {.name= "December" , .num_days= 31},
  {.name= NULL, .num_days= 0}
};

/* A date consists of the day of the month
 * and the month.
 * To comply with the task the current month
 * is stored as a pointer into the
 * month_info array */
struct date_t {
  uint8_t day_of_month;
  struct month_info_t *month;
};

/**
 * Increment the given date by one day
 * and handle all possible overflows
 */
boolean date_increment(struct date_t *date)
{
  if(!date || !date->month || !date->month->num_days) {
    return(false);
  }

  date->day_of_month++;

  if (date->day_of_month > date->month->num_days) {
    date->day_of_month= 1;
    date->month++;

    if (!date->month->num_days) {
      date->month= &month_info[0];
    }
  }

  return(true);
}

/**
 * Validate the day_of_month and month inputs
 * and set the date structure
 */
boolean date_set(struct date_t *date, uint8_t day_of_month, uint8_t month)
{
  if(!date || (month-1) >= MONTHS_PER_YEAR) {
    return(false);
  }

  date->month= &month_info[month-1];

  if(day_of_month > date->month->num_days) {
    return(false);
  }

  date->day_of_month= day_of_month;

  return(true);
}

/**
 * Calculate the number of days between date da and date db
 * If da and db are equal 0 is returned
 */
uint16_t date_days_between(struct date_t *da, struct date_t *db)
{
  int16_t days= 0;

  for(struct month_info_t *mpivot= da->month;
      mpivot != db->month;
      mpivot= ((mpivot + 1)->num_days) ? (mpivot + 1) : month_info) {
    days+= mpivot->num_days;
  }

  days+= db->day_of_month;
  days-= da->day_of_month;

  if(days < 0) days+= DAYS_PER_YEAR;

  return(days);
}

void date_print(struct date_t *date)
{
  Serial.print(date->month->name);
  Serial.print(" ");
  Serial.print(date->day_of_month);
  Serial.print(". ");
}

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  struct date_t pivot;
  struct date_t birthday;

  date_set(&pivot, 14, 3);
  date_set(&birthday, 14, 3);

  for(;;) {
    uint16_t days_next_bd= date_days_between(&pivot, &birthday);

    date_print(&pivot);

    if (days_next_bd) {
      Serial.print("(");
      Serial.print(days_next_bd);
      Serial.println(" days until the next birthday)");
    }
    else {
      Serial.println("Happy birthday!");
    }

    delay(100);
    date_increment(&pivot);
  }
}
