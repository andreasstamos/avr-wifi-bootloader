# Quickstart guide

The following assumes that the WiFi Bootloader is already installed on the ntuAboard. If not, follow the instructions
in the [bootloader/INSTALL.md](bootloader/INSTALL.md). You need to install the WiFi Bootloader only once.

## Steps to get started

1. **Install cross compiler AVR-GCC and AVR-LIBC.**
	
	```bash
	sudo apt install avr-gcc avr-libc
	```

2. **Download the necessary files from Microchip.**

	Visit: [http://packs.download.atmel.com/](http://packs.download.atmel.com/)

	and download the Atmel ATmega Series Device Support.

3. **Unzipping the .atpack file.**

	Create a folder pack/ in the current folder.

	Unzip inside it the `.atpack` file (it is a `.zip` file) you just downloaded in Step 2.

4. **Install Python requirements.**
	a. Enter `server/` folder.
	b. Install the `requirements.txt`:

	```bash
	pip install -r requirements.txt
	```

	**Optional:** This can be done in a Python Virtual Environment to ensure nothing messes up wih your system's configuration.
	To do this:

	```bash
	python3 -m venv .venv
	source .venv/bin/activate
	pip install -r requirements.txt
	```

5. **Add your code files.**

	Copy your main C code file in the `server/` folder and rename it to `main.c.`

	Copy there also any additional code file (e.g. C header files) you might have.

	**Notice:** The `Makefile` that is currently in the `server/` folder is just for the example `main.c` that is given.

	You should copy the `Makefile.template` to `Makefile`.

	If you want to use Seperate Compilation add the desired `.o` files
	as dependencies for the `main.o` target. (as in the example `Makefile`)

6. **Build and deploy.**
	
	Inside the `server/` folder run:

	```bash
	make deploy
	```
	
	Your code will be compiled and then a server will be hosted that will send the executable to the ntuAboard.

	*Note that your IP address will be logged in the terminal. (this is necessary for the next step)*

7. **Load on the ntuAboard.**

	Power on the ntuAboard.
	
	Enter your PC's IP address.
	
	Use `'*'` instead of `'.'`
	
	When you have finished typing, enter `'#'`.

	e.g. `192.168.1.1` shall be typed as `192*168*1*1#`

8. **Success!**

	The bootloader will download the executable, flash it to the Program Memory and then automatically run it.
	It might take a few seconds. (this latency is mostly due to the connection to the WiFi network)

---

*Common issue:* Make sure that your firewall does not block the TCP port 5000 that is used by the server.

