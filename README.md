
# Projetos de Sistemas Embarcados - EmbarcaTech 2025

Autor: **Arthur Franco Neto**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, 11 de Maio de 2025

---

# Galton Board Digital

Este projeto implementa uma versão digital de uma Galton Board (ou Plinko), demonstrando como uma série de decisões binárias aleatórias leva a uma **distribuição normal de probabilidades**.

## Objetivo

	Criar uma visualização interativa que simula o comportamento de uma Galton Board usando:

	- Display OLED
	- Botões para incluir desequilíbrios ao modelo


##  Lista de materiais: 

| Componente            | Conexão na BitDogLab      |
|-----------------------|---------------------------|
| BitDogLab (RP2040)    | -                         |
| Display OLED I2C      | SDA: GPIO14 / SCL: GPIO15 |
| Botões para Entrada   | ESQ: GPIO5  / DIR: GPIO6  |
| Botão para Debug      | Valores Absolutos | GPIO22|


## Execução

1. Abra o projeto no VS Code, usando o ambiente com suporte ao SDK do Raspberry Pi Pico (CMake + compilador ARM), utilizado SDK **2.1.0**;
2. Compile o projeto normalmente (Ctrl+Shift+B no VS Code ou via terminal com cmake e make);
3. Conecte sua BitDogLab via cabo USB e coloque a Pico no modo de boot (pressione o botão BOOTSEL e conecte o cabo);
4. Copie o arquivo .uf2 gerado para a unidade de armazenamento que aparece (RPI-RP2);
5. A Pico reiniciará automaticamente e começará a executar o código;
6. O histograma será atualizado no display OLED.

## Lógica

- A cada passo, a "bola" se desloca para esquerda ou direita com probabilidade 50%;
- A posição final da "bola" é contabilizada no vetor de contagem;
- As barras do OLED representam visualmente a frequência de cada posição.

##  Arquivos

- `src/lab-01-galton-board.c`: Código principal do projeto;
- `assets/galton_hist.jpg`: Histograma de distribuição.

## 🖼️ Imagens do Projeto

### Display OLED durante a execução
![galton_display](./assets/Simulação Galton no Display.jpg)

### Debug serial com dados
![galton_monitor](./assets/Valores Absulotos no Compartimento.jpg)

---

## 📜 Licença
MIT License - MIT GPL-3.0.
