// ? ▼▼ DEFINIÇÃO DE CONSTANTES ▼▼
#define sonar_corredorPin (5)       // TODO INSERIR NUMERO DO PIN
#define sonar_amoedacaoPin (6)      // TODO INSERIR NUMERO DO PIN
#define sensorPin (7)               // TODO INSERIR NUMERO DO PIN
#define okCorPin (15)               // TODO INSERIR NUMERO DO PIN
#define okAmoPin (16)               // TODO INSERIR NUMERO DO PIN
#define OK (1)
#define NOTOK (2)
#define OCUPADO (3)
#define DESOCUPADO (4)
#define ALARME (8)
int contador;

void setup()
{
  // * ▼▼ DEFINIR PINS DE INPUT ▼▼
  pinMode(sonar_corredorPin, INPUT);
  pinMode(sonar_amoedacaoPin, INPUT);
  pinMode(sensorPin, INPUT);
  pinMode(okCorPin, INPUT);
  pinMode(okAmoPin, INPUT);

  // * ▼▼ DEFINIR PINS DE OUTPUT ▼▼
  pinMode(OK, OUTPUT);
  pinMode(NOTOK, OUTPUT);
  pinMode(OCUPADO, OUTPUT);
  pinMode(DESOCUPADO, OUTPUT);
  pinMode(ALARME, OUTPUT);
}

void loop()
{
  if (digitalRead(okCorPin) == HIGH)
  {
    if (digitalRead(sensorPin) == HIGH && entradaPessoa(sonar_corredorPin) == 1)
    {
      // ? SE SENSOR E CONTADOR = 1 DOU OK E OCUPADO
      digitalWrite(OK, HIGH);
      digitalWrite(OCUPADO, HIGH);
      while (saidaPessoa(sonar_amoedacaoPin) != 0); // ? ESPERA QUE A PESSOA SAIR
      if (digitalRead(sensorPin) == LOW)
      {
        // ? VALIDA QUE A PESSOA SAIU
        digitalWrite(OK, LOW);
        digitalWrite(OCUPADO, LOW);
        digitalWrite(DESOCUPADO, HIGH);
      }
      else
      {
        digitalWrite(ALARME, HIGH); // TODO ASK ABOUT THIS!!
      }
    }
    else if (digitalRead(sensorPin) == HIGH && entradaPessoa(sonar_corredorPin) > 1)
    {
      // ? SE SENSOR E CONTADOR > 1 DOU NOT OK E OCUPADO
      digitalWrite(NOTOK, HIGH);
      digitalWrite(OCUPADO, HIGH);
      while (saidaPessoa(sonar_corredorPin) != 0); // ? ESPERA QUE A PESSOA SAIR
      if (digitalRead(sensorPin) == LOW)
      {
        // ? VALIDA QUE AS PESSOAS SAIRAM
        digitalWrite(OK, LOW);
        digitalWrite(OCUPADO, LOW);
        digitalWrite(DESOCUPADO, HIGH);
      }
    }
  }
}

int entradaPessoa(int sonarPin)
{
  if (digitalRead(sonarPin) == HIGH)
    contador += 1;
  return contador;
}

int saidaPessoa(int sonarPin)
{
  if (digitalRead(sonarPin) == HIGH)
    contador -= 1;
  return contador;
}