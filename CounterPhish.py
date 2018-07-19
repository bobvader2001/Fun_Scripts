#Author: bobvader2001
#
#Worked in my case but is very situation-specific so edit as required
#My case was a btinternet email phishing site

import requests
import random
import string

counter = 1
while(True):
    user = ''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase, k=random.randint(5,15)))
    email = user + '@btinternet.com'
    password = ''.join(random.choices(string.ascii_lowercase + string.ascii_uppercase + string.digits + '!@#$%^&*()_', k=random.randint(3,25)))
    data = email + ' - ' + password
    print(str(counter) + ': ' + data)
    r = requests.post("http://A URL.com/face/btins/next.php", data={'u':email, 'p':password})
    if "Access denied.  Your IP address is blacklisted." in r.text:
        print(r.text)
        exit(0)
    counter += 1
