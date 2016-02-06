import PIL

__author__ = 'Ryan Branch'
import csv
from PIL import Image, ImageTk
import os
import errno
import sys
import Tkinter
import itertools
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
    # canvas - the root's canvas, on which visuals are displayed
    # labels - a list of Tkinter Label objects stored here so that the
    #          references are saved and the images can be displayed
    #          NOTE: This is not currently in use.
    # rowNum - an integer storing the "current" row number
    # rowLen - an integer storing the number of chars in the "current" row
    # charNum - an integer storing the "current" character number
    # numRows - the total number of rows in the input file

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
        self.root.resizable(width=False, height=False)
        #self.labels = [] NOTE: This is not currently in use.
        self.rowNum = 0
        self.charNum = 0

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

    #Function to "wrap-around" any objects outside of the width-height range
    #Should be called after moving any objects.
    #NOTE: In the future, if ever dealing with particles that don't move, I
    #      should write this as a member function for objects, and call it
    #      with roomWidth and roomHeight as input values
    #      This would be more efficient as long as not everything is moving
    #      Honestly should rewrite this very soon whenever I get the chance
    #NOTE: When dealing with any networks/lines connecting 2 objects, this
    #      could become an issue. Be careful.
    def wrapAround(self):
        for obj in self.objects:
            x = obj.getX()
            y = obj.getY()
            w = self.roomWidth
            h = self.roomHeight
            if ((x > w) or (x < 0)):
                obj.setX(x % w)
            if ((y > h) or (y < 0)):
                obj.setY(y % w)

    #Set function for rowNum
    def setRowNum(self, numIn):
        self.rowNum = numIn
        #print("Row num set to: " + str(self.rowNum))

    #Get function for rowNum
    def getRowNum(self):
        return self.rowNum

    #Set function for rowLen
    def setRowLen(self, lenIn):
        self.rowLen = lenIn
        #print("Row len set to: " + str(self.rowLen))

    #Get function for rowLen
    def getRowLen(self):
        return self.rowLen

    #Set function for charNum
    def setCharNum(self, numIn):
        self.charNum = numIn
        #print("Char num set to: " + str(self.charNum))

    #Get function for charNum
    def getCharNum(self):
        return self.charNum

    #Set function for numRows
    def setNumRows(self, numIn):
        self.numRows = numIn
        #print("num rows set to: " + str(self.numRows))

    #Get function for numRows
    def getNumRows(self):
        return self.numRows

    #Updates charNum based on input row
    def updateCharNum(self, rowIn):
        for row in rowIn:
            self.charNum += len(row)


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

    #Set function for canvas
    def setCanvas(self, canvasIn):
        self.canvas = canvasIn

    #Get function for canvas
    def getCanvas(self):
        return self.canvas

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
        #       NOTE: If either x or y go outside of the width or height range,
        #             they should "wrap around"
        # newPos - the coordinates of the next position of the object
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
        self.pos = [0, 0]
        self.newPos = self.pos
        self.appearance = []
        self.isVisible = True
        self.identifier = 0
        self.image = ImageTk.PhotoImage(image=None)

    #Constructor Method
    def __init__(self, width, height, pos, appearance, id):
        self.width = width
        self.height = height
        self.pos = pos
        self.newPos = pos
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

    #Set function for pos
    def setPos(self, posIn):
        self.pos[0] = posIn[0]
        self.pos[1] = posIn[1]

    #Get function for newPos
    def getNewPos(self):
        return self.newPos

    #Set function for newPos
    def setNewPos(self, posIn):
        self.newPos[0] = posIn[0]
        self.newPos[1] = posIn[1]

    #Get function for x-coordinate of pos
    def getX(self):
        return self.pos[0]

    #Set function for x-coordinate of pos
    def setX(self, xIn):
        self.pos[0] = xIn

    #Get function for y-coordinate of pos
    def getY(self):
        return self.pos[1]

    #Set function for y-coordinate of pos
    def setY(self, yIn):
        self.pos[1] = yIn

    #Get function for x-coordinate of newPos
    def getNewX(self):
        return self.newPos[0]

    #Set function for x-coordinate of newPos
    def setNewX(self, xIn):
        self.newPos[0] = xIn

    #Get function for y-coordinate of newPos
    def getNewY(self):
        return self.newPos[1]

    #Set function for y-coordinate of newPos
    def setNewY(self, yIn):
        self.newPos[1] = yIn

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
    numObjects = 0
    objectIn = 0
    objHeight = 0
    objPos = 0
    pixels = []
    pixelsRemaining = -1
    readyToPlay = False
    #sim.setNumRows(len(list(reader)))

    for row in reader: #Defines the current row
        #Gets header data
        if (sim.getRowNum() == 0):
            sim.setRoomWidth(int(row[0]))
            sim.setRoomHeight(int(row[1]))
            numObjects = int(row[2]) #Crash if this isn't 1 or more
            sim.setRowNum(sim.getRowNum() + 1)
            sim.updateCharNum(row)
        #Reads in objects
        elif (objectIn < numObjects):
            if (pixelsRemaining == -1):
                objWidth = int(row[0])
                objHeight = int(row[1])
                objPos = [int(row[2]), int(row[-1])]
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
            sim.setRowNum(sim.getRowNum() + 1)
            sim.updateCharNum(row)

        #All objects are now read in
        else:
            readyToPlay = True

        if (readyToPlay):
            data.close()
            return

def motionHandler(event, sim):
    data = open(sim.getFileName(), 'rb')
    reader = csv.reader(data)
    try:
        row = (itertools.islice(reader, (sim.getRowNum()), None)).next()
    except StopIteration:
        print("Reached end of file.")
    for i in range((len(row) / 2)):
        sim.objects[i].setNewPos([int(row[i]), int(row[i + 1])])
        #sim.objects[]
    if (event.keysym == 'Up'):
        for obj in sim.getObjects():
            obj.setX(obj.getNewX())
            obj.setY(obj.getNewY())
            obj.getLabel().place(x=obj.getX(),
                                 y=obj.getY(),
                                 width=obj.getWidth(),
                                 height=obj.getHeight())
    sim.setRowNum(sim.getRowNum() + 1)
    sim.wrapAround()
    data.close()

def playVideo(sim):
    def handler(event, sim=sim):
            return motionHandler(event, sim)
    sim.getCanvas().focus_set()
    print("Set the focus")
    sim.getRoot().bind("<Key>", handler)
    print("Bound the key")
    #sim.getCanvas().pack(expand=1) NOTE: this line useless?
    sim.getRoot().mainloop()
    print"Video would be played here."

def key(event=None):
    print("pressed", repr(event.char))

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
    simulation.setCanvas(Tkinter.Canvas(simulation.getRoot(),
                                        width=simulation.getRoomWidth(),
                                        height=simulation.getRoomHeight()))
    simulation.getRoot().geometry(str(simulation.getRoomWidth()) +
                                  "x" +
                                  str(simulation.getRoomHeight()))

    for obj in simulation.getObjects():
        """
        This code appears to be unnecessary for now, but I'm new to PIL and
        Tkinter so I'm leaving it in as a reference to myself for later use

        simulation.getCanvas().create_image(obj.getX(),
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