__author__ = 'Ryan Branch'
import csv
import Image
import os
import errno
import _tkinter

#Some global constants are defined here
BACKGROUND_COLOR = (255, 255, 255)

#Some global variables are defined here
roomWidth = 0
roomHeight = 0
folderName = ""
objects = []
#root = _tkinter.Tk()

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
        # id - an integer representing the object.  Each object should
        #      have a unique id, counting up from 1

    #Default constructor
    def __init__(self):
        self.width = 0
        self.height = 0
        self.pos = 0.0
        self.appearance = []
        self.isVisible = True
        self.id = 0

    #Constructor Method
    def __init__(self, width, height, pos, appearance, identifier):
        self.width = width
        self.height = height
        self.pos = pos
        self.appearance = appearance
        self.isVisible = True
        self.id = id

    #Used to build an image of the object based on the appearance list
    def buildImage(self):
        print len(self.appearance)
        for test in self.appearance:
            print test
        tempImage = Image.new('RGB', (self.width, self.height))
        pixels = tempImage.load()
        for y in range(self.height):
            for x in range(self.width):
                pixels[x,y] = self.appearance[(y * self.width) + x]
        tempImage.save("test_csv" + "/test.png")
        print("image saved.")

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

def checkPath(path):
    try:
        os.makedirs(path)
    except OSError as exception:
        if exception.errno != errno.EEXIST:
            raise

def fileInput():
    #filename = raw_input('Enter filename, including extension.')
    filename = "test.csv"
    nameOfFolder = ""
    for char in filename:
        if (char == '.'):
            nameOfFolder += "_"
        else:
            nameOfFolder += char
    folderName = nameOfFolder
    checkPath(folderName)
    data = open(filename, 'rb')
    reader = csv.reader(data)
    print ("unique message")
    rowNum = 0
    numObjects = 0
    objectIn = 0
    objHeight = 0
    objPos = 0
    pixels = []
    pixelsRemaining = -1
    readyToPlay = False

    for row in reader: #Defines the current row
        print("objectIn: " + str(objectIn))
        print("numObjects: " + str(numObjects))
        print("row: " + str(rowNum))
        #Gets header data
        if (rowNum == 0):
            roomWidth = int(row[0])
            roomHeight = int(row[1])
            numObjects = int(row[2]) #Crash if this isn't 1 or more
            rowNum += 1

        #Reads in objects
        elif (objectIn < numObjects):
            print("pixels remaining: " + str(pixelsRemaining))
            if (pixelsRemaining == -1):
                objWidth = int(row[0])
                objHeight = int(row[1])
                print("setting width and height to " + str(objHeight) + ", " + str(objWidth))
                objPos = (int(row[2]), int(row[-1]))
                pixelsRemaining = objWidth * objHeight
            else:
                pixelColor = (int(row[0]), int(row[1]), int(row[2]))
                pixels.append(pixelColor)
                if (pixelsRemaining > 1):
                    pixelsRemaining -= 1
                else:
                    pixelsRemaining = -1
                    appearance = pixels[:]
                    objects.append(Object(objWidth,
                                          objHeight,
                                          objPos,
                                          appearance,
                                          (objectIn + 1)))
                    print("FINISHED MAKING OBJECT")
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
    buildImages(objects)

def buildImages(objList):
    for obj in objList:
        obj.buildImage()
    objList[0].buildImage()

def main():
    nextLine = fileInput()
    playVideo(nextLine)
    #window = _tkinter.Canvas(root, width = roomWidth, height = roomHeight)

main()