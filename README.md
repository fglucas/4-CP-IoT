# PONTO E VIRGULA
Nome dos Alunos:
- Bianca Nunes Ferraz Cabral
- Lennyk Macedo dos Santos
- Lucas Ferreira Gonçalves
- Micaela Mota Santos
- Nalita Tsu Kao


# Nome do projeto - ESTAÇÃO METEOROLÓGICA

**Turma:2TDSG**

**Ano:2021**

## Objetivo / descrição do Projeto

Foi solicitado na Classe de DISRUPTIVE ARCHITECTURES IOT & IA que fosse reproduzido através de arduino en conjunto com node-red e protocolo MQTT uma estação meteorológica, onde fosse capaz de medir Temperatura, Luminosidade e Km/H dos ventos, dessa maneira fizemos em conjunto utilizando sensores e lógica de programação o projeto descrito, o mesmo também é capaz de realizar notificação via Twitter através da API disnipobilizada na sua plataforma de desenvolvimento.


## Como usar 

Primeiro deve baixar os arquivos de simulação arduino, neste mesmo git, será nessario SimulIDE onde você conseguirá importar tanto o arduino quanto o código do mesmo, em seguida deve importar os arquivos de Node-RED para que seja gerado JSON das informações geradas em arduino, logo após com as portas devidamente instaladas e configuradas no seu computador, as informações estarão sincronizadas e preparadas para encaminhar ao Twitter quando o trigger for disparado.


Função para calculo da Velocidade do vento:

    void SpeedWind() {
    speedwind = (((2 * pi * radius * RPM) / 60) / 1000) * 3.6; //Calcula velocidade do vento em km/h
    }
   

## Link de vídeo demonstração

[Link para o video youtube](https://youtu.be/1kdAc_ag8eI)


### Referências 

* [mastering-markdown](https://guides.github.com/features/mastering-markdown/)
* [Basic writing and formatting syntax](https://docs.github.com/en/github/writing-on-github/getting-started-with-writing-and-formatting-on-github/basic-writing-and-formatting-syntax)
