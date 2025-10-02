import cv2
import numpy as np
import imgpros
#Transforma a imagem em algo legivel para o meu progama( no caso um objeto)
caminho_arquivo = "C:\\Users\\cdavi\\OneDrive\\Documentos\\PlatformIO\\Projects\\teste_semear\\raspberry_codes\\Testes\\image.png"
#image = cv2.imread(caminho_arquivo)
cap = cv2.VideoCapture(0)
while(1):
    ret, image = cap.read()
    if image is None:
        print("Imagem não Carregou")
    else:
        #Adquire as Dimensões da imagem (altura e Largura)
        height,width = image.shape[:2]
        print(f"Altura {height}, Largura: {width}")


        out_raw = image.copy()
    
        edges , teste = imgpros.processing(out_raw)

        lines = cv2.HoughLinesP(edges,1,(np.pi/180),100,minLineLength=100,maxLineGap=45)
        try:
            for line in lines:
                x_1,y_1,x_2,y_2 = line[0]
                cv2.line(out_raw,(x_1,y_1),(x_2,y_2),(200,0,170),4)
        except Exception as e:
            print(e)

        cv2.imshow("Testes2", teste)
        cv2.imshow("Testes", edges)
        cv2.imshow("Teste", out_raw)
        k = cv2.waitKey(30) & 0xff
        if k == 27:
            break

# Close the window
cap.release()
# De-allocate any associated memory usage
cv2.destroyAllWindows()