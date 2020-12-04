/* Self header */
#include <ds2411.h>

/* Arduino libraries */
#include <OneWire.h>

/* Config */
#if CONFIG_DS2411_DEBUG_ENABLED
#define CONFIG_DS2411_DEBUG_FUNCTION(x) Serial.println(x)
#else
#define CONFIG_DS2411_DEBUG_FUNCTION(x)
#endif

/**
 * Default constructor.
 */
ds2411::ds2411() {
	m_pin = 0;
	m_pin_defined = false;
}

/**
 * Configures the driver.
 * @note Call this from the Arduino setup function.
 * @param[in] pin The pin number that will be used for one wire communication with the device.
 */
void ds2411::setup(const int pin) {
	m_pin = pin;
	m_pin_defined = true;
}

/**
 * Reads the unique id from the device.
 * @param[out] bytes A pointer to an 8 bytes array that will be updated with the uid read from the device.
 * @return 0 in case of success, or a negative error code otherwise.
 */
int ds2411::read(uint8_t bytes[8]) {
	int res;

	/* Ensure pin has been defined */
	if (!m_pin_defined) {
		return -EINVAL;
	}

	/* Instantiate one wire bus */
	OneWire ow(m_pin);

	/* Perform a bus reset */
	res = ow.reset();
	if (res != 1) {
		CONFIG_DS2411_DEBUG_FUNCTION(" [e] Failed to find ic!");
		return -EIO;
	}

	/* Request to read data */
	ow.write(0x33, 0);
	ow.read_bytes(bytes, 8);

	/* Check crc */
	if (bytes[7] != ow.crc8(bytes, 7)) {
		CONFIG_DS2411_DEBUG_FUNCTION(" [e] Invalid crc!");
		return -1;
	}

	/* Return success */
	return 0;
}
