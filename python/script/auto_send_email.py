import smtplib 
from email.message import EmailMessage
import pandas as pd

def send_email(remail, rsubject, rcontent):
    email = EmailMessage()                          ## Creating a object for EmailMessage
    email['from'] = 'The Pythoneer Here'            ## Person who is sending
    email['to'] = remail                            ## Whom we are sending
    email['subject'] = rsubject                     ## Subject of email
    email.set_content(rcontent)                     ## content of email
    with smtplib.SMTP(host='smtp.gmail.com',port=587)as smtp:     
        smtp.ehlo()                                 ## server object
        smtp.starttls()                             ## used to send data between server and client
        smtp.login("deltadelta371@gmail.com","delta@371") ## login id and password of gmail
        smtp.send_message(email)                    ## Sending email
        print("email send to ",remail)              ## Printing success message

if __name__ == '__main__':
    df = pd.read_excel('list.xlsx')
    length = len(df)+1

    for index, item in df.iterrows():
        email = item[0]
        subject = item[1]
        content = item[2]

        send_email(email,subject,content)