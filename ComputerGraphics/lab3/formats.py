# formats.py
import struct


# Простейшая RLE: заголовок: 2 байта width, 2 байта height (unsigned short),
# затем байтовый поток пар (value, run_length) где value = 0 или 1 (1 байт), run_length = unsigned short (2 байта).
# Это текстово-байтовая простая схема — можно расширить.

def save_rle(path, binary_image):
    with open(path, 'wb') as f:
        w = binary_image.width
        h = binary_image.height
        f.write(struct.pack('<HH', w, h))
        # Проходим построчно
        for y in range(h):
            row = binary_image.pixels[y]
            # run-length encode
            run_val = int(row[0])
            run_len = 1
            for i in range(1, w):
                v = int(row[i])
                if v == run_val and run_len < 65535:
                    run_len += 1
                else:
                    f.write(struct.pack('BBH', run_val, 0, run_len))
                    run_val = v
                    run_len = 1
            # write last
            f.write(struct.pack('BBH', run_val, 0, run_len))
    

def load_rle(path):
    import numpy as np
    import struct
    with open(path, 'rb') as f:
        hdr = f.read(4)
        if len(hdr) < 4:
            raise ValueError('Invalid RLE file')
        w, h = struct.unpack('<HH', hdr)
        arr = np.zeros((h, w), dtype='uint8')
        y = 0
        x = 0
        while True:
            chunk = f.read(4)
            if not chunk:
                break
            val, _, run = struct.unpack('BBH', chunk)
            for i in range(run):
                if x >= w:
                    x = 0
                    y += 1
                    if y >= h:
                        break
                arr[y, x] = val
                x += 1
            if y >= h:
                break
            # Создаём объект-обёртку
            from model import BinaryImage
            bi = BinaryImage(w, h)
            bi.pixels = arr
            return bi