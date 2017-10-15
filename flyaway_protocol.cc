
// salva sainda em frame_t
int8_t create_manual_control_frame(fad_frame *frame_t, char *buff, uint16_t len, uint16_t x, uint16_t y, uint16_t z)
{

  fad_manual_control manual_control;

  manual_control.x = x;
  manual_control.y = y;
  manual_control.z = z;

  frame_t->payload = &manual_control;
  frame_t->msg_id = FLYAWAY_MANUAL_CONTROL;
  fad_manual_control *mc = (fad_manual_control*) frame_t->payload;
  //printf("x=%u y=%u, z=%u", mc->x, mc->y, mc->z);

  serialize_frame(frame_t, buff, len);

  return 0;
}

// esta funcao é chamada sempre pelas funcoes de 'criacao de frame' para que nao façamos alocação dinamica
// salva em frame_t
// len é o tamanho do payload do frame_t e do buff
// a struct frame_t serializada sera armazenada em buff
void serialize_frame(fad_frame *frame_t, char *buff, uint16_t len)
{
  uint16_t buff_len;
  buff[0] = *((char *) &frame_t->msg_id);
  //printf("msgid = %u ", buff[0]);

  switch((uint8_t) buff[0])
  {
  case FLYAWAY_MANUAL_CONTROL:
    buff_len = sizeof(fad_manual_control);
    break;
    default: break;
  }

  for(int i = 1, k = 0; i < buff_len; i++, k++){
    buff[i] = *((char *) frame_t->payload + k);
    //printf("int=%u ", buff[i]);
  }

  //printf("\n");

}

uint8_t get_message_id(char* buff)
{
  return (uint8_t) buff[0];
}

// pega buff de dados e deserializa no mesmo *buff
void decode_serialized_frame(char *buff, uint16_t len)
{
  uint8_t msgid = (uint8_t) buff[0];
  //printf("msgid=%u\n", msgid);

  for(int i = 0; i < len; i++){
    //printf("int=%u ", buff[i]);
  }

}

void decode_manual_control_frame(char *buff, fad_manual_control* manual_control)
{
    uint16_t i = 1;
    manual_control->x = buff[i] + buff[i+1];
    manual_control->y = buff[i+2] + buff[i+3];
    manual_control->z = buff[i+4] + buff[i+5];
}
