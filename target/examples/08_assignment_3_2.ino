struct month_info_t {
  char *name;
  uint8_t num_days;
};

struct month_info_t month_info[]= {
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
  {.name= "December",  .num_days= 31}
};
