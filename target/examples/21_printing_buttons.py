#!/usr/bin/env python3

import tkinter as tk

class PrintingButton(object):
    'A button that prints its label whenever it is pressed'

    def __init__(self, window, label):
        self.label= label

        self.button= tk.Button(
            window,
            text=label,
            command= self.on_pressed
        )

        self.button.pack()

    def on_pressed(self):
        print(self.label)

class ButtonsWindow(object):
    def __init__(self):
        '''Initialize the window and setup the initial content.

        To actually display the window run() has to be called.
        '''

        # Setup the empty window
        self.setup_window()

        # Setup the window content
        self.setup_buttons()

    def setup_window(self):
        self.window= tk.Tk()
        self.window.title('Button Box')

    def setup_buttons(self):
        self.buttons= list()

        for label in 'Hello world! from an OOPy GUI'.split():
            self.buttons.append(
                PrintingButton(self.window, label)
            )

    def run(self):
        'Execute the tkinter mainloop to display the Light center window'

        self.window.mainloop()

if __name__ == '__main__':
    window= ButtonsWindow()
    window.run()
