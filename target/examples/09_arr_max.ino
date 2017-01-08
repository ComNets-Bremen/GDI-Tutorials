uint32_t arr_max(uint32_t *arr, size_t length)
{
  if(length == 1) {
    return(arr[0]);
  }

  size_t length_l= length/2;
  size_t length_r= length - length_l;

  uint32_t max_l= arr_max(&arr[0], length_l);
  uint32_t max_r= arr_max(&arr[length_l], length_r);

  if(max_l > max_r) {
    return(max_l);
  }
  else {
    return(max_r);
  }
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  uint32_t arr[]= {
    1615, 1014, 2447, 3885, 3390, 1641, 3932, 3017,
    2465, 1823, 1790, 1188, 4046, 3214,  228, 2737,
       4, 3195, 1919, 1074, 3334, 3748, 2655,  572,
    2958, 3866, 1549, 1750,  576, 3973, 1963,  340
  };

  Serial.print("arr_max(arr, 32)= ");
  Serial.println(arr_max(arr, 32));

  delay(5000);
}
