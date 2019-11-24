#ifdef ESP8266//Se estiver usando ESP8266, automáticamente irá adicionar as bibliotecas do ESP8266.
#include <ESP8266WiFi.h>
#include <WiFiServer.h>
#elif defined ESP32//Se estiver usando ESP32, fara a mesma operaçao.
#include <WiFi.h>
#endif

WiFiServer sv(555);//Cria o objeto servidor na porta 555
WiFiClient cl;//Cria o objeto cliente.


void setup()
{
    Serial.begin(115200);//Habilita a comm serial.

    WiFi.mode(WIFI_AP);//Define o WiFi como Acess_Point.
    WiFi.softAP("NodeMCU", "");//Cria a rede de Acess_Point.

    sv.begin();//Inicia o servidor TCP na porta declarada no começo.
}

void loop()
{
    tcp();//Funçao que gerencia os pacotes e clientes TCP.
}

void tcp()
{
    if (cl.connected())//Detecta se há clientes conectados no servidor.
    {
        if (cl.available() > 0)//Verifica se o cliente conectado tem dados para serem lidos.
        {
            String req = "";
            while (cl.available() > 0)//Armazena cada Byte (letra/char) na String para formar a mensagem recebida.
            {
                char z = cl.read();
                req += z;
            }

            //Mostra a mensagem recebida do cliente no Serial Monitor.
            Serial.print("\nUm cliente enviou uma mensagem");
            Serial.print("\n...IP do cliente: ");
            Serial.print(cl.remoteIP());
            Serial.print("\n...IP do servidor: ");
            Serial.print(WiFi.softAPIP());
            Serial.print("\n...Mensagem do cliente: " + req + "\n");

	    //Envia uma resposta para o cliente
            cl.print("\nO servidor recebeu sua mensagem");
            cl.print("\n...Seu IP: ");
            cl.print(cl.remoteIP());
            cl.print("\n...IP do Servidor: ");
            cl.print(WiFi.softAPIP());
            cl.print("\n...Sua mensagem: " + req + "\n");
			
        }
    }
    else//Se nao houver cliente conectado,
    {
        cl = sv.available();//Disponabiliza o servidor para o cliente se conectar.
        delay(1);
    }
}
