# Repositório de RSDIS - Redes e Sistemas Distribuídos
**Mestrado em Engenharia Eletrotécnica e de Computadores (MEEC / ISEP)**

Repositório com os trabalhos práticos desenvolvidos na unidade curricular de RSDIS utilizando ROS 2 (Jazzy) e Gazebo.

---

## Estrutura do Repositório

### 📂 [Trabalho 1](Trabalho_1/)
- **Parte A (`GX_t1a.zip`):** Criação de pacote ROS 2 com Publisher e Subscriber de mensagens numéricas padrão.
- **Parte B (`GX_t1b.zip`):** Comunicação com tipos de mensagens geométricas e comprovação de tópicos.

### 📂 [Trabalho 2](Trabalho_2/)
- **Parte A (`GX_t2a.zip`):** Publisher com mensagens customizadas.
- **Parte B (`GX_t2b.zip`):** Servidor UGV com serviços de conversão de coordenadas (ECEF, geográficas, graus/radianos).
- **Parte I (`GX_t2i.zip`):** Interfaces e definições de serviços `.srv`.

### 📂 [Trabalho 3](Trabalho_3/) (Em Curso)
- **Parte A (`GX_t3a.zip` - Trabalho 3.1):** Robô aspirador autónomo a explorar o cenário `turtlebot3_house` no Gazebo sem colisões.
- **Parte B (`GX_t3b.zip` - Trabalho 3.2):**
  1. Exploração autónoma sem colisão no labirinto `turtlebot3_stage_4`.
  2. Identificação de cilindros com LiDAR 2D (posição, raio e cálculo da área da base $\pi r^2$).
  3. Construção do mapa 2D do cenário via SLAM (`slam_toolbox` / `cartographer`).

> ℹ️ **Consulte o documento detalhado [Trabalho_3/README.md](Trabalho_3/README.md) para ver o estado atual dos requisitos e os passos pendentes para a entrega.**
