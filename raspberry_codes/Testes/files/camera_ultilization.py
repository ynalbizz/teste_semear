# OpenCV program to detect face in real time
# import libraries of python OpenCV
# where its functionality resides
import cv2

# capture frames from a camera
cap = cv2.VideoCapture(0)
test_cascade = cv2.CascadeClassifier("")

# loop runs if capturing has been initialized.
while 1:
    # reads frames from a camera
    ret, img = cap.read()
    cv2.imshow('img',img)

    # Wait for Esc key to stop
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

# Close the window
cap.release()
# De-allocate any associated memory usage
cv2.destroyAllWindows()