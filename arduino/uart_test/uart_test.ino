// simplest_uart.ino
void setup() {
  // 初始化串口
  Serial.begin(115200);
  
  // 等待串口连接（如果是Leonardo等板子）
  while (!Serial) {
    delay(10);
  }
  
  // 设置LED引脚
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  // 发送启动信息
  Serial.println("UART Echo Ready");
  Serial.println("Send anything, I'll echo it back");
}

void loop() {
  // 检查是否有数据可读
  if (Serial.available() > 0) {
    // 读取一个字节
    char incoming = Serial.read();
    
    // 立即回显
    Serial.write(incoming);
    
    // LED闪烁指示
    digitalWrite(LED_BUILTIN, HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);
  }
}