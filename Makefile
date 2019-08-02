all:
	pio run --target upload

monitor:
	platformio device monitor
