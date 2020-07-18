# Resolução de um exercício de programação utilizando o algoritmo de otimização de Particle Swarm

## Introdução
O problema constitui em simular o comportamento de 5 bactérias em contato com uma célula cancerígena. A simulação deve parar quando a soma da distância que as bactérias caminham por minuto é menor que 0.001. A posição e velocidade iniciais das bactérias devem ser valores aleatórios do intervalo [0,5] e [0.5,1), respectivamente. Além disso, a concentração das substâncias que as células secretam é inversamente proporcional a distância das bactérias.

A nova velocidade de uma bactéria deve ser obtida pela fórmula abaixo. xbestcultura,t e xbestbacteria,t são as melhores posições encontradas até o instante t por todas as bactérias da cultura e pela bactéria que estamos atualizando, respectivamente.
```math
vt+1 = w · vt + α · rand() · (xbestcultura,t − xt) + β · rand() · (xbestbacteria,t − xt)
```
A nova posição deve ser obtida pela fórmula:
```math
xt+1 = xt + vt+1
```
A concentração deve ser calculada pela fórmula:
```math
C(x, y) = −(x − px)^2 − (y − py)^2 + 100
```
Os coeficientes utilizados são:
```math
w = 0.9, α = 0.2 e β = 0.2
```

## Dados de entrada:
Posição x e y de uma célula cancerigena. Onde x,y ∈ [0,5]

## Saída esperada:
As posições x e y finais das 5 bactérias.
