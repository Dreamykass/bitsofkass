#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

const int ledPin = 21;

const char *ssid = "";
const char *password = "";

WebServer server(80);

void TaskLED(void *pvParameters)
{
    pinMode(ledPin, OUTPUT);

    for (;;)
    {
        digitalWrite(ledPin, LOW);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Odpowiednik delay() w FreeRTOS

        digitalWrite(ledPin, HIGH);
        vTaskDelay(500 / portTICK_PERIOD_MS);

        digitalWrite(ledPin, LOW);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        digitalWrite(ledPin, HIGH);
        vTaskDelay(100 / portTICK_PERIOD_MS);

        Serial.println("\nIP: " + WiFi.localIP().toString());
    }
}

void handleRoot()
{
    server.send(200, "text/html", "<h1>Serwer działa niezależnie!</h1><p>Dioda mruga na drugim rdzeniu.</p>");
}

void TaskHtml(void *pvParameters)
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        vTaskDelay(500 / portTICK_PERIOD_MS);
        Serial.print(".");
    }
    Serial.println("\nPołączono! IP: " + WiFi.localIP().toString());

    server.on("/", handleRoot);
    server.begin();

    for (;;)
    {
        server.handleClient();
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}

void setup()
{
    Serial.begin(115200);

    xTaskCreatePinnedToCore(
        TaskLED,   // Funkcja, która ma się wykonywać
        "TaskLED", // Nazwa zadania
        2048,      // Rozmiar stosu (pamięci)
        NULL,      // Parametr wejściowy
        1,         // Priorytet zadania
        NULL,      // Uchwyt zadania
        0          // Numer rdzenia (0 lub 1)
    );

    xTaskCreatePinnedToCore(
        TaskHtml,   // Funkcja, która ma się wykonywać
        "TaskHtml", // Nazwa zadania
        8192,       // Rozmiar stosu (pamięci)
        NULL,       // Parametr wejściowy
        1,          // Priorytet zadania
        NULL,       // Uchwyt zadania
        1           // Numer rdzenia (0 lub 1)
    );
}

void loop()
{
    // Pusta pętla - loop() ma najniższy priorytet i nie musi nic robić
    vTaskDelete(NULL); // Opcjonalnie: usuwa zadanie loop, zwalniając odrobinę RAM
}