#ifndef IO_EXP_PLATFORM_H_
#define IO_EXP_PLATFORM_H_

#include "io_exp_def.h"
#include "esp_err.h"
#include "driver/i2c_master.h"
#include "freertos/FreeRTOS.h"
#include "string.h"


/**
 * @file io_exp_plaftform.h
 *
 * @brief All function that needs to be ported for diffrent device
 */

/**
 * @struct  io_exp_i2c_driver_t
 * @brief   All information that is needed for the i2c communication
 *
 */
typedef struct {
    /*!< user specific field */
    i2c_master_dev_handle_t i2c_dev_handler;

} io_exp_i2c_driver_t;


/**
 * Converts esp_error to io_exp_err
 * @param   err              Error Code
 * @return  IO_EXP_OK        Success
 * @return  "Other error code"    See ::io_exp_def.h
 */
io_exp_err_t esp_to_io_exp_error(esp_err_t err);


/**
 * Writes the supplied byte buffer to the device
 * @param   dev       Device Handle
 * @param   index     The register index
 * @param   pdata     Pointer to uint8_t buffer containing the data to be written
 * @param   count     Number of bytes in the supplied byte buffer
 * @return  IO_EXP_OK             Success
 * @return  "Other error code"    See ::io_exp_def.h
 */
io_exp_err_t io_exp_WriteMulti(io_exp_i2c_driver_t *dev, uint8_t index, uint8_t *pdata, uint32_t count);

/**
 * Reads the requested number of bytes from the device
 * @param   dev       Device Handle
 * @param   index     The register index
 * @param   pdata     Pointer to the uint8_t buffer to store read data
 * @param   count     Number of uint8_t's to read
 * @return  IO_EXP_OK             Success
 * @return  "Other error code"    See ::io_exp_def.h
 */
io_exp_err_t io_exp_ReadMulti(io_exp_i2c_driver_t *dev, uint8_t index, uint8_t *pdata, uint32_t count);

/**
 * Write single byte register
 * @param   dev       Device Handle
 * @param   index     The register index
 * @param   data      8 bit register data
 * @return  IO_EXP_OK             Success
 * @return  "Other error code"    See ::io_exp_def.h
 */
io_exp_err_t io_exp_WrByte(io_exp_i2c_driver_t *dev, uint8_t index, uint8_t data);

/**
 * Write word register
 * @param   dev       Device Handle
 * @param   index     The register index
 * @param   data      16 bit register data
 * @return  IO_EXP_OK             Success
 * @return  "Other error code"    See ::io_exp_def.h
 */
io_exp_err_t io_exp_WrWord(io_exp_i2c_driver_t *dev, uint8_t index, uint16_t data);

/**
 * Write double word (4 byte) register
 * @param   dev       Device Handle
 * @param   index     The register index
 * @param   data      32 bit register data
 * @return  IO_EXP_OK        Success
 * @return  "Other error code"    See ::io_exp_def.h
 */
io_exp_err_t io_exp_WrDWord(io_exp_i2c_driver_t *dev, uint8_t index, uint32_t data);

/**
 * Read single byte register
 * @param   dev       Device Handle
 * @param   index     The register index
 * @param   data      pointer to 8 bit data
 * @return  IO_EXP_OK             Success
 * @return  "Other error code"    See ::io_exp_def.h
 */
io_exp_err_t io_exp_RdByte(io_exp_i2c_driver_t *dev, uint8_t index, uint8_t *data);

/**
 * Read word (2byte) register
 * @param   dev       Device Handle
 * @param   index     The register index
 * @param   data      pointer to 16 bit data
 * @return  IO_EXP_OK             Success
 * @return  "Other error code"    See ::io_exp_def.h
 */
io_exp_err_t io_exp_RdWord(io_exp_i2c_driver_t *dev, uint8_t index, uint16_t *data);

/**
 * Read dword (4byte) register
 * @param   dev       Device Handle
 * @param   index     The register index
 * @param   data      pointer to 32 bit data
 * @return  IO_EXP_OK             Success
 * @return  "Other error code"    See ::io_exp_def.h
 */
io_exp_err_t io_exp_RdDWord(io_exp_i2c_driver_t *dev, uint8_t index, uint32_t *data);

#endif