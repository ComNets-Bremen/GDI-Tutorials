#!/usr/bin/env python3

import tkinter as tk
import socket as so

class Arduino(object):
    def __init__(self, window, host, port, on_received):
        # Open socket and connect to the Arduino
        self.socket= so.socket()
        self.socket.connect((host, port))
        self.socket.setblocking(False)

        self.on_received= on_received

        self.rd_buff= bytes()

        # Call on_readable whenever the Arduino sends a message
        window.createfilehandler(self.socket, tk.READABLE, self.on_readable)

    def send_command(self, command):
        self.socket.send(command.encode('utf-8') + b'\n')

    def on_readable(self, sock, mask):
        self.rd_buff+= self.socket.recv(1024)

        while b'\n' in self.rd_buff:
            line, self.rd_buff= self.rd_buff.split(b'\n', 1)

            self.on_received(line.decode('utf-8').strip())

class LedButton(object):
    '''A button that controls one LED connected to an Arduino
    while providing visual feedback of the current button state
    '''

    def __init__(self, window, arduino):
        self.button= tk.Button(
            window,
            text='Led',
            command= self.on_pressed
        )

        self.button.pack()

        self.arduino= arduino

        self.set_state(False)

    def set_state(self, state):
        if state:
            self.arduino.send_command('on')
            self.button.config(relief='sunken')
            self.state= True

        else:
            self.arduino.send_command('off')
            self.button.config(relief='raised')
            self.state= False

    def on_pressed(self):
        self.set_state(not self.state)


class LightCenterWindow(object):
    def __init__(self):
        # Setup the empty window
        self.setup_window()

        host= input('Hostname: ')
        port= input('Port: ')

        self.arduino= Arduino(
            self.window,
            host, int(port),
            self.on_received
        )

        self.setup_content()

    def on_received(self, line):
        self.btn_label_var.set('Button status is: {}'.format(line))

    def setup_window(self):
        self.window= tk.Tk()
        self.window.title('Light Center')

    def setup_content(self):
        self.btn_label_var= tk.StringVar(self.window)
        self.btn_label_var.set('Button status is: unknown')

        self.btn_label = tk.Label(
            self.window,
            textvariable= self.btn_label_var
        )

        self.btn_label.pack()

        self.btn= LedButton(self.window, self.arduino)

    def run(self):
        'Execute the tkinter mainloop to display the Light center window'

        self.window.mainloop()

if __name__ == '__main__':
    window= LightCenterWindow()
    window.run()
