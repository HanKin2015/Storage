import pytesseract
from PIL import Image

image = Image.open('test3.png')
text = pytesseract.image_to_string(image)
print(text)
