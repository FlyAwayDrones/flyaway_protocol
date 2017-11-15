#ifndef FLYAWAY_PROTOCOL_H_INCLUDED
#define FLYAWAY_PROTOCOL_H_INCLUDED

#ifndef STDINT_H
#include <stdint.h>
#endif // STDINT_H

#define ENABLE_DEBUG true 

//#include <stdlib.h>
//#include <stdio.h>

typedef enum fad_msg_id : uint8_t{
  FLYAWAY_RADIO_STATUS = 0,
  FLYAWAY_BATTERY_STATUS,
  FLYAWAY_POWER_CONTROL,
  FLYAWAY_ALTITUDE,
  FLYAWAY_MANUAL_CONTROL,
  FLYAWAY_COLLISION_CONTROL,
  FLYAWAY_GPS_CONTROL,
  FLYAWAY_ANGULACAO
} fad_msg_id;

/**
 * @brief Usado como payload para @struct{fad_frame}.
 *
 * Manipular os eixos x,y,z no espaço.
 * @see fad_frame
 */
typedef struct fad_manual_control{
  uint16_t x; /**< Valor que representao eixo 'x' mapeado entre [-1000 | 1000] fad_manual_control#x. */
  uint16_t y; /**< Some documentation for the member BoxStruct#a. */
  uint16_t z; /**< Some documentation for the member BoxStruct#a. */
} fad_manual_control;

typedef struct fad_frame{
  uint8_t msg_id;
  void* payload;
} fad_frame;

/**
 * @brief Cria um pacote do tipo FLYAWAY_MANUAL_CONTROL. 
 * @param frame_t [in] - É usado como entrada para a função de serialização.<b>OBS: Não manipular este parametro como saída da função<b>.
 * @param buff [in|out] - Aonde o pacote serializado é armazenado.
 * @param len [in] - Comprimento do frame_t + buff.
 * @param x [in] - Valor do eixo x em @struct{fad_manual_control}.
 * @param y [in] - Valor do eixo y em @struct{fad_manual_control}.
 * @param z [in] - Valor do eixo z em @struct{fad_manual_control}.
 * @return Retorna 0 para sucesso.
 * 
 * @see fad_manual_control.
 */
int8_t create_manual_control_frame(fad_frame *frame_t, char *buff, uint16_t len, uint16_t x, uint16_t y, uint16_t z);

// salva em frame_t
// len é o tamanho do payload do frame_t e do buff
// a struct frame_t serializada sera armazenada em buff
// essa funcao libera o espaco do payload que foi alocado dinamicamente
void serialize_frame(fad_frame *frame_t, char *buff, uint16_t len);

// retorna o numero que identifica a mensagem
uint8_t get_message_id(char* buff);

// pega buff de dados e deserializa no mesmo *buff
// DEPRECIADA NAO USAR !!!
void decode_serialized_frame(char *buff, uint16_t len);

// monta um fad_manual_control apartir de um buff e salva em manual_control
void decode_manual_control_frame(char *buff, fad_manual_control* manual_control);

// TODO: usar CRC

#include "flyaway_protocol.cc"

#endif // FLYAWAY_PROTOCOL_H_INCLUDED
