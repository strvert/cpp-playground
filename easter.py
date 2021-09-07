import qrcode
import base64
import io

qr_bytes = '█▀▀▀▀▀█ █▀▀█ ▄█▄▄▄▀▀█▄█▄█▄█▀▄ █▀▀▀▀▀██ ███ █  ▀ ▄▄▀ ▀▀▄▀▀ ▀ ▀██ ▀▄ █ ███ ██ ▀▀▀ █ █▄▄▀█▄█▀▀██▄ ▀█▄▄▄ ▄█ █ ▀▀▀ █▀▀▀▀▀▀▀ █▄▀ ▀▄▀ █▄█▄▀ █▄▀▄▀▄█ ▀▀▀▀▀▀▀▀▀▀▄ █▀ ▀█ ▀█▀ ▀▀██▄▄▄ ▀▀█▄▀ ▀██▀ ▄███ ▀▄▀▄▀▀█▄▄▄█▀█ ▄▀▄▀▄▀█▀▀▀▀▄▀█ █▀▀ ██▄█▀██▄▀▀▀▀█  ██▄▀▄ ▄▀▄  ▀▀ █▀ ██ █▄██ ▀▄▀▄█▀██ █▀ ▄ ▄ ▀ ▀▄▄▀█ ▀▀▀ █▀▄▀   ▀▄▄ ▀█ ▀ ▀▄█▀█▀ █▄ ▀▄▀▀▄ ▄██▄█▀██ █▄██▄▄▀▀▀▄▀▄▀▄▀▄█▀█ █▀▀ ▀ ▄█▄▀ █  ▄▀▀▄  ▀▀▀█▀ ▄▀▀█ ▄  ██▀▄█▀██▄▀██▄ ▄█ █▄ ▀▄▄█▀▀▄▄▄ ▀▄█▄▄▀ ▄ ▄▀   ▄ █  ▀▄▀ ▄▄ ██  ▀ █▄▄ █▀▄▄█▄▀█▀  ▀▀▄█▄ ▀ █▄▄▄█▄██ ▀ ▄█▀▀   ▄▀▄▀██▄█▀██ ▄ ▄█▀▄▀▀▀▀█▄▀█ ▄ ▀ ▀▀▀▀▀  ▀ █    ██ ▄▄█▄▄▄█ █▄▀██▀▀▀██▄▀▄█▀▀▀▀▀█ ▄▄█▀ ▄ █▄▀ █▀█ ▀  █▄█ ▀ ██ ▄▀█ ███ █  ▀█▀█▀ ▄▀▀█ ▄▄ ▄ █ ███▀▀█▄ ▄ █ ▀▀▀ █ █▀█▄█▀█ ▄█▄▀  █▄█ █ ▄█ ▄▀▄ ▀▀▀▀▀▀▀▀▀ ▀▀   ▀▀▀▀ ▀▀▀    ▀ ▀▀  ▀ ▀  ▀'

