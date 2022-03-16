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
    
    if(datacount < 10):
        print("${0}{1}0{2}{3}{4}#".format(src,dst,datacount,command,checksum))
        ser.write("${0}{1}0{2}{3}{4}#".format(src,dst,datacount,command,checksum))
    else:
        print("${0}{1}{2}{3}{4}#".format(src,dst,datacount,command,checksum))
        ser.write("${0}{1}{2}{3}{4}#".format(src,dst,datacount,command,checksum))
        
    time.sleep(0.01)
    
    print("returned from STM32: ", ser.read_all())

ser.close()    



