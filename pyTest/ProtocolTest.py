import serial
import time

print("#### Serial command builder for STM32 ####\n")

ser = serial.Serial(
        port='COM5',
        baudrate=115200)
print("port settings: ", ser.baudrate)

src = 1#int(raw_input("src: "))%10
dst = 2#int(raw_input("dst: "))%10
#command = str(raw_input("command: "))

for i in range(70):
    command = 'I'+str(i)
    datacount = len(command)
    checksum = 0
    for i in command:
        checksum += ord(i)
    checksum %= 256
    msg = ""
    
    if(datacount < 10):
        msg = bytes("${0}{1}0{2}{3}{4}#".format(src,dst,datacount,command,checksum), "ascii")
    else:
        msg = bytes("${0}{1}0{2}{3}{4}#".format(src,dst,datacount,command,checksum), "ascii")

    print(msg)
    ser.write(msg)
        
    time.sleep(0.005)
    
    print("returned from STM32: ", ser.read_all())

ser.write(bytes("$1203I63179#", "ascii")) #message error test
time.sleep(0.005)
print(ser.read_all())

ser.close()    



