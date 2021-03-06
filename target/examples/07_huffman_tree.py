#!/usr/bin/env python3

import sys
import string

# Source:
#  https://de.wikipedia.org/wiki/Buchstabenh%C3%A4ufigkeit
# There was no information about the space sign so i guessed
letter_prop_map_de_de= {
    ' ' : 10.0,
    'E' : 17.40,
    'N' : 9.78,
    'I' : 7.55,
    'S' : 7.27,
    'R' : 7.00,
    'A' : 6.51,
    'T' : 6.15,
    'D' : 5.08,
    'H' : 4.76,
    'U' : 4.35,
    'L' : 3.44,
    'C' : 3.06,
    'G' : 3.01,
    'M' : 2.53,
    'O' : 2.51,
    'B' : 1.89,
    'W' : 1.89,
    'F' : 1.66,
    'K' : 1.21,
    'Z' : 1.13,
    'P' : 0.79,
    'V' : 0.67,
    'ß' : 0.31,
    'J' : 0.27,
    'Y' : 0.04,
    'X' : 0.03,
    'Q' : 0.02
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

class EncodingTableBase(object):
    def encode_str(self, text):
        return(' '.join(self.table[l] for l in text.upper()))

class HuffmanTable(EncodingTableBase):
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

class AsciiTable(EncodingTableBase):
    def __init__(self):
        self.table= dict(
            (l, '{:08b}'.format(n + 65)) for (n, l) in enumerate(letter_prop_map_de_de)
        )

        self.table[' ']= '00100000'

def main(argv):
    ht= HuffmanTable(letter_prop_map_de_de)
    at= AsciiTable()

    txt_in= ' '.join(argv)
    
    print('Input Text:', txt_in)
    print('Huffman:   ', ht.encode_str(txt_in))
    print('ASCII:     ', at.encode_str(txt_in))

if __name__ == '__main__':
    main(sys.argv[1:])
