#!/usr/bin/env python3

print('Ratespiel')

# //2 will always round down. To make sure that both bounds
# are inclusive the upper bound has to be incremented by one.
bound_lower= 0
bound_upper= int(input('Gib eine Obergrenze ein: ')) + 1

guess_count= 1

while True:
    guess= (bound_lower + bound_upper)//2

    print('{}!'.format(guess))

    cmd= input(
        'Ist deine Zahl kleiner (1), größer (2), oder habe ich sie erraten (3)? '
    )

    if cmd == '1':
        bound_upper= guess

    elif cmd == '2':
        bound_lower= guess

    elif cmd == '3':
        # Leave the loop
        break

    else:
        # The command was not formatted correctly
        # Jump back to the start of the loop without incrementing
        # guess_count
        continue

    guess_count+= 1

print('Wieder gewonnen!!! {} Versuche'.format(guess_count))
