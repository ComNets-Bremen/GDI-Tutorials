#!/usr/bin/env python3

import atuino as at
import tkinter as tk

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
        'Provide an OptionMenu with a few buttons'

        ports= at.enumerate_ports()

        self.port_current= tk.StringVar(self.window)
        self.port_current.set(ports[0])

        # TODO

    def setup_connect_button(self):
        'Add a connect button to self.window'

        # TODO

    def on_button_clicked(self):
        port_name= self.port_current.get()

        self.on_connect_cb(port_name)

    def hide(self):
        'Remove the port selector widgets from the window'

        # TODO

        # Hint:
        #  The widgets provide a widget.pack_forget()
        #  method that performs the opposite of
        #  widget.pack()

class LightCenterWindow(object):
    def __init__(self):
        '''Initialize the window and setup
        the initial content.

        To actually display the window run
        has to be called.
        '''

        self.arduino= None

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

        # Display a "Not implemented" warning
        self.warning= tk.Label(
            self.window,
            text= 'Warning: controling features are not yet implemented'
        )
        self.warning.pack()

if __name__ == '__main__':
    window= LightCenterWindow()
    window.run()
