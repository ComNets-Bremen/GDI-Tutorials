#!/usr/bin/env python3

class Player(object):
    def __init__(self, name, symbol, initial_score=0):
        self.name= name
        self.symbol= symbol
        self.score= initial_score

    def won_match(self):
        self.score+= 100

    def lost_match(self):
        self.score-= 50

    def show_score(self):
        print('Player {}: {} points'.format(self.name, self.score))

class PlayingField(object):
    def __init__(self):
        self.field= [
            [None, None, None],
            [None, None, None],
            [None, None, None]
        ]

    def show_field(self):
        for row in self.field:
            for player in row:
                print(
                    '_' if player is None else player.symbol,
                    end=' '
                )

            print()

    def set_player(self, x, y, player):
        if self.field[y][x] is not None:
            return False

        self.field[y][x]= player

        return True

    def check_won(self, player):
        'check if the given player won the match'
        
        # Check rows
        if self.field[0][0]==player and self.field[1][0]==player and self.field[2][0]==player:
            return True

        if self.field[0][1]==player and self.field[1][1]==player and self.field[2][1]==player:
            return True

        if self.field[0][2]==player and self.field[1][2]==player and self.field[2][2]==player:
            return True

        # Check columns
        if self.field[0][0]==player and self.field[0][1]==player and self.field[0][2]==player:
            return True

        if self.field[1][0]==player and self.field[1][1]==player and self.field[1][2]==player:
            return True

        if self.field[2][0]==player and self.field[2][1]==player and self.field[2][2]==player:
            return True

        # Check diagonals
        if self.field[0][0]==player and self.field[1][1]==player and self.field[2][2]==player:
            return True

        if self.field[2][0]==player and self.field[1][1]==player and self.field[0][2]==player:
            return True

        return False

def main():
    name_1= input('Name of Player 1: ')
    name_2= input('Name of Player 2: ')

    players= [
        Player(name_1, 'X'),
        Player(name_2, 'O')
    ]

    field= PlayingField()

    while True:
        for player in players:
            field.show_field()
            x= int(
                input('Player {} choose your column: '.format(player.name))
            ) - 1

            y= int(
                input('Player {} choose your row: '.format(player.name))
            ) - 1

            if not field.set_player(x, y, player):
            	print('That field is already occupied. Ooopsie')

            elif field.check_won(player):
                field.show_field()

                print('WiWaWon! {} won the game. Now implement, the next functionallity.'.format(player.name))
                print('Score')

                for player in players:
                    print('{}: {}'.format(player.name, player.score))

                field= PlayingField()

if __name__ == '__main__':
    main()
