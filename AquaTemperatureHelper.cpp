#include "AquaTemperatureHelper.h"
#include "ClockHelper.h"
#include "OneWire.h"
#include "LedRgbHelper.h"

AquaTemperatureHelper* AquaTemperatureHelper::m_pInstance = NULL;
AquaTemperatureHelper* AquaTemperatureHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new AquaTemperatureHelper;

	return m_pInstance;
}

void AquaTemperatureHelper::setup(uint8_t tempSensorPinNum)
{
	pinMode(tempSensorPinNum, INPUT);
	oneWire = OneWire(tempSensorPinNum);
	
}

void AquaTemperatureHelper::loop()
{
	if (!ClockHelper::Instance()->isUpdatedByTimer)
	{
		ReadTemperature();

		//tempAnalog = analogRead(A0);
		//currentTempValue = GetTemperatureValue();

		if (currentTempValue < minAquaTemp)
		{
			isAquaVeryCold = true;
			isAquaNorm = false;
		}
		else if (currentTempValue > maxAquaTemp)
		{
			isAquaVeryHeat = true;
			isAquaNorm = false;
		}
		else
		{
			isAquaVeryCold = false;
			isAquaVeryHeat = false;

			isAquaNorm = true;
		}
	}
}

void AquaTemperatureHelper::ReadTemperature()
{
	byte addr[8];

	oneWire.reset_search();
	if (!oneWire.search(addr)) {
		oneWire.reset_search();
		return;
	}

	oneWire.reset();
	oneWire.select(addr);
	oneWire.write(0x44, 1);         // start conversion, with parasite power on at the end


	// обращаемс€ к датчикам раз в 1000 мс, т.к. 750 может быть недостаточно
	if (millis() - lastTempShortUpdatedTime > 1000)
	{
		lastTempShortUpdatedTime = millis();

		oneWire.reset();
		oneWire.select(addr);
		oneWire.write(0xBE);         // Read Scratchpad

		for (int i = 0; i < 12; i++) {           // we need 12 bytes
			data[i] = oneWire.read();
		}

		int LowByte = data[0];
		int	HighByte = data[1];
		int TReading = (HighByte << 8) + LowByte;

		int SignBit = TReading & 0x8000;  // test most sig bit
		if (SignBit) // negative
		{
			TReading = (TReading ^ 0xffff) + 1;
		}

		int Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25
		int Whole = Tc_100 / 100;  // separate off the whole and fractional portions
		int Fract = Tc_100 % 100;

		float celsius = Whole + Fract / 100.;

		currentTempValue = celsius;
	}
}

int AquaTemperatureHelper::GetTemperatureValue()
{
	//float Vin = 5.0;
	//float voltage = tempAnalog * Vin / 1023.0;
	//float r1 = voltage / (Vin - voltage);
	//unsigned int B = 4300; // ѕараметр конкретного типа термистора (из datasheet)

	//float temp = 1. / (1. / (B)*log(r1) + 1. / 298.) - 273;
	//int tempValue = (int)temp / 2.0;

	//return tempValue;
}

String AquaTemperatureHelper::GetTemperatureText()
{
	String retVal = String(currentTempValue);

	return retVal;
};

void AquaTemperatureHelper::IncreaseMinTemp()
{
	if (minAquaTemp < maxAquaTemp)
	{
		minAquaTemp++;
	}
};
void AquaTemperatureHelper::DecreaseMinTemp()
{
	minAquaTemp--;
};
void AquaTemperatureHelper::IncreaseMaxTemp()
{
	maxAquaTemp++;
};
void AquaTemperatureHelper::DecreaseMaxTemp()
{
	if (maxAquaTemp > minAquaTemp)
	{
		maxAquaTemp--;
	}
};





