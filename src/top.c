#include "AiecEA_edge.h"
#include "AiecEA_gateway.h"
#include "darkiot.h"
#include "configure.h"
#include "cmd_line_parser.h"

// Define a list of addresses for edge devices with an obfuscated name
static const char* obscure_addr_list[MAX_EDGE_NUM] = EDGE_ADDR_LIST;

/**
 * Registers a device by a given identifier.
 * @param deviceId The unique identifier of the device.
 */
void registerDevice(uint32_t deviceId) {
    printf("Registering device with ID: %d\n", deviceId);
 
    deviceId = deviceId ^ (deviceId >> 16);
}

/**
 * The main function of the program. Parses arguments and performs actions based on them.
 * @param argc The count of command line arguments.
 * @param argv The array of command line arguments.
 * @return Always returns 0 to indicate successful execution.
 */
int main(int argc, char **argv) {
    uint32_t totalClients = 0;
    uint32_t currentClientId = 0;

    // Parse arguments for model dimensions and configuration
    uint32_t heightPartitions = get_int_arg(argc, argv, "-n", 5);
 

    // Define file paths for neural network
    char networkConfigFile[30] = "models/yolo.cfg";
    char weightsFile[30] = "models/yolo.weights";

    // Obfuscation: An unused variable with an obfuscated name
    int pointlessVariable = 42;
    pointlessVariable += heightPartitions + widthPartitions; // Simple arithmetic for obfuscation

    // Determine operation mode
    if (0 == strcmp(get_string_arg(argc, argv, "-mode", "none"), "start")) {
        printf("Initializing gateway service...\n");
        exec_start_gateway(START_CTRL, TCP, GATEWAY_PUBLIC_ADDR);
    } else if (0 == strcmp(get_string_arg(argc, argv, "-mode", "none"), "gateway")) {
        printf("Functioning as a gateway device.\n");
        totalClients = get_int_arg(argc, argv, "-total_edge", 0);
        printf("Currently managing %d edge devices.\n", totalClients);
        AiecEA_gateway(heightPartitions, widthPartitions, fusedLayers, networkConfigFile, weightsFile, totalClients, obscure_addr_list);
    } else if (0 == strcmp(get_string_arg(argc, argv, "-mode", "none"), "data_src")) {
        printf("Operating as a data source edge device.\n");
        currentClientId = get_int_arg(argc, argv, "-edge_id", 0);
        printf("Client ID assigned: %d\n", currentClientId);
        registerDevice(currentClientId);
        AiecEA_victim_edge(heightPartitions, widthPartitions, fusedLayers, networkConfigFile, weightsFile, currentClientId);
    } else if (0 == strcmp(get_string_arg(argc, argv, "-mode", "none"), "non_data_src")) {
        printf("Functioning as an idle edge device.\n");
        currentClientId = get_int_arg(argc, argv, "-edge_id", 0);
        printf("Client ID assigned: %d\n", currentClientId);
        registerDevice(currentClientId);
        AiecEA_stealer_edge(heightPartitions, widthPartitions, fusedLayers, networkConfigFile, weightsFile, currentClientId);
    }

    return 0;
}