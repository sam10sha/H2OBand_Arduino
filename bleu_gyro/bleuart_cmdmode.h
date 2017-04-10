/**************************************************************************/
/*!
    @brief  Sets up the HW an the BLE module (this function is called
            automatically on startup)
*/
/**************************************************************************/
void bleuart_setup(void);



/**************************************************************************/
/*!
    @brief  Constantly poll for new command or response data
*/
/**************************************************************************/
void blueart_operate(void);

/// Sends the bytes in msg through the bluefruit
/// @param msg   The message to send through the bleuart
void bleuart_send(char* msg);
