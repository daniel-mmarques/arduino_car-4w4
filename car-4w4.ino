#define pinSH_CP  4
#define pinST_CP  12
#define pinDS     8
#define pinEnable 7

#define pinMotor1PWM 11
#define pinMotor2PWM 3
#define pinMotor3PWM 5
#define pinMotor4PWM 6

#define qtdeCI   1

#define bitMotor1A 2
#define bitMotor1B 3
#define bitMotor2A 1
#define bitMotor2B 4
#define bitMotor3A 5
#define bitMotor3B 7
#define bitMotor4A 0
#define bitMotor4B 6

int velPot;
int potenciometroValor;

#define pinBotao1 A1
#define pinBotao2 A2

int pressionado1;
int pressionado2;

void ci74HC595Write(byte pino, bool estado);

  void setup() {
  
    pinMode(pinSH_CP, OUTPUT);
    pinMode(pinST_CP, OUTPUT);
    pinMode(pinEnable, OUTPUT);
    pinMode(pinDS, OUTPUT);

    pinMode(pinMotor1PWM, OUTPUT);
    pinMode(pinMotor2PWM, OUTPUT);
    pinMode(pinMotor3PWM, OUTPUT);
    pinMode(pinMotor4PWM, OUTPUT);

    digitalWrite(pinEnable, LOW);

    pinMode(pinBotao1, INPUT_PULLUP);
    pinMode(pinBotao2, INPUT_PULLUP);

    Serial.begin(9600);
  }

  void loop() {

    potenciometroValor = analogRead(A0);
    velPot = map(potenciometroValor, 0, 1023, 0, 255);
    pressionado1 = digitalRead(pinBotao1);
    pressionado2 = digitalRead(pinBotao2);

    if (pressionado1 == LOW && pressionado2 == HIGH && pressionado1 != HIGH){

      paraDireita(velPot);
    
    }

    if (pressionado2 == LOW && pressionado1 == HIGH && pressionado2 != HIGH){

      paraEsquerda(velPot);
    
    }

    if (pressionado1 == HIGH && pressionado2 == HIGH){

      paraFrente(velPot);
    
    }

    if (pressionado1 == LOW && pressionado2 == LOW){

      parado(0);
    
    }
  }

  void ci74HC595Write(byte pino, bool estado) {
    static byte ciBuffer[qtdeCI];
  
    bitWrite(ciBuffer[pino / 8], pino % 8, estado);
    
    digitalWrite(pinST_CP, LOW);
    
    digitalWrite(pinDS, LOW);
    digitalWrite(pinSH_CP, LOW);
  
    for (int nC = qtdeCI-1; nC >= 0; nC--) {
        for (int nB = 7; nB >= 0; nB--) {
    
            digitalWrite(pinSH_CP, LOW);     
            
            digitalWrite(pinDS,  bitRead(ciBuffer[nC], nB) );
            
            digitalWrite(pinSH_CP, HIGH);
            digitalWrite(pinDS, LOW); 
        }  
    }
    
    digitalWrite(pinST_CP, HIGH);
  }
  
  void paraFrente (int velocidade){
  
    ci74HC595Write(bitMotor1A, HIGH);
    ci74HC595Write(bitMotor1B, LOW);
  
    ci74HC595Write(bitMotor2A, HIGH);
    ci74HC595Write(bitMotor2B, LOW);
  
    ci74HC595Write(bitMotor3A, HIGH);
    ci74HC595Write(bitMotor3B, LOW);
  
    ci74HC595Write(bitMotor4A, HIGH);
    ci74HC595Write(bitMotor4B, LOW);
  
    analogWrite(pinMotor1PWM, velocidade);
    analogWrite(pinMotor2PWM, velocidade);
    analogWrite(pinMotor3PWM, velocidade);
    analogWrite(pinMotor4PWM, velocidade);
    
  }
  
  void paraDireita (int velocidade){
  
    ci74HC595Write(bitMotor1A, LOW);
    ci74HC595Write(bitMotor1B, HIGH);
  
    ci74HC595Write(bitMotor2A, LOW);
    ci74HC595Write(bitMotor2B, LOW);
  
    ci74HC595Write(bitMotor3A, HIGH);
    ci74HC595Write(bitMotor3B, LOW);
  
    ci74HC595Write(bitMotor4A, HIGH);
    ci74HC595Write(bitMotor4B, LOW);
  
    analogWrite(pinMotor1PWM, velocidade);
    analogWrite(pinMotor2PWM, velocidade);
    analogWrite(pinMotor3PWM, velocidade);
    analogWrite(pinMotor4PWM, velocidade);
    
  }
  
  void paraEsquerda (int velocidade){
  
    ci74HC595Write(bitMotor1A, HIGH);
    ci74HC595Write(bitMotor1B, LOW);
  
    ci74HC595Write(bitMotor2A, HIGH);
    ci74HC595Write(bitMotor2B, LOW);
  
    ci74HC595Write(bitMotor3A, LOW);
    ci74HC595Write(bitMotor3B, HIGH);
  
    ci74HC595Write(bitMotor4A, LOW);
    ci74HC595Write(bitMotor4B, LOW);
  
    analogWrite(pinMotor1PWM, velocidade);
    analogWrite(pinMotor2PWM, velocidade);
    analogWrite(pinMotor3PWM, velocidade);
    analogWrite(pinMotor4PWM, velocidade);
    
  }
  
  void parado (int velocidade){
  
    ci74HC595Write(bitMotor1A, LOW);
    ci74HC595Write(bitMotor1B, LOW);
  
    ci74HC595Write(bitMotor2A, LOW);
    ci74HC595Write(bitMotor2B, LOW);
  
    ci74HC595Write(bitMotor3A, LOW);
    ci74HC595Write(bitMotor3B, LOW);
  
    ci74HC595Write(bitMotor4A, LOW);
    ci74HC595Write(bitMotor4B, LOW);
  
    analogWrite(pinMotor1PWM, velocidade);
    analogWrite(pinMotor2PWM, velocidade);
    analogWrite(pinMotor3PWM, velocidade);
    analogWrite(pinMotor4PWM, velocidade);
    
  }
