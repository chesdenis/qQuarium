#include "BeepHelper.h"

BeepHelper* BeepHelper::m_pInstance = NULL;
BeepHelper* BeepHelper::Instance()
{
	if (!m_pInstance)
		m_pInstance = new BeepHelper;

	return m_pInstance;
}

void BeepHelper::beep(int freq, unsigned long duration)
{
	unsigned long start;
	// Запоминаем момент начала выполнения
	start = millis();

	// В течение duration миллисекунд пищим
	while (millis() - start < duration) {
		// Частота писка определяется паузами между изменениями состояния пина
		digitalWrite(BeepPinNum, HIGH);
		delay(1000 / freq / 2);
		digitalWrite(BeepPinNum, LOW);
		delay(1000 / freq / 2);
	}

}
void BeepHelper::setup(uint8_t beepPinNum)
{
	BeepPinNum = beepPinNum;
	// Переводит пин в выход
	pinMode(BeepPinNum, OUTPUT);

}