code = [0x2588,0x2580,0x2580,0x2580,0x2580,0x2580,0x2588,0xa0,0x2588,0x2580,0x2580,0x2588,0xa0,0x2584,0x2588,0x2584,0x2584,0x2584,0x2580,0x2580,0x2588,0x2584,0x2588,0x2584,0x2588,0x2584,0x2588,0x2580,0x2584,0xa0,0x2588,0x2580,0x2580,0x2580,0x2580,0x2580,0x2588,0x2588,0xa0,0x2588,0x2588,0x2588,0xa0,0x2588,0xa0,0xa0,0x2580,0xa0,0x2584,0x2584,0x2580,0xa0,0x2580,0x2580,0x2584,0x2580,0x2580,0xa0,0x2580,0xa0,0x2580,0x2588,0x2588,0xa0,0x2580,0x2584,0xa0,0x2588,0xa0,0x2588,0x2588,0x2588,0xa0,0x2588,0x2588,0xa0,0x2580,0x2580,0x2580,0xa0,0x2588,0xa0,0x2588,0x2584,0x2584,0x2580,0x2588,0x2584,0x2588,0x2580,0x2580,0x2588,0x2588,0x2584,0xa0,0x2580,0x2588,0x2584,0x2584,0x2584,0xa0,0x2584,0x2588,0xa0,0x2588,0xa0,0x2580,0x2580,0x2580,0xa0,0x2588,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0xa0,0x2588,0x2584,0x2580,0xa0,0x2580,0x2584,0x2580,0xa0,0x2588,0x2584,0x2588,0x2584,0x2580,0xa0,0x2588,0x2584,0x2580,0x2584,0x2580,0x2584,0x2588,0xa0,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0x2584,0xa0,0x2588,0x2580,0xa0,0x2580,0x2588,0xa0,0x2580,0x2588,0x2580,0xa0,0x2580,0x2580,0x2588,0x2588,0x2584,0x2584,0x2584,0xa0,0x2580,0x2580,0x2588,0x2584,0x2580,0xa0,0x2580,0x2588,0x2588,0x2580,0xa0,0x2584,0x2588,0x2588,0x2588,0xa0,0x2580,0x2584,0x2580,0x2584,0x2580,0x2580,0x2588,0x2584,0x2584,0x2584,0x2588,0x2580,0x2588,0xa0,0x2584,0x2580,0x2584,0x2580,0x2584,0x2580,0x2588,0x2580,0x2580,0x2580,0x2580,0x2584,0x2580,0x2588,0xa0,0x2588,0x2580,0x2580,0xa0,0x2588,0x2588,0x2584,0x2588,0x2580,0x2588,0x2588,0x2584,0x2580,0x2580,0x2580,0x2580,0x2588,0xa0,0xa0,0x2588,0x2588,0x2584,0x2580,0x2584,0xa0,0x2584,0x2580,0x2584,0xa0,0xa0,0x2580,0x2580,0xa0,0x2588,0x2580,0xa0,0x2588,0x2588,0xa0,0x2588,0x2584,0x2588,0x2588,0xa0,0x2580,0x2584,0x2580,0x2584,0x2588,0x2580,0x2588,0x2588,0xa0,0x2588,0x2580,0xa0,0x2584,0xa0,0x2584,0xa0,0x2580,0xa0,0x2580,0x2584,0x2584,0x2580,0x2588,0xa0,0x2580,0x2580,0x2580,0xa0,0x2588,0x2580,0x2584,0x2580,0xa0,0xa0,0xa0,0x2580,0x2584,0x2584,0xa0,0x2580,0x2588,0xa0,0x2580,0xa0,0x2580,0x2584,0x2588,0x2580,0x2588,0x2580,0xa0,0x2588,0x2584,0xa0,0x2580,0x2584,0x2580,0x2580,0x2584,0xa0,0x2584,0x2588,0x2588,0x2584,0x2588,0x2580,0x2588,0x2588,0xa0,0x2588,0x2584,0x2588,0x2588,0x2584,0x2584,0x2580,0x2580,0x2580,0x2584,0x2580,0x2584,0x2580,0x2584,0x2580,0x2584,0x2588,0x2580,0x2588,0xa0,0x2588,0x2580,0x2580,0xa0,0x2580,0xa0,0x2584,0x2588,0x2584,0x2580,0xa0,0x2588,0xa0,0xa0,0x2584,0x2580,0x2580,0x2584,0xa0,0xa0,0x2580,0x2580,0x2580,0x2588,0x2580,0xa0,0x2584,0x2580,0x2580,0x2588,0xa0,0x2584,0xa0,0xa0,0x2588,0x2588,0x2580,0x2584,0x2588,0x2580,0x2588,0x2588,0x2584,0x2580,0x2588,0x2588,0x2584,0xa0,0x2584,0x2588,0xa0,0x2588,0x2584,0xa0,0x2580,0x2584,0x2584,0x2588,0x2580,0x2580,0x2584,0x2584,0x2584,0xa0,0x2580,0x2584,0x2588,0x2584,0x2584,0x2580,0xa0,0x2584,0xa0,0x2584,0x2580,0xa0,0xa0,0xa0,0x2584,0xa0,0x2588,0xa0,0xa0,0x2580,0x2584,0x2580,0xa0,0x2584,0x2584,0xa0,0x2588,0x2588,0xa0,0xa0,0x2580,0xa0,0x2588,0x2584,0x2584,0xa0,0x2588,0x2580,0x2584,0x2584,0x2588,0x2584,0x2580,0x2588,0x2580,0xa0,0xa0,0x2580,0x2580,0x2584,0x2588,0x2584,0xa0,0x2580,0xa0,0x2588,0x2584,0x2584,0x2584,0x2588,0x2584,0x2588,0x2588,0xa0,0x2580,0xa0,0x2584,0x2588,0x2580,0x2580,0xa0,0xa0,0xa0,0x2584,0x2580,0x2584,0x2580,0x2588,0x2588,0x2584,0x2588,0x2580,0x2588,0x2588,0xa0,0x2584,0xa0,0x2584,0x2588,0x2580,0x2584,0x2580,0x2580,0x2580,0x2580,0x2588,0x2584,0x2580,0x2588,0xa0,0x2584,0xa0,0x2580,0xa0,0x2580,0x2580,0x2580,0x2580,0x2580,0xa0,0xa0,0x2580,0xa0,0x2588,0xa0,0xa0,0xa0,0xa0,0x2588,0x2588,0xa0,0x2584,0x2584,0x2588,0x2584,0x2584,0x2584,0x2588,0xa0,0x2588,0x2584,0x2580,0x2588,0x2588,0x2580,0x2580,0x2580,0x2588,0x2588,0x2584,0x2580,0x2584,0x2588,0x2580,0x2580,0x2580,0x2580,0x2580,0x2588,0xa0,0x2584,0x2584,0x2588,0x2580,0xa0,0x2584,0xa0,0x2588,0x2584,0x2580,0xa0,0x2588,0x2580,0x2588,0xa0,0x2580,0xa0,0xa0,0x2588,0x2584,0x2588,0xa0,0x2580,0xa0,0x2588,0x2588,0xa0,0x2584,0x2580,0x2588,0xa0,0x2588,0x2588,0x2588,0xa0,0x2588,0xa0,0xa0,0x2580,0x2588,0x2580,0x2588,0x2580,0xa0,0x2584,0x2580,0x2580,0x2588,0xa0,0x2584,0x2584,0xa0,0x2584,0xa0,0x2588,0xa0,0x2588,0x2588,0x2588,0x2580,0x2580,0x2588,0x2584,0xa0,0x2584,0xa0,0x2588,0xa0,0x2580,0x2580,0x2580,0xa0,0x2588,0xa0,0x2588,0x2580,0x2588,0x2584,0x2588,0x2580,0x2588,0xa0,0x2584,0x2588,0x2584,0x2580,0xa0,0xa0,0x2588,0x2584,0x2588,0xa0,0x2588,0xa0,0x2584,0x2588,0xa0,0x2584,0x2580,0x2584,0xa0,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0x2580,0xa0,0x2580,0x2580,0xa0,0xa0,0xa0,0x2580,0x2580,0x2580,0x2580,0xa0,0x2580,0x2580,0x2580,0xa0,0xa0,0xa0,0xa0,0x2580,0xa0,0x2580,0x2580,0xa0,0xa0,0x2580,0xa0,0x2580,0xa0,0xa0,0x2580]


