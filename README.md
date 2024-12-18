# Cub3D

El proyecto **Cub3D** forma parte del currículo de 42 y está diseñado como una introducción práctica al desarrollo de gráficos 3D. Inspirado en el clásico juego *Wolfenstein 3D*, este proyecto tiene como objetivo crear un motor gráfico básico en 2D/3D utilizando raycasting.

---

## 🚀 Descripción del Proyecto

Cub3D es un proyecto de gráficos en C que simula una vista tridimensional en un entorno bidimensional utilizando la técnica de **raycasting**. Los jugadores pueden navegar por un mapa predefinido, y la aplicación renderiza paredes y espacios abiertos en tiempo real.

---

## 🔧 Requisitos

- **Librería miniLibX**: Se utiliza para manejar la ventana, eventos y gráficos 2D.
- **Entorno**: Linux o MacOS.
- **Lenguaje**: C.
- **Herramientas adicionales**: `gcc` para la compilación.

---

## 📁 Estructura del Proyecto

```plaintext
cub3d/
├── srcs/           # Código fuente principal
├── includes/       # Archivos de cabecera
├── maps/           # Mapas de ejemplo
├── textures/       # Texturas usadas en el renderizado
├── Makefile        # Sistema de compilación
└── README.md       # Documentación
```

---

## 🛠️ Uso

1. Clona el repositorio:
   ```bash
   git clone https://github.com/cacharri/cub3d.git
   cd cub3d
   ```

2. Compila el proyecto:
   ```bash
   make
   ```

3. Ejecuta el juego con un mapa:
   ```bash
   ./cub3d maps/example_map.cub
   ```

4. Usa las teclas de movimiento para explorar el mapa:
   - **W, A, S, D**: Movimiento.
   - **Flechas izquierda/derecha**: Rotación de la cámara.
   - **ESC**: Salir del juego.

---

## 🌟 Características

- Renderizado en tiempo real utilizando raycasting.
- Soporte para texturas personalizadas.
- Mapas configurables mediante archivos `.cub`.
- Manejo de eventos de teclado para movimiento y rotación.

---

## 🧪 Testing

Prueba el proyecto con diferentes mapas personalizados:

1. Crea un mapa personalizado en el formato `.cub` siguiendo las reglas del proyecto.
2. Ejecuta el juego con tu mapa:
   ```bash
   ./cub3d maps/mi_mapa.cub
   ```
3. Asegúrate de probar escenarios como:
   - Mapas cerrados y sin errores.
   - Mapas con texturas personalizadas.
   - Mapas que incluyan elementos complejos como espacios abiertos y pasillos estrechos.

---
