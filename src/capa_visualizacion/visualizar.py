import pandas as pd
import matplotlib.pyplot as plt
import re

def read_execution_times(filename):
    """Lee los tiempos de ejecución de un archivo y devuelve un DataFrame."""
    data = []
    with open(filename, 'r') as file:
        for line in file:
            # Extraer información usando expresión regular
            match = re.match(r'(.+?) para tamanio (.+?): ([0-9.]+) segundos', line.strip())
            if match:
                algorithm = match.group(1)
                size = match.group(2)
                time = float(match.group(3))
                data.append({'Algorithm': algorithm, 'Size': size, 'Time': time})
    return pd.DataFrame(data)

# Rutas de los archivos de tiempo de ejecución
file_c = r"C:\Users\ljane\Downloads\Proyecto-Analisis-Algoritmos\guardadoTiempos\tiempos_ejecucion_c.txt"
file_python = r"C:\Users\ljane\Downloads\Proyecto-Analisis-Algoritmos\guardadoTiempos\tiempos_ejecucion_python.txt"

# Leer los tiempos de ejecución
df_c = read_execution_times(file_c)
df_python = read_execution_times(file_python)

# Verificar los datos leídos
print("Datos de C++:")
print(df_c)
print("\nDatos de Python:")
print(df_python)

# Añadir columna de lenguaje
df_c['Language'] = 'C++'
df_python['Language'] = 'Python'

# Combinar ambos DataFrames
combined_df = pd.concat([df_c, df_python], ignore_index=True)

# Crear una columna combinada para el tamaño y el lenguaje
combined_df['Size_Language'] = combined_df['Size'].astype(str) + ' ' + combined_df['Language']

# Ordenar el DataFrame por tamaño de matriz, de mayor a menor
def extract_size(size_str):
    """Extrae el tamaño de la matriz desde el string 'NxN'."""
    return int(size_str.split('x')[0])  # Extrae el primer número antes de 'x'

# Usar la función para ordenar el DataFrame
size_order = sorted(combined_df['Size'].unique(), key=extract_size, reverse=True)  
combined_df['Size'] = pd.Categorical(combined_df['Size'], categories=size_order, ordered=True)

# Asegurarse de que la columna Size_Language se construya después de categorizar el tamaño
combined_df['Size_Language'] = combined_df['Size'].astype(str) + ' ' + combined_df['Language']

# Pivotar el DataFrame para tener tamaños y lenguajes como índices
pivot_df = combined_df.pivot_table(values='Time', index='Size_Language', columns='Algorithm')

# Graficar los tiempos de ejecución
fig, ax = plt.subplots(figsize=(12, 8))
pivot_df.plot(kind='bar', ax=ax)

# Añadir título y etiquetas
ax.set_title('Comparación de Tiempos de Ejecución de Algoritmos en C++ y Python', fontsize=16)
ax.set_xlabel('Tamaño de la Matriz y Lenguaje', fontsize=14)
ax.set_ylabel('Tiempo de Ejecución (segundos)', fontsize=14)
ax.legend(title='Algoritmo', bbox_to_anchor=(1.05, 1), loc='upper left')

# Ajustar el layout
plt.tight_layout()
plt.show()
