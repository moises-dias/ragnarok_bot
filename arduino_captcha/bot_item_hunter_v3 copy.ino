#include <Keyboard.h>
#include <Mouse.h>

String incoming = "";
int m_x = 0;
int m_y = 0;
int to_move_x = 0;
int to_move_y = 0;
char c = "";
char enterKey = KEY_RETURN;

void setup() {
  delay(1000);
  pinMode(3, INPUT_PULLUP);
  Keyboard.begin();
  Mouse.begin();
  Serial.begin(9600);
  Serial.setTimeout(10);
}

void loop() {
  while (digitalRead(3) == HIGH) {
    Serial.println('k');                      // envia ok para o python iniciar a execução
    while (Serial.available() == 0) {}        // aguarda o python tentar identificar os monstros na tela
    incoming = Serial.readString();           // char enviado pelo python com a informação se foi identificado ou não um monstro
    if (incoming[0] == 't') {                 // t = identificou um monstro na tela
      while (Serial.available() == 0) {}      // aguarda o envio da coordenada x
      m_x = Serial.parseInt(SKIP_ALL, '\n');  // armazena coordenada x
      while (Serial.available() == 0) {}      // aguarda o envio da coordenada y
      m_y = Serial.parseInt(SKIP_ALL, '\n');  // armazena coordenada y
      aim(m_x, m_y);                          // move o mouse até as coordenadas do monstro
      attack();                               // ataca o monstro
      delay(1000);
    }
    else {
      teleport();
      delay(1000);
    }
  }
}

void teleport() {
  Keyboard.press('2');
  delay(500);
  Keyboard.press(enterKey);
  delay(75);
  Keyboard.releaseAll();
}
void aim(int m_x, int m_y) {
  for(int i = 0; i < 7; i++) {
    Mouse.move(-127, -127, 0);
  }
  while (m_x > 0 || m_y > 0) {
    if (m_x > 126)
      to_move_x = 127;
    else
      to_move_x = m_x;
    if (m_y > 126)
      to_move_y = 127;
    else
      to_move_y = m_y;
    Mouse.move(to_move_x, to_move_y, 0);
    if (to_move_x > 0)
      m_x -= to_move_x;
    if (to_move_y > 0)
      m_y -= to_move_y;
  }
}
void attack() {
  delay(30);
  Keyboard.press('1');
  delay(60);
  Mouse.press();
  delay(30);
  Keyboard.releaseAll();
  delay(20);
  Mouse.release();
  delay(20);
  Mouse.move(-50, 0, 0); // mover o mouse pra remover o cursor de cima do mob
}
