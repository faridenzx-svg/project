#define PH_PIN A0
#define TDS_PIN A1

float averageVoltage = 0, averageVoltage_PH, tdsValue = 0, pH = 0, temperature = 25;
int SCOUNT = 30;
int pHBuffer[SCOUNT];
int pHBufferTemp[SCOUNT];
int pHIndex = 0, copyIndex = 0;

int TDSBuffer[SCOUNT];
int TDSBufferTemp[SCOUNT];
int TDSIndex = 0, copyIndexTDS = 0;


void setup() {
    pinMode(PH_PIN, INPUT);
    pinMode(TDS_PIN, INPUT);

    Serial.begin(9600);
}

void loop() {
    //-- Copy Value Zone --//
    static unsigned long analogSampleTimepoint = millis();
    if (millis() - analogSampleTimepoint > 40U) {
        analogSampleTimepoint = millis();

        // -- pH Value --//
        pHBuffer[pHIndex] = analogRead(PH_PIN);
        pHIndex++;

        if (pHIndex >= SCOUNT) {
            pHIndex = 0;
        }

        //-- TDS Value --//
        TDSBuffer[TDSIndex] = analogRead(TDS_PIN);
        TDSIndex++;

        if (TDSIndex >= SCOUNT) {
            TDSIndex = 0;
        }

    }
    //-- Display Zone --//
    static unsigned long printTimepoint = millis();
    if (millis() - printTimepoint > 800U) {
        printTimepoint = millis();  


        for (int copyIndex = 0; copyIndex < SCOUNT; copyIndex++) {
            pHBufferTemp[copyIndex] = pHBuffer[copyIndex];
        }

        for (int copyIndexTDS = 0; copyIndexTDS < SCOUNT; copyIndexTDS++) {
            TDSBufferTemp[copyIndexTDS] = TDSBuffer[copyIndexTDS];
        }

        averageVoltage = getMedianNum(TDSBufferTemp, SCOUNT) * 5.0 / 1023.0;
        float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
        float compensationVolatge = averageVoltage / compensationCoefficient;
        tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5;

        averageVoltage_PH = getMedianNum(pHBufferTemp, SCOUNT) * (5.0 / 1023.0);
        pH = 7 + ((2.5 - averageVoltage_PH) / 0.18);

        Serial.print("pH Value: ");
        Serial.println(pH);

        Serial.print("TDS Value: ");
        Serial.println(tdsValue);

    }

    // -- checking zone --//
    static unsigned long checkTimepoint = millis();
    if (millis() - checkTimepoint > 5000U) {
        checkTimepoint = millis();

        if (pH >= 6.5 && pH <= 8.5) {
            if (tdsValue >= 150 && tdsValue <= 400) {
                Serial.println("Water Quality: Good");
            } else {
                Serial.println("Water Quality: Poor");
            }
        } else {
            Serial.println("PH Level: Out of Range");
        }
    }
}

int getMedianNum(int bArray[], int iFilterLen)
{
    int bTab[iFilterLen]; 
    for (int i = 0; i < iFilterLen; i++)
        bTab[i] = bArray[i];

    int i, j, bTemp;
    for (j = 0; j < iFilterLen - 1; j++)
    {
        for (i = 0; i < iFilterLen - j - 1; i++)
        {
            if (bTab[i] > bTab[i + 1])
            {
                bTemp = bTab[i];
                bTab[i] = bTab[i + 1];
                bTab[i + 1] = bTemp;
            }
        }
    }

    if (iFilterLen % 2 == 1)
        return bTab[iFilterLen / 2];
    else
        return (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
}
