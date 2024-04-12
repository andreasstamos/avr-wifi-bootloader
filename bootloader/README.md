# Installation/Compilation

Read the [bootloader/INSTALL.md](bootloader/INSTALL.md) in order to find out how to
install (and optionally compile) the bootloader.

---

# How the bootloader works?

1. The 1st Stage starts from Program Memory address 0x3000.

2. The 2nd Stage is loaded from EEPROM to SRAM

	and then flashed to the Program Memory.

3. The 2nd Stage is executed. Messages are displayed to the LCD screen and the user is
asked to type the Server IP Address in they keypad.

4. The 2nd Stage delivers the IP Address string to the 1st Stage and control is given back to the 1st Stage.

5. The bootloader requests the server for the number of memory pages.

	This happens via an HTTP **POST** at `[IP ADDR]:5000/npages`

6. The bootloader requests the server for the binary content of each page.
	
	This happens via an HTTP **POST** at `[IP ADDR]:5000/data`

7. The server responds with a **Base64** encoding of the page.

	This is due to the ESP8266 firmware that expects alphanumeric words and might not handle
	correctly other binary data.

	The Base64 encoded page is decoded in the Bootloader with a custom written Base64 decoder.

8. Each page is flashed to the Program Memory.

9. The bootloader jumps to the program it just flashed (at address `0`).

	The program then executes normally as if it was flashed from a PC.

