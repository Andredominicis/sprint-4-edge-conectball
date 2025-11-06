Sprint 4 – Edge ConectBall

Uma solução para integração IoT + borda para o jogo “ConectBall”.

Visão Geral

Este projeto tem como objetivo desenvolver um sistema embarcado com a placa ESP32 que captura dados — por exemplo luminosidade, movimento ou outro sensor — e se conecta a uma infraestrutura “edge” para monitoramento/controle em tempo real. A ideia é aplicar conceitos de Edge Computing, IoT e integração com nuvem ou local host.

Funcionalidades Principais

Leitura de sensor(es) no ESP32.

Envio dos dados para a edge (ou servidor local).

Acionamento de atuador (por exemplo servo) a partir do ESP32.

Visualização ou dashboard (html/código front) para acompanhar o estado.

Arquitetura pensada para baixo consumo e resposta rápida.

Componentes do Projeto

esp32-servo-sweep.ino – Sketch para ESP32 que realiza sweep de servo e leitura de sensor.

wokwi-project.txt – Arquivo de simulação para plataforma Wokwi.

sprint 4.html – Protótipo de interface web ou relatório.

diagram.json – Diagrama da arquitetura (talvez importável no draw.io ou similar).

libraries.txt – Lista das bibliotecas usadas no projeto (ex: WiFi, MQTT, Servo…).

Requisitos

Placa ESP32 (ex: DevKitC).

Sensor(es) compatíveis (ex: LDR, sensor de movimento, etc).

Servo motor ou outro atuador.

Ambiente Arduino IDE ou PlatformIO com suporte ESP32.

Acesso à rede WiFi ou outro meio de comunicação (dependendo da arquitetura).

Como Utilizar

Clone este repositório:

git clone https://github.com/Andredominicis/sprint-4-edge-conectball.git


Abra o arquivo esp32-servo-sweep.ino na Arduino IDE ou PlatformIO.

Verifique e instale as bibliotecas listadas em libraries.txt.

No código, configure suas credenciais WiFi, definições de pinos (sensor/servo) e parâmetros de envio de dados.

Carregue o sketch no ESP32.

Ligue o sensor e servo conforme o diagrama/hardware protótipo.

Abra o sprint 4.html para visualizar os dados ou interface (se aplicável).

Monitore os dados no servidor/edge ou local host conforme o seu ambiente.

Arquitetura

A arquitetura segue o modelo:

Sensor → ESP32 → Edge/Servidor → Dashboard
     ↑                      ↓
   Atuador               Interface Web


O diagrama completo está no arquivo diagram.json.

Licença

Este projeto é disponibilizado sob a licença MIT (ou outra que você definir). Sinta-se à vontade para utilizar, modificar e distribuir.

Contribuição

Contribuições são bem-vindas! Se você identificar melhorias, correções de bugs ou novas funcionalidades, envie um pull request ou abra uma issue.








<img width="1258" height="905" alt="image" src="https://github.com/user-attachments/assets/2bbe9837-eb74-4d58-836a-9682b21d9674" />
