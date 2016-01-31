__author__ = 'Ryan Branch'
import csv

#Some global constants are defined here
BACKGROUND_COLOR = (255, 255, 255)

#Some global variables are defined here
roomWidth = 0
roomHeight = 0
numObjects = 0
objects = []

#A class describing any object that can be displayed on the screen
class Object:
    #MEMBER VARIABLES
        # width - the width of the object, in pixels
        # height - the height of the object, in pixels
        # pos - the coordinates of the top-left point of the object,
        #       referenced from the top left of the room
        # appearance - a list of (width * height) elements, describing
        #              the color of each pixel in the object

    #Default constructor
    def __init__(self):
        self.width = 0
        self.height = 0
        self.pos = 0.0
        self.appearance = []

    #Constructor Method
    def __init__(self, width, height, pos, appearance):
        self.width = width
        self.height = height
        self.pos = pos
        self.appearance = appearance

def playVideo():
    1 == 1

def fileInput():
    #filename = raw_input('Enter filename, including extension.')
    filename = "test.csv"
    data = open(filename, 'rb')
    reader = csv.reader(data)
    rowNum = 0
    objectIn = 0
    objHeight = 0
    objPos = 0
    pixels = []
    pixelsRemaining = -1
    readyToPlay = False

    for row in reader: #Defines the current row

        #Gets header data
        if (rowNum == 0):
            roomWidth = int(row[0])
            roomHeight = int(row[1])
            numObjects = int(row[2]) #Crash if this isn't 1 or more
            rowNum += 1

        #Reads in objects
        elif (objectIn < numObjects):
            if (pixelsRemaining == -1):
                objWidth = int(row[0])
                objHeight = int(row[1])
                objPos = (int(row[2]), int(row[-1]))
                pixelsRemaining = objWidth * objHeight
            else:
                if (pixelsRemaining != 0):
                    pixelColor = (int(row[0]), int(row[1]), int(row[2]))
                    pixels.append(pixelColor)
                    pixelsRemaining -= 1
                else:
                    pixelsRemaining = -1
                    objects.append(Object(objWidth, objHeight, objPos, pixels))
                    objectIn += 1
            rowNum += 1
        #All objects are now read in
        else:
            readyToPlay = True

        if (readyToPlay):
            data.close()
            playVideo(reader)

        rowNum += 1

fileInput()