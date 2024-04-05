// Define os números dos pinos para LEDs, buzzer e LDR (Sensor de Luz Dependente)
int redLed = 2;
int yellowLed = 3;
int greenLed = 4;
int buzzer = 5;
int LDR = A0;

// Define valores de limiar para diferentes níveis de luz
// Esses valores são baseados em leituras analógicas do LDR
// Ajuste esses valores de acordo com o seu LDR específico e condições de luz ambiente
// Valores de exemplo são fornecidos para referência
// Modifique esses valores conforme necessário para sua aplicação
const int DEZ_PORCENTO = 411;
const int QUINZE_PORCENTO = 445;
const int VINTE_CINCO_PORCENTO = 512;
const int TRINTA_PORCENTO = 547;

void setup() {
    // Inicializa os modos dos pinos para LEDs e buzzer
    pinMode(redLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(buzzer, OUTPUT);
  
    // Inicializa a comunicação serial para depuração (opcional)
    Serial.begin(9600);
}

void loop(){
    // Verifica continuamente os níveis de luz
    checkLight();
}

void checkLight() {
    // Lê o valor analógico do LDR
    int lightLevel = analogRead(LDR);
    
    // Imprime o nível de luz para depuração (opcional)
    Serial.println(lightLevel);
  
    // Determina a ação apropriada com base no nível de luz
    if (lightLevel >= QUINZE_PORCENTO && lightLevel <= VINTE_CINCO_PORCENTO) {
        // O nível de luz está dentro da faixa aceitável
        okLight();
    }
    else if ((lightLevel > DEZ_PORCENTO && lightLevel < QUINZE_PORCENTO) ||
             (lightLevel > VINTE_CINCO_PORCENTO && lightLevel < TRINTA_PORCENTO)){
        // O nível de luz está na faixa de advertência
        warningLight();
    }
    else {
        // O nível de luz está na faixa de perigo
        dangerLight();
    }
}

void okLight(){
    // Se o LED verde não estiver ligado, define o ambiente seguro
    if (digitalRead(greenLed) == LOW) {
        safeAmbient();
    }
    delay(1000); // Atraso para estabilidade
}

void warningLight(){
    // Se o LED amarelo não estiver ligado, define o ambiente de aviso
    if (digitalRead(yellowLed) == LOW) {
        warningAmbient();
    }
    // Ativa o buzzer para indicação de aviso
    tone(buzzer, 400);
    delay(3000); // Ativa o buzzer por 3 segundos
    noTone(buzzer); // Desliga o buzzer
    delay(1000); // Atraso para estabilidade
}

void dangerLight(){
    // Se o LED vermelho não estiver ligado, define o ambiente de perigo
    if (digitalRead(redLed) == LOW) {
        dangerAmbient();
    }
    // Ativa o buzzer para indicação de perigo
    tone(buzzer, 200);
    delay(3000); // Ativa o buzzer por 3 segundos
    noTone(buzzer); // Desliga o buzzer
    delay(1000); // Atraso para estabilidade
}

void safeAmbient (){
    // Define LEDs para o ambiente seguro
    ambientChange(redLed, yellowLed, greenLed);
}

void warningAmbient (){
    // Define LEDs para o ambiente de aviso
    ambientChange(redLed, greenLed, yellowLed);
}

void dangerAmbient (){
    // Define LEDs para o ambiente de perigo
    ambientChange(yellowLed, greenLed, redLed);
}

void ambientChange(int lowLed1, int lowLed2, int highLed){
    // Desliga LEDs de baixa intensidade e liga o LED de alta intensidade
    digitalWrite(lowLed1, LOW);
    digitalWrite(lowLed2, LOW);
    digitalWrite(highLed, HIGH);
}