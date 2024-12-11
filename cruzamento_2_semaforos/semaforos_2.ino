// Definição dos pinos do semáforo
const int SEM1_VERMELHO = 7;
const int SEM1_AMARELO = 8;
const int SEM1_VERDE = 3;
const int SEM2_VERMELHO = 4;
const int SEM2_AMARELO = 5;
const int SEM2_VERDE = 6;

// Definição dos pinos do sensor ultrassônico
const int TRIG_PIN = 9; // Pino TRIG do sensor
const int ECHO_PIN = 10; // Pino ECHO do sensor

// Tempos de transição (em milissegundos)
const int TEMPO_VERDE = 5000;
const int TEMPO_AMARELO = 2500;

// Distância mínima para detecção de presença (em centímetros)
const int DISTANCIA_DETECCAO = 10;

// Variável para controlar o estado atual
int estadoAtual = 1;

void setup() {
  // Configurar todos os pinos como saída
  pinMode(SEM1_VERMELHO, OUTPUT);
  pinMode(SEM1_AMARELO, OUTPUT);
  pinMode(SEM1_VERDE, OUTPUT);
  pinMode(SEM2_VERMELHO, OUTPUT);
  pinMode(SEM2_AMARELO, OUTPUT);
  pinMode(SEM2_VERDE, OUTPUT);
  
  // Configurar os pinos do sensor ultrassônico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Inicializar a comunicação serial (opcional, para depuração)
  Serial.begin(9600);
}

void loop() {
  // Verificar a distância medida pelo sensor ultrassônico
  int distancia = medirDistancia();
  
  // Se a distância for menor ou igual à distância de detecção, mudar para o estado 3
  if (distancia > 0 && distancia <= DISTANCIA_DETECCAO) {
    estadoAtual = 3;
  }

  // Lógica do semáforo
  switch (estadoAtual) {
    case 1:
      // Semáforo 1 Verde, Semáforo 2 Vermelho
      digitalWrite(SEM1_VERDE, HIGH);
      digitalWrite(SEM2_VERMELHO, HIGH);
      digitalWrite(SEM1_VERMELHO, LOW);
      digitalWrite(SEM1_AMARELO, LOW);
      digitalWrite(SEM2_VERDE, LOW);
      digitalWrite(SEM2_AMARELO, LOW);
      delay(TEMPO_VERDE);
      estadoAtual = 2;
      break;

    case 2:
      // Semáforo 1 Amarelo, Semáforo 2 Vermelho
      digitalWrite(SEM1_AMARELO, HIGH);
      digitalWrite(SEM2_VERMELHO, HIGH);
      digitalWrite(SEM1_VERDE, LOW);
      digitalWrite(SEM1_VERMELHO, LOW);
      digitalWrite(SEM2_VERDE, LOW);
      digitalWrite(SEM2_AMARELO, LOW);
      delay(TEMPO_AMARELO);
      estadoAtual = 3;
      break;

    case 3:
      // Semáforo 1 Vermelho, Semáforo 2 Verde
      digitalWrite(SEM1_VERMELHO, HIGH);
      digitalWrite(SEM2_VERDE, HIGH);
      digitalWrite(SEM1_VERDE, LOW);
      digitalWrite(SEM1_AMARELO, LOW);
      digitalWrite(SEM2_VERMELHO, LOW);
      digitalWrite(SEM2_AMARELO, LOW);
      delay(TEMPO_VERDE);
      estadoAtual = 4;
      break;

    case 4:
      // Semáforo 1 Vermelho, Semáforo 2 Amarelo
      digitalWrite(SEM1_VERMELHO, HIGH);
      digitalWrite(SEM2_AMARELO, HIGH);
      digitalWrite(SEM1_VERDE, LOW);
      digitalWrite(SEM1_AMARELO, LOW);
      digitalWrite(SEM2_VERDE, LOW);
      digitalWrite(SEM2_VERMELHO, LOW);
      delay(TEMPO_AMARELO);
      estadoAtual = 1;  
      break;
  }
}

// Função para medir a distância com o sensor ultrassônico
int medirDistancia() {
  // Enviar um pulso de 10 microsegundos no pino TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Medir o tempo de retorno do pulso no pino ECHO
  long duracao = pulseIn(ECHO_PIN, HIGH);
  
  // Calcular a distância em centímetros (velocidade do som: 343 m/s)
  int distancia = duracao * 0.034 / 2;

  return distancia; // Retorna a distância medida
}
