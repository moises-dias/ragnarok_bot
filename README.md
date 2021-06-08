# ragnarok_bot

### Descrição:
Esse projeto realiza a automatização de um personagem (bot) no ragnarok online, utilizando Python com OpenCV para identificar um determinado monstro e Arduino para movimentar o mouse e "pressionar" as teclas de ataque. A comunicação entre o Arduino e o OpenCV é feita via serial. O código do arduino foi criado por mim e o código para identificar as imagens foi baseado nas excelentes video aulas do canal [Learn code by game](https://www.youtube.com/watch?v=KecMlLUuiE4&list=RDCMUCD8vb6Bi7_K_78nItq5YITA&start_radio=1&rv=WymCpVUPWQ4).

#### Instruções para execução dos programas:
1. carregue o código .ino em um arduino pro micro ou arduino leonardo
2. conecte o pino 3 ao gnd do arduino
3. abrir a janela do jogo e colocar o nome da janela na inicialização do objeto WindowCapture na linha 14 do arquivo main.py
4. colocar a imagem do monstro que se deseja identificar na pasta e referenciar a imagem na linha 17, na inicialização do objeto Vision
5. executar o arquivo main.py
6. desconectar o pino 3 do GND
