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
/// Ensures that the last character of msg is null termination character
/// @param msg   The message to send through the bleuart
/// @param len   The length of the message to send
void bleuart_send(char* msg, int len);
