#ifndef AiecEA_GATEWAY_H
#define AiecEA_GATEWAY_H
#include "darkiot.h"
#include "configure.h"
void AiecEA_work_stealing_thread(void *arg);
device_ctxt* AiecEA_gateway_init(uint32_t N, uint32_t M, uint32_t fused_layers, char* network, char* weights, uint32_t total_edge_number, const char** addr_list);
void AiecEA_gateway(uint32_t N, uint32_t M, uint32_t fused_layers, char* network, char* weights, uint32_t total_edge_number, const char** addr_list);
#endif
