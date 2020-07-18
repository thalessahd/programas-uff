import random

def printaDadosBacterias(pos,vel):
    for i in range(5):
        print("Bacteria",i)
        print("Pos",pos[i])
        #print("Vel",vel[i])

def conc(pos,px,py):
    C = -(pos[0] - px)**2 - (pos[1] - py)**2 + 100
    return C

def vel(vel_atual, melhor_pos_coletiva, melhor_pos_individual, pos_atual):
    vel_nova_x = 0.9*vel_atual[0] + 0.2*random.uniform(0,1) * (melhor_pos_coletiva[0] - pos_atual[0]) + 0.2*random.uniform(0,1) * (melhor_pos_individual[0] - pos_atual[0])
    vel_nova_y = 0.9*vel_atual[1] + 0.2*random.uniform(0,1) * (melhor_pos_coletiva[1] - pos_atual[1]) + 0.2*random.uniform(0,1) * (melhor_pos_individual[1] - pos_atual[1])
    
    vel_nova = (vel_nova_x, vel_nova_y)
    return vel_nova

def pos(pos_atual,vel_nova):
    pos_nova_x = pos_atual[0] + vel_nova[0]
    pos_nova_y = pos_atual[1] + vel_nova[1]

    pos_nova = (pos_nova_x, pos_nova_y)
    return pos_nova

def distancia(pos_atual, pos_nova): 
  mod = ((pos_nova[0] - pos_atual[0])**2 + (pos_nova[1] - pos_atual[1])**2)**(1/2)
  return mod

def main():
    px = float(input('Posição x da célula de câncer '))
    py = float(input('Posição y da célula de câncer '))

    bacterias_pos = [] #Lista com as posições das bactérias
    bacterias_vel = [] #Lista com as velocidades das bactérias

    melhores_pos = [] #Lista com a melhor posição de cada bactéria

    melhor_pos = (0, 0) #Valor inicial da melhor posição coletiva
    conc_melhor_pos = 0.0 #Valor inicial da maior concentração

    for i in range(5): #Inicialização de posição, velocidade das bactérias, melhor pos individual e melhor pos coletiva
        #Define vel e pos individuais
        vx = random.uniform(0.5,1)
        vy = random.uniform(0.5,1)
        x = random.uniform(0,5)
        y = random.uniform(0,5)
        baka_pos = (x,y)
        baka_vel = (vx,vy)
        bacterias_pos.append(baka_pos)
        bacterias_vel.append(baka_vel)
        #Define melhor pos individual (usa a pos inicial)
        melhores_pos.append(baka_pos)
        #Acha a melhor pos coletiva
        baka_conc = conc(baka_pos,px,py) 
        conc_melhor_pos = conc(melhor_pos,px,py)
        
        if(baka_conc > conc_melhor_pos):
            melhor_pos = baka_pos

    soma_distancias = 1 #Valor inicial

    while(soma_distancias > 0.001):
        soma_distancias = 0.0
        for i in range(5):
            #Calcula nova velocidade e posição da bactéria
            nova_vel = vel(bacterias_vel[i], melhor_pos,melhores_pos[i], bacterias_pos[i])
            nova_pos = pos(bacterias_pos[i], nova_vel)

            baka_conc = conc(nova_pos, px, py)
            conc_melhor_pos_individual = conc(melhores_pos[i], px, py)

            #Atualiza melhor posição indidual
            if(baka_conc > conc_melhor_pos_individual):
                melhores_pos[i] = nova_pos

            #Atualiza melhor posição coletiva
            conc_melhor_pos = conc(melhor_pos, px, py)
            if(baka_conc > conc_melhor_pos):
                melhor_pos = nova_pos
            
            #Calcula distância de pos_atual pra post_nova
            d = distancia(bacterias_pos[i], nova_pos)
            soma_distancias = soma_distancias + d

            #Atualiza posição e velocidade da bactéria
            bacterias_pos[i] = nova_pos
            bacterias_vel[i] = nova_vel
        

    printaDadosBacterias(bacterias_pos ,bacterias_vel)

if __name__ == "__main__":
    main()