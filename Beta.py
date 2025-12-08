import time 

ColorRock_Input = ""
phupha = 'None'
Rock_Upper = True
count = 0

def Convert(minute):
    return minute * 60

def ColorRock():
    if ColorRock_Input == 'Phushi':
        return 'Color'
    else:
        return 'None'


while True:
    if Rock_Upper == True:
        ColorRock_Input = input("Color: ")

        if ColorRock() != "Color":
            print('เปลี่ยนหินใหม่!')
            count = 0
            Rock_Upper = True
            phupha = "None"
            continue


    phupha = "Ready"

    if phupha == "Ready":

        if count == 0:
            print('กดลง')
            Rock_Upper = False
            count = 1
            time.sleep(1)

        elif count == 1 and Rock_Upper == False:
            Rock_Upper = True
            time.sleep(1)
            print('Check Rock')
            count = 2
            time.sleep(1)

        elif count == 2 and Rock_Upper == True:
            Rock_Upper = False
            time.sleep(1)
            print('ลงน้ำ')
            count = 3
            time.sleep(1)

        elif count == 3:
            count = 0
            Rock_Upper = True
            print('ยกขึ้น')
            time.sleep(1)
