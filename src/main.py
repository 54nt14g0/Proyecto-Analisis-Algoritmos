import numpy as np
import os
import time
import tkinter as tk
from tkinter import messagebox

# Ruta donde se encuentran las matrices
ruta_matrices = r"C:\Users\ljane\Downloads\Proyecto-Analisis-Algoritmos"
# Ruta donde se guardarán los tiempos de ejecución
ruta_guardado_tiempos = r"C:\Users\ljane\Downloads\Proyecto-Analisis-Algoritmos\guardadoTiempos"

# Crear la carpeta para guardar los tiempos de ejecución si no existe
if not os.path.exists(ruta_guardado_tiempos):
    os.makedirs(ruta_guardado_tiempos)

# Función para cargar matrices desde archivos .txt
def cargar_matriz(nombre_archivo):
    return np.loadtxt(nombre_archivo, dtype=int)

# Función para medir el tiempo de ejecución de un algoritmo
def medir_tiempo(funcion, *args):
    start_time = time.time()
    C = funcion(*args)  # Aquí se pasan todos los argumentos a la función
    end_time = time.time()
    return end_time - start_time

# Importar los algoritmos desde sus respectivos archivos
from naiv_on_array import naiv_on_array
from naiv_loop_unrolling_two import naiv_loop_unrolling_two
from naiv_loop_unrolling_four import naiv_loop_unrolling_four
from winograd_original import winograd_original
from winograd_scaled import winograd_scaled
from strassen_naiv import strassen_naiv
from strassen_winograd import strassen_winograd
from sequential_block_III_3 import block_matrix_mult_III_3
from sequential_block_IV_3 import block_matrix_mult_IV_3
from sequential_block_V_3 import block_matrix_mult_V_3

# Función para mostrar un mensaje en una ventana emergente
def mostrar_mensaje(titulo, mensaje):
    root = tk.Tk()
    root.withdraw()  # Ocultar la ventana principal
    messagebox.showinfo(titulo, mensaje)
    root.destroy()

# Lista de funciones y sus nombres para el registro
algoritmos = [
    (naiv_on_array, "Naive on Array", False),  # No requiere block_size
    (naiv_loop_unrolling_two, "Naive Loop Unrolling Two", False),  # No requiere block_size
    (naiv_loop_unrolling_four, "Naive Loop Unrolling Four", False),  # No requiere block_size
    (winograd_original, "Winograd Original", False),  # No requiere block_size
    (winograd_scaled, "Winograd Scaled", False),  # No requiere block_size
    (strassen_naiv, "Strassen Naive", False),  # No requiere block_size
    (strassen_winograd, "Strassen Winograd", False),  # No requiere block_size
    (block_matrix_mult_III_3, "Block Matrix Mult III.3", True),  # Requiere block_size
    (block_matrix_mult_IV_3, "Block Matrix Mult IV.3", True),  # Requiere block_size
    (block_matrix_mult_V_3, "Block Matrix Mult V.3", True)  # Requiere block_size
]

# Medir y guardar los tiempos de ejecución
with open(os.path.join(ruta_guardado_tiempos, 'tiempos_ejecucion_python.txt'), 'w') as f:
    # Recorrer los tamaños de las matrices
    tamanos = [2, 4, 8, 16, 32, 64, 128, 256]
    
    for n in tamanos:
        # Cargar las matrices A y B
        matriz_a = cargar_matriz(os.path.join(ruta_matrices, f"matriz_a_{n}x{n}.txt"))  # A
        matriz_b = cargar_matriz(os.path.join(ruta_matrices, f"matriz_b_{n}x{n}.txt"))  # B
        
        # Probar cada algoritmo
        for algoritmo, nombre, requiere_block_size in algoritmos:
            if requiere_block_size:
                tiempo_ejecucion = medir_tiempo(algoritmo, matriz_a, matriz_b, 16)  # Pasar block_size
            else:
                tiempo_ejecucion = medir_tiempo(algoritmo, matriz_a, matriz_b)  # Sin block_size
            f.write(f"{nombre} para tamaño {n}x{n}: {tiempo_ejecucion:.6f} segundos\n")
            print(f"{nombre} para tamaño {n}x{n}: {tiempo_ejecucion:.6f} segundos")  # Mostrar en consola
            
            # Mostrar ventana emergente
            mostrar_mensaje("Algoritmo Completado", f"Se ha completado el algoritmo '{nombre}' para multiplicar matrices de {n}x{n}. ¿Desea continuar con el próximo valor de n?")

print("Tiempos de ejecución guardados en", os.path.join(ruta_guardado_tiempos, 'tiempos_ejecucion.txt'))
