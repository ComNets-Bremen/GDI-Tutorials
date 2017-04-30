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

    def check_end(self):
        for row in self.field:
            for player in row:
                if player is None:
                    return False

        return True

    def check_won(self, player):
        triplets= list()

        # Check if player owns all the fields in a row
        for col in range(3):
            if all(self.field[row][col] == player for row in range(3)):
                return True

        # Check if player owns all the fields in a col
        for row in range(3):
            if all(self.field[row][col] == player for col in range(3)):
                return True

        # Check if player owns a diagonal
        if all(self.field[diag][diag] == player for diag in range(3)):
            return True

        if all(self.field[diag][2-diag] == player for diag in range(3)):
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

            new_game= False

            if not field.set_player(x, y, player):
            	print('That field is already occupied. Ooopsie')

            elif field.check_won(player):
                field.show_field()

                # Update player scores
                for p in players:
                    updater= (p.won_match if p==player else p.lost_match)
                    updater()

                print('WiWaWon! {} won the game.'.format(player.name))

                new_game= True

            elif field.check_end():
                field.show_field()

                print('Draw! No player won')

                new_game= True


            if new_game:
                print('Scores:')

                for player in players:
                    print('{}: {}'.format(player.name, player.score))

                field= PlayingField()


if __name__ == '__main__':
    main()
