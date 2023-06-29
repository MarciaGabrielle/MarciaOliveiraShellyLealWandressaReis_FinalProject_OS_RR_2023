<div align="center">

# Simulador de Memória Física e Virtual

</div>


Desde os primórdios da computação, é comum a existência de programas maiores que o tamanho de memória disponível.

<div align="center">
    
![so - slide 1](https://github.com/MarciaGabrielle/MarciaOliveiraShellyLealWandressaReis_FinalProject_OS_RR_2023/assets/94376190/fa776afa-97ee-4431-a189-b271b44103d5)

</div>

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

## Resultados da execução do programa testando cada algoritmo: 
<div align="center">
    
### LRU

![WhatsApp Image 2023-06-28 at 20 09 35](https://github.com/MarciaGabrielle/MarciaOliveiraShellyLealWandressaReis_FinalProject_OS_RR_2023/assets/94376190/3b738583-890f-4e84-a6c6-ebfd5b99ed1d)
<div align="center">
    
</div>

<div align="center">
    
### FIFO

![WhatsApp Image 2023-06-28 at 20 07 39](https://github.com/MarciaGabrielle/MarciaOliveiraShellyLealWandressaReis_FinalProject_OS_RR_2023/assets/94376190/67f06974-c733-45ca-b975-119a6a895257)

</div>

<div align="center">
    
### RANDOM

![WhatsApp Image 2023-06-28 at 20 09 56](https://github.com/MarciaGabrielle/MarciaOliveiraShellyLealWandressaReis_FinalProject_OS_RR_2023/assets/94376190/dc12e73e-017e-4d9d-b323-d161be407530)

</div>





