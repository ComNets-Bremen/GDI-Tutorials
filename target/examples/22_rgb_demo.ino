#include <SoftwareSerial.h>

/* This Program is only intended to quickly check
 * if the WiFi shield is working as expected.
 * DO NOT USE IT AS A REFERENCE!
 * Use the Server example a few slides further
 * down in the tutorial!
 * This code is mostly copied from there and
 * only slightly adapted to being a client. */

#define ESP_SUCESS_READY ((char *)"ready\r\n")
#define ESP_SUCESS_OK ((char *)"OK\r\n")
#define ESP_SUCESS_PKG ((char *)"+IPD,")
#define ESP_SUCESS_IPQ ((char *)"+CIPSTA_CUR:ip:\"")
#define ESP_SUCESS_SENT ((char *)"SEND OK\r\n")

class EspClient : public Stream
{
private:
  Stream *_esp_serial;
  int connection_id;
  int rem_msg_len;

  void flush_in_buff();
  void reset();
  void connect_wifi(const char *ssid, const char* pwd);
  void setup_client(const char *host, uint16_t port);

public:
  EspClient(void);

  void begin(Stream *esp_serial, const char* ssid, const char *pass, const char *host, uint16_t port);
  void my_ip(char *buf, size_t buflen);
  bool connected();

  virtual int available();
  virtual int peek();
  virtual int read();
  virtual void flush();
  virtual size_t write(const uint8_t *buffer, size_t size);

  inline size_t write(uint8_t n) { return write(&n, 1); }
  inline size_t write(unsigned long n) { return write((uint8_t)n); }
  inline size_t write(long n) { return write((uint8_t)n); }
  inline size_t write(unsigned int n) { return write((uint8_t)n); }
  inline size_t write(int n) { return write((uint8_t)n); }

  using Print::write;
};

EspClient::EspClient(void)
{
  _esp_serial= NULL;
  connection_id= -1;
  rem_msg_len= 0;
}

void EspClient::begin(Stream *esp_serial, const char* ssid, const char *pass, const char *host, uint16_t port)
{
  _esp_serial= esp_serial;
  _esp_serial->setTimeout(60000);

  reset();
  connect_wifi(ssid, pass);
  setup_client(host, port);
}

void EspClient::flush_in_buff()
{
  while(_esp_serial->available()) {
    _esp_serial->read();
  }
}
void EspClient::reset()
{
  flush_in_buff();

  // Reset ESP
  _esp_serial->println("AT+RST");
  _esp_serial->find(ESP_SUCESS_READY);

  delay(500);

  // Disable command echo
  _esp_serial->println("ATE0");
  _esp_serial->find(ESP_SUCESS_OK);
}

void EspClient::connect_wifi(const char *ssid, const char* pwd)
{
  // Set station mode
  _esp_serial->println("AT+CWMODE_CUR=1");
  _esp_serial->find(ESP_SUCESS_OK);

  // Connect to AP
  _esp_serial->print("AT+CWJAP_CUR=\"");
  _esp_serial->print(ssid);
  _esp_serial->print("\",\"");
  _esp_serial->print(pwd);
  _esp_serial->println("\"");
  _esp_serial->find(ESP_SUCESS_OK);

  // Get an IP using DHCP
  _esp_serial->println("AT+CIFSR");
  _esp_serial->find(ESP_SUCESS_OK);
}

void EspClient::setup_client(const char *host, uint16_t port)
{
  /* Configure for multiple connections
   * (necessary to run as server) */
  _esp_serial->println("AT+CIPMUX=1");
  _esp_serial->find(ESP_SUCESS_OK);

  // Start listening for connections
  _esp_serial->print("AT+CIPSTART=0,\"TCP\",\"");
  _esp_serial->print(host);
  _esp_serial->print("\",");
  _esp_serial->println(port);

  connection_id= 0;

  _esp_serial->find(ESP_SUCESS_OK);
}

void EspClient::my_ip(char *buf, size_t buflen)
{
  _esp_serial->println("AT+CIPSTA_CUR?");
  _esp_serial->find(ESP_SUCESS_IPQ);

  memset(buf, 0, buflen);
  _esp_serial->readBytesUntil('"', buf, buflen - 1);

  _esp_serial->find(ESP_SUCESS_OK);
}

bool EspClient::connected()
{
  /* available() will, as a side-effect check if
   * the connection status changed */
  available();

  /* Return true if there is currently a
   * client connected */
  return(connection_id >= 0);
}

int EspClient::available()
{
  int ser_available= _esp_serial->available();

  if(rem_msg_len) {
    // There is a message in transit

    return(min(rem_msg_len, ser_available));
  }

  if(ser_available) {
    char bte= _esp_serial->peek();

    if(bte == '+') {
      char cmd[4];
      _esp_serial->readBytes(cmd, 4);

      int id= _esp_serial->parseInt();
      int len= _esp_serial->parseInt();

      _esp_serial->find((char *)":");

      if(id == connection_id) {
        rem_msg_len= len;
      }
    }
    else {
      _esp_serial->read();
    }
  }


  return(0);
}

int EspClient::peek()
{
  if(available()) {
    return(_esp_serial->peek());
  }
  else {
    return(-1);
  }
}

int EspClient::read()
{
  if(available()) {
    rem_msg_len -= 1;

    return(_esp_serial->read());
  }
  else {
    return(-1);
  }
}

void EspClient::flush()
{
  _esp_serial->flush();
}

size_t EspClient::write(const uint8_t *buffer, size_t size)
{
  while(!connected());

  _esp_serial->print("AT+CIPSEND=");
  _esp_serial->print(connection_id);
  _esp_serial->print(",");
  _esp_serial->println(size);

  _esp_serial->find((char *)">");

  _esp_serial->write(buffer, size);
  _esp_serial->find((char *)ESP_SUCESS_SENT);

  return(size);
}

/* The WiFi shield is connected to
 * the Arduino pins 3 and 2, as the
 * Arduino has only one hardware serial
 * port (pins 0 and 1) we are using a
 * serial port emulated in software. */
SoftwareSerial esp_serial(3, 2);
EspClient esp_client;

void setup()
{
  Serial.begin(9600);
  esp_serial.begin(9600);

  /* Connect to the wireless network with the name "GDI"
   * and password "password", change these to match
   * your wifi settings. */
  Serial.println("Staring client...");
  esp_client.begin(&esp_serial, "GDI", "password", "192.168.42.42", 30303);
  Serial.println("...client is running");
}

void loop()
{
  /* Check if the python program
   * sent a new color */
  if(esp_client.available()) {
    int hue= esp_client.parseInt();

    int16_t intens_r= 255-abs(hue-255);
    int16_t intens_g= 255-abs(hue-511);
    int16_t intens_b= (hue > 300) ? (hue-511) : (255-hue);

    analogWrite(9, (intens_r > 0) ? intens_r : 0);
    analogWrite(10, (intens_g > 0) ? intens_g : 0);
    analogWrite(11, (intens_b > 0) ? intens_b : 0);
  }
}
