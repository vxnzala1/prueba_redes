🎮 **4 en Raya por Terminal: Multijugador por Socket** 🎮

💡 **Descripción**
Juego clásico de 4 en raya adaptado para ser jugado por terminal. Cuenta con un cliente y un servidor que permiten a dos jugadores enfrentarse en tiempo real. Mientras un jugador realiza su movimiento, el otro espera su turno. ¡Prepárate para una experiencia desafiante!

🔧 **Configuración Inicial**
- Configura tu entorno de desarrollo para ejecutar aplicaciones por terminal.
- Establece la conexión por sockets para permitir la comunicación entre el cliente y el servidor.

🖥️ **Jugando por Terminal**
- El juego se ejecuta completamente por terminal.
- Un jugador actuará como servidor, esperando las conexiones entrantes, y el otro como cliente, que enviará y recibirá datos del servidor.
- La interfaz mostrará el tablero de juego y las indicaciones para realizar cada movimiento.

🔄 **Funciones Principales**
- `iniciarJuego()`: Inicia una nueva partida y establece quién comienza primero.
- `comprobarFilasColumnas()`: Verifica las filas y columnas para detectar si algún jugador ha conseguido 4 en raya.
- Posteriormente, el programa verifica automáticamente si hay un ganador o si se ha producido un empate.

🔗 **Conexión Cliente-Servidor**
- El servidor espera a que el cliente se conecte para empezar la partida.
- Una vez conectados, el cliente y el servidor se comunican entre sí enviando y recibiendo movimientos y actualizaciones del estado del juego.

🎉 **Final del Juego**
- Al detectar un ganador o un empate, el juego muestra un mensaje por terminal anunciando el resultado.
- Los jugadores tienen la opción de iniciar una nueva partida o finalizar el juego.

📝 **Notas**
- ¡Diviértete y que gane el mejor!

😄 ¡Espero que disfrutes de este clásico juego adaptado para terminal! 🌟
