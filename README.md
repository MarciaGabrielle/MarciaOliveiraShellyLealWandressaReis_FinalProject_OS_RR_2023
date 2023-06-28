<div align="center">

# Simulador de Memória Física e Virtual

</div>


Desde os primórdios da computação, é comum a existência de programas maiores que o tamanho de memória disponível.

(IMAGEM AQUI)

Daí a importância da utilização da memória virtual que é uma técnica emepregada para o gerenciamento da memória  permitindo que o sistema operacional aloque espaço em disco para complementar a memória física criando uma ilusão de que o sistema possui mais memória do que realmente tem.

A memória virtual também utiliza algumas técnica para otimizar esse gerenciamento de memória, como o uso de algoritmos de substituição de página. 

Neste projeto foram implementados três tipos de algoritmos de substituição de página. São eles: 

- **FIFO (First In, First Out):** Trata-se de uma fila que prioriza a substituição de uma página que está há mais tempo em memória.
- **LRU (Least Recently Used):** A página que foi acessada há mais tempo é a menos provável de ser acessada novamente no futuro próximo. Portanto, a página que está há mais tempo na memória sem ter sido acessada será escolhida para ser substituída.
- **RANDOM:**  Seleciona aleatoriamente uma página para ser substituída quando ocorre uma falta de página na memória. Ele não leva em consideração o histórico de uso das páginas nem qualquer outro critério, apenas escolhe uma página de forma aleatória para ser substituída. 

### Para compilar o código:

    gcc mem_virtual -o mem_vitual

### Para executar o código:

    sim_virtual lru arquivo.log 4 128

## Resultados da execução do programa, testando cada algoritmo: 

