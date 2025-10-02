import cv2
import numpy as np

import cv2
import numpy as np

def processing(img):
    # 1. Converter para HLS de uma só vez (já era rápido)
    hls_img = cv2.cvtColor(img, cv2.COLOR_BGR2HLS)

    # Extrair o canal L (Luminosidade) para facilitar a manipulação
    # hls_img é um array NumPy de shape (altura, largura, 3)
    # hls_img[:, :, 1] seleciona o canal de índice 1 (L) para todos os pixels
    h_channel = hls_img[:, :, 0]
    l_channel = hls_img[:, :, 1].astype(np.float32) # Converte para float para a divisão
    s_channel = hls_img[:, :, 2]

    # 2. Otimização 1: Substituir o primeiro loop `for` por máscaras NumPy
    # Criar uma máscara booleana para pixels onde a luminosidade > 220
    mask_bright = l_channel > 220
    
    # Onde a máscara é True (l > 220), definir L para 255
    l_channel[mask_bright] = 255
    # Onde a máscara é False (l <= 220), dividir L por 2
    # O operador '~' inverte a máscara booleana
    l_channel[~mask_bright] /= 2
    
    # Remontar a imagem HLS com o canal L modificado
    # E converter de volta para inteiro de 8 bits
    final_hls = cv2.merge([h_channel, l_channel.astype(np.uint8), s_channel])

    # 3. Converter de volta para BGR e depois para GRAY (já era rápido)
    bgr_img = cv2.cvtColor(final_hls, cv2.COLOR_HLS2BGR)
    gray_img = cv2.cvtColor(bgr_img, cv2.COLOR_BGR2GRAY)

    # 4. Otimização 2: Substituir o segundo loop `for` por indexação booleana
    # Para todos os pixels com valor >= 200, atribuir 255
    gray_img[gray_img >= 200] = 255
    # Para todos os pixels com valor < 100, atribuir 0
    gray_img[gray_img < 100] = 0

    # 5. Aplicar o detector de bordas Canny (já era rápido)
    # A cópia aqui é desnecessária, Canny não modifica o array de entrada
    edges = cv2.Canny(gray_img, 400, 400)

    return edges, gray_img