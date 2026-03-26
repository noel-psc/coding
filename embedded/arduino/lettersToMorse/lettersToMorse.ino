#include <Arduino.h>

#define BUZZER 3
#define LED 13

void setup()
{
    // 设置通信频率为9600
    Serial.begin(9600);
    pinMode(LED, OUTPUT);
    pinMode(BUZZER, INPUT);
}

void loop()
{
    lToM(Serial.readString());
    // lToM("The new major release of the Arduino IDE is faster and even more powerful! In addition to a more modern editor and a more responsive interface it features autocompletion, code navigation, and even a live debugger.");
}

void lToM(String letters)
{
    String morse;

    // 循环遍历letters里的字母，每个字母转换成莫尔斯电码后用play()函数输出
    for (int i = 0; i < letters.length(); i++)
    {
        // 字母转换成莫尔斯电码
        switch (letters[i])
        {
        case 'A':
        case 'a':
            morse = ".-";
            break;
        case 'B':
        case 'b':
            morse = "-...";
            break;
        case 'C':
        case 'c':
            morse = "-.-.";
            break;
        case 'D':
        case 'd':
            morse = "-..";
            break;
        case 'E':
        case 'e':
            morse = ".";
            break;
        case 'F':
        case 'f':
            morse = "..-.";
            break;
        case 'G':
        case 'g':
            morse = "--.";
            break;
        case 'H':
        case 'h':
            morse = "....";
            break;
        case 'I':
        case 'i':
            morse = "..";
            break;
        case 'J':
        case 'j':
            morse = ".---";
            break;
        case 'K':
        case 'k':
            morse = "-.-";
            break;
        case 'L':
        case 'l':
            morse = ".-..";
            break;
        case 'M':
        case 'm':
            morse = "--";
            break;
        case 'N':
        case 'n':
            morse = "-.";
            break;
        case 'O':
        case 'o':
            morse = "---";
            break;-----------
        case 'P':
        case 'p':
            morse = ".--.";
            break;
        case 'Q':
        case 'q':
            morse = "--.-";
            break;
        case 'R':
        case 'r':
            morse = ".-.";
            break;
        case 'S':
        case 's':
            morse = "...";
            break;
        case 'T':
        case 't':
            morse = "-";
            break;
        case 'U':
        case 'u':
            morse = "..-";
            break;
        case 'V':
        case 'v':
            morse = "...-";
            break;
        case 'W':
        case 'w':
            morse = ".--";
            break;
        case 'X':
        case 'x':
            morse = "-..-";
            break;
        case 'Y':
        case 'y':
            morse = "-.--";
            break;
        case 'Z':
        case 'z':
            morse = "--..";
            break;
        default:
            morse = "/"; // 非字母均识别为间隔
        }
        // 通信打印正在输出的莫尔斯电码和字母
        Serial.print(letters[i]);
        Serial.println(morse);
        // 播放莫尔斯电码
        play(morse);
    }
}

void play(String morse)
{
    // 循环遍历morse的每个滴答并输出相应声音

    for (int i = 0; i < morse.length(); i++)
    {
        if (morse[i] == '.')
        {
            // delay(100);
            flicker(100, 100);
        }
        else if (morse[i] == '-')
        {
            // delay(50);
            flicker(250, 100);
        }
        else
        {
            delay(100);
        }
    }
    // 此处为每个字母或单词间的间隔，用于区分字母和字母
    delay(100);
}
void flicker(size_t on_delay, size_t off_delay) {
  digitalWrite(LED, HIGH);
  pinMode(BUZZER, OUTPUT);
  delay(on_delay);
  digitalWrite(LED, LOW);
  pinMode(BUZZER, INPUT);
  delay(off_delay);
}