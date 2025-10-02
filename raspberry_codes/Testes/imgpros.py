import cv2
import numpy as np

def processing(img):
    hh,ww = img.shape[:2]
    new_img = img.copy()
    new_img = cv2.cvtColor(new_img,cv2.COLOR_BGR2HLS)

    #Increassing Saturation
    for i in range(hh):
        for j in range(ww):
            h,l,s = new_img[i,j]
            if(l>220):
                new_img[i,j]=(h,255,s)
            else:
                new_img[i,j]=(h,l/2,s)

    new_img = cv2.cvtColor(new_img,cv2.COLOR_HLS2BGR)
    new_img = cv2.cvtColor(new_img,cv2.COLOR_BGR2GRAY)

    for i in range(hh):
        for j in range(ww):
            g = new_img[i,j]
            if g >= 200:
                g = 255
                new_img[i,j]=g
            elif g < 100:
                new_img[i,j]=0
                
    edges = new_img.copy()

    edges = cv2.Canny(edges,400,400)
    return edges,new_img