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

    def configtype():
        pass

    def searchserial():
        pass    
    def on_selected(event):
        print('on_selected{}'.format(event))
        
    #APPLICATION - START - Menu Setup
    ttk.Style().configure('TButton', background=bgdark)

    menu = ttk.Notebook()
    menu.pack(expan = 1, fill = "both")

    tab1 = ttk.Frame(menu, style='TButton')
    menu.add(tab1, text = "Main")

    tab2 = ttk.Frame(menu, style='TButton')
    menu.add(tab2, text = "About")
    #APPLICATION -  END  - Menu Setup

    #APPLICATION - START - Tab1 Design & Setup
    emptext1 = StringVar()
    sele_l1 = Label(tab1, text="Configuration", font=("Century Gothic", 14), bg = bgdark, fg = cwhite)
    sele_l1.grid(row=0, column=0, padx=10, pady=10)
    sele_e1 = Entry(tab1, width=15, textvariable=emptext1, justify='center', font=("Century Gothic", 14))
    sele_e1.grid(row=0, column=1, padx=10, pady=10)
    emptext1.set("TEST")

    tottext1 = StringVar()
    tote_l1 = Label(tab1, text="Numero De Serie", font=("Century Gothic", 14), bg = bgdark, fg = cwhite)
    tote_l1.grid(row=0, column=3, padx=10, pady=10)
    tote_e1 = Entry(tab1, width=10, textvariable=tottext1, justify='center', font=("Century Gothic", 14))
    tote_e1.grid(row=0, column=4, padx=10, pady=10)      


    emptext2 = StringVar()
    sele_l2 = Label(tab1, text="From", font=("Century Gothic", 14), bg = bgdark, fg = cwhite)
    sele_l2.grid(row=3, column=0, padx=10, pady=10)
    sele_e2 = Entry(tab1, width=10, textvariable=emptext2, justify='center', font=("Century Gothic", 14))
    sele_e2.grid(row=3, column=1, padx=10, pady=10)

    emptext3 = StringVar()
    sele_l3 = Label(tab1, text="To", font=("Century Gothic", 14), bg = bgdark, fg = cwhite)
    sele_l3.grid(row=4, column=0, padx=10, pady=10)
    sele_e3 = Entry(tab1, width=10, textvariable=emptext3, justify='center', font=("Century Gothic", 14))
    sele_e3.grid(row=4, column=1, padx=10, pady=10)

    emptext4 = StringVar()
    sele_l3 = Label(tab1, text="Suprime RecID", font=("Century Gothic", 14), bg = bgdark, fg = cwhite)
    sele_l3.grid(row=5, column=0, padx=10, pady=10)
    sele_e3 = Entry(tab1, width=10, textvariable=emptext4, justify='center', font=("Century Gothic", 14))
    sele_e3.grid(row=5, column=1, padx=10, pady=10)

    runq_b1 = Button(tab1, text="Press To Test", command=searchconfig, font=("Century Gothic", 14), bg = bglight, fg = cwhite)
    runq_b1.grid(row=0, column=2, columnspan=1, padx=10, pady=5, ipadx=10)

    runq_b2 = Button(tab1, text="Rechercher", command=searchserial, font=("Century Gothic", 14), bg = bglight, fg = cwhite)
    runq_b2.grid(row=0, column=5, columnspan=1, padx=10, pady=5, ipadx=10)

    runq_b3 = Button(tab1, text="Modifier", command=searchserial, font=("Century Gothic", 14), bg = bglight, fg = cwhite)
    runq_b3.grid(row=2, column=2, columnspan=1, padx=10, pady=5, ipadx=10)

    runq_b4 = Button(tab1, text="Transferer", command=searchserial, font=("Century Gothic", 14), bg = bglight, fg = cwhite)
    runq_b4.grid(row=3, column=2, columnspan=1, rowspan=2, padx=10, pady=5, ipadx=10)

    runq_b5 = Button(tab1, text="Supprimer", command=searchserial, font=("Century Gothic", 14), bg = bglight, fg = cwhite)
    runq_b5.grid(row=5, column=2, columnspan=1, padx=10, pady=5, ipadx=10)

    tf1 = Frame(tab1)
    tf1.grid(row=1, column=0, padx=20, columnspan=8)
    t1 = ttk.Treeview(tf1, columns=(1,2,3,4,5,6,7,8,9,10,11), show="headings", height="14", selectmode='browse', style="mystyle.Treeview") 
    t1.pack()

    t1.focus_set()

    t1.heading(1, text="RecID")
    t1.column(1 ,minwidth=60,width=70, stretch=NO, anchor="center")
    t1.heading(2, text="Config Name")
    t1.column(2 ,minwidth=100,width=125, stretch=NO, anchor="center")
    t1.heading(3, text="Config Type")
    t1.column(3 ,minwidth=100,width=120, stretch=NO, anchor="center")
    t1.heading(4, text="Serial #")
    t1.column(4 ,minwidth=100,width=110, stretch=NO, anchor="center")
    t1.heading(5, text="MAC Address")
    t1.column(5 ,minwidth=100,width=120, stretch=NO, anchor="center")
    t1.heading(6, text="Company")
    t1.column(6 ,minwidth=100,width=180, stretch=NO, anchor="center")
    t1.heading(7, text="Actif")
    t1.column(7 ,minwidth=60,width=60, stretch=NO, anchor="center")
    t1.heading(8, text="All T.")
    t1.column(8 ,minwidth=60,width=80, stretch=NO, anchor="center")
    t1.heading(9, text="Open T.")
    t1.column(9 ,minwidth=60,width=80, stretch=NO, anchor="center")
    t1.heading(10, text="Project T.")
    t1.column(10 ,minwidth=60,width=80, stretch=NO, anchor="center")
    t1.heading(11, text="Placeholder 2")
    t1.column(11 ,minwidth=100,width=130, stretch=NO, anchor="center")
    
    t1.bind('<ButtonRelease-1>', on_selected)
    #APPLICATION -  END  - Tab1 Design & Setup

runapp = PGT()

newroot.mainloop()