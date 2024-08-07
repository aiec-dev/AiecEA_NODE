
![image](https://img.shields.io/badge/AIEC_TEAM-AI-blue)
![image](https://img.shields.io/badge/AIEC_TEAM-hardware-blue)
![image](https://www.aiec.pro/gitimage/githead.png)


***AIEC Edge Computing: AiecEA Framework***

AiecEA is a framework specifically designed for resource-constrained IoT (Internet of Things) edge clusters, aimed at achieving local distributed and adaptive Convolutional Neural Network (CNN) inference. The framework primarily consists of two core components:

1.  **Fusion Tile Partitioning (FTP) Method**: This method is used to divide convolutional layers into independently distributable tasks. By fusing layers and vertically partitioning them in a grid manner, the FTP method significantly reduces communication and task migration overhead.

2.  **Distributed Work-Stealing Runtime System**: Designed specifically for IoT clusters, this system can adaptively allocate FTP partitions in dynamic application scenarios to optimize resource utilization and inference efficiency.
 
![image](https://www.aiec.pro/gitimage/p1.png)
> PCB Pinout Definition Diagram
![image](https://www.aiec.pro/gitimage/p2.png)

![image](https://www.aiec.pro/gitimage/p3.png)
> We will open source all EPS development mainboards, schematic diagrams, and firmware codes on August 20th.


**Deep Dive into the AI Edge Computing Framework: AiecEA**

AiecEA is an advanced framework tailored for IoT edge computing environments. It combines core technologies from Artificial Intelligence (AI) and edge computing to enable efficient, adaptive CNN inference in resource-constrained edge clusters. The following is an in-depth introduction to the AiecEA framework and its AI edge computing capabilities:

### I. Overview of AI Edge Computing

AI edge computing is an emerging branch in the field of edge computing that combines AI technology with edge computing to bring computing and data processing capabilities closer to the source of data generation. This computing model significantly reduces data transmission latency, enhances processing efficiency, and strengthens data privacy protection. In domains such as IoT, smart manufacturing, and intelligent transportation, AI edge computing is gradually becoming a key technology for realizing intelligent and real-time applications.

### II. Core Features of the AiecEA Framework

1.  **Fusion Tile Partitioning (FTP) Method**:
    *   **Definition**: The FTP method is an innovative convolutional layer partitioning strategy that vertically partitions convolutional layers in a grid format, forming independently processable task units.
    *   **Advantages**: Through FTP, AiecEA can significantly reduce communication overhead and task migration costs, improving the efficiency and scalability of distributed inference.

2.  **Distributed Work-Stealing Runtime System**:
    *   **Function**: This system is designed specifically for dynamic IoT clusters and can intelligently monitor cluster loads and adaptively allocate FTP partition tasks.
    *   **Characteristics**: Supports a work-stealing mechanism, allowing idle nodes to actively take on tasks from other nodes, thereby balancing cluster loads and improving resource utilization.

3.  **AI Edge Computing Optimization**:
    *   **Real-time Performance**: AiecEA deploys AI computing capabilities on edge devices, achieving low-latency data processing and decision feedback, suitable for application scenarios with extremely high real-time requirements.
    *   **Privacy Protection**: By processing sensitive data locally, AiecEA avoids the risks associated with transmitting and processing large amounts of data in the cloud, enhancing data privacy protection capabilities.
    *   **Efficient Resource Utilization**: Leveraging the computing and storage resources of edge devices, AiecEA reduces reliance on cloud resources, lowering bandwidth consumption and operational costs.

### III. Application of AI Edge Computing in AiecEA

In the AiecEA framework, AI edge computing is not only embodied in the FTP partitioning method and distributed runtime system but also permeates the entire inference process. By integrating advanced AI algorithms and models, AiecEA can achieve efficient image recognition, target tracking, anomaly detection, and other functions on edge devices. For example, in the field of intelligent transportation, AiecEA can utilize vehicle-mounted cameras and sensor data to analyze road conditions and traffic behavior in real-time on edge devices, providing precise decision support for intelligent driving.

### IV. Conclusion

The AiecEA framework is an innovative achievement in the field of AI edge computing. By integrating the fusion tile partitioning method and distributed work-stealing runtime system, it achieves efficient and adaptive CNN inference. In the future, with the continuous development of IoT technology and the sustained enhancement of edge computing capabilities, AiecEA is expected to play a significant role in more domains, driving the popularization and deepening of intelligent applications. Meanwhile, as a cutting-edge computing model, AI edge computing will continue to lead the direction of technological innovation.

## Compilation and Deployment

To deploy AiecEA in your IoT cluster, you need to edit the configuration file `include/aiec_run.h` to adapt to your cluster parameters. Then, execute the following commands to compile the framework and generate executable files:

```bash
make clean_all
make
```

If you plan to run AiecEA on a Raspberry Pi, you need to prepare by following the `installNNPACK` instructions and setting the following options in the Makefile:

```bash
NNPACK=1
ARM_NEON=1
```

## Distributed Inference

To perform distributed inference, you need to download pre-trained CNN models and place them in the `./models` folder. The current implementation has been tested with YOLOv2. You can download the YOLOv2 model and weights from the provided link. If the link is unavailable, you can obtain these weights from other sources.

Input data needs to be numbered (starting from 0) and renamed to `<#>.jpg` and placed in the `./data/input` folder.

## Running in an IoT Cluster

AiecEA provides the following command-line options for starting and running in an IoT cluster:

```bash
./AiecEA -mode <execution mode: {start, gateway, data_src, non_data_src}> 
             -total_edge <total edge number: t> 
             -edge_id <edge device ID: {0, ... t-1}>
             -n <FTP dimension: N> 
             -m <FTP dimension: M> 
             -l <number of fused layers: L>
```

For example, suppose you have a host H, a gateway device G, and two edge devices E0 (data source) and E1 (idle), and you want to execute a 5x16 FTP with 5 fused layers. You can run the following commands on each device:

On gateway device G:

```bash
./AiecEA -mode gateway -total_edge 2 -n 5 -m 5 -l 16
```

On edge device E0:

```bash
./AiecEA -mode data_src -edge_id 0 -n 5 -m 5 -l 16
```

On edge device E1:

```bash
./AiecEA -mode non_data_src -edge_id 1 -n 5 -m 5 -l 16
```

All devices will wait for a trigger signal to start the inference process. You can execute the following command on host H to trigger inference:

```bash
./AiecEA -mode start
```

## Running on a Single Device

To simplify testing and verification, AiecEA provides examples of running FTP partition inference on a single device. You can find these examples in the `./examples` folder. To run them, execute the following commands:

```bash
make clean_all
make
make test
```

This will initialize gateway and client contexts and simulate device-to-device communication and FTP partition inference processes in different local threads. Inference results will be transmitted between queues associated with each context.
