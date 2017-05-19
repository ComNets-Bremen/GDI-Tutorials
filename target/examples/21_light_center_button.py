#!/usr/bin/env python3

import atuino as at
import tkinter as tk

class LedButton(object):
    '''A button that controls one LED connected to an Arduino
    while providing visual feedback of the current button state
    '''

    def __init__(self, window, arduino, pin_no):
        self.button= tk.Button(
            window,
            text='Led {}'.format(pin_no),
            command= self.on_pressed
        )

        # Get an instance of OutputPin
        # and turn it off
        self.led= at.OutputPin(arduino, pin_no)
        self.set_state(False)

        self.button.pack()

    def set_state(self, state):
        if state:
            self.button.config(relief='sunken')
            self.state= True

        else:
            self.button.config(relief='raised')
            self.state= False

    def on_pressed(self):
        self.set_state(not self.state)

class PortSelector(object):
    '''Display a dropdown menu and a button in a given window
    that lets you choose the serial port your Arduino
    is connected to.
    '''

    def __init__(self, window, on_connect_cb):
        '''Initialize the port selector menu.

        Upon pressing the connect button the selected
        port name is passed as first argument to the
        on_connect_cb callback function.
        '''

        self.window= window
        self.on_connect_cb= on_connect_cb

        self.setup_port_menu()
        self.setup_connect_button()

    def setup_port_menu(self):
        ports= at.enumerate_ports()

        self.port_current= tk.StringVar(self.window)
        self.port_current.set(ports[0])

        self.menu_widget= tk.OptionMenu(
            self.window,
            self.port_current,
            *ports
        )
        self.menu_widget.pack()

    def setup_connect_button(self):
        self.connect_button= tk.Button(
            self.window,
            text= 'connect',
            command= self.on_button_clicked
        )
        self.connect_button.pack()

    def on_button_clicked(self):
        port_name= self.port_current.get()

        self.on_connect_cb(port_name)

    def hide(self):
        'Remove the port selector widgets from the window'

        self.connect_button.pack_forget()
        self.menu_widget.pack_forget()

class LightCenterWindow(object):
    def __init__(self):
        '''Initialize the window and setup
        the initial content.

        To actually display the window run
        has to be called.
        '''

        self.arduino= None
        self.led_buttons= list()

        # Setup the empty window
        self.setup_window()

        # Setup the initial window content
        self.port_selector= PortSelector(
            self.window, self.on_connect
        )

    def setup_window(self):
        self.window= tk.Tk()
        self.window.title('Light Center')

    def run(self):
        'Execute the tkinter mainloop to display the Light center window'

        self.window.mainloop()

    def on_connect(self, port_name):
        # Connect to the Arduino ...
        self.arduino= at.Arduino(port_name)

        # ... hide the connection widgets ...
        self.port_selector.hide()

        # ... and create buttons for the LEDs
        for pin_no in (10, 11, 12, 13):
            self.led_buttons.append(
                LedButton(self.window, self.arduino, pin_no)
            )

if __name__ == '__main__':
    window= LightCenterWindow()
    window.run()
