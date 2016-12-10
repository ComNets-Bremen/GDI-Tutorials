#define MONTHS_PER_YEAR (12)
#define DAYS_PER_YEAR (365)

struct month_info_t {
  char *name;
  uint8_t num_days;
};

struct month_info_t month_info[MONTHS_PER_YEAR]= {
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
  {.name= "December" , .num_days= 31}
};

/* A date consists of the day of the month
 * and the month.
 * The month is stored as index into the month_info
 * array. (Janurary = 0) */
struct date_t {
  uint8_t day_of_month;
  uint8_t mi_idx;
};

/**
 * Increment the given date by one day
 * and handle all possible overflows
 */
boolean date_increment(struct date_t *date)
{
  if(!date || date->mi_idx >= MONTHS_PER_YEAR) {
    return(false);
  }

  date->day_of_month++;

  if (date->day_of_month > month_info[date->mi_idx].num_days) {
    date->day_of_month= 1;
    date->mi_idx= (date->mi_idx + 1) % MONTHS_PER_YEAR;
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

  date->mi_idx= month-1;

  if(day_of_month > month_info[date->mi_idx].num_days) {
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

  for(uint8_t mi= da->mi_idx;
      mi != db->mi_idx;
      mi= (mi + 1)%MONTHS_PER_YEAR) {
    days+= month_info[mi].num_days;
  }

  days+= db->day_of_month;
  days-= da->day_of_month;

  if(days < 0) days+= DAYS_PER_YEAR;

  return(days);
}

void date_print(struct date_t *date)
{
  Serial.print(month_info[date->mi_idx].name);
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
