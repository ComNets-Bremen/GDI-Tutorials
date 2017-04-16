#!/usr/bin/env python3

import io
import time

import serial

class Arduino(object):
    def __init__(self, port):
        self.port= serial.Serial(port, 115200, timeout=0.1)
        self.iow= io.TextIOWrapper(
            io.BufferedRWPair(self.port, self.port, 1),
            'utf-8',
            newline='\r\n'
        )

    def exec_cmd(self, *params):
        cmd= 'AT'

        if len(params) >= 1:
            cmd+= '+' + params[0]

        if len(params) >= 2:
            cmd+= '=' + ','.join(
                map(str, params[1:])
            )

        self.iow.write(cmd + '\r\n')

        resp= list()

        for ln in map(str.strip, self.iow):
            if ln == 'OK':
                return(resp)

            elif ln == 'FAIL':
                raise(Exception('Arduino Error'))

            else:
                resp.append(ln)

class OutputPin(object):
    def __init__(self, arduino, pin_no):
        self.arduino= arduino
        self.pin_no= pin_no

        self.arduino.exec_cmd('SET_OUT', self.pin_no)

    def turn_on(self):
        self.set_state(True)

    def turn_off(self):
        self.set_state(False)

    def set_state(self, state):
        self.arduino.exec_cmd(
            'WRITE_HIGH' if state else 'WRITE_LOW',
            self.pin_no
        )

class InputPin(object):
    def __init__(self, arduino, pin_no, pullup=False):
        self.arduino= arduino
        self.pin_no= pin_no

        self.arduino.exec_cmd('SET_IN', self.pin_no)

        self.arduino.exec_cmd(
            'WRITE_HIGH' if pullup else 'WRITE_LOW',
            self.pin_no
        )

    def is_high(self):
        res= self.arduino.exec_cmd('PIN_READ', self.pin_no)

        state= True if (res[0].split(':')[1] == '1') else False

        return(state)


duino= Arduino('/dev/ttyACM0')

key1= InputPin(duino, 10, True)
led1= OutputPin(duino, 13)

while True:
    state= key1.is_high()
    led1.set_state(state)

    time.sleep(0.5)
