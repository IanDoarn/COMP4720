

memory_size = 0
frame_size = 0
numFrames = 0

def memoryManager(memory_size,frame_size):
    global numFrames
    numFrames = int(memory_size)//int(frame_size)
    print(numFrames)
    memList = [0]*numFrames
    print(memList)
    freeFrameList = []
    count = 0
    for frame in memList:
        count += 1
        if frame == 0:
            freeFrameList.append(count)
    print(freeFrameList)
    print(str(memory_size) + " bytes of physical memory (" + str(numFrames) + " frames) has been created")


def getMemSize():#to do: create error check on input, make one input for all with a check to see which will run
    pass

def allocate(allocate_size,pid):
    global frame_size
    neededFrames = 0
    pass

def getInput():
    global memory_size, frame_size

    while(1):
        userInput = input("Enter memory command (M,P,A,D,W,R) followed by the appropriate parameters for that command, or enter exit to exit program: " )
        inputList = userInput.split(" ")
        if inputList[0] == "M":
            memory_size = inputList[1]
            frame_size = inputList[2]
            memoryManager(memory_size,frame_size)
        elif inputList[0] == "P":
            pass
        elif inputList[0] == "A":
            processSize = inputList[1]
            pid = inputList[2]
            memory = allocate(processSize,pid)
        elif inputList[0] == "D":
            pass
        elif inputList[0] == "W":
            pass
        elif inputList[0] == "R":
            pass
        elif inputList[0] == "exit":
            print("Goodbye")
            break
print("memory1",memory_size, frame_size)
getInput()
print("memory2",memory_size, frame_size)