# def gen_qr():
#     qr = qrcode.QRCode(
#         version=3,
#         error_correction=qrcode.constants.ERROR_CORRECT_L,
#         box_size=1,
#         border=0,
#     )
#     qr.add_data('https://ja.wikipedia.org/wiki/%E3%82%A4%E3%83%BC%E3%82%B9%E3%82%BF%E3%83%BC%E3%83%BB%E3%82%A8%E3%83%83%E3%82%B0')
#     qr.make(fit=True)
#     f = io.StringIO()
#     qr.print_ascii(out=f)
#     f.seek(0)
#     print(f.read())

def to_embedcode(in_code):
    for ch in in_code:
        b = hex(ord(ch))
        print(b + ',', end='')
# to_embedcode(qr_bytes)

def numtostr(num):
    if num <= 9:
        return str(num)
    elif num <= 10 + ord('Z') - ord('A'):
        return str(chr(ord('A') + num - 10))
    else:
        return str(chr(ord('a') + num - 36))


def baseconv(v, b):
    ret = ''
    while(True):
        c = numtostr(v % b)
        if v // b == 0:
            return c + ret
        ret = c + ret
        v //= b

def bytes_to_str(bytes_code):
    str_list = []
    for b in bytes_code:
        str_list.append(baseconv(b, 62))
    return str_list

def toobf(str_list):
    ret = ''
    for e in str_list:
        ret += e + '#'
    return ret[:-1]

def printer(ml):
    # clues = ml.split('#')
    # for clue in clues:
    #     shadow = '2' + clue
    #     for i, part in enumerate(shadow):
    #         if ()
    #         print(part, end='')
    #     print()
    # for i, b in enumerate(what):
    #     if i % 37 == 0:
    #         print()
    #     print(chr(b), end='')
    pass


