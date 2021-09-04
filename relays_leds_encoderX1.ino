// El programa fue diseñado para un Arduino Nano (100% compatible con Arduino Uno). El encoder está conectado a las patillas 2 y 3 del Arduino Uno/Nano que se corresponde con el puerto D,
// y éste será leído de forma paralela. Para cualquier otro Arduino que no sea Nano ni Uno habría que modificar la parte del programa que decodifica el encoder y el patillaje del
// conexionado del enconder. El resto de patillas (para los leds y los relés) no son críticas siempre y cuando sepas lo que estás haciendo.


int           enc = 0, aux = 0;                // Variables para decodificar el encoder.
int           x = 3;                           // Variable para conocer la posición del encoder. Lo incializamos con el valor "3" para que se corresponda con la posición real del encoder.
long          pause = 0;                       // Variable contador que usaremos como temporizador.
boolean       push0 = false, push1 = false, push2 = false, push3 = false; // Variables booleanas (inicialmente todas "off") para los 4 relés.


void setup() {
    pinMode(A0, OUTPUT);                       // Salida del relé 0.
    pinMode(A1, OUTPUT);                       // Salida del relé 1.
    pinMode(A2, OUTPUT);                       // Salida del relé 2.
    pinMode(A3, OUTPUT);                       // Salida del relé 3.
    pinMode(8,  OUTPUT);                       // Salida del led 0.
    pinMode(9,  OUTPUT);                       // Salida del led 1.
    pinMode(10, OUTPUT);                       // Salida del led 2.
    pinMode(11, OUTPUT);                       // Salida del led 3.
    pinMode(2,  INPUT_PULLUP);                 // Entrada encoder A
    pinMode(3,  INPUT_PULLUP);                 // Entrada encoder B
    pinMode(4,  INPUT_PULLUP);                 // Entrada pulsador del encoder, o un pulsador normalmente abierto que lo equivalga.
}


void loop() {
     aux = enc;                                // En "aux" se guarda la posición del encoder como valor pasado y así poder notar los cambios producidos en el tiempo.
     enc = PIND & 12;                          // El encoder se lee de forma paralela (no como bits por separado). Se hace un enmascaramiento de los bits 2 y 3 (00001100 = 12).
     
     if ((aux == 12) && (enc == 8))  { x--; }  // Decodificador de enconder x1.
     if ((aux == 8)  && (enc == 12)) { x++; }

     if(x > 3) x = 3;                          // Limitamos a 4 posiciones, de la 0 a la 3.
     if(x < 0) x = 0;

     
     if(!digitalRead(4)) {                     // Si pulsamos el pulsador del encoder, comprueba en qué posición está el encoder y en función de esa posición activa/desactiva    
        delay(100);                            // una de las cuatro variables booleanas "push0..3". Sólo permite activar/desactivar una a la vez. Utilizamos lógica inversa para leer el pulsador.
        if(digitalRead(4)) {                   // Al pulsar se ejecuta una pequeña demora que sirve como antirrevotes y al soltar se activa/desactiva la variable booleana correspondiente.
           if (x == 0) { push0 = !push0; push1 = false; push2 = false; push3 = false; }
           if (x == 1) { push1 = !push1; push0 = false; push2 = false; push3 = false; }
           if (x == 2) { push2 = !push2; push0 = false; push1 = false; push3 = false; }
           if (x == 3) { push3 = !push3; push0 = false; push1 = false; push2 = false; }
        }
     }
     
     
     pause++;
     if(pause > 10000) pause = 0;              // El contador depende de los ciclos ejecutados (cada vez que pase por aquí) y lo usaremos como temporizador;
                                               // de 0 a 5000 apagar (250 ms aprox.); y de 5000 a 10000 encender (250 ms aprox.); más adelante se verá esto. Aquí sólo limitamos el valor máximo de conteo.
     
     if(push0 && (x == 0)) {                   // Activa el led 0 de forma permanente si push0=on y el encoder se encuentra en la posición 0, y apaga el resto de leds.
        digitalWrite(9,  LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(8, HIGH);
     } 
     else                                      // En caso contrario activa el led 0 de forma intermitente si se cumple que el encoder se encuentra en la posición 0 del encoder.
     {
        if (x == 0){ if(pause < 5000) digitalWrite(8, LOW); else digitalWrite(8, HIGH);} else { if (!push0) digitalWrite(8, LOW); }
     }


     if(push1 && (x == 1)) {                   // Activa el led 1 de forma permanente si push1=on y el encoder se encuentra en la posición 1, y apaga el resto de leds.
        digitalWrite(8,  LOW);
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);
        digitalWrite(9, HIGH);
     }   
     else                                      // En caso contrario activa el led 1 de forma intermitente si se cumple que el encoder se encuentra en la posición 1 del encoder.
     {
        if (x == 1){ if(pause < 5000) digitalWrite(9, LOW); else digitalWrite(9, HIGH);} else { if (!push1) digitalWrite(9, LOW); }
     }


     if(push2 && (x == 2)) {                   // Activa el led 2 de forma permanente si push2=on y el encoder se encuentra en la posición 2, y apaga el resto de leds.
        digitalWrite(8,   LOW);
        digitalWrite(9,   LOW);
        digitalWrite(11,  LOW);
        digitalWrite(10, HIGH);
     }   
     else                                      // En caso contrario activa el led 2 de forma intermitente si se cumple que el encoder se encuentra en la posición 2 del encoder.
     {
        if (x == 2){ if(pause < 5000) digitalWrite(10, LOW); else digitalWrite(10, HIGH);} else { if (!push2) digitalWrite(10, LOW); }
     }


     if(push3 && (x == 3)) {                   // Activa el led 3 de forma permanente si push3=on y el encoder se encuentra en la posición 3, y apaga el resto de leds.
        digitalWrite(8,   LOW);
        digitalWrite(9,   LOW);
        digitalWrite(10,  LOW);
        digitalWrite(11, HIGH);
     }   
     else                                      // En caso contrario activa el led 3 de forma intermitente si se cumple que el encoder se encuentra en la posición 3 del encoder.
     {
        if (x == 3){ if(pause < 5000) digitalWrite(11, LOW); else digitalWrite(11, HIGH);} else { if (!push3) digitalWrite(11, LOW); }
     }


     if (push0) digitalWrite(A0, HIGH); else digitalWrite(A0, LOW); // Los valores booleanos de los "push 0..3" activan/desactivan el relé correspondiente.
     if (push1) digitalWrite(A1, HIGH); else digitalWrite(A1, LOW); // Sólo puede haber 1 activado a la vez y esto se decide arriba de este programa (después de decodificar el encoder).
     if (push2) digitalWrite(A2, HIGH); else digitalWrite(A2, LOW);
     if (push3) digitalWrite(A3, HIGH); else digitalWrite(A3, LOW);
}
