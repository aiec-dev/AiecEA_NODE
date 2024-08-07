#include "test_utils.h"

static const char* addr_list[MAX_EDGE_NUM] = EDGE_ADDR_LIST;

int main(int argc, char **argv){
   /*Initialize the data structure and network model*/
   uint32_t total_cli_num = get_int_arg(argc, argv, "-total_edge", 1);
   uint32_t this_cli_id = get_int_arg(argc, argv, "-edge_id", 0);

   uint32_t partitions_h = get_int_arg(argc, argv, "-n", 3);
   uint32_t partitions_w = get_int_arg(argc, argv, "-m", 3);
   uint32_t fused_layers = get_int_arg(argc, argv, "-l", 8);

   char network_file[30] = "../models/yolo.ini";
   char weight_file[30] = "../models/yolo.weights";

   device_ctxt* client_ctxt = AiecEA_edge_init(partitions_h, partitions_w, fused_layers, network_file, weight_file, this_cli_id);
   device_ctxt* gateway_ctxt = AiecEA_gateway_init(partitions_h, partitions_w, fused_layers, network_file, weight_file, total_cli_num, addr_list);
   
   /*Multi-threaded version*/ 
   
   sys_thread_t t1 = sys_thread_new("partition_frame_and_perform_inference_thread_single_device", 
                                     partition_frame_and_perform_inference_thread_single_device, client_ctxt, 0, 0);
   sys_thread_t t2 = sys_thread_new("AiecEA_merge_result_thread_single_device", AiecEA_merge_result_thread_single_device, gateway_ctxt, 0, 0);
   transfer_data(client_ctxt, gateway_ctxt);
   printf("Finished Transferring Data\n"); 
   sys_thread_join(t1);
   sys_thread_join(t2);
   
  
   return 0;
}

