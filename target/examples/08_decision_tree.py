#!/usr/bin/env python3

import sys
import string

def treeify_range(start, end):
    if start==end-1:
        yield('─╼ {}'.format(start))

    else:
        middle= (start+end)//2

        fmt_str= '       '

        for a in treeify_range(start, middle):
            if a.startswith('─'):
                yield(' ╭─(<)─' + a)

                fmt_str= ' │     '
            else:
                yield(fmt_str + a)

        yield('─┤ {}'.format(middle))

        for a in treeify_range(middle+1, end):
            if a.startswith('─'):
                yield(' ╰─(>)─' + a)

                fmt_str= '       '
            else:
                yield(fmt_str + a)

print('\n'.join(treeify_range(1, 32)))
