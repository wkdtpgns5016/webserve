#! /usr/bin/python3

import cgi
import os
import cgitb; cgitb.enable()

UPLOAD_DIR = os.getenv('HTTP_X_UPLOAD_FILE_PATH')
if UPLOAD_DIR == "":
    UPLOAD_DIR = 'var/upload'

form = cgi.FieldStorage()

if 'filename' in form:
    fileitem = form['filename']
    open(os.getcwd() + "/" + UPLOAD_DIR + "/" + os.path.basename(fileitem.filename), 'wb').write(fileitem.file.read())
    message = 'The file "' + os.path.basename(fileitem.filename) + '" was uploaded to ' + os.getcwd() + UPLOAD_DIR
    print("Status: 200\r\n\r\n")
else:
    message = 'Uploading Failed'
    print("Status: 500\r\n\r\n")
print("<h1> " + message + " </h1>")