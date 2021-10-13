


from PyPDF2 import PdfFileWriter, PdfFileReader
path = r'./SVM算法的推导过程.pdf' # 这里填写目标 PDF 所在的路径

pdf_reader = PdfFileReader(path + r'\test.pdf')
pdf_writer = PdfFileWriter()

for page in range(pdf_reader.getNumPages()):
    pdf_writer.addPage(pdf_reader.getPage(page))
pdf_writer.encrypt('a123') # 设置密码为 a123
with open(path + r'\test.pdf', 'wb') as out:
    pdf_writer.write(out)