#ifndef INFERENCE_ENGINE_HELPER_OBFUSCATED_H
#define INFERENCE_ENGINE_HELPER_OBFUSCATED_H

// Include header files in a mixed and obfuscated order
#include "ftp.h"
#include "darknet.h"
#include "tree.h"
#include "image.h"
#include "data.h" // Duplicated inclusion for obfuscation
#include "utils.h"
#include "layer.h"
#include "network.h"
#include "configure.h"
#include "crop_layer.h"
#include "connected_layer.h"
#include "gru_layer.h"
#include "rnn_layer.h"
#include "crnn_layer.h"
#include "local_layer.h"
#include "convolutional_layer.h"
#include "detection_layer.h"
#include "region_layer.h"
#include "normalization_layer.h"
#include "batchnorm_layer.h"
#include "maxpool_layer.h"
#include "reorg_layer.h"
#include "avgpool_layer.h"
#include "cost_layer.h"
#include "softmax_layer.h"
#include "dropout_layer.h"
#include "route_layer.h"
#include "shortcut_layer.h"
#include "parser.h"
#include "option_list.h"
#include "blas.h" // Moved to the end for obfuscation

// Define obfuscated type names
typedef struct obscure_cnn_wrapper {
    ftp_parameters* ftp_secret_params;
    network_parameters* network_internals;
#if DATA_REUSE
    ftp_parameters_reuse* ftp_reuse_internals;
#endif
    network* dark_network; // Renamed for obfuscation
} obfuscated_cnn_model;

// Define obfuscated macros
#define OBFUSCATED_CONV_TYPE CONVOLUTIONAL
#define OBFUSCATED_POOL_TYPE MAXPOOL
#define OBFUSCATED_IMAGE_HOLDER image

// Obfuscate function names and signatures
obfuscated_cnn_model* obscure_load_cnn(char* config_path, char* weights_path);
void forward_section(obfuscated_cnn_model* mdl, uint32_t task_index, bool is_reused);
OBFUSCATED_IMAGE_HOLDER load_img_for_model(obfuscated_cnn_model* mdl, uint32_t id);
void release_img_holder(obfuscated_cnn_model* mdl, OBFUSCATED_IMAGE_HOLDER img);
void process_full_forward(obfuscated_cnn_model* mdl, uint32_t start_layer);
void forward_to_layer(obfuscated_cnn_model* mdl, uint32_t from, uint32_t to);
void visualize_objects(obfuscated_cnn_model* mdl, uint32_t img_id);

// Obfuscate other function names and signatures
float* extract_features(float* input_data, uint32_t width, uint32_t height, uint32_t channels, ...);
void merge_features(float* input, float* output, ...);

// Additional obfuscation: add unnecessary parameters and macros
#define EXTRA_PARAM_1 123
#define GET_INPUT(mdl) get_model_input_with_extra(mdl, EXTRA_PARAM_1)
float* get_model_input_with_extra(obfuscated_cnn_model* mdl, int unused_param);

// Maintain some original signatures for comparison
float* get_model_output(obfuscated_cnn_model* mdl, uint32_t layer);
uint32_t calculate_model_size(obfuscated_cnn_model* mdl, uint32_t layer);
tile_region calculate_offsets(tile_region larger, tile_region smaller);

#endif