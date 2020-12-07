

#IMPORT LIBRARIES & MODULES
from tkinter import *
from tkinter import ttk
from tkinter import Tk,Frame
from tkinter.ttk import Notebook
from datetime import datetime,date,time
from PIL import ImageTk,Image
import pyodbc
import os, sys

#APPLICATION - Start of Application
newroot = Tk()

#APPLICATION - Configure New Window Parameters
newroot.geometry("1200x600")
newroot.title(' PCT ')
newroot.grid_columnconfigure(0, weight=1)
newroot.grid_rowconfigure(0, weight=1)

#SET CUSTOM APPLICATION COLORS
bglight = '#7d8ea3'
bgmid = '#5a6b7e'
bgdark = '#3d4855'
cwhite = 'yellow'
cgrey = 'red'

#SET STYLING FOR MENU
style = ttk.Style()
style.theme_create( "fclassic", parent="alt", settings={
            "TNotebook": {
                "configure": {
                   "tabmargins": [2, 5, 2, 0],
                   "background": bgdark,
                   "foreground": cwhite}},
                        'Treeview': {
                            'map': {
                                'background': [('selected', 'DarkGreen')],
                                'foreground': [('selected', 'black')],
                                'font': [('selected', ("Century Gothic", 10, 'bold'))],
                            }  # end 'map'
                        },  # end 'Treeview'
        "TNotebook.Tab": {
                "configure": {"padding": [5, 1], 
                   "background": bglight,
                   "foreground": cwhite,
                         "font": ("Century Gothic", '14', 'italic')},

                  "map": 
              {"background": [("selected", bgmid)],
                       "expand": [("selected", [1, 1, 1, 0])]}}})
style.theme_use("fclassic")

#SET STYLING FOR TABLES
tvstyle = ttk.Style()
tvstyle.configure("mystyle.Treeview", highlightthickness=1, bd=0, background=cwhite, font=("Century Gothic", 10))
tvstyle.configure("mystyle.Treeview.Heading", background=bglight, foreground=cwhite, font=("Century Gothic", 10, 'bold'))

#APPLICATION - Start Of Application Code
def PGT(): 

    def searchconfig():

        crecords = [('test','test','test','test','test','test','test','test','test','test','test'),('test','test','test','test','test','test','test','test','test','test','test'),('test','test','test','test','test','test','test','test','test','test','test')]
        rowalt = 0

        #SET TABLE ROW COLOR TAGS
        t1.tag_configure('evenrow', background=cgrey)
        t1.tag_configure('oddrow', background=cwhite)   

        #CLEAR TABLE
        for row in t1.get_children():
            t1.delete(row)

        #TABLE ENTRY LOOP                
        for record in crecords:

            #SET ROW COUNT
            rowalt = rowalt + 1

            #INSERT INTO TABLE WITH SPECIFIC TAGS DEPENDING OF STATEMENT
            if (rowalt % 2) == 0:
                t1.insert('', 'end', values=[record[0],record[1],record[2],record[3],record[4],record[5],record[6],record[7],record[8]],tags = ('evenrow'))
            else:
                t1.insert('', 'end', values=[record[0],record[1],record[2],record[3],record[4],record[5],record[6],record[7],record[8]],tags = ('oddrow'))
        
    #APPLICATION - START - Menu Setup
    ttk.Style().configure('TButton', background=bgdark)

    tab1 = ttk.Frame()
    tab1.pack()
    runq_b1 = Button(tab1, text="Press To Test", command=searchconfig, font=("Century Gothic", 14), bg = bglight, fg = cwhite)
    runq_b1.grid(row=0, column=2, columnspan=1, padx=10, pady=5, ipadx=10)
    tf1 = Frame(tab1)
    tf1.grid(row=1, column=0, padx=20, columnspan=8)
    t1 = ttk.Treeview(tf1, columns=(1,2,3,4,5,6,7,8,9,10,11), show="headings", height="14", selectmode='browse', style="mystyle.Treeview") 
    t1.pack()

    

runapp = PGT()

newroot.mainloop()