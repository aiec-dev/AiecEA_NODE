#include "reuse_data_serialization.h"
#if DATA_REUSE

 
void do_nothing(void*) {}

 
void serialize_single_layer(float*& reuse_data, uint32_t& size, overlapped_tile_data& regions_and_data, tile_region& overlap_index, uint32_t amount_of_element) {
    memcpy(reuse_data, get_data(&regions_and_data, 0), amount_of_element * sizeof(float));
    reuse_data += amount_of_element;
    size += amount_of_element;
}

blob* self_reuse_data_serialization(device_ctxt* ctxt, uint32_t task_id, uint32_t frame_num) {
    cnn_model* model = (cnn_model*)(ctxt->model);
    ftp_parameters_reuse* ftp_para_reuse = model->ftp_para_reuse;
    network_parameters* net_para = model->net_para;
    int32_t* adjacent_id = get_adjacent_task_id_list(model, task_id);

    float* reuse_data = (float*)malloc(ftp_para_reuse->self_reuse_data_size[task_id]);
    uint32_t size = 0;

    for (uint32_t l = ftp_para_reuse->fused_layers - 1; l > 0; l--) { 
        for (uint32_t position = 3; position >= 0; position--) {  
            if (adjacent_id[position] == -1) continue;

            overlapped_tile_data regions_and_data = ftp_para_reuse->output_reuse_regions[task_id][l - 1];  
            tile_region overlap_index = get_region(&regions_and_data, position);

            if (overlap_index.w > 0 && overlap_index.h > 0) {
                uint32_t amount_of_element = overlap_index.w * overlap_index.h * net_para->output_maps[l - 1].c;
#if DEBUG_SERIALIZATION
                if (position == 0) printf("Self below overlapped amount is %d \n", amount_of_element);
               
#endif
                serialize_single_layer(reuse_data, size, regions_and_data, overlap_index, amount_of_element);
            }
        }
    }

    reuse_data -= size;  
    blob* temp = new_blob_and_copy_data((int32_t)task_id, size * sizeof(float), (uint8_t*)reuse_data);
    annotate_blob(temp, get_this_client_id(ctxt), frame_num, task_id);
    free(reuse_data);
    free(adjacent_id);
    return temp;
}

 

#endif