meaningless = '4paI4paA4paA4paA4paA4paA4paIwqDilojiloDiloDilojCoOKWhOKWiOKWhOKWhOKWhOKWgOKWgOKWiOKWhOKWiOKWhOKWiOKWhOKWiOKWgOKWhMKg4paI4paA4paA4paA4paA4paA4paI4paIwqDilojilojilojCoOKWiMKgwqDiloDCoOKWhOKWhOKWgMKg4paA4paA4paE4paA4paAwqDiloDCoOKWgOKWiOKWiMKg4paA4paEwqDilojCoOKWiOKWiOKWiMKg4paI4paIwqDiloDiloDiloDCoOKWiMKg4paI4paE4paE4paA4paI4paE4paI4paA4paA4paI4paI4paEwqDiloDilojiloTiloTiloTCoOKWhOKWiMKg4paIwqDiloDiloDiloDCoOKWiOKWgOKWgOKWgOKWgOKWgOKWgOKWgMKg4paI4paE4paAwqDiloDiloTiloDCoOKWiOKWhOKWiOKWhOKWgMKg4paI4paE4paA4paE4paA4paE4paIwqDiloDiloDiloDiloDiloDiloDiloDiloDiloDiloDiloTCoOKWiOKWgMKg4paA4paIwqDiloDilojiloDCoOKWgOKWgOKWiOKWiOKWhOKWhOKWhMKg4paA4paA4paI4paE4paAwqDiloDilojilojiloDCoOKWhOKWiOKWiOKWiMKg4paA4paE4paA4paE4paA4paA4paI4paE4paE4paE4paI4paA4paIwqDiloTiloDiloTiloDiloTiloDilojiloDiloDiloDiloDiloTiloDilojCoOKWiOKWgOKWgMKg4paI4paI4paE4paI4paA4paI4paI4paE4paA4paA4paA4paA4paIwqDCoOKWiOKWiOKWhOKWgOKWhMKg4paE4paA4paEwqDCoOKWgOKWgMKg4paI4paAwqDilojilojCoOKWiOKWhOKWiOKWiMKg4paA4paE4paA4paE4paI4paA4paI4paIwqDilojiloDCoOKWhMKg4paEwqDiloDCoOKWgOKWhOKWhOKWgOKWiMKg4paA4paA4paAwqDilojiloDiloTiloDCoMKgwqDiloDiloTiloTCoOKWgOKWiMKg4paAwqDiloDiloTilojiloDilojiloDCoOKWiOKWhMKg4paA4paE4paA4paA4paEwqDiloTilojilojiloTilojiloDilojilojCoOKWiOKWhOKWiOKWiOKWhOKWhOKWgOKWgOKWgOKWhOKWgOKWhOKWgOKWhOKWgOKWhOKWiOKWgOKWiMKg4paI4paA4paAwqDiloDCoOKWhOKWiOKWhOKWgMKg4paIwqDCoOKWhOKWgOKWgOKWhMKgwqDiloDiloDiloDilojiloDCoOKWhOKWgOKWgOKWiMKg4paEwqDCoOKWiOKWiOKWgOKWhOKWiOKWgOKWiOKWiOKWhOKWgOKWiOKWiOKWhMKg4paE4paIwqDilojiloTCoOKWgOKWhOKWhOKWiOKWgOKWgOKWhOKWhOKWhMKg4paA4paE4paI4paE4paE4paAwqDiloTCoOKWhOKWgMKgwqDCoOKWhMKg4paIwqDCoOKWgOKWhOKWgMKg4paE4paEwqDilojilojCoMKg4paAwqDilojiloTiloTCoOKWiOKWgOKWhOKWhOKWiOKWhOKWgOKWiOKWgMKgwqDiloDiloDiloTilojiloTCoOKWgMKg4paI4paE4paE4paE4paI4paE4paI4paIwqDiloDCoOKWhOKWiOKWgOKWgMKgwqDCoOKWhOKWgOKWhOKWgOKWiOKWiOKWhOKWiOKWgOKWiOKWiMKg4paEwqDiloTilojiloDiloTiloDiloDiloDiloDilojiloTiloDilojCoOKWhMKg4paAwqDiloDiloDiloDiloDiloDCoMKg4paAwqDilojCoMKgwqDCoOKWiOKWiMKg4paE4paE4paI4paE4paE4paE4paIwqDilojiloTiloDilojilojiloDiloDiloDilojilojiloTiloDiloTilojiloDiloDiloDiloDiloDilojCoOKWhOKWhOKWiOKWgMKg4paEwqDilojiloTiloDCoOKWiOKWgOKWiMKg4paAwqDCoOKWiOKWhOKWiMKg4paAwqDilojilojCoOKWhOKWgOKWiMKg4paI4paI4paIwqDilojCoMKg4paA4paI4paA4paI4paAwqDiloTiloDiloDilojCoOKWhOKWhMKg4paEwqDilojCoOKWiOKWiOKWiOKWgOKWgOKWiOKWhMKg4paEwqDilojCoOKWgOKWgOKWgMKg4paIwqDilojiloDilojiloTilojiloDilojCoOKWhOKWiOKWhOKWgMKgwqDilojiloTilojCoOKWiMKg4paE4paIwqDiloTiloDiloTCoOKWgOKWgOKWgOKWgOKWgOKWgOKWgOKWgOKWgMKg4paA4paAwqDCoMKg4paA4paA4paA4paAwqDiloDiloDiloDCoMKgwqDCoOKWgMKg4paA4paAwqDCoOKWgMKg4paAwqDCoOKWgA=='

if __name__ == '__main__':
    decoded = base64.b64decode(meaningless).decode('utf-8')
    for i, ch in enumerate(decoded):
        if i % 37 == 0:
            print()
        print(ch, end='')