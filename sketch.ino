#include <WiFi.h>
#include <HTTPClient.h>

#define led_verde 2  // Pino utilizado para controle do led verde
#define led_vermelho 40 // Pino utilizado para controle do led vermelho
#define led_amarelo 9 // Pino utilizado para controle do led amarelo

const int pino_botao = 18;  // N° número do pino do botão de pressão
int estado_botao = 0;  // Variável para visualização do estado do botão
int statusVermelho = 0;

const int pino_ldr = 4;  // Número do pino do LDR
int threshold=600;

void setup() {
  pinMode(pino_ldr, INPUT);
  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);
  pinMode(led_amarelo, OUTPUT);

  // Inicialização das entradas
  pinMode(pino_botao, INPUT); //Inicializa o botão como entrada

  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  while (WiFi.status() != WL_CONNECT_FAILED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  // Verifica estado do botão
  estado_botao = digitalRead(pino_botao);
  if (estado_botao == HIGH) {
    Serial.println("Botão pressionado!");
    //Debounce botão
    delay(70);
  } else {
    Serial.println("Botão não pressionado!");
  }

//   if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
//     HTTPClient http;

//     String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

//     http.begin(serverPath.c_str());

//     int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

//     if (httpResponseCode>0) {
//       Serial.print("HTTP Response code: ");
//       Serial.println(httpResponseCode);
//       String payload = http.getString();
//       Serial.println(payload);
//       }
//     else {
//       Serial.print("Error code: ");
//       Serial.println(httpResponseCode);
//       }
//       http.end();
//     }

//   else {
//     Serial.println("WiFi Disconnected");
//   }

//   estado_led_vermelho = digitalRead(led_vermelho);
// }
}

void loop() {
   Serial.println("Teste");
  int ldrstatus = 4063 - analogRead(pino_ldr)

  if(ldrstatus<=threshold){
    Serial.print("Está escuro, ligar as luzes.");

    Serial.println(ldrstatus);
    digitalWrite(led_amarelo, HIGH);
    delay(1000);
    digitalWrite(led_amarelo, LOW);
    delay(1000);

  }else{
    // Quando está claro ciclo normal
    Serial.print("Está claro, apagar as luzes");
    statusVermelho = false;
    digitalWrite(led_verde, HIGH);
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_vermelho, LOW);
    delay(3000);

    statusVermelho = false;
    digitalWrite(led_verde, LOW);
    digitalWrite(led_amarelo, HIGH);
    digitalWrite(led_vermelho, LOW);
    delay(2000);
    statusVermelho = true;
    // 5 - Fluxo
    while((digitalRead(pinoBotao) != 1) && (statusVermelho == true)){
      Serial.println("Vermelho ligado");
      digitalWrite(led_verde, LOW);
      digitalWrite(led_amarelo, LOW);
      digitalWrite(led_vermelho, HIGH);
      delay(5000);
      statusVermelho = false;
      break;
    }
    if(digitalRead(pinoBotao) == 1){
      Serial.println("1 SEGUNDO");
        delay(1000);
        digitalWrite(led_verde, HIGH);
        digitalWrite(led_amarelo, LOW);
        digitalWrite(led_vermelho, HIGH);  
    }

  }

}