# Trabalho 3: Gazebo & TurtleBot3

Este diretório contém as entregas do **Trabalho 3.1 (Parte A)** e **Trabalho 3.2 (Parte B)** da unidade curricular de **Redes e Sistemas Distribuídos (RSDIS)** - Mestrado em Engenharia Eletrotécnica e de Computadores (MEEC / ISEP).

Ambiente: **Ubuntu 24.04 LTS**, **ROS 2 Jazzy**, **Gazebo Sim** (gz-sim), modelo **TurtleBot3 Burger**.

---

## Estado Atual do Trabalho

| Requisito do Enunciado | Estado do Código | Elementos de Comprovação |
| :--- | :---: | :---: |
| **Parte A (3.1):** Aspirador na Casa (`turtlebot3_house`) | ✅ Concluído (100%) | ⏳ **Falta tirar screenshots** |
| **Parte B (3.2):** Exploração no Labirinto (`stage_4`) | ✅ Concluído (100%) | ⏳ **Falta vídeo / screenshots** |
| **Parte B (3.2):** Deteção de Cilindros via LiDAR 2D | ✅ Concluído (100%) | ⏳ **Falta screenshot do terminal/RViz** |
| **Parte B (3.2):** Construção do Mapa 2D (SLAM) | ✅ Concluído (100%) | ✅ Mapa salvo (`.pgm` / `.yaml`) |

---

## O que FALTA FAZER para Finalizar a Entrega

Todo o desenvolvimento em C++, compilação no ROS 2 Jazzy e geração do mapa SLAM estão **completos e testados**. 
Faltam apenas os **elementos visuais de comprovação** exigidos para avaliação:

### 1. Na Parte A (`GX_t3a.zip` - Trabalho 3.1)
- [ ] **Tirar 1 ou 2 screenshots do robô na casa:**
  - Abrir o cenário `turtlebot3_house` e correr o nó `aspirador_node`.
  - Capturar o ecrã a mostrar o robô a navegar sem colidir com as mobílias.
  - Guardar as imagens na pasta `rsdis_t3a/screenshots/` dentro do `GX_t3a.zip`.

### 2. Na Parte B (`GX_t3b.zip` - Trabalho 3.2)
- [ ] **Gravar um vídeo de demonstração (ou screenshots sequenciais):**
  - O enunciado valoriza a demonstração visual completa.
  - Colocar as janelas lado a lado:
    1. **Gazebo Sim:** Robô a navegar no labirinto (`turtlebot3_dqn_stage4`).
    2. **RViz2:** Mapa do SLAM a ser construído em tempo real e marcadores cor-de-laranja dos cilindros.
    3. **Terminal:** Mensagens `🎯 [CILINDRO DETETADO]` com as coordenadas $(x, y)$, raio e a área da base calculada ($\approx 0.0452\text{ m}^2$).
  - Guardar o vídeo curto ($\approx 1$ minuto) ou screenshots na pasta `rsdis_t3b/screenshots/` dentro do `GX_t3b.zip`.

---

## Como Executar para Obter os Comprovativos

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
  - `rsdis_t3a/screenshots/` (Pasta para colocar os prints da casa)

- **`GX_t3b.zip`**:
  - `rsdis_t3b/src/laser_subscritor.cpp` (Aspirador com paragem a 30 cm)
  - `rsdis_t3b/src/identificador_cilindro.cpp` (Deteção por largura/área e marcadores RViz)
  - `rsdis_t3b/launch/trabalho.launch.py` (Lança SLAM Toolbox, RViz e nós)
  - `rsdis_t3b/mapa/` (`mapa_stage4.pgm` e `mapa_stage4.yaml`)
  - `rsdis_t3b/rviz/trabalho.rviz`
  - `rsdis_t3b/screenshots/` (Pasta para colocar os prints/vídeo da demonstração)
