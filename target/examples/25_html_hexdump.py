#!/usr/bin/env python3

PREAMBLE= '''<html>
 <head>
  <meta charset="UTF-8" />
  <title>HexDump</title>
  <style>
   body {
    background-color: #171717;
    color: white;
   }

   span.hdaddr {
    margin-right: 1em;
    display: inline-block;
    background-color: #e0e0e0;
    color: black;
   }

   p.hdline {
    margin: 0;
    font-family: monospace;
   }
  </style>
 </head>
 <body>
  <h1>Fabulous HexDump</h1>
'''

FOOTER= '''</body>
</html>
'''

LINE_FMT= '<p class="hdline"><span class="hdaddr">{:04x}</span>{}</p>'

def read_binary(name):
    with open(name, 'rb') as fd:
        return(fd.read())

def hexdump_html(binary):
    def to_chunks(src):
        idx= 0
        end= len(src)

        while idx<end:
            yield(idx, src[idx:idx+16])

            idx+= 16

    for (index, chunk) in to_chunks(binary):
        as_hex= ' '.join(
            '<span style="color: hsl({}, 100%, 60%)">{:02x}</span>'.format(
                int(byte/255*330), byte
            )
            for byte in chunk
        )

        html= LINE_FMT.format(index, as_hex)

        yield(html)

rom= read_binary('25_flash_dump.bin')

with open('hex.html', 'w') as fd:
    fd.write(PREAMBLE)

    for line in hexdump_html(rom):
        fd.write(line + '\n')

    fd.write(FOOTER)
