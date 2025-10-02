import cv2
import numpy as np
import imgpros
#Transforma a imagem em algo legivel para o meu progama( no caso um objeto)
caminho_arquivo = "C:\\Users\\cdavi\\OneDrive\\Documentos\\PlatformIO\\Projects\\teste_semear\\raspberry_codes\\Testes\\img.jpg"
image = cv2.imread(caminho_arquivo)

if image is None:
    print("Imagem não Carregou")
else:
    #Adquire as Dimensões da imagem (altura e Largura)
    height,width = image.shape[:2]
    print(f"Altura {height}, Largura: {width}")

    #image[x,y,z] = 1 pixel, 1 pixel = (Blue, Green, Red)

    out_raw = image.copy()
   
    edges , teste = imgpros.processing(out_raw)

    lines = cv2.HoughLinesP(edges,1,(np.pi/180),100,minLineLength=100,maxLineGap=45)

    for line in lines:
        x_1,y_1,x_2,y_2 = line[0]
        cv2.line(out_raw,(x_1,y_1),(x_2,y_2),(200,0,170),4)

    cv2.imshow("Testes2", teste)
    cv2.imshow("Testes", edges)
    cv2.imshow("Teste", out_raw)
    cv2.waitKey(0)