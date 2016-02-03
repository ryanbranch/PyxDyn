import PIL

__author__ = 'Ryan Branch'
import csv
from PIL import Image, ImageTk
import os
import errno
import sys
import Tkinter
#from Tkinter import *

#Some global constants are defined here
BACKGROUND_COLOR = (255, 255, 255)

#A class containing various variables central to the entire program
class Room:
    #MEMBER VARIABLES
    # backgroundColor - the RGB value of the color of the room's background
    # transparentColor - the RGB value to be treated as transparent
    # roomWidth - the width of the room, in pixels
    # roomHeight - the height of the room, in pixels
    # fileName - the name of the file being used for simulation input
    # folderName - the name of the folder in which to store data such as images
    # objects - a list containing all of the objects
    # root - Tk root widget for the program
    # room - the root's canvas, on which visuals are displayed
    # labels - a list of Tkinter Label objects stored here so that the
    #          references are saved and the images can be displayed
    #          NOTE: This is not currently in use.

    #Default constructor
    def __init__(self):
        self.backgroundColor = (255, 255, 255)
        self.transparentColor = (255, 254, 253)
        self.roomWidth = 1024
        self.roomHeight = 768
        self.fileName = "input.csv"
        self.folderName = "input_csv"
        self.objects = []
        self.root = Tkinter.Tk()
        self.root.resizable(0,0)
        #self.labels = [] NOTE: This is not currently in use.

    """
    #Wrote this first but I'm thinking of just keeping the labels as a member
     variable of the "object" class instead.

    #Function to add a label to the end of "labels"
    def addLabel(self, labelIn):
        self.labels.append(labelIn)

    #Function to return the label at a given index of "labels"
    def getLabel(self, index):
        return self.labels[index]
    """

    #Set function for backgroundColor
    def setBackgroundColor(self, colorIn):
        self.backgroundColor = colorIn

    #Get function for backgroundColor
    def getBackgroundColor(self):
        return self.backgroundColor

    #Set function for transparentColor
    def setTransparentColor(self, colorIn):
        self.transparentColor = colorIn

    #Get function for transparentColor
    def getTransparentColor(self):
        return self.transparentColor

    #Set function for roomWidth
    def setRoomWidth(self, widthIn):
        self.roomWidth = widthIn

    #Get function for roomWidth
    def getRoomWidth(self):
        return self.roomWidth

    #Set function for roomHeight
    def setRoomHeight(self, heightIn):
        self.roomHeight = heightIn

    #Get function for roomHeight
    def getRoomHeight(self):
        return self.roomHeight

    #Set function for fileName
    def setFileName(self, nameIn):
        self.fileName = nameIn

    #Get function for fileName
    def getFileName(self):
        return self.fileName

    #Set function for folderName
    def setFolderName(self, nameIn):
        self.folderName = nameIn

    #Get function for folderName
    def getFolderName(self):
        return self.folderName

    #Set function for room
    def setRoom(self, roomIn):
        self.room = roomIn

    #Get function for room
    def getRoom(self):
        return self.room

    #Function to add an object to the end of "objects"
    def addObject(self, objectIn):
        self.objects.append(objectIn)

    #Function to return the object at a given index of "objects"
    def getObject(self, index):
        return self.objects[index]

    #Function to return the entire "objects" list
    def getObjects(self):
        return self.objects

    #Get function for root
    def getRoot(self):
        return self.root

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
            tempImage = PIL.Image.new('RGB', (w,h))
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
            obj.image = ImageTk.PhotoImage(tempImage)

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
        # label - a Tkinter Label object used to keep a reference to the image
    #Default constructor
    def __init__(self):
        self.width = 0
        self.height = 0
        self.pos = 0.0
        self.appearance = []
        self.isVisible = True
        self.identifier = 0
        self.image = ImageTk.PhotoImage(image=None)

    #Constructor Method
    def __init__(self, width, height, pos, appearance, id):
        self.width = width
        self.height = height
        self.pos = pos
        self.appearance = appearance
        self.isVisible = True
        self.identifier = id
        #HEREHER

        #im = Image.open("input_csv/1_input.csv.png")
        #self.image = ImageTk.PhotoImage(im)

    #Get function for label
    def getLabel(self):
        return self.label

    #Set function for label
    def setLabel(self, labelIn):
        self.label = labelIn

    #Get function for image
    def getImage(self):
        return self.image

    #Get function for width
    def getWidth(self):
        return self.width

    #Get function for height
    def getHeight(self):
        return self.height

    #Get function for pos
    def getPos(self):
        return self.pos

    #Get function for x-coordinate of pos
    def getX(self):
        return self.pos[0]

    #Get function for y-coordinate of pos
    def getY(self):
        return self.pos[1]

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
                    sim.addObject(Object(objWidth,
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

def playVideo(sim):

    sim.getRoot().mainloop()
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

    fileInput(simulation)

    simulation.buildImages()
    simulation.getRoot().wm_title(simulation.getFileName())
    simulation.setRoom(Tkinter.Canvas(simulation.getRoot(),
                                      width=simulation.getRoomWidth(),
                                      height=simulation.getRoomHeight()))
    for obj in simulation.getObjects():
        """
        This code appears to be unnecessary for now, but I'm new to PIL and
        Tkinter so I'm leaving it in as a reference to myself for later use

        simulation.getRoom().create_image(obj.getX(),
                                          obj.getY(),
                                          anchor=Tkinter.NE,
                                          image=obj.getImage())
        """
        obj.setLabel(Tkinter.Label(simulation.getRoot(),
                                          image=obj.getImage()))
        obj.getLabel().place(x=obj.getX(),
                            y=obj.getY(),
                            width=obj.getWidth(),
                            height=obj.getHeight())

    playVideo(simulation)
main()