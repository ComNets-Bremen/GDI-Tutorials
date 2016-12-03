#!/usr/bin/env python3

import sys
import string

differences= {
    -2 : 9,
    -1 : 19,
    0 : 40,
    1 : 18,
    2 : 13
}

class HuffmanTreeNode(object):
    def __lt__(self, other):
        return(other.get_propability() < self.get_propability())


class HuffmanTreeBranch(HuffmanTreeNode):
    def __init__(self, child_b, child_a):
        self.child_a= child_a
        self.child_b= child_b

    def get_encodings(self):
        side_a= list((l, '1' + enc) for (l, enc) in self.child_a.get_encodings())
        side_b= list((l, '0' + enc) for (l, enc) in self.child_b.get_encodings())

        return (side_a + side_b)

    def format_subtree(self):
        sub_a= self.child_a.format_subtree()
        sub_b= self.child_b.format_subtree()

        fmt= list()
        fmt_char= ' '

        middle_text= '─({:2.2f}%)─┤'.format(self.get_propability())
        pad= ' '*(len(middle_text) - 1)

        for e in sub_a:
            if e.startswith('─'):
                fmt_char= '│'
                fmt.append(pad + '╭' + e)

            else:
                fmt.append(pad + fmt_char + e)

        fmt.append(middle_text)

        for e in sub_b:
            if e.startswith('─'):
                fmt_char= ' '
                fmt.append(pad + '╰' + e)

            else:
                fmt.append(pad + fmt_char + e)

        return(fmt)

    def get_propability(self):
        return(self.child_a.get_propability() + self.child_b.get_propability())

class HuffmanTreeLeaf(HuffmanTreeNode):
    def __init__(self, letter, propability):
        self.letter= letter
        self.propability= propability

    def get_encodings(self):
        return([(self.letter, '')])

    def get_propability(self):
        return(self.propability)

    def format_subtree(self):
        return(['─({}%)─╼ {}'.format(self.propability, repr(self.letter))])

class HuffmanTable(object):
    def __init__(self, letters):
        tree= sorted(list(HuffmanTreeLeaf(letter, prop) for (letter, prop) in letters.items()))

        def print_tree():
            headline='Noch {} Schritte:'.format(len(tree) - 1)
            print('\n'.join(('','', headline, '-'*len(headline), '')))

            for n in tree:
                print('\n'.join(n.format_subtree()))


        print_tree()

        while(len(tree) != 1):
            new_branch= HuffmanTreeBranch(tree.pop(), tree.pop())
            tree.append(new_branch)

            tree= sorted(tree)

            print_tree()

        root= tree[0]

        self.table= dict(root.get_encodings())

def main(argv):
    ht= HuffmanTable(differences)

if __name__ == '__main__':
    main(sys.argv[1:])
