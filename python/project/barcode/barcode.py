import zxing

reader = zxing.BarCodeReader()
barcode = reader.decode("./1111.png")
print(barcode.parsed)