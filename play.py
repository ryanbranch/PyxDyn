__author__ = 'Ryan Branch'
import csv
import Image
import os
import errno
import sys
import _tkinter

#Some global constants are defined here
BACKGROUND_COLOR = (255, 255, 255)

#A class containing various variables central to the entire program
class Room:
    #MEMBER VARIABLES
    # backgroundColor - the RGB value of the color of the window's background
    # transparentColor - the RGB value to be treated as transparent
    # roomWidth - the width of the window, in pixels
    # roomHeight - the height of the window, in pixels
    # fileName - the name of the file being used for simulation input
    # folderName - the name of the folder in which to store data such as images
    # objects - a list containing all of the objects

    #Default constructor
    def __init__(self):
        self.backgroundColor = (255, 255, 255)
        self.transparentColor = (255, 254, 253)
        self.roomWidth = 1024
        self.roomHeight = 768
        self.fileName = "input.csv"
        self.folderName = "input_csv"
        self.objects = []

    #Set function for backgroundColor
    def setBackgroundColor(self, colorIn):
        self.backgroundColor = colorIn

    #Set function for transparentColor
    def setTransparentColor(self, colorIn):
        self.transparentColor = colorIn

    #Set function for roomWidth
    def setRoomWidth(self, widthIn):
        self.roomWidth = widthIn

    #Set function for roomHeight
    def setRoomHeight(self, heightIn):
        self.roomHeight = heightIn

    #Set function for fileName
    def setFileName(self, nameIn):
        self.fileName = nameIn

    #Set function for folderName
    def setFolderName(self, nameIn):
        self.folderName = nameIn

    #Function to add an object to the end of "objects"
    def addObject(self, objectIn):
        self.objects.append(objectIn)

    #Function to return the object at a given index of "objects"
    def getObject(self, index):
        return self.objects[index]

    #Get function for backgroundColor
    def getBackgroundColor(self):
        return self.backgroundColor

    #Get function for transparentColor
    def getTransparentColor(self):
        return self.transparentColor

    #Get function for roomWidth
    def getRoomWidth(self):
        return self.roomWidth

    #Get function for roomHeight
    def getRoomWidth(self):
        return self.roomHeight

    #Get function for fileName
    def getFileName(self):
        return self.fileName

    #Get function for folderName
    def getFolderName(self):
        return self.folderName

    #Makes a directory with the name folderName, if one doesn't already exist
    def makeFolder(self):
        try:
            os.makedirs(self.folderName)
        except OSError as exception:
            if exception.errno != errno.EEXIST:
                raise

    #Builds images of the objects in "objects" based on their appearance lists
    def buildImages(self):
        for obj in self.objects:
            w = obj.getWidth()
            h = obj.getHeight()
            tempImage = Image.new('RGB', (w,h))
            pixels = tempImage.load()
            for y in range(h):
                for x in range(w):
                    pixels[x,y] = obj.getAppearance((y * w) + x)
            tempImage.save(self.folderName +
                           "/" +
                           str(obj.getIdentifier()) +
                           "_" +
                           self.fileName +
                           ".png")

#A class describing any object that can be displayed on the screen
class Object:
    #MEMBER VARIABLES
        # width - the width of the object, in pixels
        # height - the height of the object, in pixels
        # pos - the coordinates of the top-left point of the object, referenced
        #       from the top left of the room
        # appearance - a list of (width * height) elements, describing the
        #              color of each pixel in the object.  Used mainly to build
        #              the image, but also if the image is edited down the line
        # isVisible - A boolean describing whether or not the object should be
        #             displayed visibly on the screen
        # image - an image representing the appearance list
        # identifier - an integer representing the object.  Each object should
        #              have a unique id, counting up from 1

    #Default constructor
    def __init__(self):
        self.width = 0
        self.height = 0
        self.pos = 0.0
        self.appearance = []
        self.isVisible = True
        self.identifier = 0

    #Constructor Method
    def __init__(self, width, height, pos, appearance, id):
        self.width = width
        self.height = height
        self.pos = pos
        self.appearance = appearance
        self.isVisible = True
        self.identifier = id

    #Get function for width
    def getWidth(self):
        return self.width

    #Get function for height
    def getHeight(self):
        return self.height

    #Get function for pos
    def getPos(self):
        return self.pos

    #Get function for isVisible
    def getIsVisible(self):
        return self.isVisible

    #Get function for identifier
    def getIdentifier(self):
        return self.identifier

    #Function to return the color at a given index of "appearance"
    def getAppearance(self, index):
        return self.appearance[index]

def fileInput(sim):
    sim.makeFolder()
    data = open(sim.getFileName(), 'rb')
    reader = csv.reader(data)
    rowNum = 0
    numObjects = 0
    objectIn = 0
    objHeight = 0
    objPos = 0
    pixels = []
    pixelsRemaining = -1
    readyToPlay = False

    for row in reader: #Defines the current row
        #Gets header data
        if (rowNum == 0):
            sim.setRoomWidth(int(row[0]))
            sim.setRoomHeight(int(row[1]))
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
                if (len(row) == 1):
                    pixelColor = (int(row[0]), int(row[0]), int(row[0]))
                else:
                    pixelColor = (int(row[0]), int(row[1]), int(row[2]))
                pixels.append(pixelColor)
                if (pixelsRemaining > 1):
                    pixelsRemaining -= 1
                else:
                    pixelsRemaining = -1
                    appearance = pixels[:]
                    sim.objects.append(Object(objWidth,
                                          objHeight,
                                          objPos,
                                          appearance,
                                          (objectIn + 1)))
                    objectIn += 1
                    del pixels[:]
            rowNum += 1

        #All objects are now read in
        else:
            readyToPlay = True

        if (readyToPlay):
            data.close()
            return rowNum

def playVideo(nextLine):
    print"Video would be played here."

def main():
    simulation = Room()
    if (len(sys.argv) == 2):
        simulation.setFileName(sys.argv[1])
        tempName = ""
        for char in sys.argv[1]:
            if (char == '.'):
                tempName += "_"
            else:
                tempName += char
        simulation.setFolderName(tempName)
    nextLine = fileInput(simulation)
    simulation.buildImages()
    playVideo(nextLine)
    #window = _tkinter.Canvas(root, width = roomWidth, height = roomHeight)

main()