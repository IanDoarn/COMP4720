
# written by Kyle Murry and Jose Torres
# Fall 2018 Operating Systems
# Programming Assignment 3

f = open("sys_config.txt","r")#opens and reads text file assuming the file is in the same directory of this python file
doc = f.readlines()
doc = [x.strip() for x in doc]
allo_del = doc.index("Allocation")
max_del = doc.index("Max")
avail_del = doc.index("Available")

allo_list = doc[allo_del+1:max_del]
max_list = doc[max_del+1:avail_del]
avail = doc[avail_del+1]


value_list = []
allo_dic = {}
max_dic = {}
need_dic = {}
temp = ""

for process in allo_list:#to put allocation values into a dicionary referenced by process number
    temp = process.split(":")
    temp[1] = [temp[1].replace(" ", "")]
    value_list.append(temp[1])
    temp[1] =  list(map(int, temp[1]))
    allo_dic[temp[0]] = temp[1]

avail = avail.replace(" ", "")# to set available parameter
input_check = len(avail)
avail = int(avail)



for process in max_list:# to put max values into a dicionary referenced by process number
    temp = process.split(":")
    temp[1] = [temp[1].replace(" ", "")]
    temp[1] =  list(map(int, temp[1]))
    max_dic[temp[0]] = temp[1]

temp_minus1 = 0
temp_minus2 = 0

work = avail


for item in max_dic:# to create need vector and place in a dicionary referenced by process number
    temp_minus1 = max_dic[item]
    temp_minus2 = allo_dic[item]
    need_dic[item] = (temp_minus1[0] - temp_minus2[0])

loop_count = 0
finish = []
loop_pass = 0
change_count = 0


for process in range(len(allo_dic)):#to initialize finish list
    finish.append(False)


def safe_check():# to check if the current process parameters will lead to a safe mode
    global loop_count, finish, need_dic, allo_dic, work, change_count
    while(1):
        for key in allo_dic:
            temp = ("Process " + str(loop_count))
            process_need = need_dic[temp]
            temp = "Process " + str(loop_count)
            process_allo = allo_dic[temp]
            process_allo = process_allo[0]
            if work >= process_need and finish[loop_count] == False:
                work += process_allo
                finish[loop_count] = True
                change_count += 1



            loop_count += 1
        if change_count == 0:
            loop_count = 0
            break
        else:
            change_count = 0

        loop_count = 0

def safe_grant_check():#to check each process chosen by grant_resource() to be endend, to see if ending the process will result in a safe mode
    global loop_count, finish, need_dic, allo_dic, work, change_count
    work = avail
    change_count = 0
    while(1):
        for key in allo_dic:
            temp = ("Process " + str(loop_count))
            process_need = need_dic[temp]
            temp = "Process " + str(loop_count)
            process_allo = allo_dic[temp]
            process_allo = process_allo[0]

            if work >= process_need and finish[loop_count] == False:
                work += process_allo
                finish[loop_count] = True
                change_count += 1



            loop_count += 1
        if change_count == 0:
            loop_count = 0
            finish_check = 0
            for element in finish:
                if element == True:
                    finish_check += 1
            if finish_check == len(finish):
                return True
            else:
                return False
        else:
            change_count = 0

        loop_count = 0

finish_check = 0

safe_check()

for element in finish:
    if element == True:
        finish_check += 1
if finish_check == len(finish):
    print("SAFE")
else:
    print("UNSAFE")

work = 0
Request_Vector = input("Request Vector:")
Request_Vector = Request_Vector.replace(" ", "")

try:
    #global Request_Vector
    process_vector = int(Request_Vector)
except ValueError:
    print("Wrong Input!")

if len(Request_Vector) != input_check:
    print("Wrong Input!")


which_process = str(input("Enter the Process that is making the request. Use corect format i.e. Process 0:"))
which_process = which_process.strip()
this_process = which_process.split(" ")

try:
    process_number = int(this_process[1])
except ValueError:
    print("Wrong Input!")

if this_process[0] != "Process" or process_number < 0 or process_number > len(allo_dic)-1 or len(this_process) > 2:
    print("Wrong Input!")


avail = avail - process_vector
new_allo = allo_dic[which_process]
new_need = need_dic[which_process]

allo_dic[which_process] = [new_allo[0] + process_vector]
need_dic[which_process] = new_need - process_vector


for process in range(len(allo_dic)):
    finish[process] = False

safe_check()
finish_check = 0
for element in finish:
    if element == True:
        finish_check += 1

terminate_list = []

def grant_resource():#to find which process to end to stop deadlock

    global terminate_list, avail

    grant_check = avail
    end_process = ""
    loop_end = False

    while(loop_end != True):
        allo_check = 0
        for element in allo_dic:
            this_allo = allo_dic[element]
            this_allo = this_allo[0]
            if this_allo > allo_check:
                allo_check = this_allo
                end_process = element

        terminate_list.append(end_process)
        allo_dic[end_process] = [0]
        need_dic[end_process] = 0
        avail += allo_check


        loop_end = safe_grant_check()

    print(terminate_list, " should be terminated to grant the requested resources.<--------")
for process in range(len(allo_dic)):
    finish[process] = False
if finish_check == len(finish):
    print("PROCESS GRANTED")
else:
    print("PROCESS NOT GRANTED")
    grant_resource()
