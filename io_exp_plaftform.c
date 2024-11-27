#include "io_exp_plaftform.h"


io_exp_err_t esp_to_io_exp_error(esp_err_t err) {
  switch (err) {
    case ESP_OK:
      return IO_EXP_OK;
    case ESP_ERR_INVALID_ARG:
      return IO_EXP_ERR_INVALID_PARAMS;
    case ESP_FAIL:
    case ESP_ERR_INVALID_STATE:
      return IO_EXP_ERR_INVALID_STATE;
    case ESP_ERR_TIMEOUT:
      return IO_EXP_ERR_TIMEOUT;
    default:
      return IO_EXP_FAIL;
  }
}

io_exp_err_t io_exp_WriteMulti(io_exp_i2c_driver_t *dev, uint8_t index, uint8_t *pdata, uint32_t count){
  uint8_t buffer[count + 1];

  buffer[0] = index;
  memcpy(buffer + sizeof(uint8_t), pdata, count);

  return esp_to_io_exp_error(i2c_master_transmit(dev->i2c_dev_handler, buffer, sizeof(buffer)/sizeof(uint8_t), 1000 / portTICK_PERIOD_MS) );
}

io_exp_err_t io_exp_ReadMulti(io_exp_i2c_driver_t *dev, uint8_t index, uint8_t *pdata, uint32_t count){
  esp_err_t ret = i2c_master_transmit_receive(dev->i2c_dev_handler, &index, sizeof(index), pdata, count, 1000 / portTICK_PERIOD_MS);

  return esp_to_io_exp_error(ret);
}

io_exp_err_t io_exp_WrByte(io_exp_i2c_driver_t *dev, uint8_t index, uint8_t data){
  return io_exp_WriteMulti(dev, index, &data, 1);
}

io_exp_err_t io_exp_WrWord(io_exp_i2c_driver_t *dev, uint8_t index, uint16_t data){
    uint8_t buffer[2]; // 2
    buffer[0] = (uint8_t)(data >> 8);
    buffer[1] = (uint8_t)(data &  0x00FF);

    return io_exp_WriteMulti(dev, index, buffer, 2);
}

io_exp_err_t io_exp_WrDWord(io_exp_i2c_driver_t *dev, uint8_t index, uint32_t data){
    uint8_t buffer[4]; // 4

    buffer[0] = (uint8_t) (data >> 24);
    buffer[1] = (uint8_t)((data &  0x00FF0000) >> 16);
    buffer[2] = (uint8_t)((data &  0x0000FF00) >> 8);
    buffer[3] = (uint8_t) (data &  0x000000FF);

    return io_exp_WriteMulti(dev, index, buffer, 4);
}

io_exp_err_t io_exp_RdByte(io_exp_i2c_driver_t *dev, uint8_t index, uint8_t *data){
  return io_exp_WriteMulti(dev, index, data, 1);
}

io_exp_err_t io_exp_RdWord(io_exp_i2c_driver_t *dev, uint8_t index, uint16_t *data){
    io_exp_err_t status;
    uint8_t  buffer[2];

    status = io_exp_WriteMulti(dev, index, buffer, 2);
    *data = ((uint16_t)buffer[0]<<8) + (uint16_t)buffer[1];

    return status;
}

io_exp_err_t io_exp_RdDWord(io_exp_i2c_driver_t *dev, uint8_t index, uint32_t *data){
    io_exp_err_t status;
    uint8_t  buffer[4];

    status = io_exp_WriteMulti(dev, index, buffer, 4);
    *data = ((uint32_t)buffer[0]<<24) + ((uint32_t)buffer[1]<<16) +
             ((uint32_t)buffer[2]<<8) + (uint32_t)buffer[3];

    return status;
}

