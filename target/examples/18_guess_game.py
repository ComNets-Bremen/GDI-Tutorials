#!/usr/bin/env python3

def game_iteration(bound_lower, bound_upper):
    '''
    This function tries to recursively guess a number in a given range.
    The size of the range is halved for every recursion step.
    It returns the number of guesses that had to be made.
    '''

    # Calculate and print the next guess
    guess= (bound_lower + bound_upper)//2
    print('{}!'.format(guess))

    # Loop until the user entered a legal command
    cmd= None
    while cmd not in ('1', '2', '3'):
        cmd= input(
            'Ist deine Zahl kleiner (1), größer (2), oder habe ich sie erraten (3)? '
        )

    if cmd == '1':
        # The number to guess is smaller than our guess
        # run game_iteration with an updated upper bound.
        # Add one to the number of guesses game_iteration
        # return to account for this guess
        return(game_iteration(bound_lower, guess) + 1)

    elif cmd == '2':
        # The number to guess is larger than our guess
        # run game_iteration with an updated lower bound.
        return(game_iteration(guess, bound_upper) + 1)

    elif cmd == '3':
        # The guess was correct, this is the base case
        # of the recursion.
        return(1)


# Start the game by printing the greeting
print('Ratespiel')

# //2 will always round down. To make sure that both bounds
# are inclusive the upper bound has to be incremented by one.
num_max= int(input('Gib eine Obergrenze ein: ')) + 1

iterattions= game_iteration(0, num_max)

print('Wieder gewonnen!!! {} Versuche'.format(iterattions))
