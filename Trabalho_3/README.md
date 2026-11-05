# Trabalho 3: Gazebo & TurtleBot3

Este diretório contém as entregas do **Trabalho 3.1 (Parte A)** e **Trabalho 3.2 (Parte B)** da unidade curricular de **Redes e Sistemas Distribuídos (RSDIS)** - Mestrado em Engenharia Eletrotécnica e de Computadores (MEEC / ISEP).

Ambiente: **Ubuntu 24.04 LTS**, **ROS 2 Jazzy**, **Gazebo Sim** (gz-sim), modelo **TurtleBot3 Burger**.

---

## Estado Atual do Trabalho

| Requisito do Enunciado | Estado do Código | Elementos de Comprovação |
| :--- | :---: | :---: |
| **Parte A (3.1):** Aspirador na Casa (`turtlebot3_house`) | ⚠️ **Atenção: Robô sai fora de casa** | ⏳ **Falta tirar screenshots após resolver** |
| **Parte B (3.2):** Exploração no Labirinto (`stage_4`) | ✅ Concluído (100%) | ⏳ **Falta vídeo / screenshots** |
| **Parte B (3.2):** Deteção de Cilindros via LiDAR 2D | ✅ Concluído (100%) | ⏳ **Falta screenshot do terminal/RViz** |
| **Parte B (3.2):** Construção do Mapa 2D (SLAM) | ✅ Concluído (100%) | ✅ Mapa salvo (`.pgm` / `.yaml`) |

---

## ⚠️ Problema a Resolver na Parte A (Trabalho 3.1): O robô sai fora de casa

> [!WARNING]
> **Descrição do Problema na Casa (`turtlebot3_house`):**
> O cenário `turtlebot3_house` tem portas exteriores que dão acesso direto ao exterior da casa (ao plano infinito do Gazebo).  
> Como no exterior não existem paredes, as leituras do LiDAR vão para o infinito (`ranges = inf`). O algoritmo do aspirador assume que o caminho está totalmente livre à sua frente e **o robô acaba por fugir de casa pelas portas abertas e continuar a andar em linha reta pelo vazio**.

### O que já está implementado em `rsdis_t3a/src/robot_aspirador.cpp`:
- Foi adicionada a subscrição do tópico de odometria (`/odom`) para rastrear a posição $(x, y)$ do robô.
- Foi definida uma **"parede virtual"** através dos limites aproximados da casa:
  ```cpp
  const double X_MIN = -5.2, X_MAX = 9.2;
  const double Y_MIN = -4.5, Y_MAX = 5.5;
  ```
- Quando o robô ultrapassa estes limites (`fora_de_casa = true`), é iniciada uma manobra de meia-volta (`meia_volta_ = 63` ciclos de rotação a $-0.5\text{ rad/s}$).

### O que é necessário afinar / corrigir:
1. **Garantir o regresso efetivo para dentro de casa:**  
   Quando o robô roda 180º no sítio após passar a porta, ele ainda se encontra fora dos limites. O código precisa de **avançar obrigatoriamente para a frente** na direção do interior da casa (ou rodar diretamente apontado para o centro da casa `atan2(Y_CENTRO - y, X_CENTRO - x)`) até voltar a cruzar a fronteira de entrada.
2. **Afinar os limites da "parede virtual":**  
   Confirmar se os limites $(X_{min}, X_{max}, Y_{min}, Y_{max})$ cobrem bem todas as divisões interiores sem deixar o robô passar pelo batente das portas que dão para a rua.
3. **Após resolver a fuga:**  
   Lançar a simulação e tirar 1 ou 2 screenshots com o robô a navegar dentro das várias divisões da casa para colocar na pasta `rsdis_t3a/screenshots/`.

---

## O que Falta Fazer na Parte B (Trabalho 3.2 - Stage 4)

O código C++ e o mapa SLAM estão **100% concluídos**. Falta apenas a recolha do comprovativo visual:

- [ ] **Gravar um vídeo de demonstração (ou screenshots sequenciais):**
  - Colocar as janelas lado a lado no ecrã:
    1. **Gazebo Sim:** Robô a navegar no labirinto (`turtlebot3_dqn_stage4`).
    2. **RViz2:** Mapa do SLAM Toolbox a ser desenhado em tempo real e marcadores cor-de-laranja dos cilindros.
    3. **Terminal:** Logs com `🎯 [CILINDRO DETETADO]` indicando posição $(x, y)$, raio e área da base ($\approx 0.0452\text{ m}^2$).
  - Guardar o vídeo curto ($\approx 1$ minuto) ou capturas de ecrã na pasta `rsdis_t3b/screenshots/` dentro do `GX_t3b.zip`.

---

## Como Executar

### Teste da Parte A (Trabalho 3.1 - Casa)
```bash
# Terminal 1: Iniciar o Gazebo com a Casa
export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_gazebo turtlebot3_house.launch.py

# Terminal 2: Iniciar o Aspirador
cd ~/ros2_ws
source install/setup.bash
ros2 run rsdis_t3a aspirador_node
```

### Teste da Parte B (Trabalho 3.2 - Stage 4, SLAM e Cilindros)
```bash
# Terminal 1: Iniciar o Gazebo com o Stage 4
export TURTLEBOT3_MODEL=burger
ros2 launch turtlebot3_gazebo turtlebot3_dqn_stage4.launch.py

# Terminal 2: Iniciar o sistema completo (Aspirador + SLAM + Deteção + RViz)
cd ~/ros2_ws
source install/setup.bash
ros2 launch rsdis_t3b trabalho.launch.py
```

---

## Estrutura dos Pacotes nos Ficheiros ZIP

- **`GX_t3a.zip`**:
  - `rsdis_t3a/src/robot_aspirador.cpp` (Aspirador com odometria e parede virtual)
  - `rsdis_t3a/CMakeLists.txt` e `package.xml`
  - `rsdis_t3a/screenshots/` (Pasta para os prints da casa após resolver a saída para o exterior)

- **`GX_t3b.zip`**:
  - `rsdis_t3b/src/laser_subscritor.cpp` (Aspirador afinado para o labirinto)
  - `rsdis_t3b/src/identificador_cilindro.cpp` (Deteção de cilindros por largura/área e marcadores RViz)
  - `rsdis_t3b/launch/trabalho.launch.py` (Lança SLAM Toolbox, RViz e nós)
  - `rsdis_t3b/mapa/` (`mapa_stage4.pgm` e `mapa_stage4.yaml`)
  - `rsdis_t3b/rviz/trabalho.rviz`
  - `rsdis_t3b/screenshots/` (Pasta para os prints/vídeo da demonstração)
