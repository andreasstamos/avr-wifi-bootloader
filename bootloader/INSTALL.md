# Bootloader Installation Guide

## If you only want to install the prebuilt WiFi Bootloader *(given by the `main.hex` and `eeprom.bin` files)*:

1. **Install AVRDUDE:**

	```bash
sudo apt install avr-dude
	```

2. **Connect the ntuAboard to your PC using USB.**

3. **Enter `bootloader/` folder.**

4. **Execute `./install.sh.`**

5. **Success!**

	WiFi bootloader has been successfully installed. You may proceed to send a program.
	
	Follow the instructions given in [../quickstart.md](../quickstart.md).

## If you also want to compile from scratch the WiFi Bootloader:

1. **Install cross compiler AVR-GCC, AVR-LIBC:**

	``bash
sudo apt install avr-gcc avr-libc (in Ubuntu/Debian)
	``bash

2. **Download the necessary files from Microchip.**
	
	Go to: [http://packs.download.atmel.com/](http://packs.download.atmel.com/)

	and download the Atmel ATmega Series Device Support.

3. **Unzipping the .atpack file.**

	Create a folder pack/ in the `../` folder.

	Unzip inside it the `.atpack` file (it is a `.zip` file) you just downloaded in Step 2.

4. **Enter `bootloader/`.**

5. **Building**.:

	Run:
	```bash
	make install
	```

6. **Sucesss!**
	
	WiFi bootloader has been successfully installed. You may proceed to send a program.
	
	Follow the instructions given in [../quickstart.md](../quickstart.md).
