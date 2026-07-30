import serial
import time
import datetime

################################################################################
serial_port = '/dev/tty.usbmodem1201'
serial_speed = 115200
serial_socket = None

################################################################################

# Import the necessary modules from Selenium
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys  # Added import for Keys
from selenium.webdriver.support.ui import WebDriverWait  # To wait for elements
from selenium.webdriver.support import expected_conditions as EC  # For expected conditions
from selenium.webdriver.firefox.options import Options

DEBUG = False #True

LIGNE="1"
#LIGNE="4"

#DIRECTION="OUTWARD" # -> GLAISIN
#ARRET="GARE QUAI SUD"
##ARRET="PAPETERIES"

DIRECTION="RETURN" # -> POISY
ARRET="CAMPUS"
#ARRET="GARE QUAI NORD"

options = webdriver.FirefoxOptions()
if not DEBUG:
    options.add_argument("-headless")
###driver.implicitly_wait(10)
delay = 3

def click(path):
    try:
        elt = driver.find_element(By.XPATH, path)
        elt.click()
        time.sleep(delay)
        if DEBUG:
            print("\t" + path + " clicked.")
    except:
        print(path + " NOT FOUND.")
        if DEBUG:
            print("sleeping...")
            time.sleep(3000)
    if DEBUG:
        print("---")

def type(path, str):
    try:
        elt = driver.find_element(By.XPATH, path)
        elt.send_keys(str)
        time.sleep(delay)
        if DEBUG:
            print(path + " = '" + str + "'.")
    except:
        print(path + " NOT FOUND.")
    if DEBUG:
        print("---")

while True:
    
    print("###################################################################")
    arr = []

    driver = webdriver.Firefox(options=options)
    driver.get("https://www.sibra.fr/")
    driver.maximize_window()
    time.sleep(delay)
    driver.switch_to.default_content()

    click("//button[@id='tarteaucitronAllDenied2']") # Cookies

    click("//a[@id='sibra-popup-homepage-close']")

    click("//button[@id='pills-temps-reel-desktop-tab']")
    type("//input[@id='is-SchedulesInput']", ARRET)
    click("//div[contains(@class, 'is-Autocomplete-Suggestion-Item-BadgeAndText') and contains(text(), '" + ARRET + "')]") # Popup list
    click("//button[@aria-label='Rechercher une ligne ou un arrêt']")
    print(ARRET)

    try:
        activeChild = driver.find_element(By.XPATH, "//li[contains(@data-line-id, '" + LIGNE + "')]")
        time.sleep(delay)
        print("\t" + LIGNE)

        try:
            directions = activeChild.find_elements(By.XPATH, ".//a[contains(@class, 'is-Schedule-Line-Directions-Link is-line-directions-stoppoint') and contains(@data-direction, '" + DIRECTION + "')]")
            for d in directions:
                print("\t\t" + str(datetime.datetime.now()))

                try:
                    subdirs = d.find_elements(By.XPATH, ".//li[@class='is-Schedule-Line-Directions-Item-NextDepartures-Item']")
                    for s in subdirs:
                        try:
                            subdir = s.find_element(By.XPATH, ".//span[@class='is-Schedule-Line-Directions-Item-Label']")
                            print("\t\t\tsubdir = '" + subdir.text + "'.")

                            try:
                                times = s.find_elements(By.XPATH, ".//span[starts-with(@class, 'is-Schedule-Line-Directions-Item-Time-C2')]")
                                for t in times:
                                    print("\t\t\t\ttime = '" + t.text + "'.")
                                    arr.append(t.text)
                            except:
                                print("TIMES NOT FOUND.")
                        except:
                            print("LABEL NOT FOUND.")
                except:
                    print("SUBDIR NOT FOUND.")
        except:
            print(DIRECTION + " NOT FOUND.")
    except:
        print(LIGNE + " NOT FOUND.")

### void initButtonUL( LovyanGFX *gfx, int16_t x, int16_t y, uint16_t w, uint16_t h, const T& outline, const T& fill, const T& textcolor, const char *label, float textsize_x = 1.0f, float textsize_y = 0.0f):
### 
### {
###     (int) x,
###     (int) y,
###     (int) w,
###     (int) h,
###     (color) outline,
###     (color) fill,
###     (color) textcolor,
###     (str) label,
###     (float) textsize_x = 1.0f,
###     (float) textsize_y = 0.0f
### }
### 
### {
###   "sensor": "gps",
###   "time": 1351824120,
###   "data": [
###     48.756080,
###     2.302038
###   ]
### }

    try:
        serial_socket = serial.Serial(serial_port, serial_speed, timeout=2)
        minutes = []
        for line in arr:
            if line.startswith("<"):
                line = line[1:]
            if line.endswith("min"):
                line = line[:-3]
                if line.isdecimal():
                    minutes.append(int(line))
        minutes.sort()
        minutes.append(0)
        for m in minutes:
            serial_socket.write(str(m).encode())
            serial_socket.write("\n".encode())
        serial_socket.flush()
        serial_socket.close()
        print("\nSent " + str(minutes) + " to '" + serial_port + "'.")
    except:
        print("\nWarning: Could not open serial port '" + serial_port + "' (" + str(serial_speed) + " bauds) !")
        serial_socket = None

    time.sleep(delay)
    driver.quit()

exit()
