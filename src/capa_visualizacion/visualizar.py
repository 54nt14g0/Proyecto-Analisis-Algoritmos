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

# Añadir columna de lenguaje
df_c['Language'] = 'C++'
df_python['Language'] = 'Python'

# Crear dos DataFrames separados por lenguaje
df_c['Size_Language'] = df_c['Size']
df_python['Size_Language'] = df_python['Size']

# Pivotar cada DataFrame para tener los algoritmos como columnas
pivot_df_c = df_c.pivot_table(values='Time', index='Size_Language', columns='Algorithm')
pivot_df_python = df_python.pivot_table(values='Time', index='Size_Language', columns='Algorithm')

# Crear los subplots
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 7), sharey=True)  # Dos gráficos en una fila

# Graficar los tiempos de ejecución en Python
pivot_df_python.plot(kind='bar', ax=ax1, color=plt.cm.Paired.colors)
ax1.set_title('Tiempos de Ejecución en Python', fontsize=14)
ax1.set_xlabel('Tamaño de la Matriz', fontsize=12)
ax1.set_ylabel('Tiempo de Ejecución (segundos)', fontsize=12)
ax1.legend(title='Algoritmo', bbox_to_anchor=(1.05, 1), loc='upper left')

# Graficar los tiempos de ejecución en C++
pivot_df_c.plot(kind='bar', ax=ax2, color=plt.cm.Paired.colors)
ax2.set_title('Tiempos de Ejecución en C++', fontsize=14)
ax2.set_xlabel('Tamaño de la Matriz', fontsize=12)
ax2.legend(title='Algoritmo', bbox_to_anchor=(1.05, 1), loc='upper left')

# Ajustar el layout para que los gráficos no se solapen
plt.tight_layout()

# Mostrar los gráficos
plt.show()
