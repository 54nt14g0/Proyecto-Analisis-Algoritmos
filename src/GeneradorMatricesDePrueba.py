import numpy as np
import os

# Función para generar matrices de tamaño n x n con números de al menos 6 dígitos
def generar_matriz(n):
    return np.random.randint(100000, 999999, size=(n, n))

# Función para guardar la matriz en un archivo .txt en la ruta especificada
def guardar_matriz(matriz, nombre_archivo):
    np.savetxt(nombre_archivo, matriz, fmt='%d')
    print(f"Matriz guardada en {nombre_archivo}")

# Función para generar y guardar 10 pares de matrices de prueba en la ruta especificada
def generar_casos_prueba():
    # Lista de tamaños de matrices (n donde n es múltiplo de 2n)
    tamanos = [2, 4, 8, 16, 32, 64, 128, 256]
    
    # Ruta donde se guardarán los archivos
    ruta_guardado = r"C:\Users\ljane\Downloads\Proyecto-Analisis-Algoritmos"
    
    # Crear la carpeta si no existe
    if not os.path.exists(ruta_guardado):
        os.makedirs(ruta_guardado)
    
    # Generar y guardar cada matriz de prueba
    for n in tamanos:
        # Generar dos matrices para cada tamaño
        matriz_a = generar_matriz(n)
        matriz_b = generar_matriz(n)

        # Guardar las matrices en archivos
        nombre_archivo_a = os.path.join(ruta_guardado, f"matriz_a_{n}x{n}.txt")
        nombre_archivo_b = os.path.join(ruta_guardado, f"matriz_b_{n}x{n}.txt")
        
        guardar_matriz(matriz_a, nombre_archivo_a)
        guardar_matriz(matriz_b, nombre_archivo_b)

# Ejecutar la generación de matrices de prueba
generar_casos_prueba()
