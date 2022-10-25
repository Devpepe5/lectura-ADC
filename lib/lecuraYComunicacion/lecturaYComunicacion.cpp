//#include <Arduino.h>
#include"lecturaYComunicacion.h"
//#include <driver/can.h>
//#include <driver/gpio.h>

  void setup_can_driver(){
  Serial.begin(115200);// se comentó  esta linea de codigo y se quitó en todas la llamadas al objeto 

  //en un dato de tipo struct se guarda la condiguración del modulo can
  can_general_config_t general_config={
    .mode = CAN_MODE_NORMAL,
    .tx_io=(gpio_num_t) GPIO_NUM_5,// declaramos el GPIO5 como el transmisor
    .rx_io=(gpio_num_t)GPIO_NUM_4,//declaramos el GPIO4 como receptor 
    .clkout_io=(gpio_num_t)CAN_IO_UNUSED,//no se usa algún 
    .bus_off_io=(gpio_num_t)CAN_IO_UNUSED,
    .tx_queue_len=0,// en el ejemplo no se transmite 
    .rx_queue_len=65,
    .alerts_enabled= CAN_ALERT_ALL,
    .clkout_divider=0,

  };
  can_timing_config_t timing_config = CAN_TIMING_CONFIG_250KBITS();// velocidad del bus esp32 
  can_filter_config_t filter_config = CAN_FILTER_CONFIG_ACCEPT_ALL();
  esp_err_t error;
  error=can_driver_install(&general_config,&timing_config,&filter_config);
  if (error==ESP_OK){
    Serial.println("instalación del driver CAN correcta ");
    }
    else{
      Serial.println("La instalación del driver CAN falló");
      return;
    }
   error=can_start();
   if(error==ESP_OK) {
    Serial.println("el driver CAN ha iniciado ");
   }
   else{
    Serial.println("el driver CAN falló al iniciar");
   }
}
   
  void readCanFrame(void){
  can_message_t rx_frame;
  if(can_receive(&rx_frame,pdMS_TO_TICKS(1000))==ESP_OK){
    Serial.printf("from 0x%08X,DLC%d,Data",rx_frame.identifier,rx_frame.data_length_code);
    for (int i = 0; i < rx_frame.data_length_code; i++){
      printf("ox%02X",rx_frame.data[i]);
    }
    printf("\n");
  }

}
