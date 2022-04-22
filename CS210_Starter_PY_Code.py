import re
import string

#This function reads the input file and puts data into a dictionary
def read():
    itemDict ={}    #dictionary of purchased items (key) and the amount of times item was purchesed (value)

    inputFile = open("CS210_Project_Three_Input_File.txt")  #open file

    #loop until all file lines have been looped through
    for item in inputFile.readlines():
        item = item.rstrip()  #strip key of newline at the end

        #if item is a key in the directory 
        if item in itemDict.keys():
            itemDict.update({item  :(itemDict[item] + 1)})    #if key is in dictionary, increases the value by 1
        else:
            itemDict[item] = 1  #if key is not in dictionary, add to dictionary and set value to 1

    inputFile.close()

    return itemDict

#This function creates frequency.dat and writes items purchased and number of items purchased to a new file
def write():
    itemDict = read()   #call read function to get item dictionary

    outputFile = open("frequency.dat","w")  #open file frequency.data and write over contents

    #loop for number of items in itemDict 
    for y in itemDict:
        newLine = [y, " ", str(itemDict[y]), '\n']
        outputFile.writelines(newLine)  #writes key value pairs into frequency.dat file 

    outputFile.close()

#This function lists items and the number of times they were purchased
def listItems():
    write() #call write function so file has data from item dictionary

    outputFile = open("frequency.dat")  #open frequency.dat file

    print(outputFile.read())    #print contents of file

    outputFile.close()

#This function gets the frequency and item is purchased
def frequencyOfItem(item):
    itemDict = read()   #call read function to get item dictionary

    #if item is a key in the dictionary
    if item in itemDict.keys():
        return itemDict[item]   #return value of item if key is in dictionary
    else:
        return -1   #return -1 if key is not in dictionary
